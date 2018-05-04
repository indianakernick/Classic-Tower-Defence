//
//  tower gold component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 4/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_gold_component_hpp
#define tower_gold_component_hpp

#include <Simpleton/Data/json.hpp>

struct TowerGold {
  uint32_t buy;
  uint32_t sell;
};

inline void from_json(const json &j, TowerGold &comp) {
  DATA_GET(comp, buy);
  DATA_GET(comp, sell);
}

#endif
