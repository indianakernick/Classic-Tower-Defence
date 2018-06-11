//
//  tower sound system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower sound system.hpp"

#include "sound component.hpp"
#include "tower sprites component.hpp"

void towerSoundSystem(ECS::Registry &reg, SoundQueue &queue) {
  auto view = reg.view<Sound, TowerSprites>();
  for (const ECS::EntityID entity : view) {
    if (view.get<TowerSprites>(entity).gun.firstFrame()) {
      queue.push(view.get<Sound>(entity).id);
    }
  }
}
