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
class GPUPIXEL_API SphereRefractionFilter : public Filter {
 public:
  static std::shared_ptr<SphereRefractionFilter> Create();
  bool Init();
  virtual bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void setPositionX(float x);
  void setPositionY(float y);
  void SetRadius(float radius);
  void setRefractiveIndex(float refractive_index);

 protected:
  SphereRefractionFilter() {};

  // The position about which to apply the distortion, with a default of (0.5,
  // 0.5)
  Vector2 position_;

  // The radius of the distortion, ranging from 0.0 to 1.0, with a default of
  // 0.25
  float radius_;

  // The index of refraction for the sphere, with a default of 0.71
  float refractive_index_;
};

NS_GPUPIXEL_END
