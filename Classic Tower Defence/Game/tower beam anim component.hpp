//
//  tower beam anim component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 10/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_beam_anim_component_hpp
#define tower_beam_anim_component_hpp

#include <Simpleton/Data/json.hpp>

struct TowerBeamAnim {
  uint32_t frame = 0;
  uint32_t frames = 1;
};

inline void from_json(const json &j, TowerBeamAnim &comp) {
  Data::getOptional(comp.frames, j, "frames");
}

#endif
