//
//  sound component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef sound_component_hpp
#define sound_component_hpp

#include <Simpleton/Data/json.hpp>

struct Sound {
  uint32_t id;
  bool play;
};

inline void from_json(const json &j, Sound &comp) {
  DATA_GET(comp, id);
  comp.play = false;
}

#endif
