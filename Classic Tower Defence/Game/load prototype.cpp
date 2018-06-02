//
//  load prototype.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 7/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "load prototype.hpp"

#include "component list.hpp"
#include <Simpleton/Utils/type name.hpp>
#include <Simpleton/Type List/foreach.hpp>

namespace {
  template <typename Comp>
  constexpr auto hasFromjson(int) -> decltype(from_json(json{}, std::declval<Comp &>()), bool()) {
    return true;
  }

  template <typename Comp>
  constexpr bool hasFromjson(long) {
    return false;
  }
}

bool loadComponent(
  DefaultPrototype &proto,
  const std::string_view name,
  const json &component
) {
  bool read = false;
  List::forEach<CompList>([&proto, name, &component, &read] (auto t) {
    using Comp = LIST_TYPE(t);
    if (Utils::typeName<Comp>() == name) {
      if constexpr (hasFromjson<Comp>(0)) {
        proto.assign<Comp>(component.get<Comp>());
      } else {
        proto.assign<Comp>();
      }
      read = true;
    }
  });
  return read;
}

int loadProto(DefaultPrototype &proto, const json &entity) {
  const json::object_t &object = entity.get_ref<const json::object_t &>();
  int unreadCount = 0;
  for (auto pair : object) {
    unreadCount += !loadComponent(proto, pair.first, pair.second);
  }
  return unreadCount;
}
