//
//  splash tower component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef splash_tower_component_hpp
#define splash_tower_component_hpp

#include <Simpleton/Data/json.hpp>

struct SplashTower {
  float range;
  float aoe;
};

inline void from_json(const json &j, SplashTower &comp) {
  DATA_GET(comp, range);
  DATA_GET(comp, aoe);
}

#endif
