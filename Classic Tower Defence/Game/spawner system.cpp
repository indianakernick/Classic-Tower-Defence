//
//  spawner system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "spawner system.hpp"

#include "waves tag.hpp"
#include "spawner state tag.hpp"
#include "spawner timing tag.hpp"

void spawnerSystem(ECS::Registry &reg) {
  auto &timing = reg.get<SpawnerTiming>();
  auto &state = reg.get<SpawnerState>();
  
  if (state.state == SpawnerState::FINISHED) {
    return;
  }
  if (timing.timeSinceLastSpawn < timing.minTimeBetweenSpawns) {
    return;
  }
  const Wave &wave = reg.get<Waves>()[state.currentWave];
  if (state.state == SpawnerState::STARTING) {
    state.numUnitsLeft = wave.quantity;
    state.state = SpawnerState::SPAWNING;
  }
  timing.timeSinceLastSpawn = 0.0f;
  
  if (state.numUnitsLeft == 0) {
    state.state = SpawnerState::FINISHED;
  } else {
    wave.proto();
    --state.numUnitsLeft;
  }
}
