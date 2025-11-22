/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "sphere_refraction_filter.h"
#include "../gpupixel_define.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API GlassSphereFilter : public SphereRefractionFilter {
 public:
  static std::shared_ptr<GlassSphereFilter> Create();
  bool Init();

 protected:
  GlassSphereFilter() {};
};

NS_GPUPIXEL_END
