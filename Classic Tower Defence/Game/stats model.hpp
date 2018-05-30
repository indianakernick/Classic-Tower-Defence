//
//  stats model.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef stats_model_hpp
#define stats_model_hpp

#include <string_view>
#include "prototype.hpp"
#include <Simpleton/ECS/registry.hpp>

class StatsModel {
public:
  
  using TableRow = std::pair<std::string_view, float>;
  using Table = std::vector<TableRow>;
  
  void selectTower(ECS::Registry &, int);
  void selectPreview(ECS::Registry &);
  void unselect();
  
  bool hasTable() const;
  std::string getName(ECS::Registry &) const;
  Table getTable(ECS::Registry &) const;
  
private:
  // @TODO use varient when available
  ECS::EntityID entity = ECS::NULL_ENTITY;
  const DefaultPrototype *proto = nullptr;
};

#endif
