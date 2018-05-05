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
#include "component list.hpp"
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
  
  template <typename Comp>
  constexpr auto hasFromjson(int) -> decltype(from_json(json{}, std::declval<Comp &>()), bool()) {
    return true;
  }
  
  template <typename Comp>
  constexpr bool hasFromjson(long) {
    return false;
  }
  
  template <typename Proto>
  bool readComponent(Proto &proto, const std::string_view name, const json &component) {
    bool read = false;
    Utils::forEach<CompList>([&proto, name, &component, &read] (auto t) {
      using Comp = UTILS_TYPE(t);
      if constexpr (hasFromjson<Comp>(0)) {
        if (Utils::typeName<Comp>() == name) {
          proto.template assign<Comp>(component.get<Comp>());
          read = true;
        }
      } else if constexpr (std::is_empty_v<Comp>) {
        if (Utils::typeName<Comp>() == name) {
          proto.template assign<Comp>();
          read = true;
        }
      }
    });
    return read;
  }
  
  template <typename Proto>
  size_t readEntity(Proto &proto, const json &entity) {
    const json::object_t &object = entity.get_ref<const json::object_t &>();
    size_t unreadCount = 0;
    for (auto pair : object) {
      unreadCount += !readComponent(proto, pair.first, pair.second);
    }
    return unreadCount;
  }
}

void loadTowers(ECS::Registry &reg) {
  std::fstream file(SDL::getResDir() + "towers.json");
  json towersNode;
  file >> towersNode;
  
  const ECS::EntityID entity = reg.create();
  Towers &towers = reg.attach<Towers>(entity);
  
  for (const json &towerNode : towersNode) {
    TowerProto tower;
    [[maybe_unused]]
    const size_t unreadCount = readEntity(tower, towerNode);
    assert(unreadCount == 1);
    towers.emplace_back(std::move(tower));
  }
  
  for (size_t i = 0; i != towers.size(); ++i) {
    // upgrades on the json object are indicies onto the array of towers
    // upgrades on the game object are pointers onto the array of towers
    const json &j = towersNode[i].at("upgrades");
    TowerUpgrades &upgrades = towers[i].assign<TowerUpgrades>();
    upgrades.first = getUpgrade(j, towers, "first");
    upgrades.second = getUpgrade(j, towers, "second");
  }
}
