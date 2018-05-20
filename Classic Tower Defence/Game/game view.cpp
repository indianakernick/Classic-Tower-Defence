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
#include <Simpleton/Utils/profiler.hpp>
#include "tower aura rendering system.hpp"
#include "tower beam rendering system.hpp"
#include "unit death rendering system.hpp"
#include "unit health rendering system.hpp"
#include "tower range rendering system.hpp"
#include "tower projectile rendering system.hpp"

void GameView::init(G2D::Renderer &renderer) {
  camera.transform.setOrigin(Cam2D::Origin::BOTTOM_LEFT);
  camera.setPos({-4.0f, 0.0f});
  zoomToFit.setSize({20.0f, 11.25f});
  camera.transform.setSize({20.0f, 11.25f});
  
  sheetTex.load(renderer, "sprites");
}

void GameView::pushSounds(ECS::Registry &reg, SoundQueue &sounds) {
  towerSoundSystem(reg, sounds);
  unitDeathSoundSystem(reg, sounds);
}

void GameView::updateCam(const Cam2D::Params params) {
  camera.update(params, zoomToFit);
}

void GameView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  PROFILE(GameView::render);

  unitWalkAnimSystem(reg);
  unitDeathAnimSystem(reg);
  
  writer.section({camera.transform.toPixels(), sheetTex.tex()});
  mapRenderingSystem(reg, writer, sheetTex.sheet());
  unitRenderingSystem(reg, writer, sheetTex.sheet());
  towerRenderingSystem(reg, writer, sheetTex.sheet());
  towerBeamRenderingSystem(reg, writer, sheetTex.sheet());
  unitDeathRenderingSystem(reg, writer, sheetTex.sheet());
  towerAuraRenderingSystem(reg, writer, sheetTex.sheet());
  unitHealthRenderingSystem(reg, writer, sheetTex.sheet());
  towerProjectileRenderingSystem(reg, writer, sheetTex.sheet());
  
  /*writer.section({textCam.transform.toPixels(), textSheetTex.tex()});
  text.setCursor({100.0f, 338.0f});
  text.pushText(writer, textSheetTex.sheet(), "01234567890123456789\n");
  text.centerAlign("center");
  text.pushText(writer, textSheetTex.sheet(), "center");*/
}
