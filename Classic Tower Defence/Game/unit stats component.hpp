//
//  unit stats component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_stats_component_hpp
#define unit_stats_component_hpp

#include <cstdint>

struct UnitStatsBase {
  uint32_t health;
  uint32_t moveSpeed;
};

struct UnitStats : UnitStatsBase {
  const UnitStatsBase *proto;
};

#endif
