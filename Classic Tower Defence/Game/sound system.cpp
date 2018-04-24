//
//  sound system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "sound system.hpp"

#include "sound component.hpp"

void soundSystem(ECS::Registry &reg, const Sounds &sounds) {
  auto view = reg.view<Sound>();
  for (const ECS::EntityID entity : view) {
    Sound &sound = view.get(entity);
    if (sound.play) {
      sound.play = false;
      Mix_PlayChannel(-1, sounds.at(sound.id), 0);
    }
  }
}
