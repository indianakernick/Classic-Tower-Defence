//
//  tower sprites component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_sprites_component_hpp
#define tower_sprites_component_hpp

#include <Simpleton/Sprite/json.hpp>

struct TowerSprites {
  Sprite::ToggleAnim gun;
  Sprite::ID base;
  Sprite::ID projectile;
};

inline void from_json(const json &j, TowerSprites &sprites) {
  DATA_GET(sprites, gun);
  DATA_GET(sprites, base);
  DATA_GET(sprites, projectile);
}

#endif
