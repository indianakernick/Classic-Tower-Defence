//
//  preview entity.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 20/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef preview_entity_hpp
#define preview_entity_hpp

#include "prototype.hpp"
#include <Simpleton/ECS/registry.hpp>

ECS::EntityID makePreviewEntity(ECS::Registry &);
void updatePreviewEntity(ECS::Registry &, ECS::EntityID);
const DefaultPrototype *getPreviewProto(ECS::Registry &);

#endif
