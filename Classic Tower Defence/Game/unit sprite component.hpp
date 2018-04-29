//
//  unit sprite component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_sprite_component_hpp
#define unit_sprite_component_hpp

#include <Simpleton/Data/json.hpp>
#include <Simpleton/Sprite/types.hpp>

struct UnitSprite {
  Sprite::ID sprite;
  Sprite::ID frames;
  Sprite::ID death;
  Sprite::ID deathFrames;
};

inline void from_json(const json &j, UnitSprite &comp) {
  DATA_GET(comp, sprite);
  DATA_GET(comp, frames);
  DATA_GET(comp, death);
  DATA_GET(comp, deathFrames);
}

#endif
