/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once
#include "filter.h"
#include "../gpupixel_define.h"
#include "../utils/math_toolbox.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API ColorMatrixFilter : public Filter {
 public:
  static std::shared_ptr<ColorMatrixFilter> Create();
  bool Init();

  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setIntensity(float intensity) { intensity_factor_ = intensity; }
  void setColorMatrix(Matrix4 color_matrix) { color_matrix_ = color_matrix; }

 protected:
  ColorMatrixFilter();

  float intensity_factor_;
  Matrix4 color_matrix_;
};

NS_GPUPIXEL_END
