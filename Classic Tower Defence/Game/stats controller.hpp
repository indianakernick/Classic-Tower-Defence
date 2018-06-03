//
//  stats controller.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 3/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef stats_controller_hpp
#define stats_controller_hpp

#include "stats view.hpp"
#include "stats model.hpp"
#include "text renderer.hpp"
#include "input consumed.hpp"
#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/SDL/system cursors.hpp>
#include <Simpleton/Graphics 2D/sheet writer.hpp>

class StatsController {
public:
  Consumed click(glm::vec2, ECS::Registry &);
  Consumed hover(glm::vec2, SDL::SystemCursors &);
  void setRenderState(ECS::Registry &);
  void render(G2D::SheetWriter, TextRenderer &);
  
  StatsView view;
  StatsModel model;
};

#endif
