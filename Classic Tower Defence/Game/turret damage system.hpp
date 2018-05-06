//
//  turret tower shoot system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef turret_tower_shoot_system_hpp
#define turret_tower_shoot_system_hpp

#include <Simpleton/ECS/registry.hpp>

// apply turret damage to targeted unit if tower can shoot
void turretDamageSystem(ECS::Registry &);

#endif
