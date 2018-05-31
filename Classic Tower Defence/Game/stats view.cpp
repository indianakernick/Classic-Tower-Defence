//
//  stats view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 31/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "stats view.hpp"

#include "depth.hpp"

void StatsView::setSheetTex(const G2D::SheetTex &sheetTex) {
  uiSheetTex = &sheetTex;
}

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

void StatsView::renderButtons(TextRenderer &text, const TowerButtons &buttons) {
  assert(uiSheetTex);
  assert(tableBottom != NO_TABLE);
  
  G2D::QuadWriter &writer = text.writer();
  const Sprite::Sheet &sheet = uiSheetTex->sheet();
  float top = tableBottom;
  
  writer.quad();
  writer.depth(Depth::UI_ELEM);
  writer.tilePos({0.0f, top}, {128.0f, 1.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sheet.getSprite("line"));
  
  top += 5.0f;
  
  const Sprite::Rect button = buttons.upgrade
                            ? sheet.getSprite("upgrade")
                            : sheet.getSprite("buy");
  
  writer.quad();
  writer.depth(Depth::UI_ELEM);
  writer.tilePos({4.0f, top}, {128.0f, 16.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(button);
  
  if (!buttons.afford) {
    writer.quad();
    writer.depth(Depth::UI_ELEM_1);
    writer.dupPos();
    writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sheet.getSprite("disable"));
  }
  
  tableBottom = NO_TABLE;
}
