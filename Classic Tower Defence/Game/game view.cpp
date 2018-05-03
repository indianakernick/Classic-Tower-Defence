//
//  game view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game view.hpp"

#include "tower sound system.hpp"
#include <Simpleton/SDL/paths.hpp>
#include "map rendering system.hpp"
#include "unit rendering system.hpp"
#include "unit walk anim system.hpp"
#include "unit death anim system.hpp"
#include "tower rendering system.hpp"
#include "unit death sound system.hpp"
#include "tower firing anim system.hpp"
#include <Simpleton/Utils/profiler.hpp>
#include "unit death rendering system.hpp"
#include "unit health rendering system.hpp"
#include "tower range rendering system.hpp"

void GameView::init(G2D::Renderer &renderer) {
  camera.transform.setOrigin(Cam2D::Origin::BOTTOM_LEFT);
  zoomToFit.setSize({20.0f, 11.25f});
  camera.setPos({-4.0f, 0.0f});
  
  textCam.transform.setOrigin(Cam2D::Origin::BOTTOM_LEFT);
  textZoom.setSize({640.0f, 360.0f});
  
  sheetTex.load(renderer, "sprites");
  radiusSheetTex.load(renderer, "radius");
  textSheetTex.load(renderer, "5x8 ascii");
  
  textRenderer.setGlyphSize({5.0f, 8.0f});
  textRenderer.setAdvance({6.0f, -9.0f});
  textRenderer.setCursor({0.0f, 338.0f});
  textRenderer.setScale(2.0f);

  sounds.load();
}

void GameView::playSounds(ECS::Registry &reg) {
  towerSoundSystem(reg, sounds);
  unitDeathSoundSystem(reg, sounds);
  //sounds.play(DupSound::PLAY_LATER);
}

void GameView::updateCam(const float aspect, const float delta) {
  camera.update({aspect, delta}, zoomToFit);
  textCam.update({aspect, delta}, textZoom);
}

void GameView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  PROFILE(GameView::render);

  unitWalkAnimSystem(reg);
  unitDeathAnimSystem(reg);
  towerFiringAnimSystem(reg);
  
  writer.section({camera.transform.toPixels(), sheetTex.tex()});
  mapRenderingSystem(reg, writer, sheetTex.sheet());
  unitRenderingSystem(reg, writer, sheetTex.sheet());
  towerRenderingSystem(reg, writer, sheetTex.sheet());
  unitDeathRenderingSystem(reg, writer, sheetTex.sheet());
  unitHealthRenderingSystem(reg, writer, sheetTex.sheet());
  
  //writer.section({camera.transform.toPixels(), sheetTex.tex()});
  
  writer.section({textCam.transform.toPixels(), textSheetTex.tex()});
  textRenderer.resetCursor();
  textRenderer.pushText(writer, textSheetTex.sheet(), "I created a text renderer!\nIsn't it cool!");
  textRenderer.startLine();
  textRenderer.pushText(writer, textSheetTex.sheet(), "Some text that renders over the game");
}
