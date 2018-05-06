//
//  tower firing anim component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_firing_anim_component_hpp
#define tower_firing_anim_component_hpp

#include <cstdint>
#include <Simpleton/Data/json.hpp>

struct TowerFiringAnim {
  uint32_t frame;
  uint32_t frames;
  bool running;
};

inline void from_json(const json &j, TowerFiringAnim &anim) {
  DATA_GET(anim, frames);
  anim.frame = 0;
  anim.running = false;
}

#endif
