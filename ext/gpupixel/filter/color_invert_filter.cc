/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "color_invert_filter.h"
#include "core/gpupixel_context.h"
NS_GPUPIXEL_BEGIN

const std::string kColorInvertFragmentShaderString = R"(

    uniform sampler2D inputImageTexture; varying highp vec2 textureCoordinate;

    void main() {
      lowp vec4 color = texture2D(inputImageTexture, textureCoordinate);
      gl_FragColor = vec4((1.0 - color.rgb), color.a);
    })";

std::shared_ptr<ColorInvertFilter> ColorInvertFilter::Create() {
  auto ret = std::shared_ptr<ColorInvertFilter>(new ColorInvertFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool ColorInvertFilter::Init() {
  if (!Filter::initWithFragmentShaderString(kColorInvertFragmentShaderString)) {
    return false;
  }
  return true;
}

bool ColorInvertFilter::proceed(bool updateSinks, int64_t frametime) {
  return Filter::proceed(updateSinks, frametime);
}

NS_GPUPIXEL_END
