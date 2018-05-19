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
#include "level info tag.hpp"
#include "map sprites tag.hpp"
#include <Simpleton/SDL/paths.hpp>
#include <Simpleton/Data/json.hpp>

void loadLevel(ECS::Registry &reg, const int level) {
  std::ifstream file(SDL::getResDir() + "level " + std::to_string(level) + ".json");
  json levelNode;
  file >> levelNode;
  
  LevelInfo &levelInfo = reg.get<LevelInfo>();
  levelInfo.level = level;
  levelInfo.map = levelNode.at("map").get<int>();
  
  Data::get(reg.get<MapSprites>().sprite, levelNode, "sprite");
  loadMap(reg, levelInfo.map);
  initMapInfo(reg);
  
  loadWaves(reg, levelNode.at("waves"));
  loadBase(reg, levelNode);
  loadSpawner(reg, levelNode);
}
