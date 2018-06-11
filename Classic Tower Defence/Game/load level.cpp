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
#include "count live units.hpp"
#include <Simpleton/SDL/paths.hpp>
#include <Simpleton/Data/json.hpp>
#include "common tower stats component.hpp"

bool loadLevel(ECS::Registry &reg, const int level) {
  std::ifstream file(SDL::getResDir() + "level " + std::to_string(level) + ".json");
  if (!file.is_open()) {
    return false;
  }
  
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
  
  return true;
}

void loadNextLevel(ECS::Registry &reg) {
  if (countLiveUnits(reg) != 0) {
    return;
  }
  
  for (const ECS::EntityID entity : reg.view<CommonTowerStats>()) {
    reg.destroy(entity);
  }

  const int current = reg.get<LevelInfo>().level;
  if (!loadLevel(reg, current + 1)) {
    // @TODO player has finished the game
  }
}
