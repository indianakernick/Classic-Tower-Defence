//
//  unit motion system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit motion system.hpp"

#include <glm/glm.hpp>
#include "position component.hpp"
#include "unit dir component.hpp"
#include "unit path component.hpp"
#include "unit stats component.hpp"
#include "unit exit distance component.hpp"

namespace {
  float orthoDist(const glm::vec2 a, const glm::vec2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
  }
  
  glm::vec2 roundInDir(const glm::vec2 vec, const Math::Dir dir) {
    constexpr Math::Dir PLUS_X = Math::Dir::RIGHT;
    constexpr Math::Dir PLUS_Y = Math::Dir::UP;
    
    switch (dir) {
      case PLUS_X:
        return {std::ceil(vec.x), vec.y};
      case PLUS_Y:
        return {vec.x, std::ceil(vec.y)};
      case Math::opposite(PLUS_X):
        return {std::floor(vec.x), vec.y};
      case Math::opposite(PLUS_Y):
        return {vec.x, std::floor(vec.y)};
      case Math::Dir::NONE:
        return vec;
      
      default:
        assert(false);
    }
  }
}

void unitMotionSystem(ECS::Registry &registry, const MapInfo &map, const float delta) {
  using FromVec =  Math::FromVec<float>;

  auto view = registry.view<Position, UnitDir, UnitPath, UnitStats, UnitExitDistance>();
  for (const ECS::EntityID entity : view) {
    float moveDist = view.get<UnitStats>(entity).moveSpeed * delta;
    view.get<UnitExitDistance>(entity).dist -= moveDist;
    Math::Dir &dir = view.get<UnitDir>(entity).dir;
    glm::vec2 &pos = view.get<Position>(entity).pos;
    size_t &pathIndex = view.get<UnitPath>(entity).index;
    
    do {
      const glm::vec2 dirVec = Math::ToVec<float>::conv(dir);
      const Map::Pos nextTile = map.path[pathIndex + 1];
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
      dir = Math::FromVec<unsigned>::conv(map.path[pathIndex + 1] - nextTile);
    } while (moveDist > 0.01f);
  }
}
