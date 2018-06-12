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
#include "cursor systems.hpp"
#include "preview entity.hpp"
#include "game info view.hpp"
#include "game info model.hpp"
#include "basic components.hpp"
#include <Simpleton/SDL/mouse pos.hpp>
#include "tower range rendering system.hpp"

namespace {
  const Bounds TOWERS[4] {
    {8.0f, 49.0f, 57.0f, 98.0f},
    {70.0f, 49.0f, 119.0f, 98.0f},
    {8.0f, 123.0f, 57.0f, 172.0f},
    {70.0f, 123.0f, 119, 172.0f}
  };
  const Bounds NEXT_WAVE = {381.0f, 8.0f, 494.0f, 31.0f};
  const Bounds PREVIEW = {603.0f, 3.0f, 636.0f, 36.0f};
  
  template <typename Function>
  void createButton(
    ECS::Registry &reg,
    const Bounds rect,
    Function &&function
  ) {
    const ECS::EntityID entity = reg.create();
    reg.assign<Bounds>(entity, rect);
    reg.assign<SDL_SystemCursor>(entity, SDL_SYSTEM_CURSOR_HAND);
    reg.assign<ClickHandler>(entity, std::forward<Function>(function));
  }
}

void UIView::init(ECS::Registry &reg, G2D::Renderer &renderer) {
  camera.transform.setOrigin(Cam2D::Origin::TOP_LEFT);
  camera.transform.setInvertY(true);
  zoom.setSize({640.0f, 360.0f});
  camera.transform.setSize({640.0f, 360.0f});
  
  gameCam.transform.setOrigin(Cam2D::Origin::BOTTOM_LEFT);
  gameCam.setPos({-4.0f, 0.0f});
  gameZoom.setSize({20.0f, 11.25f});
  gameCam.transform.setSize({20.0f, 11.25f});
  
  uiSheetTex.load(renderer, "ui");
  textSheetTex.load(renderer, "5x8 ascii");
  radiusSheetTex.load(renderer, "radius");
  
  text.glyphSize({5.0f, 8.0f});
  text.advance({6.0f, 12.0f});
  text.depth(G2D::depth(Depth::UI_TEXT));
  
  cursors.load();
  
  for (size_t i = 0; i != 4; ++i) {
    createButton(uiReg, TOWERS[i], [i, this, &reg] {
      stats.model.selectTower(reg, i);
    });
  }
  createButton(uiReg, NEXT_WAVE, [this, &reg] {
    if (nextWave(reg) == WaveStatus::FINISHED_LEVEL) {
      stats.model.unselect();
      loadNextLevel(reg);
    }
  });
  createButton(uiReg, PREVIEW, [this, &reg] {
    stats.model.selectPreview(reg);
  });
  
  previewEntity = makePreviewEntity(reg);
  updatePreviewEntity(reg, previewEntity);
}

void UIView::updateCam(const Cam2D::Params params) {
  camera.update(params, zoom);
  gameCam.update(params, gameZoom);
}

Consumed UIView::input(ECS::Registry &reg, const SDL_Event &e) {
  Consumed consumed = Consumed::NO;
  
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    const glm::vec2 pos = SDL::mousePos(camera.transform.toMeters(), e.button);
    consumed = handleClick(uiReg, getObjAtPos(uiReg, pos));
  }
  
  if (!consumed && e.type == SDL_MOUSEBUTTONDOWN) {
    const glm::vec2 pos = SDL::mousePos(camera.transform.toMeters(), e.button);
    consumed = stats.click(pos, reg);
  }
  
  if (!consumed && e.type == SDL_MOUSEBUTTONDOWN) {
    const glm::vec2 pos = SDL::mousePos(gameCam.transform.toMeters(), e.button);
    stats.model.selectTower(reg, pos);
    consumed = Consumed::YES;
  }
  
  return consumed;
}

void UIView::updateAnim(ECS::Registry &, float) {}

void UIView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  const glm::vec2 pos = SDL::mousePos(camera.transform.toMeters());
  updateCursor(uiReg, cursors, getObjAtPos(uiReg, pos));
  stats.hover(pos, cursors);

  const glm::mat3 &cam = camera.transform.toPixels();
  G2D::Section &uiSec = writer.section(cam, uiSheetTex);
  text.section(writer.section(cam, textSheetTex, {0.0f, 0.0f, 0.0f, 1.0f}));
  text.scale(2.0f);
  
  if (stats.model.hasButtons(reg)) {
    const ECS::EntityID tower = stats.model.selected();
    if (tower != ECS::NULL_ENTITY) {
      towerRangeRenderingSystem(reg, writer.section(gameCam.transform.toPixels(), radiusSheetTex), tower);
    }
  }
  
  renderGameInfo(uiSec, text, getGameInfo(reg));
  
  updatePreviewEntity(reg, previewEntity);
  
  text.scale(1.0f);
  stats.setRenderState(reg);
  stats.render(uiSec, text, writer.section(cam, textSheetTex));
}
