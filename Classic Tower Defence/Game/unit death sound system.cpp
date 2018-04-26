//
//  unit death sound system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 26/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit death sound system.hpp"

#include "sound component.hpp"
#include "unit death anim component.hpp"

void unitDeathSoundSystem(ECS::Registry &reg, SoundQueue &queue) {
  auto view = reg.view<Sound, UnitDeathAnim>();
  for (const ECS::EntityID entity : view) {
    queue.push(view.get<Sound>(entity).id);
    reg.remove<Sound>(entity);
  }
}
