//
//  start beam firing anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 6/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "start beam firing anim system.hpp"

#include "beam tower component.hpp"
#include "tower shoot component.hpp"
#include "tower timing component.hpp"
#include "tower firing anim component.hpp"

void startBeamFiringAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<BeamTower, TowerShoot, TowerTiming, TowerFiringAnim>();
  
  for (const ECS::EntityID entity : view) {
    if (!view.get<TowerShoot>(entity).canShoot) {
      continue;
    }
    
    view.get<TowerTiming>(entity).timeSinceLastShot = 0.0f;
    
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    if (!view.get<BeamTower>(entity).firing && !anim.running) {
      anim.frame = 0;
      anim.running = true;
    }
  }
}
