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
class GPUPIXEL_API PixellationFilter : public Filter {
 public:
  static std::shared_ptr<PixellationFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setPixelSize(float pixel_size);

 protected:
  PixellationFilter() {};

  float pixel_size_;
};

NS_GPUPIXEL_END
