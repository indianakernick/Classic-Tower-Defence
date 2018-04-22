//
//  map rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "map rendering system.hpp"

void mapRenderingSystem(
  const Map &map,
  G2D::QuadWriter &writer,
  const Unpack::Spritesheet &sheet,
  const MapSprites sprites
) {
  const size_t numTiles = map.scalarSize();
  for (size_t t = 0; t != numTiles; ++t) {
    Unpack::SpriteID id = sprites.sprite;
    id += static_cast<Unpack::SpriteID>(map[t]);
    const Unpack::Rect rect = sheet.getSprite(id);
    
    writer.quad();
    writer.tilePos(0.99f, map.toPos(t));
    writer.tileTex(rect.min, rect.max);
  }
}
