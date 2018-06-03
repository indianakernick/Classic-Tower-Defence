//
//  ui view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "ui view.hpp"

#include "depth.hpp"
#include "next wave.hpp"
#include "load level.hpp"
#include "cursor area.hpp"
#include "preview entity.hpp"
#include "game info view.hpp"
#include "game info model.hpp"
#include <Simpleton/SDL/mouse pos.hpp>

namespace {
  using Rect = Math::RectPP<float>;
  
  const Rect TOWERS[4] {
    {8.0f, 49.0f, 57.0f, 98.0f},
    {70.0f, 49.0f, 119.0f, 98.0f},
    {8.0f, 123.0f, 57.0f, 172.0f},
    {70.0f, 123.0f, 119, 172.0f}
  };
  const Rect NEXT_WAVE = {381.0f, 8.0f, 494.0f, 31.0f};
  const Rect PREVIEW = {603.0f, 3.0f, 636.0f, 36.0f};
  
  template <typename Function>
  void createButton(
    ECS::Registry &reg,
    const Rect rect,
    Function &&function
  ) {
    const ECS::EntityID entity = reg.create();
    reg.assign<Rect>(entity, rect);
    reg.assign<SDL_SystemCursor>(entity, SDL_SYSTEM_CURSOR_HAND);
    reg.assign<ClickHandler>(entity, std::forward<Function>(function));
  }
}

void UIView::init(ECS::Registry &reg, G2D::Renderer &renderer) {
  camera.transform.setOrigin(Cam2D::Origin::TOP_LEFT);
  camera.transform.setInvertY(true);
  zoom.setSize({640.0f, 360.0f});
  camera.transform.setSize({640.0f, 360.0f});
  
  uiSheetTex.load(renderer, "ui");
  textSheetTex.load(renderer, "5x8 ascii");
  radiusSheetTex.load(renderer, "radius");
  
  text.glyphSize({5.0f, 8.0f});
  text.advance({6.0f, 12.0f});
  text.writer(textWriter);
  text.sheet(textSheetTex.sheet());
  text.depth(G2D::depth(Depth::UI_TEXT));
  
  cursors.load();
  
  for (size_t i = 0; i != 4; ++i) {
    createButton(uiReg, TOWERS[i], [i, this, &reg] {
      statsModel.selectTower(reg, i);
    });
  }
  createButton(uiReg, NEXT_WAVE, [this, &reg] {
    if (nextWave(reg) == WaveStatus::FINISHED_LEVEL) {
      statsModel.unselect();
      loadNextLevel(reg);
    }
  });
  createButton(uiReg, PREVIEW, [this, &reg] {
    statsModel.selectPreview(reg);
  });
  
  previewEntity = makePreviewEntity(reg);
}

void UIView::updateCam(const Cam2D::Params params) {
  camera.update(params, zoom);
}

InputConsumed UIView::input(ECS::Registry &, const SDL_Event &e) {
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    const glm::vec2 pos = SDL::mousePos(camera.transform.toMeters(), e.button);
    return handleClick(uiReg, getObjAtPos(uiReg, pos));
  } else {
    return InputConsumed::NO;
  }
}

void UIView::updateAnim(ECS::Registry &, float) {}

void UIView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  updateCursor(
    uiReg,
    cursors,
    getObjAtPos(uiReg, SDL::mousePos(camera.transform.toMeters()))
  );

  writer.section({camera.transform.toPixels(), uiSheetTex.tex()});
  textWriter.section({camera.transform.toPixels(), textSheetTex.tex(), {0.0f, 0.0f, 0.0f, 1.0f}});
  text.scale(2.0f);
  
  renderGameInfo({uiSheetTex.sheet(), writer}, text, getGameInfo(reg));
  
  updatePreviewEntity(reg, previewEntity);
  
  text.scale(1.0f);
  if (statsModel.hasTable()) {
    statsView.renderName(text, statsModel.getName(reg));
    const float bottom = statsView.renderTable(text, statsModel.getTable(reg));
    if (statsModel.hasButtons(reg)) {
      textWriter.section({camera.transform.toPixels(), textSheetTex.tex()});
      statsView.renderButtons(
        bottom,
        {uiSheetTex.sheet(), writer},
        text,
        statsModel.getButtons(reg)
      );
    }
  }
  
  writer.append(textWriter);
  textWriter.clear();
}
