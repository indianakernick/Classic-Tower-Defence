//
//  cursor area.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef cursor_area_hpp
#define cursor_area_hpp

#include <glm/mat3x3.hpp>
#include <Simpleton/Math/rect.hpp>
#include <Simpleton/SDL/system cursors.hpp>

class CursorArea {
public:
  using Rect = Math::RectPP<float>;
  struct Pair {
    Rect rect;
    SDL_SystemCursor cursor;
  };

  void init();
  void update(glm::mat3);
  
  size_t mark(Rect, SDL_SystemCursor);
  Pair &get(size_t);
  void remove(size_t);
  
private:
  SDL::SystemCursors cursors;
  std::vector<Pair> pairs;
};

#endif
