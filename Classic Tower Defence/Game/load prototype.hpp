//
//  load prototype.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef load_prototype_hpp
#define load_prototype_hpp

#include "prototype.hpp"
#include <Simpleton/Data/json.hpp>

//@SIMPLETON

bool loadComponent(DefaultPrototype &, std::string_view, const json &);
int loadProto(DefaultPrototype &, const json &);

#endif
