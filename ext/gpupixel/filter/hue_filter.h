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
class GPUPIXEL_API HueFilter : public Filter {
 public:
  static std::shared_ptr<HueFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setHueAdjustment(float hue_adjustment);

 protected:
  HueFilter() {};

  float hue_adjustment_;
};

NS_GPUPIXEL_END
