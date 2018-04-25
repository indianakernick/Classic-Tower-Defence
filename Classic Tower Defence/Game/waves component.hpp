//
//  waves component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef waves_component_hpp
#define waves_component_hpp

#include <vector>
#include "unit stats component.hpp"
#include "unit sprite component.hpp"

struct Wave {
  size_t quantity;
  UnitStatsBase stats;
  UnitSprite sprite;
};

using Waves = std::vector<Wave>;

inline void from_json(const json &j, Wave &wave) {
  DATA_GET(wave, quantity);
  DATA_GET(wave, stats);
  DATA_GET(wave, sprite);
}

#endif
