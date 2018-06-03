//
//  ui view.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef ui_view_hpp
#define ui_view_hpp

#include "stats controller.hpp"
#include <Simpleton/Camera 2D/camera.hpp>
#include <Simpleton/SDL/system cursors.hpp>
#include <Simpleton/Camera 2D/zoom to fit.hpp>
#include <Simpleton/Graphics 2D/sheet tex.hpp>

class UIView {
public:
  UIView() = default;
  
  void init(ECS::Registry &, G2D::Renderer &);
  void updateCam(Cam2D::Params);
  Consumed input(ECS::Registry &, const SDL_Event &);
  void updateAnim(ECS::Registry &, float);
  void render(ECS::Registry &, G2D::QuadWriter &);

private:
  G2D::SheetTex uiSheetTex;
  G2D::SheetTex textSheetTex;
  G2D::SheetTex radiusSheetTex;
  Cam2D::Camera camera;
  Cam2D::ZoomToFit zoom;
  TextRenderer text;
  G2D::QuadWriter textWriter;
  ECS::Registry uiReg;
  ECS::EntityID previewEntity;
  StatsController stats;
  SDL::SystemCursors cursors;
  
  Cam2D::Camera gameCam;
  Cam2D::ZoomToFit gameZoom;
};

#endif
