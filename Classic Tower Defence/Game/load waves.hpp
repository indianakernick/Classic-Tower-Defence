//
//  load waves.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef load_waves_hpp
#define load_waves_hpp

#include <Simpleton/Data/json.hpp>
#include <Simpleton/ECS/registry.hpp>

void loadWaves(ECS::Registry &, const json &);

#endif
