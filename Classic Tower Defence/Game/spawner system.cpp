//
//  spawner system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "spawner system.hpp"

#include "waves component.hpp"
#include "map info component.hpp"
#include "unit dir component.hpp"
#include "position component.hpp"
#include "unit path component.hpp"
#include "spawner state component.hpp"
#include "spawner timing component.hpp"
#include "unit walk anim component.hpp"
#include "unit exit distance component.hpp"

namespace {
  void spawnUnit(ECS::Registry &reg, const Wave &wave) {
    UnitStats unitStats;
    *static_cast<UnitStatsBase *>(&unitStats) = wave.stats;
    unitStats.proto = &wave.stats;
    
    const MapInfo &map = reg.get<MapInfo>();
    const ECS::EntityID id = reg.create();
    reg.assign<UnitStats>(id, unitStats);
    reg.assign<UnitSprite>(id, wave.sprite);
    reg.assign<UnitDir>(id, map.entryDir);
    reg.assign<UnitPath>(id, size_t(0));
    reg.assign<UnitExitDistance>(id, map.pathDist);
    reg.assign<Position>(id, map.entry);
    reg.assign<UnitWalkAnim>(id, uint32_t(0));
    reg.assign<Sound>(id, wave.sound);
  }
}

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
    spawnUnit(reg, wave);
    --state.numUnitsLeft;
  }
}
