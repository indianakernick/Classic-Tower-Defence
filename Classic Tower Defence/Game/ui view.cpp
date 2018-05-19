//
//  ui view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "ui view.hpp"

#include "depth.hpp"

void UIView::init(G2D::Renderer &renderer) {
  camera.transform.setOrigin(Cam2D::Origin::TOP_LEFT);
  camera.transform.setInvertY(true);
  zoom.setSize({640.0f, 360.0f});
  
  uiSheetTex.load(renderer, "ui");
  textSheetTex.load(renderer, "5x8 ascii");
  radiusSheetTex.load(renderer, "radius");
  
  text.setGlyphSize({5.0f, 8.0f});
  text.setAdvance({6.0f, -9.0f});
  text.setCursor({50.0f, 338.0f});
  text.setScale(2.0f);
}

void UIView::updateCam(const Cam2D::Params params) {
  camera.update(params, zoom);
}

void UIView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  writer.section({camera.transform.toPixels(), uiSheetTex.tex()});
  
  writer.quad();
  writer.depth(Depth::UI_BASE);
  writer.tilePos({0.0f, 0.0f}, {640.0f, 360.0f});
  writer.tileTex<G2D::PlusXY::RIGHT_DOWN>(uiSheetTex.sheet().getSprite(0));
}
