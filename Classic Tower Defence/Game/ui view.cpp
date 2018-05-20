//
//  ui view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "ui view.hpp"

#include "depth.hpp"
#include "waves tag.hpp"
#include "mouse pos.hpp"
#include "base gold tag.hpp"
#include "level info tag.hpp"
#include "base health tag.hpp"
#include "spawner state tag.hpp"
#include "position component.hpp"
#include "unit dir component.hpp"
#include "unit sprite component.hpp"
#include "unit walk anim component.hpp"

namespace {
  using Rect = Math::RectPP<float>;
  
  const Rect TOWER_0 = {8.0f, 49.0f, 57.0f, 98.0f};
  const Rect TOWER_1 = {70.0f, 49.0f, 119.0f, 98.0f};
  const Rect TOWER_2 = {8.0f, 123.0f, 57.0f, 172.0f};
  const Rect TOWER_3 = {70.0f, 123.0f, 119, 172.0f};
  const Rect NEXT_WAVE = {381.0f, 8.0f, 494.0f, 31.0f};
  const Rect PREVIEW = {603.0f, 3.0f, 636.0f, 36.0f};
}

void UIView::init(G2D::Renderer &renderer) {
  camera.transform.setOrigin(Cam2D::Origin::TOP_LEFT);
  camera.transform.setInvertY(true);
  zoom.setSize({640.0f, 360.0f});
  
  uiSheetTex.load(renderer, "ui");
  textSheetTex.load(renderer, "5x8 ascii");
  radiusSheetTex.load(renderer, "radius");
  
  text.setGlyphSize({5.0f, 8.0f});
  text.setAdvance({6.0f, 9.0f});
  text.setScale(2.0f);
  
  cursor.init();
  cursor.mark(TOWER_0, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark(TOWER_1, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark(TOWER_2, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark(TOWER_3, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark(NEXT_WAVE, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark(PREVIEW, SDL_SYSTEM_CURSOR_HAND);
  
  base = uiSheetTex.sheet().getIDfromName("base");
  previewBack = uiSheetTex.sheet().getIDfromName("preview back");
}

void UIView::updateCam(const Cam2D::Params params) {
  camera.update(params, zoom);
}

InputConsumed UIView::input(ECS::Registry &reg, const SDL_Event &e) {
  if (e.type != SDL_MOUSEBUTTONDOWN) {
    return InputConsumed::NO;
  }
  
  const glm::vec2 pos = mousePos(camera.transform.toMeters(), e.button);
  if (!NEXT_WAVE.encloses(pos)) {
    return InputConsumed::NO;
  }
  
  SpawnerState &state = reg.get<SpawnerState>();
  Waves &waves = reg.get<Waves>();
  if (state.state == SpawnerState::FINISHED) {
    if (state.currentWave + 1 < waves.size()) {
      ++state.currentWave;
      state.state = SpawnerState::STARTING;
      reg.destroy(previewEntity);
      previewEntity = ECS::NULL_ENTITY;
    } else {
      // go to next level
    }
  }
  
  return InputConsumed::YES;
}

void UIView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  cursor.update(camera.transform.toMeters());

  writer.section({camera.transform.toPixels(), uiSheetTex.tex()});
  
  writer.quad();
  writer.depth(Depth::UI_BASE);
  writer.tilePos({0.0f, 0.0f}, {640.0f, 360.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(uiSheetTex.sheet().getSprite(base));
  
  writer.quad();
  writer.depth(Depth::MAP);
  writer.tilePos({604.0f, 4.0f}, {32.0f, 32.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(uiSheetTex.sheet().getSprite(previewBack));
  
  writer.section({camera.transform.toPixels(), textSheetTex.tex(), {0.0f, 0.0f, 0.0f, 1.0f}});
  
  text.setDepth(G2D::depth(Depth::UI_TEXT));
  
  rightNum(writer, {124.0f, 2.0f}, reg.get<BaseGold>().gold);
  rightNum(writer, {124.0f, 22.0f}, reg.get<BaseHealth>().health);
  
  const LevelInfo levelInfo = reg.get<LevelInfo>();
  rightNum(writer, {235.0f, 2.0f}, levelInfo.level);
  rightNum(writer, {235.0f, 22.0f}, levelInfo.map);
  
  const SpawnerState spawnerState = reg.get<SpawnerState>();
  
  const size_t wave = spawnerState.currentWave + 1;
  const Waves &waves = reg.get<Waves>();
  const size_t numWaves = waves.size();
  const std::string waveText = std::to_string(wave) + "/" + std::to_string(numWaves);
  rightText(writer, {372.0f, 12.0f}, waveText);
  
  size_t num;
  switch (spawnerState.state) {
    case SpawnerState::STARTING:
      num = waves[spawnerState.currentWave].quantity;
      break;
    case SpawnerState::SPAWNING:
      num = spawnerState.numUnitsLeft;
      break;
    case SpawnerState::FINISHED:
      if (spawnerState.currentWave + 1 < waves.size()) {
        num = waves[spawnerState.currentWave + 1].quantity;
      } else {
        num = 0;
      }
      break;
  }
  rightNum(writer, {599.0f, 12.0f}, num);
  
  if (previewEntity == ECS::NULL_ENTITY) {
    const size_t currentWave = spawnerState.state == SpawnerState::FINISHED
                             ? spawnerState.currentWave + 1
                             : spawnerState.currentWave;
    if (currentWave < waves.size()) {
      previewEntity = reg.create();
      reg.assign<Position>(previewEntity, glm::vec2(14.875f, 10.125f));
      reg.assign<UnitDir>(previewEntity, Grid::Dir::RIGHT);
      const auto &proto = waves[currentWave].proto;
      reg.assign<UnitSprite>(previewEntity, proto.get<UnitSprite>());
      reg.assign<UnitWalkAnim>(previewEntity, proto.get<UnitWalkAnim>());
    }
  }
}

void UIView::rightText(
  G2D::QuadWriter &writer,
  const glm::vec2 pos,
  const std::string_view string
) {
  text.rightAlign(pos, string);
  text.pushText<G2D::PlusXY::RIGHT_DOWN>(writer, textSheetTex.sheet(), string);
}

void UIView::rightNum(
  G2D::QuadWriter &writer,
  const glm::vec2 pos,
  const uint64_t num
) {
  rightText(writer, pos, std::to_string(num));
}
