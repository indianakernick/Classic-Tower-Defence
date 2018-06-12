//
//  load map.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load map.hpp"

#include <fstream>
#include "map tag.hpp"
#include <Simpleton/SDL/paths.hpp>

namespace {
  TileType tileChar(const char c) {
    switch (c) {
      case 's':
        return TileType::ENTRY;
      case 'b':
        return TileType::EXIT;
      case ' ':
        return TileType::PATH;
      case '#':
        return TileType::PLATFORM;
      case 'x':
        return TileType::TREE;
      case EOF:
        throw std::runtime_error("Unexpected end of map file");
      default:
        throw std::runtime_error("Invalid character in map");
    }
  }
}

void loadMap(ECS::Registry &reg, const int mapID) {
  std::ifstream file(SDL::getResDir() + "map " + std::to_string(mapID) + ".txt");
  Map &map = reg.get<Map>();
  for (Grid::Coord y = map.height() - 1; y != Grid::Coord(-1); --y) {
    for (Grid::Coord x = 0; x != map.width(); ++x) {
      map[{x, y}] = tileChar(file.get());
    }
    if (file.get() != '\n') {
      file.unget();
    }
  }
}
