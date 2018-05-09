//
//  load spawner.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef load_spawner_hpp
#define load_spawner_hpp

#include <Simpleton/Data/json.hpp>
#include <Simpleton/ECS/registry.hpp>

void loadSpawner(ECS::Registry &, const json &);

#endif
