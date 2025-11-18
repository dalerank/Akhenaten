/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once
#include "nearby_sampling3x3_filter.h"
#include "../gpupixel_define.h"
#include "../utils/math_toolbox.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API Convolution3x3Filter : public NearbySampling3x3Filter {
 public:
  virtual bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

 protected:
  Convolution3x3Filter() {};

  // The convolution kernel is a 3x3 matrix of values to apply to the pixel and
  // its 8 surrounding pixels.
  Matrix3 convolution_kernel_;
};

NS_GPUPIXEL_END
