//
//  sound component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef sound_component_hpp
#define sound_component_hpp

#include "sound id.hpp"
#include <Simpleton/Data/json.hpp>

struct Sound {
  SoundID id;
};

inline void from_json(const json &j, Sound &comp) {
  DATA_GET(comp, id);
}

#endif
