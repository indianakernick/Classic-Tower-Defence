//
//  ui view.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef ui_view_hpp
#define ui_view_hpp

#include "prototype.hpp"
#include "cursor area.hpp"
#include "text renderer.hpp"
#include "input consumed.hpp"
#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Camera 2D/camera.hpp>
#include <Simpleton/Camera 2D/zoom to fit.hpp>
#include <Simpleton/Graphics 2D/sheet tex.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

class UIView {
public:
  UIView() = default;
  
  void init(ECS::Registry &, G2D::Renderer &);
  void updateCam(Cam2D::Params);
  InputConsumed input(ECS::Registry &, const SDL_Event &);
  void updateAnim(ECS::Registry &, float);
  void render(ECS::Registry &, G2D::QuadWriter &);

private:
  G2D::SheetTex uiSheetTex;
  G2D::SheetTex textSheetTex;
  G2D::SheetTex radiusSheetTex;
  Cam2D::Camera camera;
  Cam2D::ZoomToFit zoom;
  TextRenderer text;
  CursorArea cursor;
  ECS::EntityID previewEntity;
  Sprite::ID base;
  Sprite::ID previewBack;
  const DefaultPrototype *statsProto = nullptr;
  
  void leftText(G2D::QuadWriter &, glm::vec2, std::string_view);
  void rightText(G2D::QuadWriter &, glm::vec2, std::string_view);
  void rightNum(G2D::QuadWriter &, glm::vec2, uint64_t);
  void renderProto(G2D::QuadWriter &);
  
  void renderUnitStats(G2D::QuadWriter &);
  void renderTowerStats(G2D::QuadWriter &);
};

#endif
