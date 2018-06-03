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
  static void renderName(TextRenderer &, const std::string &);
  static float renderTable(TextRenderer &, const StatsTable &);
  static void renderButtons(float, G2D::SheetWriter, TextRenderer &, const TowerButtons &);
  
private:
  static void renderLine(G2D::SheetWriter, float);
  static void renderDisable(G2D::SheetWriter);
  static void renderButton(G2D::SheetWriter, float, Sprite::ID);
};

#endif
