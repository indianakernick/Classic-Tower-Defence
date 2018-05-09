//
//  load level.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load level.hpp"

#include <fstream>
#include "load map.hpp"
#include "load base.hpp"
#include "load waves.hpp"
#include "load spawner.hpp"
#include "init map info.hpp"
#include "map sprites tag.hpp"
#include <Simpleton/SDL/paths.hpp>
#include <Simpleton/Data/json.hpp>

void loadLevel(ECS::Registry &reg, const int level) {
  std::ifstream file(SDL::getResDir() + "level " + std::to_string(level) + ".json");
  json levelNode;
  file >> levelNode;
  
  Data::get(reg.get<MapSprites>().sprite, levelNode, "sprite");
  loadMap(reg, levelNode.at("map").get<int>());
  initMapInfo(reg);
  
  loadWaves(reg, levelNode.at("waves"));
  loadBase(reg, levelNode);
  loadSpawner(reg, levelNode);
}
