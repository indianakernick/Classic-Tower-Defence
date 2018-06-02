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
#include "get wave info.hpp"
#include "base gold tag.hpp"
#include "level info tag.hpp"
#include "preview entity.hpp"
#include "base health tag.hpp"
#include "tower gold component.hpp"
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
  
  cursor.init();
  for (const Rect &tower : TOWERS) {
    cursor.mark(tower, SDL_SYSTEM_CURSOR_HAND);
  }
  cursor.mark(NEXT_WAVE, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark(PREVIEW, SDL_SYSTEM_CURSOR_HAND);
  
  previewEntity = makePreviewEntity(reg);
}

void UIView::updateCam(const Cam2D::Params params) {
  camera.update(params, zoom);
}

InputConsumed UIView::input(ECS::Registry &reg, const SDL_Event &e) {
  if (e.type != SDL_MOUSEBUTTONDOWN) {
    return InputConsumed::NO;
  }
  
  const glm::vec2 pos = SDL::mousePos(camera.transform.toMeters(), e.button);
  
  for (size_t i = 0; i != 4; ++i) {
    if (TOWERS[i].encloses(pos)) {
      statsModel.selectTower(reg, i);
      break;
    }
  }
  
  if (NEXT_WAVE.encloses(pos)) {
    if (nextWave(reg) == WaveStatus::FINISHED_LEVEL) {
      statsModel.unselect();
      loadNextLevel(reg);
    }
  } else if (PREVIEW.encloses(pos)) {
    statsModel.selectPreview(reg);
  } else {
    return InputConsumed::NO;
  }
  
  return InputConsumed::YES;
}

void UIView::updateAnim(ECS::Registry &, float) {}

void UIView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  cursor.update(camera.transform.toMeters());

  writer.section({camera.transform.toPixels(), uiSheetTex.tex()});
  
  writer.quad();
  writer.depth(Depth::UI_BASE);
  writer.tilePos({0.0f, 0.0f}, {640.0f, 360.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(uiSheetTex.sheet().getSprite("base"));
  
  writer.quad();
  writer.depth(Depth::MAP);
  writer.tilePos({604.0f, 4.0f}, {32.0f, 32.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(uiSheetTex.sheet().getSprite("preview back"));
  
  textWriter.section({camera.transform.toPixels(), textSheetTex.tex(), {0.0f, 0.0f, 0.0f, 1.0f}});
  text.scale(2.0f);
  
  text.write<Align::RIGHT>({124.0f, 2.0f}, reg.get<BaseGold>().gold);
  text.write<Align::RIGHT>({124.0f, 22.0f}, reg.get<BaseHealth>().health);
  
  const LevelInfo levelInfo = reg.get<LevelInfo>();
  text.write<Align::RIGHT>({235.0f, 2.0f}, levelInfo.level + 1);
  text.write<Align::RIGHT>({235.0f, 22.0f}, levelInfo.map + 1);
  
  text.write<Align::RIGHT>({372.0f, 12.0f}, getWaveStr(reg));
  text.write<Align::RIGHT>({599.0f, 12.0f}, getNumUnits(reg));
  
  updatePreviewEntity(reg, previewEntity);
  
  text.scale(1.0f);
  if (statsModel.hasTable()) {
    statsView.renderName(text, statsModel.getName(reg));
    statsView.renderTable(text, statsModel.getTable(reg));
  }
  if (statsModel.hasButtons(reg)) {
    textWriter.section({camera.transform.toPixels(), textSheetTex.tex()});
    statsView.renderButtons({uiSheetTex.sheet(), writer}, text, statsModel.getButtons(reg));
  }
  
  writer.append(textWriter);
  textWriter.clear();
}
