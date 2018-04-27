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
  void assign(Args &&... args) {
    factories.emplace_back(
      [Comp comp = Comp{std::forward<Args>(args)...}]
      (Registry &reg, entity_type entity) {
        reg.template assign<Comp>(entity, comp);
      }
    );
  }
  
  uint32_t operator()(Registry &reg) {
    uint32_t id = reg.create();
    for (auto &factory : factories) {
      factory(reg, id);
    }
    return id;
  }
  
private:
  std::vector<std::function<void (Registry &, uint32_t)>> factories;
};

#endif
