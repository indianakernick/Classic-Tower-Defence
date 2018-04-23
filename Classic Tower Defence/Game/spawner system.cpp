//
//  spawner system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "spawner system.hpp"

#include "map info.hpp"
#include "unit dir component.hpp"
#include "position component.hpp"
#include "unit path component.hpp"
#include "spawner state component.hpp"
#include "spawner timing component.hpp"
#include "unit walk anim component.hpp"
#include "unit exit distance component.hpp"

namespace {
  void spawn(ECS::Registry &reg, const Wave::Group &group) {
    UnitStats unitStats;
    *static_cast<UnitStatsBase *>(&unitStats) = group.stats;
    unitStats.proto = &group.stats;
    
    const MapInfo &map = reg.get<MapInfo>();
    const ECS::EntityID id = reg.create();
    reg.assign<UnitStats>(id, unitStats);
    reg.assign<UnitSprite>(id, group.sprite);
    reg.assign<UnitDir>(id, map.entryDir);
    reg.assign<UnitPath>(id, size_t(0));
    reg.assign<UnitExitDistance>(id, map.pathDist);
    reg.assign<Position>(id, map.entry);
    reg.assign<UnitWalkAnim>(id, uint32_t(0));
  }
}

void spawnerSystem(ECS::Registry &reg, const Wave &wave) {
  auto &timing = reg.get<SpawnerTiming>();
  auto &state = reg.get<SpawnerState>();
  
  if (state.state == SpawnerState::FINISHED) {
    return;
  }
  if (timing.timeSinceLastSpawn < timing.minTimeBetweenSpawns) {
    return;
  }
  if (state.state == SpawnerState::STARTING) {
    state.numUnitsLeft = wave.groups.front().quantity;
  }
  timing.timeSinceLastSpawn = 0.0f;
  
  spawn(reg, wave.groups[state.currentGroup]);
  --state.numUnitsLeft;
  if (state.numUnitsLeft == 0) {
    if (state.currentGroup == wave.groups.size() - 1) {
      state.state = SpawnerState::FINISHED;
    } else {
      ++state.currentGroup;
      state.numUnitsLeft = wave.groups[state.currentGroup].quantity;
      assert(state.numUnitsLeft != 0);
    }
  }
}
