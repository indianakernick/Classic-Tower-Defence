//
//  create tower.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "create tower.hpp"

#include "towers tag.hpp"

const ECS::Prototype *getTowerProto(ECS::Registry &reg, const size_t index) {
  const Towers &towers = reg.get<Towers>();
  if (index < towers.size()) {
    return &towers[index];
  } else {
    return nullptr;
  }
}
