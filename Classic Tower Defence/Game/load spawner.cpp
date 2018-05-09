//
//  load spawner.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load spawner.hpp"

#include "spawner state tag.hpp"
#include "spawner timing tag.hpp"

void loadSpawner(ECS::Registry &reg, const json &node) {
  SpawnerTiming &timing = reg.get<SpawnerTiming>();
  Data::get(timing.minTimeBetweenSpawns, node, "spawntime");
  timing.timeSinceLastSpawn = timing.minTimeBetweenSpawns + 1.0f;
  reg.get<SpawnerState>() = {};
}
