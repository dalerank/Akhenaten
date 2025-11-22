/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "blusher_filter.h"
#include "gpupixel_context.h"
#include "../source/source_image.h"

NS_GPUPIXEL_BEGIN

BlusherFilter::BlusherFilter() {}

std::shared_ptr<BlusherFilter> BlusherFilter::Create() {
  auto ret = std::shared_ptr<BlusherFilter>(new BlusherFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool BlusherFilter::Init() {
  std::string basePath = Util::getResourcePath("");
  std::string resPath = basePath.empty() ? "res" : (basePath + "/res");
  auto blusher = SourceImage::create(resPath + "/blusher.png");
  SetImageTexture(blusher);
  SetTextureBounds(FrameBounds{395, 520, 489, 209});
  return FaceMakeupFilter::Init();
}

NS_GPUPIXEL_END
