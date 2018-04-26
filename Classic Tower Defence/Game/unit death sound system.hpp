//
//  unit death sound system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 26/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_death_sound_system_hpp
#define unit_death_sound_system_hpp

#include "sound queue.hpp"
#include <Simpleton/ECS/registry.hpp>

void unitDeathSoundSystem(ECS::Registry &, SoundQueue &);

#endif
