//
//  create spawner.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "create spawner.hpp"

#include "spawner timing tag.hpp"
#include "spawner state tag.hpp"

void createSpawner(ECS::Registry &reg, const float timeBetween) {
  const ECS::EntityID id = reg.create();
  
  auto &timing = reg.assign<SpawnerTiming>(entt::tag_t{}, id);
  timing.minTimeBetweenSpawns = timeBetween;
  timing.timeSinceLastSpawn = 0.0f;
  
  auto &state = reg.assign<SpawnerState>(entt::tag_t{}, id);
  state.numUnitsLeft = 0;
  state.state = SpawnerState::STARTING;
}
