//
//  load prototype.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load prototype.hpp"

#include "component list.hpp"
#include <Simpleton/ECS/load prototype.hpp>

int loadProto(ECS::Prototype &proto, const json &node) {
  return ECS::loadProto<CompList>(proto, node);
}
