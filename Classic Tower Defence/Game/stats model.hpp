//
//  stats model.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef stats_model_hpp
#define stats_model_hpp

#include <glm/vec2.hpp>
#include "stats table.hpp"
#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/ECS/prototype.hpp>

class StatsModel {
public:
  void selectTower(ECS::Registry &, size_t);
  void selectPreview(ECS::Registry &);
  void selectEntity(ECS::EntityID);
  void unselect();
  
  bool canBuy(ECS::Registry &, glm::ivec2);
  void buy(ECS::Registry &, glm::ivec2);
  void sell(ECS::Registry &);
  void upgrade(ECS::Registry &);
  
  bool hasTable() const;
  std::string getName(ECS::Registry &) const;
  StatsTable getTable(ECS::Registry &) const;
  
  bool hasButtons(ECS::Registry &) const;
  TowerButtons getButtons(ECS::Registry &) const;
  
private:
  // @TODO use varient when available
  ECS::EntityID entity = ECS::NULL_ENTITY;
  const ECS::Prototype *proto = nullptr;
};

#endif
