//
//  sound queue.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 26/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef sound_queue_hpp
#define sound_queue_hpp

#include <vector>
#include "sound id.hpp"
#include <Simpleton/SDL/chunk.hpp>

//@SIMPLETON

class SoundQueue {
public:
  SoundQueue() = default;
  SoundQueue(SoundQueue &&) = default;
  SoundQueue &operator=(SoundQueue &&) = default;
  
  void load(const char * = "sounds.json");
  void push(SoundID);
  void clear();
  void play(DupSound = DupSound::PLAY);
  
private:
  std::vector<SDL::Chunk> sounds;
  std::vector<SoundID> ids;
  
  void cullRow();
  void playSounds();
  std::vector<SoundID> collectDups();
};

#endif
