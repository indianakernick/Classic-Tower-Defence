//
//  create spawner.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "create spawner.hpp"

#include "spawner timing component.hpp"
#include "spawner state component.hpp"

void createSpawner(ECS::Registry &reg, const float timeBetween) {
  const ECS::EntityID id = reg.create();
  
  auto &timing = reg.attach<SpawnerTiming>(id);
  timing.minTimeBetweenSpawns = timeBetween;
  timing.timeSinceLastSpawn = 0.0f;
  
  auto &state = reg.attach<SpawnerState>(id);
  state.numUnitsLeft = 0;
  state.state = SpawnerState::STARTING;
}
