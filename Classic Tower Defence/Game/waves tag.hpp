//
//  waves tag.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef waves_tag_hpp
#define waves_tag_hpp

#include <vector>
#include <Simpleton/ECS/prototype.hpp>

struct Wave {
  size_t quantity;
  ECS::Prototype proto;
};

using Waves = std::vector<Wave>;

#endif
