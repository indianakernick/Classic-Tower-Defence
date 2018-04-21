//
//  spawner timing system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "spawner timing system.hpp"

#include "spawner timing component.hpp"

void spawnerTimingSystem(ECS::Registry &registry, const float delta) {
  auto view = registry.view<SpawnerTiming>();
  for (const ECS::EntityID entity : view) {
    view.get(entity).timeSinceLastSpawn += delta;
  }
}
