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
#include "basic components.hpp"
#include <experimental/optional>
#include <Simpleton/Math/rect.hpp>
#include <Simpleton/Graphics 2D/text.hpp>

class StatsView {
public:
  void setName(const std::string &);
  void setTable(const StatsTable &);
  void setButtons(const TowerButtons &);
  
  void setNoButtons();
  void clearState();
  
  Bounds sellBounds() const;
  Bounds upgradeBounds() const;

  void render(G2D::Section &, G2D::Text &) const;
  
private:
  std::experimental::optional<std::string> name;
  std::experimental::optional<StatsTable> table;
  std::experimental::optional<TowerButtons> buttons;

  void renderName(G2D::Text &) const;
  float renderTable(G2D::Text &) const;
  void renderButtons(float, G2D::Section &, G2D::Text &) const;
  
  static void renderLine(float, G2D::Section &);
  static void renderDisable(G2D::Section &);
  static void renderButton(float, G2D::Section &, Sprite::ID);
};

#endif
