//
//  ui view.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef ui_view_hpp
#define ui_view_hpp

#include "cursor area.hpp"
#include "text renderer.hpp"
#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Camera 2D/camera.hpp>
#include <Simpleton/Camera 2D/zoom to fit.hpp>
#include <Simpleton/Graphics 2D/sheet tex.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

class UIView {
public:
  UIView() = default;
  
  void init(G2D::Renderer &);
  void updateCam(Cam2D::Params);
  void render(ECS::Registry &, G2D::QuadWriter &);

private:
  G2D::SheetTex uiSheetTex;
  G2D::SheetTex textSheetTex;
  G2D::SheetTex radiusSheetTex;
  Cam2D::Camera camera;
  Cam2D::ZoomToFit zoom;
  TextRenderer text;
  CursorArea cursor;
  
  void rightText(G2D::QuadWriter &, glm::vec2, std::string_view);
  void rightNum(G2D::QuadWriter &, glm::vec2, uint64_t);
};

#endif
