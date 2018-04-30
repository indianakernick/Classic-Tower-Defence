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
#include <Simpleton/Sprite/sheet.hpp>
#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Camera 2D/camera.hpp>
#include <Simpleton/Graphics 2D/renderer.hpp>
#include <Simpleton/Camera 2D/zoom to fit.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

class GameView {
public:
  GameView() = default;

  void init(G2D::Renderer &);
  void playSounds(ECS::Registry &);
  void updateCam(float, float);
  void render(ECS::Registry &, G2D::QuadWriter &);

private:
  Sprite::Sheet sheet;
  Cam2D::Camera camera;
  Cam2D::ZoomToFit zoomToFit;
  G2D::TextureID tex;
  SoundQueue sounds;
};

#endif
