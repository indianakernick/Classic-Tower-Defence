//
//  unit sprite component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_sprite_component_hpp
#define unit_sprite_component_hpp

#include <Simpleton/Sprite/json.hpp>

struct UnitSprite {
  Sprite::Anim walk;
  Sprite::Anim death;
};

inline void from_json(const json &j, UnitSprite &comp) {
  DATA_GET(comp, walk);
  DATA_GET(comp, death);
}

#endif
