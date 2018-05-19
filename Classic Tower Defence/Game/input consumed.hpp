//
//  input consumed.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef input_consumed_hpp
#define input_consumed_hpp

#include <cstdint>

enum class InputConsumed : uint8_t {
  NO,
  YES
};

constexpr bool operator!(const InputConsumed input) {
  return !static_cast<bool>(input);
}

#endif
