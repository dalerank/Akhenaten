/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "nearby_sampling3x3_filter.h"
#include "../core/gpupixel_macros.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API ToonFilter : public NearbySampling3x3Filter {
 public:
  static std::shared_ptr<ToonFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setThreshold(float threshold);
  void setQuantizatinLevels(float quantization_levels);

 protected:
  ToonFilter() {};

  float threshold_;
  float quantization_levels_;
};

NS_GPUPIXEL_END
