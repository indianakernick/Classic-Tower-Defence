//
//  next wave.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 3/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "next wave.hpp"

#include "waves tag.hpp"
#include "spawner state component.hpp"

WaveStatus nextWave(ECS::Registry &reg) {
  SpawnerState &state = reg.get<SpawnerState>();
  if (state.state == SpawnerState::FINISHED) {
    ++state.currentWave;
    if (state.currentWave == reg.get<Waves>().size()) {
      state.currentWave = 0;
      return WaveStatus::FINISHED_LEVEL;
    }
    return WaveStatus::STARTING_NEXT;
  }
  return WaveStatus::RUNNING;
}
