//
//  tower shoot system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_shoot_system_hpp
#define tower_shoot_system_hpp

#include <SDL2/SDL_mixer.h>
#include <Simpleton/ECS/registry.hpp>

void towerShootSystem(ECS::Registry &, Mix_Chunk *);

#endif
