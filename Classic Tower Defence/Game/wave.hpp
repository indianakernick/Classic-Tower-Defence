//
//  wave.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef wave_hpp
#define wave_hpp

#include <vector>
#include "unit stats component.hpp"
#include "unit sprite component.hpp"

struct WaveGroup {
  size_t quantity;
  UnitStatsBase stats;
  UnitSprite sprite;
};

using Wave = std::vector<WaveGroup>;
using Waves = std::vector<Wave>;

inline void from_json(const json &j, WaveGroup &group) {
  DATA_GET(group, quantity);
  DATA_GET(group, stats);
  DATA_GET(group, sprite);
}

#endif
