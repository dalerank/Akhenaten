/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "filter_group.h"
#include "grayscale_filter.h"
#include "nearby_sampling3x3_filter.h"
#include "../core/gpupixel_macros.h"

NS_GPUPIXEL_BEGIN

class _SobelEdgeDetectionFilter;

class GPUPIXEL_API SobelEdgeDetectionFilter : public FilterGroup {
 public:
  static std::shared_ptr<SobelEdgeDetectionFilter> Create();
  ~SobelEdgeDetectionFilter();
  bool Init();

 protected:
  SobelEdgeDetectionFilter();

  std::shared_ptr<GrayscaleFilter> grayscale_filter_;
  std::shared_ptr<_SobelEdgeDetectionFilter> sobel_edge_detection_filter_;

  float edge_strength_;
};

class GPUPIXEL_API _SobelEdgeDetectionFilter : public NearbySampling3x3Filter {
 public:
  static std::shared_ptr<_SobelEdgeDetectionFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setEdgeStrength(float edge_strength);

 protected:
  _SobelEdgeDetectionFilter() {};

  float edge_strength_;
};

NS_GPUPIXEL_END
