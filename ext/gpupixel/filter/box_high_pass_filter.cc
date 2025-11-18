/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "box_high_pass_filter.h"
#include "core/gpupixel_context.h"
NS_GPUPIXEL_BEGIN

BoxHighPassFilter::BoxHighPassFilter() {}

BoxHighPassFilter::~BoxHighPassFilter() {}

std::shared_ptr<BoxHighPassFilter> BoxHighPassFilter::Create() {
  auto ret = std::shared_ptr<BoxHighPassFilter>(new BoxHighPassFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool BoxHighPassFilter::Init() {
  if (!FilterGroup::init()) {
    return false;
  }

  box_blur_filter_ = BoxBlurFilter::Create();
  addFilter(box_blur_filter_);

  box_difference_filter_ = BoxDifferenceFilter::Create();
  addFilter(box_difference_filter_);

  box_blur_filter_->addTarget(box_difference_filter_, 1);
  setTerminalFilter(box_difference_filter_);

  box_blur_filter_->SetTexelSpacingMultiplier(4);
  return true;
}

void BoxHighPassFilter::setInputFramebuffer(
    FramebufferPtr framebuffer,
    RotationMode rotationMode,
    int texIdx) {
  for (auto& filter : _filters) {
    filter->setInputFramebuffer(framebuffer, rotationMode, texIdx);
  }
}

void BoxHighPassFilter::SetRadius(float radius) {
  box_blur_filter_->SetRadius(radius);
}

void BoxHighPassFilter::SetDelta(float delta) {
  box_difference_filter_->SetDelta(delta);
}

NS_GPUPIXEL_END
