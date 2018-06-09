//
//  game info view.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef game_info_view_hpp
#define game_info_view_hpp

#include "game info.hpp"
#include "text renderer.hpp"
#include <Simpleton/Graphics 2D/quad writer.hpp>

void renderGameInfo(G2D::Section &, TextRenderer &, const GameInfo &);

#endif
