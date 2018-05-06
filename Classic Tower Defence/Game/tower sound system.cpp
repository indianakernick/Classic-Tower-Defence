//
//  tower sound system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower sound system.hpp"

#include "sound component.hpp"
#include "tower firing anim component.hpp"

void towerSoundSystem(ECS::Registry &reg, SoundQueue &queue) {
  auto view = reg.view<Sound, TowerFiringAnim>();
  for (const ECS::EntityID entity : view) {
    const TowerFiringAnim anim = view.get<TowerFiringAnim>(entity);
    if (anim.running && anim.frame == 0) {
      queue.push(view.get<Sound>(entity).id);
    }
  }
}
