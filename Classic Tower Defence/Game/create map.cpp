//
//  create map.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "create map.hpp"

#include "map component.hpp"
#include "map info component.hpp"
#include "map sprites component.hpp"

void createMap(ECS::Registry &reg) {
  const ECS::EntityID mapID = reg.create();
  reg.attach<Map>(mapID, glm::ivec2(16, 10), TileType::PLATFORM);
  reg.attach<MapInfo>(mapID);
  reg.attach<MapSprites>(mapID, Unpack::SpriteID(0));
}
