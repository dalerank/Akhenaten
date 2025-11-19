/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "single_component_gaussian_blur_filter.h"
#include <cmath>
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

SingleComponentGaussianBlurFilter::SingleComponentGaussianBlurFilter()
    : h_blur_filter_(nullptr), v_blur_filter_(nullptr) {}

SingleComponentGaussianBlurFilter::~SingleComponentGaussianBlurFilter() {}

std::shared_ptr<SingleComponentGaussianBlurFilter>
SingleComponentGaussianBlurFilter::Create(int radius /* = 4*/,
                                          float sigma /* = 2.0*/) {
  auto ret = std::shared_ptr<SingleComponentGaussianBlurFilter>(
      new SingleComponentGaussianBlurFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init(radius, sigma)) {
      ret.reset();
    }
  });
  return ret;
}

bool SingleComponentGaussianBlurFilter::Init(int radius, float sigma) {
  if (!FilterGroup::init()) {
    return false;
  }

  h_blur_filter_ = SingleComponentGaussianBlurMonoFilter::Create(
      SingleComponentGaussianBlurMonoFilter::HORIZONTAL, radius, sigma);
  v_blur_filter_ = SingleComponentGaussianBlurMonoFilter::Create(
      SingleComponentGaussianBlurMonoFilter::VERTICAL, radius, sigma);
  h_blur_filter_->addTarget(v_blur_filter_);
  addFilter(h_blur_filter_);

  registerProperty("radius", 4, "", [this](int& radius) { SetRadius(radius); });

  registerProperty("sigma", 2.0, "", [this](float& sigma) { setSigma(sigma); });

  return true;
}

void SingleComponentGaussianBlurFilter::SetRadius(int radius) {
  h_blur_filter_->SetRadius(radius);
  v_blur_filter_->SetRadius(radius);
}

void SingleComponentGaussianBlurFilter::setSigma(float sigma) {
  h_blur_filter_->setSigma(sigma);
  v_blur_filter_->setSigma(sigma);
}

NS_GPUPIXEL_END
