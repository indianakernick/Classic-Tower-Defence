//
//  common tower stats component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef common_tower_stats_component_hpp
#define common_tower_stats_component_hpp

#include <Simpleton/Data/json.hpp>

struct CommonTowerStats {
  float range;
  float damage;
  float rof;
  float armourPiercing;
};

inline void from_json(const json &j, CommonTowerStats &stats) {
  DATA_GET(stats, range);
  DATA_GET(stats, damage);
  DATA_GET(stats, rof);
  DATA_GET(stats, armourPiercing);
}

#endif
