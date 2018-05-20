//
//  next wave.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 3/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "next wave.hpp"

#include "waves tag.hpp"
#include "spawner state tag.hpp"

WaveStatus nextWave(ECS::Registry &reg) {
  SpawnerState &state = reg.get<SpawnerState>();
  if (state.state == SpawnerState::FINISHED) {
    if (state.currentWave + 1 == reg.get<Waves>().size()) {
      return WaveStatus::FINISHED_LEVEL;
    } else {
      ++state.currentWave;
      state.state = SpawnerState::STARTING;
      return WaveStatus::STARTING_NEXT;
    }
  }
  return WaveStatus::RUNNING;
}
