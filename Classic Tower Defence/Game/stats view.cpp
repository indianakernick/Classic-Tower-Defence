//
//  stats view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 31/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "stats view.hpp"

#include "depth.hpp"

void StatsView::renderTable(TextRenderer &text, const StatsTable &table) {
  assert(tableBottom == NO_TABLE);
  
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
  
  tableBottom = top;
}

void StatsView::renderButtons(
  G2D::SheetWriter sw,
  TextRenderer &text,
  const TowerButtons &buttons
) {
  assert(tableBottom != NO_TABLE);
  
  float top = tableBottom;
  
  sw.writer.quad();
  sw.writer.depth(Depth::UI_ELEM);
  sw.writer.tilePos({0.0f, top}, {128.0f, 1.0f});
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite("line"));

  Sprite::Rect button;
  uint32_t price;
  if (buttons.upgrade) {
    button = sw.sheet.getSprite("upgrade");
    price = buttons.upgrade;
  } else if (buttons.buy) {
    button = sw.sheet.getSprite("buy");
    price = buttons.buy;
  } else {
    assert(false);
  }

  top += 5.0f;
  sw.writer.quad();
  sw.writer.depth(Depth::UI_ELEM);
  sw.writer.tilePos({4.0f, top}, {128.0f, 16.0f});
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(button);
  
  if (!buttons.afford) {
    sw.writer.quad();
    sw.writer.depth(Depth::UI_ELEM_1);
    sw.writer.dupPos();
    sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite("disable"));
    text.write<Align::RIGHT>({120.0f, top + 4.0f}, price);
  }
  
  if (buttons.sell) {
    top += 20.0f;
    sw.writer.quad();
    sw.writer.depth(Depth::UI_ELEM);
    sw.writer.tilePos({4.0f, top}, {120.0f, 16.0f});
    sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite("sell"));
    text.write<Align::RIGHT>({120.0f, top + 4.0f}, buttons.sell);
  }
  
  top += 20.0f;
  sw.writer.quad();
  sw.writer.depth(Depth::UI_ELEM);
  sw.writer.tilePos({0.0f, top}, {128.0f, 1.0f});
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite("line"));
  
  tableBottom = NO_TABLE;
}
