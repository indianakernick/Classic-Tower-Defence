//
//  map rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "map rendering system.hpp"

#include "depth.hpp"
#include "map tag.hpp"
#include "map sprites tag.hpp"
#include <Simpleton/Utils/profiler.hpp>

void mapRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet
) {
  PROFILE(mapRenderingSystem);
  const Map &map = reg.get<Map>();
  const MapSprites &sprites = reg.get<MapSprites>();

  for (size_t t = 0; t != map.area(); ++t) {
    const Sprite::ID id = sprites.sprite + static_cast<Sprite::ID>(map[t]);
    
    writer.quad();
    writer.depth(Depth::MAP);
    writer.tilePos(map.toPos(t));
    writer.tileTex(sheet.getSprite(id));
  }
}
