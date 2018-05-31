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
#include "base gold tag.hpp"
#include "level info tag.hpp"
#include "map sprites tag.hpp"
#include "base health tag.hpp"
#include "spawner state tag.hpp"
#include "spawner timing tag.hpp"

void createLevel(ECS::Registry &reg) {
  const ECS::EntityID id = reg.create();
  reg.assign<Map>(entt::tag_t{}, id, glm::ivec2(16, 10));
  reg.assign<MapInfo>(entt::tag_t{}, id);
  reg.assign<MapSprites>(entt::tag_t{}, id);
  reg.assign<Waves>(entt::tag_t{}, id);
  reg.assign<BaseHealth>(entt::tag_t{}, id);
  reg.assign<BaseGold>(entt::tag_t{}, id);
  reg.assign<SpawnerState>(entt::tag_t{}, id);
  reg.assign<SpawnerTiming>(entt::tag_t{}, id);
  reg.assign<LevelInfo>(entt::tag_t{}, id);
}
