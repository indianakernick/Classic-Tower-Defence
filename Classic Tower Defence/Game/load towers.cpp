//
//  load towers.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load towers.hpp"

#include <fstream>
#include "towers component.hpp"
#include <Simpleton/SDL/paths.hpp>

namespace {
  TowerProto *getUpgrade(
    const json &j,
    Towers &towers,
    const char *name
  ) {
    if (JSON_OPTIONAL(index, j, name)) {
      return &towers.at(index->get<size_t>());
    } else {
      return nullptr;
    }
  }
}

void loadTowers(ECS::Registry &reg) {
  std::fstream file(SDL::getResDir() + "towers.json");
  json node;
  file >> node;
  
  const ECS::EntityID entity = reg.create();
  Towers &towers = reg.attach<Towers>(entity);
  
  for (const json &j : node) {
    TowerProto tower;
    DATA_GET(tower, stats);
    DATA_GET(tower, sprites);
    DATA_GET(tower, sound);
    towers.push_back(tower);
  }
  
  for (size_t i = 0; i != towers.size(); ++i) {
    // upgrades on the json object are indicies onto the array of towers
    // upgrades on the game object are pointers onto the array of towers
    const json &j = node[i].at("upgrades");
    TowerUpgradesBase &upgrades = towers[i].upgrades;
    upgrades.first = getUpgrade(j, towers, "first");
    upgrades.second = getUpgrade(j, towers, "second");
  }
}
