//
//  tower sprites component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_sprites_component_hpp
#define tower_sprites_component_hpp

#include <Simpleton/Data/json.hpp>
#include <Simpleton/Unpack/types.hpp>

struct TowerSpritesBase {
  Unpack::SpriteID gun;
  Unpack::SpriteID firingFrames;
  Unpack::SpriteID base;
  Unpack::SpriteID projectile;
};

struct TowerSprites {
  const TowerSpritesBase *proto;
};

inline void from_json(const json &j, TowerSpritesBase &sprites) {
  DATA_GET(sprites, gun);
  DATA_GET(sprites, firingFrames);
  DATA_GET(sprites, base);
  DATA_GET(sprites, projectile);
}

#endif
