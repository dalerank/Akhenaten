/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "face_makeup_filter.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API BlusherFilter : public FaceMakeupFilter {
 public:
  static std::shared_ptr<BlusherFilter> Create();
  bool Init() override;

 private:
  BlusherFilter();
};

NS_GPUPIXEL_END
