//
//  sound id.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef sound_id_hpp
#define sound_id_hpp

#include <cstdint>

//@SIMPLETON

using SoundID = uint16_t;

enum class DupSound : uint8_t {
  /// Play all sounds regardless of duplicates
  PLAY,
  /// Remove contigious regions of duplicate sounds
  CULL_ROW,
  /// Remove all duplicate sounds from the queue
  CULL_ALL,
  /// Leave duplicate sounds in the queue to be played next tick
  PLAY_LATER
};

#endif
