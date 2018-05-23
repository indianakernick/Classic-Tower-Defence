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
  
  text.glyphSize({5.0f, 8.0f});
  text.advance({6.0f, 12.0f});
  
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
  
  text.writer(writer);
  text.sheet(textSheetTex.sheet());
  text.depth(G2D::depth(Depth::UI_TEXT));
  
  text.scale(2.0f);
  
  text.write<Align::RIGHT>({124.0f, 2.0f}, reg.get<BaseGold>().gold);
  text.write<Align::RIGHT>({124.0f, 22.0f}, reg.get<BaseHealth>().health);
  
  const LevelInfo levelInfo = reg.get<LevelInfo>();
  text.write<Align::RIGHT>({235.0f, 2.0f}, levelInfo.level + 1);
  text.write<Align::RIGHT>({235.0f, 22.0f}, levelInfo.map + 1);
  
  text.write<Align::RIGHT>({372.0f, 12.0f}, getWaveStr(reg));
  text.write<Align::RIGHT>({599.0f, 12.0f}, getNumUnits(reg));
  
  updatePreviewEntity(reg, previewEntity);
  
  renderProto();
}

void UIView::renderProto() {
  if (statsProto == nullptr) {
    return;
  }
  
  text.scale(1.0f);
  
  text.write({4.0f, 204.0f}, statsProto->get<Name>().name);
  
  if (statsProto->has<UnitStats>()) {
    renderUnitStats();
  } else if (statsProto->has<CommonTowerStats>()) {
    renderTowerStats();
  }
}

class TableText {
public:
  TableText(const float top, const float left, const float right, const float vertAdv)
    : top(top), left(left), right(right), vertAdv(vertAdv) {}
  
  template <typename T>
  void field(TextRenderer &text, const std::string_view key, const T &val) {
    const glm::vec2 pos = text.write({left, top}, key);
    text.write(pos, ":");
    text.write<Align::RIGHT>({right, top}, val);
    top += vertAdv;
  }
  
private:
  float top, left, right, vertAdv;
};

void UIView::renderUnitStats() {
  assert(statsProto);
  const UnitStats stats = statsProto->get<UnitStats>();
  
  TableText table(221.0f, 4.0f, 124.0f, 12.0f);
  
  table.field(text, "HEALTH", stats.health);
  table.field(text, "ARMOUR", stats.armour);
  table.field(text, "HEALTH REGEN", stats.healthRegen);
  table.field(text, "ARMOUR REGEN", stats.armourRegen);
  table.field(text, "DODGE", stats.dodge);
  table.field(text, "MOVE SPEED", stats.moveSpeed);
  table.field(text, "GOLD", stats.gold);
}

void UIView::renderTowerStats() {
  assert(statsProto);
  const CommonTowerStats stats = statsProto->get<CommonTowerStats>();
  
  TableText table(221.0f, 4.0f, 124.0f, 12.0f);
  
  table.field(text, "DAMAGE", stats.damage);
  table.field(text, "DAMAGE RATE", stats.damage * stats.rof);
  table.field(text, "ARMOUR PIERCING", stats.armourPiercing);
  table.field(text, "FIRE RATE", stats.rof);
  table.field(text, "RANGE", stats.range);
  
  if (statsProto->has<SplashTower>()) {
    const SplashTower splash = statsProto->get<SplashTower>();
    table.field(text, "AREA OF EFFECT", splash.aoe);
  }
  
  #undef FIELD
}
