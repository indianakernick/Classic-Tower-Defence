//
//  count live units.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 20/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "count live units.hpp"

#include "unit stats component.hpp"

size_t countLiveUnits(ECS::Registry &reg) {
  return reg.size<UnitStats>();
}
