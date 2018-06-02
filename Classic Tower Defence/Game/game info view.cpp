//
//  game info view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game info view.hpp"

#include "depth.hpp"

void renderGameInfo(
  const G2D::SheetWriter sw,
  TextRenderer &text,
  const GameInfo &info
) {
  sw.writer.quad();
  sw.writer.depth(Depth::UI_BASE);
  sw.writer.tilePos({0.0f, 0.0f}, {640.0f, 360.0f});
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite("base"));
  
  sw.writer.quad();
  sw.writer.depth(Depth::MAP);
  sw.writer.tilePos({604.0f, 4.0f}, {32.0f, 32.0f});
  sw.writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(sw.sheet.getSprite("preview back"));
  
  text.write<Align::RIGHT>({124.0f, 2.0f}, info.gold);
  text.write<Align::RIGHT>({124.0f, 22.0f}, info.base);
  text.write<Align::RIGHT>({235.0f, 2.0f}, info.level);
  text.write<Align::RIGHT>({235.0f, 22.0f}, info.map);
  text.write<Align::RIGHT>({372.0f, 12.0f}, info.wave);
  text.write<Align::RIGHT>({599.0f, 12.0f}, info.units);
}
