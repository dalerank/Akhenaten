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

class GPUPIXEL_API DirectionalNonMaximumSuppressionFilter : public Filter {
 public:
  static std::shared_ptr<DirectionalNonMaximumSuppressionFilter> Create();
  bool Init();

  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

 protected:
  uint32_t texel_width_uniform_;
  uint32_t texel_height_uniform_;
  DirectionalNonMaximumSuppressionFilter() {};
};

NS_GPUPIXEL_END
