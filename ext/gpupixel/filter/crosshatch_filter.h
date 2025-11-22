/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "filter.h"
#include "../gpupixel_define.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API CrosshatchFilter : public Filter {
 public:
  static std::shared_ptr<CrosshatchFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setCrossHatchSpacing(float cross_hatch_spacing);
  void setLineWidth(float line_width);

 protected:
  CrosshatchFilter() {};

  float cross_hatch_spacing_;
  float line_width_;
};

NS_GPUPIXEL_END
