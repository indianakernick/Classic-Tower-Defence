//
//  map info component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef map_info_component_hpp
#define map_info_component_hpp

#include "map component.hpp"
#include <Simpleton/Math/dir.hpp>

struct MapInfo {
  using Pos = Map::Pos;

  Pos entry;
  Pos exit;
  Math::Dir entryDir;
  float pathDist;
  std::vector<Pos> path;
};

#endif
