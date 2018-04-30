//
//  create level.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "create level.hpp"

#include "map tag.hpp"
#include "waves tag.hpp"
#include "map info tag.hpp"
#include "map sprites tag.hpp"

void createLevel(ECS::Registry &reg) {
  const ECS::EntityID id = reg.create();
  reg.attach<Map>(id, glm::ivec2(16, 10), TileType::PLATFORM);
  reg.attach<MapInfo>(id);
  reg.attach<MapSprites>(id);
  reg.attach<Waves>(id);
}
