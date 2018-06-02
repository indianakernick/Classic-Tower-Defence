//
//  preview entity.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 20/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "preview entity.hpp"

#include "waves tag.hpp"
#include "spawner state tag.hpp"
#include "position component.hpp"
#include "unit dir component.hpp"
#include "unit sprite component.hpp"
#include "unit walk anim component.hpp"

ECS::EntityID makePreviewEntity(ECS::Registry &reg) {
  const ECS::EntityID entity = reg.create();
  reg.assign<Position>(entity, glm::vec2(14.875f, 10.125f));
  reg.assign<UnitDir>(entity, Grid::Dir::RIGHT);
  reg.assign<UnitSprite>(entity);
  reg.assign<UnitWalkAnim>(entity);
  return entity;
}

namespace {
  size_t getCurrentWave(ECS::Registry &reg) {
    const SpawnerState state = reg.get<SpawnerState>();
    return state.currentWave + (state.state == SpawnerState::FINISHED);
  }
}

void updatePreviewEntity(ECS::Registry &reg, const ECS::EntityID entity) {
  const Waves &waves = reg.get<Waves>();
  const size_t currentWave = getCurrentWave(reg);
  if (currentWave < waves.size()) {
    const auto &proto = waves[currentWave].proto;
    reg.replace<UnitSprite>(entity, proto.get<UnitSprite>());
    UnitWalkAnim &anim = reg.get<UnitWalkAnim>(entity);
    const UnitWalkAnim &newAnim = proto.get<UnitWalkAnim>();
    anim.frames = newAnim.frames;
    anim.subframes = newAnim.subframes;
  }
}

const ECS::Prototype *getPreviewProto(ECS::Registry &reg) {
  const Waves &waves = reg.get<Waves>();
  const size_t currentWave = getCurrentWave(reg);
  if (currentWave < waves.size()) {
    return &waves[currentWave].proto;
  } else {
    return nullptr;
  }
}
