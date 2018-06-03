//
//  cursor systems.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef cursor_systems_hpp
#define cursor_systems_hpp

#include <glm/vec2.hpp>
#include "input consumed.hpp"
#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/SDL/system cursors.hpp>

ECS::EntityID getObjAtPos(ECS::Registry &, glm::vec2);
void updateCursor(ECS::Registry &, SDL::SystemCursors &, ECS::EntityID);
InputConsumed handleClick(ECS::Registry &, ECS::EntityID);

#endif
