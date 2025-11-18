/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "filter_group.h"
#include "../core/gpupixel_macros.h"

NS_GPUPIXEL_BEGIN

// Forward declarations
class BoxBlurFilter;
class BoxHighPassFilter;
class BeautyFaceUnitFilter;

class GPUPIXEL_API BeautyFaceFilter : public FilterGroup {
 public:
  static std::shared_ptr<BeautyFaceFilter> Create();

  ~BeautyFaceFilter();

  bool Init();

  void SetHighPassDelta(float highPassDelta);
  void SetSharpen(float sharpen);
  void SetBlurAlpha(float blurAlpha);
  void SetWhite(float white);
  void SetRadius(float sigma);

  virtual void setInputFramebuffer(
      FramebufferPtr framebuffer,
      RotationMode rotationMode = NoRotation,
      int texIdx = 0) override;

 private:
  BeautyFaceFilter();
  std::shared_ptr<BoxBlurFilter> box_blur_filter_;
  std::shared_ptr<BoxHighPassFilter> box_high_pass_filter_;
  std::shared_ptr<BeautyFaceUnitFilter> beauty_face_filter_;
};

NS_GPUPIXEL_END
