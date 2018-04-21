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
#include "unit exit distance component.hpp"

namespace {
  void spawn(ECS::Registry &registry, const UnitStatsBase &stats, const MapInfo &map) {
    UnitStats unitStats;
    *static_cast<UnitStatsBase *>(&unitStats) = stats;
    unitStats.proto = &stats;
    
    const UnitDir dir {map.entryDir};
    const UnitPath path {0};
    const UnitExitDistance dist {map.pathDist};
    const Position pos {map.entry};
    
    registry.create(unitStats, dir, path, dist, pos);
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
    
    spawn(registry, wave.groups[state.currentGroup].stats, map);
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
