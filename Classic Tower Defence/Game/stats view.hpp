//
//  stats view.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 31/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef stats_view_hpp
#define stats_view_hpp

#include "stats table.hpp"
#include "text renderer.hpp"
#include <Simpleton/Graphics 2D/sheet writer.hpp>

class StatsView {
public:
  void renderName(TextRenderer &, const std::string &);
  void renderTable(TextRenderer &, const StatsTable &);
  void renderButtons(G2D::SheetWriter, TextRenderer &, const TowerButtons &);
  
private:
  static constexpr float NO_TABLE = -1.0f;

  float tableBottom = NO_TABLE;
};

#endif
