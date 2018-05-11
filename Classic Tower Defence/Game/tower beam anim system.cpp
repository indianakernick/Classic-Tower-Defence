//
//  tower beam anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 10/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower beam anim system.hpp"

#include "tower beam anim component.hpp"

void towerBeamAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerBeamAnim>();
  for (const ECS::EntityID entity : view) {
    TowerBeamAnim &anim = view.get(entity);
    ++anim.frame;
    if (anim.frame == anim.frames) {
      anim.frame = 0;
    }
  }
}
