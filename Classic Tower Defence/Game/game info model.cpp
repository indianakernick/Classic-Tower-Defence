//
//  game info model.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 2/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game info model.hpp"

#include "base gold tag.hpp"
#include "get wave info.hpp"
#include "level info tag.hpp"
#include "base health tag.hpp"

GameInfo getGameInfo(ECS::Registry &reg) {
  GameInfo info;
  info.wave = getWaveStr(reg);
  info.gold = reg.get<BaseGold>().gold;
  info.base = reg.get<BaseHealth>().health;
  const LevelInfo levelInfo = reg.get<LevelInfo>();
  info.level = levelInfo.level + 1;
  info.map = levelInfo.map + 1;
  info.units = static_cast<uint32_t>(getNumUnits(reg));
  return info;
}
