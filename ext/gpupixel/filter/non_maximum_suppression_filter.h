/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "nearby_sampling3x3_filter.h"
#include "../gpupixel_define.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API NonMaximumSuppressionFilter
    : public NearbySampling3x3Filter {
 public:
  static std::shared_ptr<NonMaximumSuppressionFilter> Create();
  bool Init();

 protected:
  NonMaximumSuppressionFilter() {};
};

NS_GPUPIXEL_END
