//
//  stats table.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 31/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef stats_table_hpp
#define stats_table_hpp

#include <vector>
#include <string_view>

using StatsTableRow = std::pair<std::string_view, float>;
using StatsTable = std::vector<StatsTableRow>;

struct TowerButtons {
  uint32_t upgrade;   // 0 means cannot upgrade
  uint32_t sell;      // 0 means cannot sell
  uint32_t buy;       // 0 means cannot buy
  bool afford;        // has enough gold to upgrade or buy
};

#endif
