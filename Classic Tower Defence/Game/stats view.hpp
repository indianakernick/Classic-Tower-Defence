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
#include <experimental/optional>
#include <Simpleton/Graphics 2D/sheet writer.hpp>

class StatsView {
public:
  void setName(const std::string &);
  void setTable(const StatsTable &);
  void setButtons(const TowerButtons &);
  void setNoButtons();

  void render(G2D::SheetWriter, TextRenderer &) const;
  
private:
  std::string name;
  StatsTable table;
  std::experimental::optional<TowerButtons> buttons;

  void renderName(TextRenderer &) const;
  float renderTable(TextRenderer &) const;
  void renderButtons(float, G2D::SheetWriter, TextRenderer &) const;
  
  static void renderLine(float, G2D::SheetWriter);
  static void renderDisable(G2D::SheetWriter);
  static void renderButton(float, G2D::SheetWriter, Sprite::ID);
};

#endif
