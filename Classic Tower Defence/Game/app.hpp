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

#include "wave.hpp"
#include "map info.hpp"
#include "towers.hpp"
#include <Simpleton/Unpack/sheet.hpp>
#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Camera 2D/camera.hpp>
#include <Simpleton/Graphics 2D/renderer.hpp>
#include <Simpleton/Camera 2D/zoom to fit.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

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
  
  G2D::Renderer renderer;
  Cam2D::Camera camera;
  Cam2D::ZoomToFit zoomToFit;
  ECS::Registry reg;
  Map map;
  MapInfo mapInfo;
  Wave wave;
  G2D::QuadWriter writer;
  Unpack::Spritesheet sheet;
  TowerProto tower;

  bool input();
  void update(float);
  void render(float);
};

#endif
