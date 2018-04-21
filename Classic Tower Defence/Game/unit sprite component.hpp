//
//  unit sprite component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_sprite_component_hpp
#define unit_sprite_component_hpp

#include <Simpleton/Unpack/types.hpp>

struct UnitSprite {
  Unpack::SpriteID sprite;
  Unpack::SpriteID frames;
};

#endif
