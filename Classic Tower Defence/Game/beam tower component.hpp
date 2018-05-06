//
//  beam tower component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 5/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef beam_tower_component_hpp
#define beam_tower_component_hpp

#include <Simpleton/Data/json.hpp>

struct BeamTower {
  bool firing = false;
};

inline void from_json(const json &, BeamTower &) {}

#endif
