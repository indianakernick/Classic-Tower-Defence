//
//  tower shoot component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_shoot_time_component_hpp
#define tower_shoot_time_component_hpp

#include <Simpleton/Data/json.hpp>

struct TowerShootTime {
  float elapsed = 0.0f;  // time elapsed since last shot
  float fireTime;        // value of elapsed at which damage is dealt
                         // inverse of the rate of fire
  float startTime;       // value of elapsed at which the animation should start
                         // fireTime - duration of shooting animation
  bool target = false;   // the tower has a target
};

inline void from_json(const json &j, TowerShootTime &comp) {
  DATA_GET(comp, fireTime);
  DATA_GET(comp, startTime);
}

#endif
