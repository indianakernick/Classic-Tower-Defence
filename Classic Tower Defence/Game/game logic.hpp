//
//  game logic.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef game_logic_hpp
#define game_logic_hpp

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_events.h>
#include "input consumed.hpp"
#include <Simpleton/ECS/registry.hpp>

class GameLogic {
public:
  GameLogic() = default;
  
  void init(ECS::Registry &);
  InputConsumed input(const SDL_Event &);
  void update(ECS::Registry &, float);
};

#endif
