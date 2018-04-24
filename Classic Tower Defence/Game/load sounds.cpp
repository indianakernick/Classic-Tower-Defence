//
//  load sounds.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load sounds.hpp"

#include <Simpleton/SDL/paths.hpp>

Sounds loadSounds() {
  Sounds sounds;
  sounds.push_back(Mix_LoadWAV((SDL::getResDir() + "blaster.wav").c_str()));
  return sounds;
}

void freeSounds(Sounds &sounds) {
  for (Mix_Chunk *chunk : sounds) {
    Mix_FreeChunk(chunk);
  }
  sounds.clear();
}
