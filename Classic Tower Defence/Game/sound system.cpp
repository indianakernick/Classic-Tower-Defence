//
//  sound system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 24/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "sound system.hpp"

void soundSystem(SoundQueue &queue, Sounds &sounds) {
  while (!queue.empty()) {
    sounds.at(queue.front()).play();
    queue.pop();
  }
}
