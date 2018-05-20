//
//  ui view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "ui view.hpp"

#include "depth.hpp"
#include "mouse pos.hpp"
#include "next wave.hpp"
#include "load level.hpp"
#include "get wave info.hpp"
#include "base gold tag.hpp"
#include "level info tag.hpp"
#include "preview entity.hpp"
#include "base health tag.hpp"

namespace {
  using Rect = Math::RectPP<float>;
  
  const Rect TOWER_0 = {8.0f, 49.0f, 57.0f, 98.0f};
  const Rect TOWER_1 = {70.0f, 49.0f, 119.0f, 98.0f};
  const Rect TOWER_2 = {8.0f, 123.0f, 57.0f, 172.0f};
  const Rect TOWER_3 = {70.0f, 123.0f, 119, 172.0f};
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
  
  previewEntity = makePreviewEntity(reg);
}

void UIView::updateCam(const Cam2D::Params params) {
  camera.update(params, zoom);
}

InputConsumed UIView::input(ECS::Registry &reg, const SDL_Event &e) {
  if (e.type != SDL_MOUSEBUTTONDOWN) {
    return InputConsumed::NO;
  }
  
  if (!NEXT_WAVE.encloses(mousePos(camera.transform.toMeters(), e.button))) {
    return InputConsumed::NO;
  }
  
  if (nextWave(reg) == WaveStatus::FINISHED_LEVEL) {
    loadNextLevel(reg);
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
  rightNum(writer, {235.0f, 2.0f}, levelInfo.level + 1);
  rightNum(writer, {235.0f, 22.0f}, levelInfo.map + 1);
  
  rightText(writer, {372.0f, 12.0f}, getWaveStr(reg));
  rightNum(writer, {599.0f, 12.0f}, getNumUnits(reg));
  
  updatePreviewEntity(reg, previewEntity);
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
