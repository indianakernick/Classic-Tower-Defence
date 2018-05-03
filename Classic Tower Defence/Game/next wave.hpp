//
//  next wave.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 3/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef next_wave_hpp
#define next_wave_hpp

#include <Simpleton/ECS/registry.hpp>

enum class WaveStatus {
  RUNNING,
  STARTING_NEXT,
  FINISHED_LEVEL
};

WaveStatus nextWave(ECS::Registry &);

#endif
