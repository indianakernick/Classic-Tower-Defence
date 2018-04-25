//
//  unit stats component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_stats_component_hpp
#define unit_stats_component_hpp

#include <Simpleton/Data/json.hpp>

struct UnitStatsBase {
  float health;
  float moveSpeed;
};

struct UnitStats : UnitStatsBase {
  const UnitStatsBase *proto;
};

inline void from_json(const json &j, UnitStatsBase &comp) {
  DATA_GET(comp, health);
  DATA_GET(comp, moveSpeed);
}

#endif
