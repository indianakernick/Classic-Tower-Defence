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
#include <Simpleton/Data/json.hpp>

struct UnitWalkAnim {
  uint32_t frame;
  uint32_t frames;
  uint32_t subframe;
  uint32_t subframes;
};

inline void from_json(const json &j, UnitWalkAnim &anim) {
  anim.frame = 0;
  anim.subframe = 0;
  Data::get(anim.frames, j, "frames");
  anim.subframes = 1;
  Data::getOptional(anim.subframes, j, "subframes");
}

#endif
