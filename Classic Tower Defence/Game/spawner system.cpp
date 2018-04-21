//
//  spawner system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "spawner system.hpp"

#include "unit dir component.hpp"
#include "position component.hpp"
#include "unit path component.hpp"
#include "spawner state component.hpp"
#include "spawner timing component.hpp"
#include "unit walk anim component.hpp"
#include "unit exit distance component.hpp"

namespace {
  void spawn(ECS::Registry &registry, const Wave::Group &group, const MapInfo &map) {
    UnitStats unitStats;
    *static_cast<UnitStatsBase *>(&unitStats) = group.stats;
    unitStats.proto = &group.stats;
    
    const ECS::EntityID id = registry.create();
    registry.assign<UnitStats>(id, unitStats);
    registry.assign<UnitSprite>(id, group.sprite);
    registry.assign<UnitDir>(id, map.entryDir);
    registry.assign<UnitPath>(id, size_t(0));
    registry.assign<UnitExitDistance>(id, map.pathDist);
    registry.assign<Position>(id, map.entry);
    registry.assign<UnitWalkAnim>(id, uint32_t(0));
  }
}

void spawnerSystem(ECS::Registry &registry, const Wave &wave, const MapInfo &map) {
  // Assumes there is one spawner
  
  auto view = registry.view<SpawnerState, SpawnerTiming>();
  for (const ECS::EntityID entity : view) {
    SpawnerTiming &timing = view.get<SpawnerTiming>(entity);
    SpawnerState &state = view.get<SpawnerState>(entity);
    
    if (timing.timeSinceLastSpawn < timing.minTimeBetweenSpawns || state.doneSpawning) {
      continue;
    }
    timing.timeSinceLastSpawn = 0.0f;
    
    spawn(registry, wave.groups[state.currentGroup], map);
    --state.numUnitsLeft;
    if (state.numUnitsLeft == 0) {
      if (state.currentGroup == wave.groups.size() - 1) {
        state.doneSpawning = true;
      } else {
        ++state.currentGroup;
        state.numUnitsLeft = wave.groups[state.currentGroup].quantity;
        assert(state.numUnitsLeft != 0);
      }
    }
  }
}
