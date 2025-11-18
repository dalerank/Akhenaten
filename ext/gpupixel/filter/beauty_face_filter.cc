/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "beauty_face_filter.h"
#include "beauty_face_unit_filter.h"
#include "box_blur_filter.h"
#include "box_high_pass_filter.h"
#include "core/gpupixel_context.h"
NS_GPUPIXEL_BEGIN

BeautyFaceFilter::BeautyFaceFilter() {}

BeautyFaceFilter::~BeautyFaceFilter() {}

std::shared_ptr<BeautyFaceFilter> BeautyFaceFilter::Create() {
  auto ret = std::shared_ptr<BeautyFaceFilter>(new BeautyFaceFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool BeautyFaceFilter::Init() {
  if (!FilterGroup::init()) {
    return false;
  }

  box_blur_filter_ = BoxBlurFilter::Create();
  addFilter(box_blur_filter_);

  box_high_pass_filter_ = BoxHighPassFilter::Create();
  addFilter(box_high_pass_filter_);

  beauty_face_filter_ = BeautyFaceUnitFilter::Create();
  addFilter(beauty_face_filter_);

  box_blur_filter_->addTarget(beauty_face_filter_, 1);
  box_high_pass_filter_->addTarget(beauty_face_filter_, 2);

  setTerminalFilter(beauty_face_filter_);

  box_blur_filter_->SetTexelSpacingMultiplier(4);
  SetRadius(4);

  registerProperty("whiteness", 0.0f,
                   "The whiteness of filter with range between -1 and 1.",
                   [this](float& val) { SetWhite(val); });

  registerProperty("skin_smoothing", 0.0f,
                   "The smoothing of filter with range between -1 and 1.",
                   [this](float& val) { SetBlurAlpha(val); });
  return true;
}

void BeautyFaceFilter::setInputFramebuffer(
    FramebufferPtr framebuffer,
    RotationMode rotationMode,
    int texIdx) {
  for (auto& filter : _filters) {
    filter->setInputFramebuffer(framebuffer, rotationMode, texIdx);
  }
}

void BeautyFaceFilter::SetHighPassDelta(float highPassDelta) {
  box_high_pass_filter_->SetDelta(highPassDelta);
}

void BeautyFaceFilter::SetSharpen(float sharpen) {
  beauty_face_filter_->SetSharpen(sharpen);
}

void BeautyFaceFilter::SetBlurAlpha(float blurAlpha) {
  beauty_face_filter_->SetBlurAlpha(blurAlpha);
}

void BeautyFaceFilter::SetWhite(float white) {
  beauty_face_filter_->SetWhite(white);
}

void BeautyFaceFilter::SetRadius(float radius) {
  box_blur_filter_->SetRadius(radius);
  box_high_pass_filter_->SetRadius(radius);
}
NS_GPUPIXEL_END
