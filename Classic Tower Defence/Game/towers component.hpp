//
//  towers.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef towers_hpp
#define towers_hpp

#include "prototype.hpp"
#include <Simpleton/ECS/registry.hpp>

using TowerProto = Prototype<ECS::EntityID, struct Tower>;
using Towers = std::vector<TowerProto>;

#endif
