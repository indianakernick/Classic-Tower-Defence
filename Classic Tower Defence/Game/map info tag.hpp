//
//  map info tag.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef map_info_tag_hpp
#define map_info_tag_hpp

#include "map tag.hpp"
#include <Simpleton/Grid/dir.hpp>

struct MapInfo {
  using Pos = Grid::Pos;

  Pos entry;
  Pos exit;
  Grid::Dir entryDir;
  float pathDist;
  std::vector<Pos> path;
};

#endif
