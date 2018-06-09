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

void GameView::updateAnim(ECS::Registry &reg, float) {
  unitWalkAnimSystem(reg);
  unitDeathAnimSystem(reg);
}

void GameView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  PROFILE(GameView::render);
  
  G2D::Section &sec = writer.section(camera.transform.toPixels(), sheetTex);
  mapRenderingSystem(reg, sec);
  unitRenderingSystem(reg, sec);
  towerRenderingSystem(reg, sec);
  towerBeamRenderingSystem(reg, sec);
  unitDeathRenderingSystem(reg, sec);
  towerAuraRenderingSystem(reg, sec);
  unitHealthRenderingSystem(reg, sec);
  towerProjectileRenderingSystem(reg, sec);
}
