//
//  sound queue.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "sound queue.hpp"

#include <fstream>
#include <Simpleton/Data/json.hpp>
#include <Simpleton/SDL/paths.hpp>

void SoundQueue::load(const char *const filename) {
  std::ifstream file(SDL::getResDir() + filename);
  json node;
  file >> node;
  
  for (const json &j : node.at("files")) {
    sounds.push_back(SDL::loadWAV(
      (SDL::getResDir() + j.get<std::string>()).c_str()
    ));
  }
}

void SoundQueue::push(const SoundID id) {
  assert(id < sounds.size());
  ids.push_back(id);
}

void SoundQueue::clear() {
  ids.clear();
}

void SoundQueue::play(const DupSound dup) {
  switch (dup) {
    case DupSound::PLAY:
      playSounds();
      ids.clear();
      break;
    case DupSound::CULL_ROW:
      cullRow();
      playSounds();
      ids.clear();
      break;
    case DupSound::CULL_ALL:
      std::sort(ids.begin(), ids.end());
      cullRow();
      playSounds();
      ids.clear();
      break;
    case DupSound::PLAY_LATER: {
      std::sort(ids.begin(), ids.end());
      std::vector<SoundID> dups = collectDups();
      cullRow();
      playSounds();
      ids = std::move(dups);
      break;
    }
    
    default:
      assert(false);
  }
}

void SoundQueue::cullRow() {
  SoundID prev = -1;
  for (auto id = ids.cbegin(); id != ids.cend();) {
    const SoundID curr = *id;
    if (curr == prev) {
      id = ids.erase(id);
    } else {
      ++id;
    }
    prev = curr;
  }
}

void SoundQueue::playSounds() {
  for (const SoundID id : ids) {
    sounds[id].play();
  }
}

std::vector<SoundID> SoundQueue::collectDups() {
  std::vector<SoundID> dups;
  SoundID prev = -1;
  for (auto id = ids.cbegin(); id != ids.cend(); ++id) {
    const SoundID curr = *id;
    if (curr == prev) {
      dups.push_back(curr);
    }
    prev = curr;
  }
  return dups;
}
