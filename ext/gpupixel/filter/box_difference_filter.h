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
class GPUPIXEL_API BoxDifferenceFilter : public Filter {
 public:
  static std::shared_ptr<BoxDifferenceFilter> Create();
  ~BoxDifferenceFilter();
  bool Init();
  bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  //
  void SetDelta(float delta);

 protected:
  BoxDifferenceFilter();
  float delta_;
  uint32_t filter_texture_coordinate_attribute_;
  uint32_t filter_texture_coordinate_attribute2_;
};

NS_GPUPIXEL_END
