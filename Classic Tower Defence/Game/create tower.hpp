//
//  create tower.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef create_tower_hpp
#define create_tower_hpp

#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/ECS/prototype.hpp>

const ECS::Prototype *getTowerProto(ECS::Registry &, size_t);

#endif
