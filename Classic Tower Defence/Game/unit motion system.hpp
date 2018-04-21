//
//  unit motion system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_motion_system_hpp
#define unit_motion_system_hpp

#include "map info.hpp"
#include <Simpleton/ECS/registry.hpp>

void unitMotionSystem(ECS::Registry &, const MapInfo &, float);

#endif
