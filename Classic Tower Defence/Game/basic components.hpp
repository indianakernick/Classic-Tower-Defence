//
//  basic components.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 3/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef basic_components_hpp
#define basic_components_hpp

#include <functional>
#include <Simpleton/Math/rect.hpp>

using Bounds = Math::RectPP<float>;
using ClickHandler = std::function<void ()>;

#endif
