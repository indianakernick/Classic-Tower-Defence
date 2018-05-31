//
//  load towers.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load towers.hpp"

#include <fstream>
#include "towers tag.hpp"
#include "load prototype.hpp"
#include <Simpleton/SDL/paths.hpp>
#include "tower upgrades component.hpp"

void loadTowers(ECS::Registry &reg) {
  std::fstream file(SDL::getResDir() + "towers.json");
  json towersNode;
  file >> towersNode;
  
  const ECS::EntityID entity = reg.create();
  Towers &towers = reg.assign<Towers>(entt::tag_t{}, entity);
  
  for (const json &towerNode : towersNode) {
    TowerProto tower;
    [[maybe_unused]]
    const int unreadCount = loadProto(tower, towerNode);
    assert(unreadCount == 1);
    towers.emplace_back(std::move(tower));
  }
  
  for (size_t i = 0; i != towers.size(); ++i) {
    // upgrades on the json object are indicies onto the array of towers
    // upgrades on the game object are pointers onto the array of towers
    const json &j = towersNode[i].at("upgrades");
    TowerUpgrades &upgrades = towers[i].assign<TowerUpgrades>();
    if (JSON_OPTIONAL(index, j, "next")) {
      upgrades.next = &towers.at(index->get<size_t>());
    } else {
      upgrades.next = nullptr;
    }
  }
}
