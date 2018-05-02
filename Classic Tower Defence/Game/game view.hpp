//
//  game view.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef game_view_hpp
#define game_view_hpp

#include "sound queue.hpp"
#include "text renderer.hpp"
#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Camera 2D/camera.hpp>
#include <Simpleton/Camera 2D/zoom to fit.hpp>
#include <Simpleton/Graphics 2D/sheet tex.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

class GameView {
public:
  GameView() = default;

  void init(G2D::Renderer &);
  void playSounds(ECS::Registry &);
  void updateCam(float, float);
  void render(ECS::Registry &, G2D::QuadWriter &);

private:
  G2D::SheetTex sheetTex;
  Cam2D::Camera camera;
  Cam2D::ZoomToFit zoomToFit;
  SoundQueue sounds;
  
  // might put these in a separate class
  G2D::SheetTex radiusSheetTex;
  G2D::SheetTex textSheetTex;
  Cam2D::Camera textCam;
  Cam2D::ZoomToFit textZoom;
  TextRenderer textRenderer;
};

#endif
