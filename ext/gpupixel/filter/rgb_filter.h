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
class GPUPIXEL_API RGBFilter : public Filter {
 public:
  static std::shared_ptr<RGBFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setRedAdjustment(float red_adjustment);
  void setGreenAdjustment(float green_adjustment);
  void setBlueAdjustment(float blue_adjustment);

 protected:
  RGBFilter() {};

  float red_adjustment_;
  float green_adjustment_;
  float blue_adjustment_;
};

NS_GPUPIXEL_END
