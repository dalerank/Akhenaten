/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "gaussian_blur_filter.h"
#include <cmath>
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

GaussianBlurFilter::GaussianBlurFilter()
    : horizontal_blur_filter_(nullptr), vertical_blur_filter_(nullptr) {}

GaussianBlurFilter::~GaussianBlurFilter() {}

std::shared_ptr<GaussianBlurFilter> GaussianBlurFilter::Create(
    int radius /* = 4*/,
    float sigma /* = 2.0*/) {
  auto ret = std::shared_ptr<GaussianBlurFilter>(new GaussianBlurFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init(radius, sigma)) {
      ret.reset();
    }
  });
  return ret;
}

bool GaussianBlurFilter::Init(int radius, float sigma) {
  if (!FilterGroup::init()) {
    return false;
  }

  horizontal_blur_filter_ = GaussianBlurMonoFilter::Create(
      GaussianBlurMonoFilter::HORIZONTAL, radius, sigma);
  vertical_blur_filter_ = GaussianBlurMonoFilter::Create(
      GaussianBlurMonoFilter::VERTICAL, radius, sigma);
  horizontal_blur_filter_->addTarget(vertical_blur_filter_);
  addFilter(horizontal_blur_filter_);

  registerProperty("radius", 4, "", [this](int& radius) { SetRadius(radius); });

  registerProperty("sigma", 2.0, "", [this](float& sigma) { setSigma(sigma); });

  return true;
}

void GaussianBlurFilter::SetRadius(int radius) {
  horizontal_blur_filter_->SetRadius(radius);
  vertical_blur_filter_->SetRadius(radius);
}

void GaussianBlurFilter::setSigma(float sigma) {
  horizontal_blur_filter_->setSigma(sigma);
  vertical_blur_filter_->setSigma(sigma);
}

NS_GPUPIXEL_END
