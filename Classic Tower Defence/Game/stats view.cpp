//
//  stats view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 31/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "stats view.hpp"

#include "depth.hpp"

void StatsView::renderName(TextRenderer &text, const std::string &name) {
  text.write({4.0f, 204.0f}, name);
}

float StatsView::renderTable(TextRenderer &text, const StatsTable &table) {
  const float left = 4.0f;
  const float right = 124.0f;
  const float vertAdv = 12.0f;
  float top = 221.0f;
  
  for (const StatsTableRow &row : table) {
    const glm::vec2 pos = text.write({left, top}, row.first);
    text.write(pos, ':');
    text.write<Align::RIGHT>({right, top}, row.second);
    top += vertAdv;
  }
  
  return top;
}

void StatsView::renderButtons(
  float top,
  G2D::SheetWriter sw,
  TextRenderer &text,
  const TowerButtons &buttons
) {
  renderLine(sw, top);

  // buy/upgrade button
  const Sprite::ID button = sw.sheet.getIDfromName(
    buttons.upgrade ? "upgrade" : "buy"
  );
  const uint32_t price = buttons.upgrade ? buttons.upgrade : buttons.buy;
  top += 5.0f;
  renderButton(sw, top, button);
  if (!buttons.afford) {
    renderDisable(sw);
  }
  text.write<Align::RIGHT>({120.0f, top + 4.0f}, price);
  
  // sell button
  if (buttons.sell) {
    top += 20.0f;
    renderButton(sw, top, sw.sheet.getIDfromName("sell"));
    text.write<Align::RIGHT>({120.0f, top + 4.0f}, buttons.sell);
  }
  
  top += 20.0f;
  renderLine(sw, top);
}

void StatsView::renderLine(const G2D::SheetWriter sw, const float top) {
  sw.writer.quad();
  sw.writer.depth(Depth::UI_ELEM);
  sw.writer.tilePos({0.0f, top}, {128.0f, 1.0f});
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite("line"));
}

void StatsView::renderDisable(const G2D::SheetWriter sw) {
  sw.writer.quad();
  sw.writer.depth(Depth::UI_ELEM_1);
  sw.writer.dupPos();
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite("disable"));
}

void StatsView::renderButton(
  const G2D::SheetWriter sw,
  const float top,
  const Sprite::ID sprite
) {
  sw.writer.quad();
  sw.writer.depth(Depth::UI_ELEM);
  sw.writer.tilePos({4.0f, top}, {120.0f, 16.0f});
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite(sprite));
}
