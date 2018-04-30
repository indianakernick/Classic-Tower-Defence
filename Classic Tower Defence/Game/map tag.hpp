//
//  map tag.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef map_tag_hpp
#define map_tag_hpp

#include <cstdint>
#include <Simpleton/Utils/grid.hpp>

enum class TileType : uint8_t {
  ENTRY,
  EXIT,
  PATH,
  PLATFORM
};

using Map = Utils::Grid<TileType>;

#endif
