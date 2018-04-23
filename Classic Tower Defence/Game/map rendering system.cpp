//
//  map rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "map rendering system.hpp"

#include "map.hpp"
#include "map sprites.hpp"

void mapRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Unpack::Spritesheet &sheet
) {
  const Map &map = reg.get<Map>();
  const MapSprites &sprites = reg.get<MapSprites>();

  const size_t numTiles = map.scalarSize();
  for (size_t t = 0; t != numTiles; ++t) {
    Unpack::SpriteID id = sprites.sprite;
    id += static_cast<Unpack::SpriteID>(map[t]);
    const Unpack::Rect rect = sheet.getSprite(id);
    
    writer.quad();
    writer.depth(0.99f);
    writer.tilePos(map.toPos(t));
    writer.tileTex(rect.min, rect.max);
  }
}
