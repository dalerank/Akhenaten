/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "smooth_toon_filter.h"
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

SmoothToonFilter::SmoothToonFilter()
    : gaussian_blur_filter_(0), toon_filter_(0) {}

SmoothToonFilter::~SmoothToonFilter() {}

std::shared_ptr<SmoothToonFilter> SmoothToonFilter::Create() {
  auto ret = std::shared_ptr<SmoothToonFilter>(new SmoothToonFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool SmoothToonFilter::Init() {
  if (!FilterGroup::init()) {
    return false;
  }
  gaussian_blur_filter_ = GaussianBlurFilter::Create();
  toon_filter_ = ToonFilter::Create();
  gaussian_blur_filter_->addTarget(toon_filter_);
  addFilter(gaussian_blur_filter_);

  blur_radius_ = 2.0;
  setBlurRadius(blur_radius_);
  registerProperty("blurRadius", blur_radius_, "",
                   [this](float& blurRadius) { setBlurRadius(blurRadius); });

  toon_threshold_ = 0.2;
  registerProperty(
      "toonThreshold", toon_threshold_,
      "The threshold at which to apply the edges",
      [this](float& toonThreshold) { setToonThreshold(toonThreshold); });

  toon_quantization_levels_ = 10.0;
  registerProperty("toonQuantizationLevels", toon_quantization_levels_,
                   "The levels of quantization for the posterization of colors "
                   "within the scene",
                   [this](float& toonQuantizationLevels) {
                     setToonQuantizationLevels(toonQuantizationLevels);
                   });

  return true;
}

void SmoothToonFilter::setBlurRadius(int blurRadius) {
  blur_radius_ = blurRadius;
  gaussian_blur_filter_->SetRadius(blur_radius_);
}

void SmoothToonFilter::setToonThreshold(float toonThreshold) {
  toon_threshold_ = toonThreshold;
  toon_filter_->setThreshold(toon_threshold_);
}

void SmoothToonFilter::setToonQuantizationLevels(float toonQuantizationLevels) {
  toon_quantization_levels_ = toonQuantizationLevels;
  toon_filter_->setQuantizatinLevels(toon_quantization_levels_);
}

NS_GPUPIXEL_END
