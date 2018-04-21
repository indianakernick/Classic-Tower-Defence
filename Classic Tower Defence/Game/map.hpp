//
//  map.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef map_hpp
#define map_hpp

#include <cstdint>
#include <Simpleton/Utils/grid.hpp>

enum class TileType : uint8_t {
  ENTRY,
  EXIT,
  PATH,
  PLATFORM
};

struct Map {
  using Grid = Utils::Grid<TileType>;
  using Pos = Grid::Pos;
  
  Grid grid;
  std::vector<Pos> entries;
  std::vector<Pos> exits;
};

#endif
