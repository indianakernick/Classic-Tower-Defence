//
//  main.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "Game/app.hpp"
#include <Simpleton/SDL/mainloop.hpp>
#include <Simpleton/Utils/profiler.hpp>

#undef main

#include <Simpleton/Grid/morton.hpp>
#include <Simpleton/Time/benchmark.hpp>

int main() {
  bool success = true;
  TIME_BENCHMARK(Morton,
    for (uint64_t i = 0; i != 1'000'000; ++i) {
      if (i != Grid::toMorton(Grid::fromMorton(i))) {
        std::cout << "Failed: " << i << '\n';
        success = false;
      }
    }
  );
  
  if (success) {
    std::cout << "Succeeded\n";
  }


  /*App app;
  SDL::runMainloop(&app);
  PROFILER_INFO(stdout);*/
  return 0;
}
