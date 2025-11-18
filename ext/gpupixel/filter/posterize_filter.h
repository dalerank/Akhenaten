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
class GPUPIXEL_API PosterizeFilter : public Filter {
 public:
  static std::shared_ptr<PosterizeFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setColorLevels(int color_levels);

 protected:
  PosterizeFilter() {};

  int color_levels_;
};

NS_GPUPIXEL_END
