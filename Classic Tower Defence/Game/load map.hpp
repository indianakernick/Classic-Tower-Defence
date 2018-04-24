//
//  load map.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef load_map_hpp
#define load_map_hpp

#include <iosfwd>
#include <Simpleton/ECS/registry.hpp>

void loadMap(ECS::Registry &, std::istream &);

#endif
