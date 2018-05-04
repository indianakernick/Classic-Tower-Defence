//
//  load level.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load level.hpp"

#include <fstream>
#include "map tag.hpp"
#include "waves tag.hpp"
#include "init map info.hpp"
#include "base gold tag.hpp"
#include "map sprites tag.hpp"
#include "base health tag.hpp"
#include "spawner state tag.hpp"
#include "spawner timing tag.hpp"
#include <Simpleton/SDL/paths.hpp>
#include <Simpleton/Data/json.hpp>

namespace {
  TileType tileChar(const char c) {
    switch (c) {
      case 's':
        return TileType::ENTRY;
      case 'b':
        return TileType::EXIT;
      case ' ':
        return TileType::PATH;
      case '#':
        return TileType::PLATFORM;
      case EOF:
        throw std::runtime_error("Unexpected end of map file");
      default:
        throw std::runtime_error("Invalid character in map");
    }
  }

  void loadMap(ECS::Registry &reg, const int mapID) {
    std::ifstream file(SDL::getResDir() + "map " + std::to_string(mapID) + ".txt");
    Map &map = reg.get<Map>();
    using Scalar = Map::Pos::value_type;
    const Scalar width = map.tileSize().x;
    for (Scalar y = map.tileSize().y - 1; y != Scalar(-1); --y) {
      for (Scalar x = 0; x != width; ++x) {
        map[{x, y}] = tileChar(file.get());
      }
      if (file.get() != '\n') {
        file.unget();
      }
    }
  }
}

void loadLevel(ECS::Registry &reg, const int level) {
  std::ifstream file(SDL::getResDir() + "level " + std::to_string(level) + ".json");
  json levelNode;
  file >> levelNode;
  Data::get(reg.get<MapSprites>().sprite, levelNode, "sprite");
  
  loadMap(reg, levelNode.at("map").get<int>());
  initMapInfo(reg);
  
  reg.get<Waves>() = levelNode.at("waves").get<Waves>();
  
  Data::get(reg.get<BaseHealth>().health, levelNode, "health");
  Data::get(reg.get<BaseGold>().gold, levelNode, "gold");
  
  SpawnerTiming &timing = reg.get<SpawnerTiming>();
  Data::get(timing.minTimeBetweenSpawns, levelNode, "spawntime");
  timing.timeSinceLastSpawn = timing.minTimeBetweenSpawns + 1.0f;
  reg.get<SpawnerState>() = {};
}
