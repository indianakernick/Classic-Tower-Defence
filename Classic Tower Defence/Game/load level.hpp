//
//  load level.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef load_level_hpp
#define load_level_hpp

#include <Simpleton/ECS/registry.hpp>

bool loadLevel(ECS::Registry &, int);
void loadNextLevel(ECS::Registry &);
void reloadLevel(ECS::Registry &);

#endif
