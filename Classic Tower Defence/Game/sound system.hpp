//
//  sound system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef sound_system_hpp
#define sound_system_hpp

#include "sounds.hpp"
#include <Simpleton/ECS/registry.hpp>

void soundSystem(ECS::Registry &, const Sounds &);

#endif
