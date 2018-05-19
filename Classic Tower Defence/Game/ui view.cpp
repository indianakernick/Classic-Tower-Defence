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
#include "base gold tag.hpp"
#include "level info tag.hpp"
#include "base health tag.hpp"
#include "spawner state tag.hpp"

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
  cursor.mark({8.0f, 49.0f, 57.0f, 98.0f}, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark({70.0f, 49.0f, 119.0f, 98.0f}, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark({8.0f, 123.0f, 57.0f, 172.0f}, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark({70.0f, 123.0f, 119, 172.0f}, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark({381.0f, 8.0f, 494.0f, 31.0f}, SDL_SYSTEM_CURSOR_HAND);
  cursor.mark({603.0f, 3.0f, 636.0f, 36.0f}, SDL_SYSTEM_CURSOR_HAND);
}

void UIView::updateCam(const Cam2D::Params params) {
  camera.update(params, zoom);
}

void UIView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  cursor.update(camera.transform.toMeters());

  writer.section({camera.transform.toPixels(), uiSheetTex.tex()});
  writer.quad();
  writer.depth(Depth::UI_BASE);
  writer.tilePos({0.0f, 0.0f}, {640.0f, 360.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(uiSheetTex.sheet().getSprite(0));
  
  writer.section({camera.transform.toPixels(), textSheetTex.tex(), {0.0f, 0.0f, 0.0f, 1.0f}});
  
  text.setDepth(G2D::depth(Depth::UI_TEXT));
  
  rightNum(writer, {124.0f, 2.0f}, reg.get<BaseGold>().gold);
  rightNum(writer, {124.0f, 22.0f}, reg.get<BaseHealth>().health);
  
  const LevelInfo levelInfo = reg.get<LevelInfo>();
  rightNum(writer, {235.0f, 2.0f}, levelInfo.level);
  rightNum(writer, {235.0f, 22.0f}, levelInfo.map);
  
  const SpawnerState spawnerState = reg.get<SpawnerState>();
  
  const size_t wave = spawnerState.currentWave + 1;
  const size_t waves = reg.get<Waves>().size();
  const std::string waveText = std::to_string(wave) + "/" + std::to_string(waves);
  rightText(writer, {372.0f, 12.0f}, waveText);
  
  rightNum(writer, {599.0f, 12.0f}, spawnerState.numUnitsLeft);
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
