//
//  mouse pos.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 20/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef mouse_pos_hpp
#define mouse_pos_hpp

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <SDL2/SDL_events.h>

//@SIMPLETON

glm::vec2 mousePos(const glm::mat3 &);
glm::vec2 mousePos(const glm::mat3 &, const SDL_MouseButtonEvent &);
glm::vec2 mousePos(const glm::mat3 &, const SDL_MouseMotionEvent &);

#endif
