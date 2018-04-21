//
//  init map info.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "init map info.hpp"

#include <Simpleton/Math/dir.hpp>

namespace {
  // Finds any path between points if one exists. Handles dead ends. Gets stuck
  // in some loops but not others. Does not find the shortest path.
  // Returns true if a path was found.

  bool findPath(MapInfo &info, const Map &map, const Math::Dir prevDir, const Map::Pos pos) {
    info.path.push_back(pos);
    
    for (const Math::Dir dir : Math::DIR_RANGE) {
      if (dir == Math::opposite(prevDir)) {
        continue;
      }
      using ToVec = Math::ToVec<Map::Pos::value_type, Math::Dir::RIGHT, Math::Dir::UP>;
      const Map::Pos newPos = pos + ToVec::conv(dir);
      
      if (map.outOfRange(newPos)) {
        continue;
      }
      if (newPos == info.exit) {
        info.path.push_back(info.exit);
        return true;
      }
      
      if (map[newPos] == TileType::PATH) {
        if (findPath(info, map, dir, newPos)) {
          return true;
        } else {
          info.path.pop_back();
        }
      }
    }
    
    return false;
  }
}

void initMapInfo(MapInfo &info, const Map &map) {
  for (size_t i = 0; i != map.scalarSize(); ++i) {
    if (map[i] == TileType::ENTRY) {
      info.entry = map.toPos(i);
    } else if (map[i] == TileType::EXIT) {
      info.exit = map.toPos(i);
    }
  }
  
  if (!findPath(info, map, Math::Dir::NONE, info.entry)) {
    throw std::runtime_error("Could not find path from entry to exit");
  }
}
