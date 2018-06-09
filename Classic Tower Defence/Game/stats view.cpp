//
//  stats view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 31/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "stats view.hpp"

#include "depth.hpp"

void StatsView::setName(const std::string &newName) {
  name = newName;
}

void StatsView::setTable(const StatsTable &newTable) {
  table = newTable;
}

void StatsView::setButtons(const TowerButtons &newButtons) {
  buttons = newButtons;
}

void StatsView::setNoButtons() {
  buttons = std::experimental::nullopt;
}

void StatsView::clearState() {
  name = std::experimental::nullopt;
  table = std::experimental::nullopt;
  buttons = std::experimental::nullopt;
}

Bounds StatsView::sellBounds() const {
  if (!buttons || buttons->sell == 0) {
    return {};
  }
  
  float top = 221.0f;
  top += 12.0f * table->size();
  top += 5.0f;
  top += 20.0f;
  return {4.0f, top, 124.0f, top + 16.0f};
}

Bounds StatsView::upgradeBounds() const {
  if (!buttons || buttons->upgrade == 0 || !buttons->afford) {
    return {};
  }
  
  float top = 221.0f;
  top += 12.0f * table->size();
  top += 5.0f;
  return {4.0f, top, 124.0f, top + 16.0f};
}

void StatsView::render(G2D::Section &sec, TextRenderer &text, G2D::Section &white) const {
  renderName(text);
  const float top = renderTable(text);
  
  text.section(white);
  
  if (table) {
    renderLine(top, sec);
    renderLine(216.0f, sec);
  }
  renderButtons(top, sec, text);
}

void StatsView::renderName(TextRenderer &text) const {
  if (name) {
    text.write({4.0f, 204.0f}, *name);
  }
}

float StatsView::renderTable(TextRenderer &text) const {
  const float left = 4.0f;
  const float right = 124.0f;
  const float vertAdv = 12.0f;
  float top = 221.0f;
  
  if (!table) {
    return top;
  }
  
  for (const StatsTableRow &row : *table) {
    const glm::vec2 pos = text.write({left, top}, row.first);
    text.write(pos, ':');
    text.write<Align::RIGHT>({right, top}, row.second);
    top += vertAdv;
  }
  
  return top;
}

void StatsView::renderButtons(
  float top,
  G2D::Section &sec,
  TextRenderer &text
) const {
  if (!buttons) {
    return;
  }

  // buy/upgrade button
  const Sprite::ID button = sec.sheet().getIDfromName(
    buttons->buy ? "buy" : "upgrade"
  );
  const uint32_t price = buttons->buy ? buttons->buy : buttons->upgrade;
  top += 5.0f;
  renderButton(top, sec, button);
  if (!buttons->afford) {
    renderDisable(sec);
  }
  text.write<Align::RIGHT>({120.0f, top + 4.0f}, price);
  
  // sell button
  if (buttons->sell) {
    top += 20.0f;
    renderButton(top, sec, sec.sheet().getIDfromName("sell"));
    text.write<Align::RIGHT>({120.0f, top + 4.0f}, buttons->sell);
  }
  
  top += 20.0f;
  renderLine(top, sec);
}

void StatsView::renderLine(const float top, G2D::Section &sec) {
  sec.quad();
  sec.depth(Depth::UI_ELEM);
  sec.tilePos({0.0f, top}, {128.0f, 1.0f});
  sec.tileTex<G2D::PlusXY::RIGHT_DOWN>("line");
}

void StatsView::renderDisable(G2D::Section &sec) {
  sec.quad();
  sec.depth(Depth::UI_ELEM_1);
  sec.dupPos();
  sec.tileTex<G2D::PlusXY::RIGHT_DOWN>("disable");
}

void StatsView::renderButton(
  const float top,
  G2D::Section &sec,
  const Sprite::ID sprite
) {
  sec.quad();
  sec.depth(Depth::UI_ELEM);
  sec.tilePos({4.0f, top}, {120.0f, 16.0f});
  sec.tileTex<G2D::PlusXY::RIGHT_DOWN>(sprite);
}
