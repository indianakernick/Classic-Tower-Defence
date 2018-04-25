//
//  load sounds.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load sounds.hpp"

#include <fstream>
#include <Simpleton/Data/json.hpp>
#include <Simpleton/SDL/paths.hpp>

Sounds loadSounds() {
  std::ifstream file(SDL::getResDir() + "sounds.json");
  json node;
  file >> node;
  Sounds sounds;
  
  for (const json &j : node.at("files")) {
    sounds.push_back(SDL::loadWAV(
      (SDL::getResDir() + j.get<std::string>()).c_str()
    ));
  }
  
  return sounds;
}
