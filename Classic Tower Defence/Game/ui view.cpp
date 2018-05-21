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
#include "create tower.hpp"
#include "get wave info.hpp"
#include "base gold tag.hpp"
#include "name component.hpp"
#include "level info tag.hpp"
#include "preview entity.hpp"
#include "base health tag.hpp"
#include "unit stats component.hpp"
#include "splash tower component.hpp"
#include "common tower stats component.hpp"

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
  text.setAdvance({6.0f, 12.0f});
  
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
  
  const glm::vec2 pos = mousePos(camera.transform.toMeters(), e.button);
  
  if (TOWER_0.encloses(pos)) {
    statsProto = getTowerProto(reg, 0);
  } else if (TOWER_1.encloses(pos)) {
    statsProto = getTowerProto(reg, 3);
  } else if (TOWER_2.encloses(pos)) {
    statsProto = getTowerProto(reg, 6);
  } else if (TOWER_3.encloses(pos)) {
    statsProto = getTowerProto(reg, 9);
  } else if (NEXT_WAVE.encloses(pos)) {
    if (nextWave(reg) == WaveStatus::FINISHED_LEVEL) {
      // preview proto either points to a prototype in the Waves tag which
      // will be replace by loading the level or
      // points to the towers tag which is only loaded once.
      statsProto = nullptr;
      loadNextLevel(reg);
    }
  } else if (PREVIEW.encloses(pos)) {
    statsProto = getPreviewProto(reg);
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
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(uiSheetTex.sheet().getSprite(base));
  
  writer.quad();
  writer.depth(Depth::MAP);
  writer.tilePos({604.0f, 4.0f}, {32.0f, 32.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(uiSheetTex.sheet().getSprite(previewBack));
  
  writer.section({camera.transform.toPixels(), textSheetTex.tex(), {0.0f, 0.0f, 0.0f, 1.0f}});
  
  text.setDepth(G2D::depth(Depth::UI_TEXT));
  text.setScale(2.0f);
  
  rightNum(writer, {124.0f, 2.0f}, reg.get<BaseGold>().gold);
  rightNum(writer, {124.0f, 22.0f}, reg.get<BaseHealth>().health);
  
  const LevelInfo levelInfo = reg.get<LevelInfo>();
  rightNum(writer, {235.0f, 2.0f}, levelInfo.level + 1);
  rightNum(writer, {235.0f, 22.0f}, levelInfo.map + 1);
  
  rightText(writer, {372.0f, 12.0f}, getWaveStr(reg));
  rightNum(writer, {599.0f, 12.0f}, getNumUnits(reg));
  
  updatePreviewEntity(reg, previewEntity);
  
  renderProto(writer);
}

void UIView::leftText(
  G2D::QuadWriter &writer,
  const glm::vec2 pos,
  const std::string_view string
) {
  text.setCursor(pos);
  text.pushText<G2D::PlusXY::RIGHT_DOWN>(writer, textSheetTex.sheet(), string);
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

void UIView::renderProto(G2D::QuadWriter &writer) {
  if (statsProto == nullptr) {
    return;
  }
  
  text.setScale(1.0f);
  
  leftText(writer, {4.0f, 204.0f}, statsProto->get<Name>().name);
  
  if (statsProto->has<UnitStats>()) {
    renderUnitStats(writer);
  } else if (statsProto->has<CommonTowerStats>()) {
    renderTowerStats(writer);
  }
}

namespace {
  std::string_view niceFloat(const float f) {
    constexpr size_t size = 64;
    static char chars[size];
    const int ret = std::snprintf(chars, size, "%g", f);
    assert(0 < ret && ret < static_cast<int>(size));
    return {chars, static_cast<size_t>(ret)};
  }
}

void UIView::renderUnitStats(G2D::QuadWriter &writer) {
  assert(statsProto);
  const UnitStats stats = statsProto->get<UnitStats>();
  
  float top = 221.0f;
  const float left = 4.0f;
  const float right = 124.0f;
  const float vertAdv = 12.0f;
  
  #define FIELD(UPPER, LOWER)                                                   \
    leftText(writer, {left, top}, UPPER ":");                                   \
    rightText(writer, {right, top}, niceFloat(stats.LOWER));                    \
    top += vertAdv
  
  FIELD("HEALTH", health);
  FIELD("ARMOUR", armour);
  FIELD("HEALTH REGEN", healthRegen);
  FIELD("ARMOUR REGEN", armourRegen);
  FIELD("DODGE", dodge);
  FIELD("MOVE SPEED", moveSpeed);
  FIELD("GOLD", gold);
}

void UIView::renderTowerStats(G2D::QuadWriter &writer) {
  assert(statsProto);
  const CommonTowerStats stats = statsProto->get<CommonTowerStats>();
  
  float top = 221.0f;
  const float left = 4.0f;
  const float right = 124.0f;
  const float vertAdv = 12.0f;
  
  FIELD("DAMAGE", damage);
  FIELD("DAMAGE RATE", damage * stats.rof);
  FIELD("ARMOUR PIERCING", armourPiercing);
  FIELD("FIRE RATE", rof);
  FIELD("RANGE", range);
  
  if (statsProto->has<SplashTower>()) {
    const SplashTower stats = statsProto->get<SplashTower>();
    FIELD("AREA OF EFFECT", aoe);
  }
  
  #undef FIELD
}
