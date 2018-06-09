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
#include "basic components.hpp"
#include <experimental/optional>
#include <Simpleton/Math/rect.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

class StatsView {
public:
  void setName(const std::string &);
  void setTable(const StatsTable &);
  void setButtons(const TowerButtons &);
  
  void setNoButtons();
  void clearState();
  
  Bounds sellBounds() const;
  Bounds upgradeBounds() const;

  void render(G2D::Section &, TextRenderer &, G2D::Section &) const;
  
private:
  std::experimental::optional<std::string> name;
  std::experimental::optional<StatsTable> table;
  std::experimental::optional<TowerButtons> buttons;

  void renderName(TextRenderer &) const;
  float renderTable(TextRenderer &) const;
  void renderButtons(float, G2D::Section &, TextRenderer &) const;
  
  static void renderLine(float, G2D::Section &);
  static void renderDisable(G2D::Section &);
  static void renderButton(float, G2D::Section &, Sprite::ID);
};

#endif
