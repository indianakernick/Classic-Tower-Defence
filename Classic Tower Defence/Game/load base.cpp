//
//  load base.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load base.hpp"

#include "base gold tag.hpp"
#include "base health tag.hpp"

void loadBase(ECS::Registry &reg, const json &node) {
  Data::get(reg.get<BaseHealth>().health, node, "health");
  Data::get(reg.get<BaseGold>().gold, node, "gold");
}
