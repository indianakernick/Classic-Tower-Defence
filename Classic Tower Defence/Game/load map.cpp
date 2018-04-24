//
//  load map.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load map.hpp"

#include <istream>
#include "map component.hpp"

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
      case EOF:
        throw std::runtime_error("Unexpected end of map file");
      default:
        throw std::runtime_error("Invalid character in map");
    }
  }
}

void loadMap(ECS::Registry &reg, std::istream &stream) {
  Map &map = reg.get<Map>();
  using Scalar = Map::Pos::value_type;
  const Scalar width = map.tileSize().x;
  for (Scalar y = map.tileSize().y - 1; y != Scalar(-1); --y) {
    for (Scalar x = 0; x != width; ++x) {
      map[{x, y}] = tileChar(stream.get());
    }
    if (stream.get() != '\n') {
      stream.unget();
    }
  }
}
