//
//  tower stats component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_stats_component_hpp
#define tower_stats_component_hpp

#include <Simpleton/Data/json.hpp>

struct TowerStatsBase {
  float range;
  float damage;
  float rof;
};

struct TowerStats {
  const TowerStatsBase *proto;
};

inline void from_json(const json &j, TowerStatsBase &stats) {
  DATA_GET(stats, range);
  DATA_GET(stats, damage);
  DATA_GET(stats, rof);
}

#endif
