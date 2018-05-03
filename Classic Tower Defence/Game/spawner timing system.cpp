//
//  spawner timing system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "spawner timing system.hpp"

#include "spawner timing tag.hpp"

void spawnerTimingSystem(ECS::Registry &reg, const float delta) {
  reg.get<SpawnerTiming>().timeSinceLastSpawn += delta;
}
