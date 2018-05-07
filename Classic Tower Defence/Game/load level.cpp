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
#include "map info tag.hpp"
#include "init map info.hpp"
#include "base gold tag.hpp"
#include "load prototype.hpp"
#include "map sprites tag.hpp"
#include "base health tag.hpp"
#include "spawner state tag.hpp"
#include "spawner timing tag.hpp"
#include "unit dir component.hpp"
#include "position component.hpp"
#include <Simpleton/SDL/paths.hpp>
#include <Simpleton/Data/json.hpp>
#include "unit stats component.hpp"

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
  
  void loadWaves(ECS::Registry &reg, const json &wavesNode) {
    const MapInfo &map = reg.get<MapInfo>();
    Waves &waves = reg.get<Waves>();
    const json::array_t &array = wavesNode.get_ref<const json::array_t &>();
    for (const auto &node : array) {
      Wave &wave = waves.emplace_back();
      Data::get(wave.quantity, node, "quantity");
      const int unreadCount = loadProto(wave.proto, node.at("proto"));
      assert(unreadCount == 0);
      wave.proto.assign<UnitDir>(map.entryDir);
      wave.proto.assign<Position>(map.entry);
    }
    
    for (Wave &wave : waves) {
      wave.proto.get<UnitStats>().proto = &wave.proto;
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
  
  loadWaves(reg, levelNode.at("waves"));
  
  Data::get(reg.get<BaseHealth>().health, levelNode, "health");
  Data::get(reg.get<BaseGold>().gold, levelNode, "gold");
  
  SpawnerTiming &timing = reg.get<SpawnerTiming>();
  Data::get(timing.minTimeBetweenSpawns, levelNode, "spawntime");
  timing.timeSinceLastSpawn = timing.minTimeBetweenSpawns + 1.0f;
  reg.get<SpawnerState>() = {};
}
