//
//  start proj firing anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "start proj firing anim system.hpp"

#include "tower shoot component.hpp"
#include "tower timing component.hpp"
#include "projectile tower component.hpp"
#include "tower firing anim component.hpp"

void startProjFiringAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerShoot, TowerTiming, ProjectileTower, TowerFiringAnim>();
  
  for (const ECS::EntityID entity : view) {
    if (!view.get<TowerShoot>(entity).canShoot) {
      continue;
    }
    
    view.get<TowerTiming>(entity).timeSinceLastShot = 0.0f;
    
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    anim.frame = 0;
    anim.running = true;
  }
}
