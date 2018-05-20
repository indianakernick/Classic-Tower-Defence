//
//  get wave info.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 20/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef get_wave_info_hpp
#define get_wave_info_hpp

#include <string>
#include <Simpleton/ECS/registry.hpp>

size_t getNumUnits(ECS::Registry &);
std::string getWaveStr(ECS::Registry &);

#endif
