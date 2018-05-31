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
#include <Simpleton/Graphics 2D/sheet tex.hpp>

class StatsView {
public:

  void setSheetTex(const G2D::SheetTex &);
  void renderTable(TextRenderer &, const StatsTable &);
  void renderButtons(TextRenderer &, const TowerButtons &);
  
private:
  static constexpr float NO_TABLE = -1.0f;

  const G2D::SheetTex *uiSheetTex;
  float tableBottom = NO_TABLE;
};

#endif
