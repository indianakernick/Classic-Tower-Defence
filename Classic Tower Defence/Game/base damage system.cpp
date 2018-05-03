//
//  base damage system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "base damage system.hpp"

#include "map info tag.hpp"
#include "base health tag.hpp"
#include "unit path component.hpp"

void baseDamageSystem(ECS::Registry &reg) {
  const MapInfo &map = reg.get<MapInfo>();
  
  const size_t exitIndex = map.path.size() - 1;
  const auto view = reg.view<UnitPath>();
  uint32_t damage = 0;
  for (const ECS::EntityID entity : view) {
    if (view.get(entity).index == exitIndex) {
      reg.destroy(entity);
      ++damage;
    }
  }
  
  reg.get<BaseHealth>().health -= damage;
}
