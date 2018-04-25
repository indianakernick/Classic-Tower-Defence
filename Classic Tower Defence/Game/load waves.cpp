//
//  load waves.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load waves.hpp"

#include <istream>

void loadWaves(Waves &waves, std::istream &stream) {
  json node;
  stream >> node;
  waves = node.get<Waves>();
}
