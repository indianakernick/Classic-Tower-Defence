cmake_minimum_required(VERSION 3.10)
project(Classic_Tower_Defence)

set(CMAKE_CXX_STANDARD 17)
set(EMSCRIPTEN_CC /usr/local/Cellar/emscripten/1.37.37/libexec/emcc)
set(CMAKE_CXX_COMPILER ${EMSCRIPTEN_CC})
set(CMAKE_C_COMPILER ${EMSCRIPTEN_CC})
set(RES_PATH /Users/indikernick/Library/Developer/Xcode/DerivedData/Classic_Tower_Defence-dcezwdbogljnithjukklclgyblij/Build/Products/Debug/Classic\ Tower\ Defence.app/Contents/Resources)

if (CMAKE_BUILD_TYPE MATCHES RELEASE)
    set(EXTRA_FLAGS "-O3 --closure 1")
else()
    set(EXTRA_FLAGS "-s DEMANGLE_SUPPORT=1")
endif()

set(LINKER_FLAGS " \
  ${EXTRA_FLAGS} \
  -s WASM=1 \
  -s USE_WEBGL2=1 \
  -s USE_SDL=2 \
  -s TOTAL_MEMORY=805306368 \
  -s DISABLE_EXCEPTION_CATCHING=0 \
  --pre-js '${PROJECT_SOURCE_DIR}/Webpage/init.js' \
  --shell-file '${PROJECT_SOURCE_DIR}/Webpage/index.html' \
  --preload-file '${RES_PATH}@/' \
")
set(CMAKE_CXX_FLAGS " \
  ${EXTRA_FLAGS} \
  -msse3 \
")

include_directories(/usr/local/include/)

set(SOURCE_FILES 
        "Classic Tower Defence/Game/create spawner.cpp"
        "Classic Tower Defence/Game/unit death system.cpp"
        "Classic Tower Defence/Game/game info model.cpp"
        "Classic Tower Defence/Game/game info view.cpp"
        "Classic Tower Defence/Game/splash damage system.cpp"
        "Classic Tower Defence/Game/tower beam rendering system.cpp"
        "Classic Tower Defence/Game/aura damage system.cpp"
        "Classic Tower Defence/Game/load map.cpp"
        "Classic Tower Defence/Game/cursor systems.cpp"
        "Classic Tower Defence/Game/tower reset rof system.cpp"
        "Classic Tower Defence/Game/base damage system.cpp"
        "Classic Tower Defence/Game/unit death sound system.cpp"
        "Classic Tower Defence/Game/unit motion system.cpp"
        "Classic Tower Defence/Game/count live units.cpp"
        "Classic Tower Defence/Game/tower beam anim system.cpp"
        "Classic Tower Defence/Game/load towers.cpp"
        "Classic Tower Defence/Game/turret damage system.cpp"
        "Classic Tower Defence/Game/tower sound system.cpp"
        "Classic Tower Defence/Game/load prototype.cpp"
        "Classic Tower Defence/Game/stats controller.cpp"
        "Classic Tower Defence/Game/unit rendering system.cpp"
        "Classic Tower Defence/Game/unit death anim system.cpp"
        "Classic Tower Defence/Game/tower aura rendering system.cpp"
        "Classic Tower Defence/Game/tower aim system.cpp"
        "Classic Tower Defence/Game/unit damage system.cpp"
        "Classic Tower Defence/Game/slow effect system.cpp"
        "Classic Tower Defence/Game/game logic.cpp"
        "Classic Tower Defence/Game/next wave.cpp"
        "Classic Tower Defence/Game/unit regen system.cpp"
        "Classic Tower Defence/Game/unit effect system.cpp"
        "Classic Tower Defence/Game/poison effect system.cpp"
        "Classic Tower Defence/Game/tower rendering system.cpp"
        "Classic Tower Defence/Game/load waves.cpp"
        "Classic Tower Defence/Game/tower projectile rendering system.cpp"
        "Classic Tower Defence/Game/unit health rendering system.cpp"
        "Classic Tower Defence/Game/unit walk anim system.cpp"
        "Classic Tower Defence/Game/init map info.cpp"
        "Classic Tower Defence/Game/load level.cpp"
        "Classic Tower Defence/Game/sound queue.cpp"
        "Classic Tower Defence/Game/unit death rendering system.cpp"
        "Classic Tower Defence/Game/tower rof system.cpp"
        "Classic Tower Defence/Game/stats view.cpp"
        "Classic Tower Defence/Game/spawner timing system.cpp"
        "Classic Tower Defence/Game/load base.cpp"
        "Classic Tower Defence/Game/stats model.cpp"
        "Classic Tower Defence/Game/spawner system.cpp"
        "Classic Tower Defence/Game/preview entity.cpp"
        "Classic Tower Defence/Game/game view.cpp"
        "Classic Tower Defence/Game/create tower.cpp"
        "Classic Tower Defence/Game/ui view.cpp"
        "Classic Tower Defence/Game/get wave info.cpp"
        "Classic Tower Defence/Game/firing anim system.cpp"
        "Classic Tower Defence/Game/create level.cpp"
        "Classic Tower Defence/Game/tower range rendering system.cpp"
        "Classic Tower Defence/Game/load spawner.cpp"
        "Classic Tower Defence/Game/map rendering system.cpp"
        "Classic Tower Defence/Game/app.cpp"
        "Classic Tower Defence/main.cpp"
)

add_executable(Classic_Tower_Defence ${SOURCE_FILES})
set_target_properties(Classic_Tower_Defence PROPERTIES OUTPUT_NAME index.html)
set_target_properties(Classic_Tower_Defence PROPERTIES LINK_FLAGS "${LINKER_FLAGS}")