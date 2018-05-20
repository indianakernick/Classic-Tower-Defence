//
//  name component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef name_component_hpp
#define name_component_hpp

#include <string>
#include <Simpleton/Data/json.hpp>

struct Name {
  std::string name;
};

inline void from_json(const json &j, Name &name) {
  name.name = j.get_ref<const std::string &>();
}

#endif
