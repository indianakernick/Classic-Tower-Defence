//
//  spawner state component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef spawner_state_component_hpp
#define spawner_state_component_hpp

struct SpawnerState {
  enum State {
    STARTING,
    SPAWNING,
    FINISHED
  };

  size_t currentGroup;
  size_t numUnitsLeft;
  State state;
};

#endif
