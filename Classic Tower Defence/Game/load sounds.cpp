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
  sounds.push_back(SDL::loadWAV((SDL::getResDir() + "cannon.wav").c_str()));
  return sounds;
}
