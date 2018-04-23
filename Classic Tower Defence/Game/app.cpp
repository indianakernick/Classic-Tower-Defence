//
//  app.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "app.hpp"

#include <Simpleton/Utils/profiler.hpp>

#include <Simpleton/SDL/paths.hpp>
#include "map rendering system.hpp"
#include "init map info.hpp"
#include "spawner timing component.hpp"
#include "spawner state component.hpp"
#include "unit walk anim system.hpp"
#include "unit motion system.hpp"
#include "unit death system.hpp"
#include "spawner system.hpp"
#include "spawner timing system.hpp"
#include "unit rendering system.hpp"
#include "base damage system.hpp"

bool App::mainloop(const uint64_t deltaNano) {
  PROFILE(App::mainloop);
  const float deltaSec = deltaNano / 1'000'000'000.0f;
  
  const bool ok = input();
  update(deltaSec);
  render(deltaSec);
  
  return ok;
}

TileType tileChar(const char c) {
  switch (c) {
    case 's':
      return TileType::ENTRY;
    case 'b':
      return TileType::EXIT;
    case ' ':
      return TileType::PATH;
    case '=':
      return TileType::PLATFORM;
    default:
      assert(false);
  }
}

void setMap(Map &map, const std::string &str) {
  assert(str.size() == map.scalarSize());
  
  auto tileSize = map.tileSize();
  for (size_t i = 0; i != str.size(); ++i) {
    const Map::Pos pos = {i % tileSize.x, tileSize.y - i / tileSize.x - 1};
    const char c = str[i];
    map[pos] = tileChar(c);
  }
}

const char *testMap =
  "s              ="
  "============== ="
  "=        ===== ="
  "= ====== ===== ="
  "= ====== ===== ="
  "= ====== ===== ="
  "= ====== ===== ="
  "= ======       ="
  "= =============="
  "=              b"
;

void App::init() {
  PROFILE(App::init);

  {
    PROFILE(Open Window);
    windowLibrary = SDL::makeLibrary(SDL_INIT_EVENTS);
    window = SDL::makeWindow("Classic Tower Defence", 1280, 720);
    renderingContext.initLimitFPS(window.get(), 15);

    renderingContext.preRender();
    renderingContext.postRender();
    
    renderer.init();
  }
  
  SDL_PumpEvents();
  
  camera.transform.setOrigin(Cam2D::Origin::BOTTOM_LEFT);
  zoomToFit.setSize({20.0f, 11.25f});
  camera.setPos({-4.0f, 0.0f});
  
  map.resize({16, 10}, TileType::PLATFORM);
  setMap(map, testMap);
  
  initMapInfo(mapInfo, map);
  Wave::Group group;
  group.quantity = 10000;
  group.stats = {100.0f, 2.0f};
  group.sprite = {4, 8};
  wave.groups.push_back(group);
  
  GL::TexParams2D texParams;
  texParams.setWrap(GL_CLAMP_TO_EDGE);
  texParams.setFilter(GL_NEAREST);
  renderer.addTexture(SDL::getResDir() + "sprites.png", texParams);
  
  sheet = Unpack::makeSpritesheet(SDL::getResDir() + "sprites.atlas");
  
  const ECS::EntityID spawner = reg.create();
  auto &timing = reg.assign<SpawnerTiming>(spawner);
  timing.minTimeBetweenSpawns = 1.5f;
  timing.timeSinceLastSpawn = 1e10f;
  auto &state = reg.assign<SpawnerState>(spawner);
  state.currentGroup = 0;
  state.doneSpawning = false;
  state.numUnitsLeft = group.quantity;
}

void App::quit() {
  PROFILE(App::quit);

  renderer.quit();
  renderingContext.quit();
  window.reset();
  windowLibrary.reset();
}

bool App::input() {
  PROFILE(App::input);
  
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      
    }
  }
  return true;
}

void App::update(const float delta) {
  PROFILE(App::update);
  
  spawnerTimingSystem(reg, delta);
  spawnerSystem(reg, wave, mapInfo);
  
  unitMotionSystem(reg, mapInfo, delta);
  unitDeathSystem(reg);
  
  baseDamageSystem(reg, mapInfo);
}

void App::render(const float delta) {
  PROFILE(App::render);
  
  renderingContext.preRender();
  const glm::ivec2 windowSize = window.size();
  const float aspect = static_cast<float>(windowSize.x) / windowSize.y;
  camera.update({aspect, delta}, zoomToFit);
  
  unitWalkAnimSystem(reg);
  
  const MapSprites sprites {0};
  writer.clear();
  writer.section({camera.transform.toPixels()});
  mapRenderingSystem(map, writer, sheet, sprites);
  unitRenderingSystem(reg, writer, sheet);
  
  writer.render(renderer);
  
  renderingContext.postRender();
}
