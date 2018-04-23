//
//  spawner system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef spawner_system_hpp
#define spawner_system_hpp

#include "wave.hpp"
#include <Simpleton/ECS/registry.hpp>

void spawnerSystem(ECS::Registry &, const Wave &);

#endif
