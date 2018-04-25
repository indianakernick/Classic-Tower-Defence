//
//  game view.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game view.hpp"

#include "load sounds.hpp"
#include "sound system.hpp"
#include "tower sound system.hpp"
#include <Simpleton/SDL/paths.hpp>
#include "map rendering system.hpp"
#include "unit rendering system.hpp"
#include "unit walk anim system.hpp"
#include "tower rendering system.hpp"
#include "tower firing anim system.hpp"
#include "unit health rendering system.hpp"

void GameView::init(G2D::Renderer &renderer) {
  camera.transform.setOrigin(Cam2D::Origin::BOTTOM_LEFT);
  zoomToFit.setSize({20.0f, 11.25f});
  camera.setPos({-4.0f, 0.0f});
  
  GL::TexParams2D texParams;
  texParams.setWrap(GL_CLAMP_TO_EDGE);
  texParams.setFilter(GL_NEAREST);
  tex = renderer.addTexture(SDL::getResDir() + "sprites.png", texParams);
  
  sheet = Unpack::makeSpritesheet(SDL::getResDir() + "sprites.atlas");
  
  sounds = loadSounds();
}

void GameView::playSounds(ECS::Registry &reg) {
  towerSoundSystem(reg);
  soundSystem(reg, sounds);
}

void GameView::updateCam(const float aspect, const float delta) {
  camera.update({aspect, delta}, zoomToFit);
}

void GameView::render(ECS::Registry &reg, G2D::QuadWriter &writer) {
  unitWalkAnimSystem(reg);
  towerFiringAnimSystem(reg);
  
  writer.section({camera.transform.toPixels()});
  mapRenderingSystem(reg, writer, sheet);
  unitRenderingSystem(reg, writer, sheet);
  towerRenderingSystem(reg, writer, sheet);
  unitHealthRenderingSystem(reg, writer, sheet);
}
