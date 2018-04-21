//
//  unit death system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit death system.hpp"

#include "unit stats component.hpp"

void unitDeathSystem(ECS::Registry &registry) {
  auto view = registry.view<UnitStats>();
  for (const ECS::EntityID entity : view) {
    if (view.get(entity).health <= 0.0f) {
      registry.destroy(entity);
    }
  }
}
