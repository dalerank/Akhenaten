/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "filter.h"
#include "../core/gpupixel_macros.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API BrightnessFilter : public Filter {
 public:
  static std::shared_ptr<BrightnessFilter> Create(float brightness = 0.0);
  bool Init(float brightness);
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setBrightness(float brightness);

 protected:
  BrightnessFilter() {};

  float brightness_factor_;
};

NS_GPUPIXEL_END
