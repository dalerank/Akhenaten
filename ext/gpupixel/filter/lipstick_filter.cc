/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "lipstick_filter.h"
#include "gpupixel_context.h"
#include "../source/source_image.h"

NS_GPUPIXEL_BEGIN

LipstickFilter::LipstickFilter() {}

std::shared_ptr<LipstickFilter> LipstickFilter::Create() {
  auto ret = std::shared_ptr<LipstickFilter>(new LipstickFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool LipstickFilter::Init() {
  std::string basePath = Util::getResourcePath("");
  std::string resPath = basePath.empty() ? "res" : (basePath + "/res");
  auto mouth = SourceImage::create(resPath + "/mouth.png");
  SetImageTexture(mouth);
  SetTextureBounds(FrameBounds{502.5, 710, 262.5, 167.5});
  return FaceMakeupFilter::Init();
}

NS_GPUPIXEL_END
