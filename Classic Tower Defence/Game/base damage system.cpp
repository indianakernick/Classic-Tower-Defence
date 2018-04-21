//
//  base damage system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "base damage system.hpp"

#include "unit path component.hpp"
#include "base health component.hpp"

void baseDamageSystem(ECS::Registry &registry, const MapInfo &map) {
  // assumes there is one base
  
  const size_t exitIndex = map.path.size() - 1;
  const auto view = registry.view<UnitPath>();
  uint32_t damage = 0;
  for (const ECS::EntityID entity : view) {
    if (view.get(entity).index == exitIndex) {
      registry.destroy(entity);
      ++damage;
    }
  }
  
  auto baseView = registry.view<BaseHealth>();
  for (const ECS::EntityID entity : baseView) {
    baseView.get(entity).health -= damage;
  }
}
