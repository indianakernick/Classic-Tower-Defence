//
//  unit motion system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit motion system.hpp"

#include <glm/glm.hpp>
#include "map info tag.hpp"
#include "position component.hpp"
#include "unit dir component.hpp"
#include "unit path component.hpp"
#include "unit stats component.hpp"
#include "unit move distance component.hpp"

namespace {
  float orthoDist(const glm::vec2 a, const glm::vec2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
  }
}

void unitMotionSystem(ECS::Registry &reg, const float delta) {
  const MapInfo &map = reg.get<MapInfo>();
  auto view = reg.view<Position, UnitDir, UnitPath, UnitStats, UnitMoveDistance>();
  for (const ECS::EntityID entity : view) {
    float moveDist = view.get<UnitStats>(entity).moveSpeed * delta;
    view.get<UnitMoveDistance>(entity).dist += moveDist;
    Grid::Dir &dir = view.get<UnitDir>(entity).dir;
    glm::vec2 &pos = view.get<Position>(entity).pos;
    size_t &pathIndex = view.get<UnitPath>(entity).index;
    
    do {
      const glm::vec2 dirVec = Grid::ToVec<float>::conv(dir);
      const Grid::Pos nextTile = map.path[pathIndex + 1];
      const float distToNext = orthoDist(pos, nextTile);
      
      if (distToNext > moveDist) {
        pos = pos + dirVec * moveDist;
        break;
      }
      
      pos = nextTile;
      moveDist -= distToNext;
      ++pathIndex;
      if (pathIndex == map.path.size() - 1) {
        // we've arrived at the exit
        break;
      }
      dir = Grid::FromVec<Grid::Coord>::conv(map.path[pathIndex + 1] - nextTile);
    } while (moveDist > 0.01f);
  }
}
