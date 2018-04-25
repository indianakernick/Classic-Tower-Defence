//
//  towers.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef towers_hpp
#define towers_hpp

#include <vector>
#include "tower stats component.hpp"
#include "tower sprites component.hpp"
#include "tower upgrades component.hpp"

struct TowerProto {
  TowerStatsBase stats;
  TowerSpritesBase sprites;
  TowerUpgradesBase upgrades;
};

using Towers = std::vector<TowerProto>;

inline void from_json(const json &node, Towers &towers) {
  assert(towers.empty());
  for (const json &j : node) {
    TowerProto tower;
    DATA_GET(tower, stats);
    DATA_GET(tower, sprites);
    towers.push_back(tower);
  }
  
  for (size_t i = 0; i != towers.size(); ++i) {
    // upgrades on the json object are indicies onto the array of towers
    // upgrades on the game object are pointers onto the array of towers
    const json &j = node[i].at("upgrades");
    towers[i].upgrades.first = &towers.at(j.at("first").get<size_t>());
    towers[i].upgrades.second = &towers.at(j.at("second").get<size_t>());
  }
}

#endif
