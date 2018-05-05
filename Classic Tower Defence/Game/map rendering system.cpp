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

  const size_t numTiles = map.scalarSize();
  for (size_t t = 0; t != numTiles; ++t) {
    Sprite::ID id = sprites.sprite;
    id += static_cast<Sprite::ID>(map[t]);
    const Sprite::Rect rect = sheet.getSprite(id);
    
    writer.quad();
    writer.depth(Depth::MAP);
    writer.tilePos(map.toPos(t));
    writer.tileTex(rect.min, rect.max);
  }
}
