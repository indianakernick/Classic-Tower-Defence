//
//  load waves.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load waves.hpp"

#include "waves tag.hpp"
#include "map info tag.hpp"
#include "load prototype.hpp"
#include "position component.hpp"
#include "unit dir component.hpp"
#include "unit stats component.hpp"

void loadWaves(ECS::Registry &reg, const json &wavesNode) {
  const MapInfo &map = reg.get<MapInfo>();
  Waves &waves = reg.get<Waves>();
  waves.clear();
  const json::array_t &array = wavesNode.get_ref<const json::array_t &>();
  for (const auto &node : array) {
    Wave &wave = waves.emplace_back();
    Data::get(wave.quantity, node, "quantity");
    const int unreadCount = loadProto(wave.proto, node.at("proto"));
    assert(unreadCount == 0);
    wave.proto.set<UnitDir>(map.entryDir);
    wave.proto.set<Position>(map.entry);
  }

  for (Wave &wave : waves) {
    wave.proto.get<UnitStats>().proto = &wave.proto;
  }
}
