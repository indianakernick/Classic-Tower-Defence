//
//  prototype.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 27/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef prototype_hpp
#define prototype_hpp

#include <functional>
#include <Simpleton/ECS/registry.hpp>

template <typename Registry>
class Prototype {
public:
  template <typename Comp, typename ...Args>
  void assign(Args... args) {
    comps.emplace_back([args...] (Registry &reg, uint32_t id) {
      reg.template assign<Comp>(id, args...);
    });
  }
  
  uint32_t create(Registry &reg) {
    uint32_t id = reg.create();
    for (auto &comp : comps) {
      comp(reg, id);
    }
    return id;
  }
  
private:
  std::vector<std::function<void (Registry &, uint32_t)>> comps;
};

#endif
