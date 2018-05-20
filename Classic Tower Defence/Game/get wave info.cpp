//
//  get wave info.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 20/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "get wave info.hpp"

#include "waves tag.hpp"
#include "spawner state tag.hpp"

size_t getNumUnits(ECS::Registry &reg) {
  const SpawnerState spawnerState = reg.get<SpawnerState>();
  const Waves &waves = reg.get<Waves>();
  size_t num;
  switch (spawnerState.state) {
    case SpawnerState::STARTING:
      num = waves[spawnerState.currentWave].quantity;
      break;
    case SpawnerState::SPAWNING:
      num = spawnerState.numUnitsLeft;
      break;
    case SpawnerState::FINISHED:
      if (spawnerState.currentWave + 1 < waves.size()) {
        num = waves[spawnerState.currentWave + 1].quantity;
      } else {
        num = 0;
      }
      break;
  }
  return num;
}

std::string getWaveStr(ECS::Registry &reg) {
  const size_t wave = reg.get<SpawnerState>().currentWave + 1;
  const size_t numWaves = reg.get<Waves>().size();
  return std::to_string(wave) + "/" + std::to_string(numWaves);
}
