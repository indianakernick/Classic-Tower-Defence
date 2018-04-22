//
//  tower upgrades component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_upgrades_component_hpp
#define tower_upgrades_component_hpp

struct TowerProto;

struct TowerUpgradesBase {
  TowerProto *first;
  TowerProto *second;
};

struct TowerUpgrades {
  const TowerUpgradesBase *proto;
};

#endif
