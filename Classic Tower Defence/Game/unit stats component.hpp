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
  float armour;
  float healthRegen;
  float armourRegen;
  float dodge;
  float moveSpeed;
  uint32_t gold;
};

struct UnitStats : UnitStatsBase {
  const UnitStatsBase *proto;
};

inline void from_json(const json &j, UnitStatsBase &comp) {
  DATA_GET(comp, health);
  DATA_GET(comp, armour);
  DATA_GET(comp, healthRegen);
  DATA_GET(comp, armourRegen);
  DATA_GET(comp, dodge);
  DATA_GET(comp, moveSpeed);
  DATA_GET(comp, gold);
}

#endif
