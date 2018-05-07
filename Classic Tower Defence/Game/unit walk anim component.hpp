//
//  unit walk anim component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_walk_anim_component_hpp
#define unit_walk_anim_component_hpp

#include <cstdint>

struct UnitWalkAnim {
  uint32_t frame;
  uint32_t frames;
  uint32_t subframe;
  uint32_t subframes;
};

#endif
