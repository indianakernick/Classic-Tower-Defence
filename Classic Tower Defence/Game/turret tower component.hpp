//
//  turret tower component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef turret_tower_component_hpp
#define turret_tower_component_hpp

#include <Simpleton/Data/json.hpp>

struct TurretTower {
  float range;
};

inline void from_json(const json &j, TurretTower &comp) {
  DATA_GET(comp, range);
}

#endif
