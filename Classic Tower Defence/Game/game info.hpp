//
//  game info.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef game_info_hpp
#define game_info_hpp

#include <string>
#include <cstdint>

struct GameInfo {
  std::string wave;
  uint32_t gold;
  uint32_t base;
  uint32_t level;
  uint32_t map;
  uint32_t units;
};

#endif
