//
//  app.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef app_hpp
#define app_hpp

#include <Simpleton/SDL/library.hpp>
#include <Simpleton/OpenGL/context.hpp>

class App {
public:
  App() = default;

  bool mainloop(uint64_t);

  void init();
  void quit();

private:
  SDL::Library windowLibrary;
  SDL::Window window;
  GL::Context renderingContext;

  bool input();
  void update(float);
  void render(float);
};

#endif
