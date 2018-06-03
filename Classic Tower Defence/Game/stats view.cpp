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

void StatsView::render(const G2D::SheetWriter sw, TextRenderer &text) const {
  renderName(text);
  const float top = renderTable(text);
  
  // Change text color to white
  G2D::RenderParams currentParams = text.writer().sectionInfo();
  currentParams.color = glm::vec4{1.0f};
  text.writer().section(currentParams);
  
  renderLine(top, sw);
  
  if (buttons) {
    renderButtons(top, sw, text);
  }
}

void StatsView::renderName(TextRenderer &text) const {
  text.write({4.0f, 204.0f}, name);
}

float StatsView::renderTable(TextRenderer &text) const {
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
  const G2D::SheetWriter sw,
  TextRenderer &text
) const {
  // buy/upgrade button
  const Sprite::ID button = sw.sheet.getIDfromName(
    buttons->upgrade ? "upgrade" : "buy"
  );
  const uint32_t price = buttons->upgrade ? buttons->upgrade : buttons->buy;
  top += 5.0f;
  renderButton(top, sw, button);
  if (!buttons->afford) {
    renderDisable(sw);
  }
  text.write<Align::RIGHT>({120.0f, top + 4.0f}, price);
  
  // sell button
  if (buttons->sell) {
    top += 20.0f;
    renderButton(top, sw, sw.sheet.getIDfromName("sell"));
    text.write<Align::RIGHT>({120.0f, top + 4.0f}, buttons->sell);
  }
  
  top += 20.0f;
  renderLine(top, sw);
}

void StatsView::renderLine(const float top, const G2D::SheetWriter sw) {
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
  const float top,
  const G2D::SheetWriter sw,
  const Sprite::ID sprite
) {
  sw.writer.quad();
  sw.writer.depth(Depth::UI_ELEM);
  sw.writer.tilePos({4.0f, top}, {120.0f, 16.0f});
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite(sprite));
}
