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

struct Wave {
  struct Group {
    size_t quantity;
    UnitStatsBase stats;
    UnitSprite sprite;
  };
  
  std::vector<Group> groups;
};

#endif
