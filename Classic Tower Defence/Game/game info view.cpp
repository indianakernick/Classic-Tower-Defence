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
  G2D::Section &sec,
  G2D::Text &text,
  const GameInfo &info
) {
  sec.quad();
  sec.depth(Depth::UI_BASE);
  sec.tilePos({0.0f, 0.0f}, {640.0f, 360.0f});
  sec.tileTex<G2D::PlusXY::RIGHT_DOWN>("base");
  
  sec.quad();
  sec.depth(Depth::MAP);
  sec.tilePos({604.0f, 4.0f}, {32.0f, 32.0f});
  sec.tileTex<G2D::PlusXY::RIGHT_DOWN>("preview back");
  
  text.writeRight({124.0f, 2.0f}, info.gold);
  text.writeRight({124.0f, 22.0f}, info.base);
  text.writeRight({235.0f, 2.0f}, info.level);
  text.writeRight({235.0f, 22.0f}, info.map);
  text.writeRight({372.0f, 12.0f}, info.wave);
  text.writeRight({599.0f, 12.0f}, info.units);
}
