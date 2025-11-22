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

// Sketch filter is just the Sobel edge detection filter with the colors
// inverted.

class _SketchFilter;

class GPUPIXEL_API SketchFilter : public FilterGroup {
 public:
  ~SketchFilter();
  static std::shared_ptr<SketchFilter> Create();
  bool Init();

 protected:
  SketchFilter();

  std::shared_ptr<GrayscaleFilter> grayscale_filter_;
  std::shared_ptr<_SketchFilter> sketch_filter_;

  float edge_strength_;
};

class GPUPIXEL_API _SketchFilter : public NearbySampling3x3Filter {
 public:
  static std::shared_ptr<_SketchFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setEdgeStrength(float edge_strength);

 protected:
  _SketchFilter() {};

  float edge_strength_;
};

NS_GPUPIXEL_END
