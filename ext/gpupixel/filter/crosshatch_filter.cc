/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "crosshatch_filter.h"
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

#if defined(GPUPIXEL_GLES_SHADER)
const std::string kCrosshatchFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; varying highp vec2 textureCoordinate;
    uniform highp float crossHatchSpacing;
    uniform highp float lineWidth;

    const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main() {
      highp float luminance =
          dot(texture2D(inputImageTexture, textureCoordinate).rgb, W);

      lowp vec4 colorToDisplay = vec4(1.0, 1.0, 1.0, 1.0);
      if (luminance < 1.00) {
        if (mod(textureCoordinate.x + textureCoordinate.y, crossHatchSpacing) <=
            lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.75) {
        if (mod(textureCoordinate.x - textureCoordinate.y, crossHatchSpacing) <=
            lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.50) {
        if (mod(textureCoordinate.x + textureCoordinate.y -
                    (crossHatchSpacing / 2.0),
                crossHatchSpacing) <= lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.3) {
        if (mod(textureCoordinate.x - textureCoordinate.y -
                    (crossHatchSpacing / 2.0),
                crossHatchSpacing) <= lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }

      gl_FragColor = colorToDisplay;
    })";
#elif defined(GPUPIXEL_GL_SHADER)
const std::string kCrosshatchFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; varying vec2 textureCoordinate;
    uniform float crossHatchSpacing;
    uniform float lineWidth;

    const vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main() {
      float luminance =
          dot(texture2D(inputImageTexture, textureCoordinate).rgb, W);

      vec4 colorToDisplay = vec4(1.0, 1.0, 1.0, 1.0);
      if (luminance < 1.00) {
        if (mod(textureCoordinate.x + textureCoordinate.y, crossHatchSpacing) <=
            lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.75) {
        if (mod(textureCoordinate.x - textureCoordinate.y, crossHatchSpacing) <=
            lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.50) {
        if (mod(textureCoordinate.x + textureCoordinate.y -
                    (crossHatchSpacing / 2.0),
                crossHatchSpacing) <= lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.3) {
        if (mod(textureCoordinate.x - textureCoordinate.y -
                    (crossHatchSpacing / 2.0),
                crossHatchSpacing) <= lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }

      gl_FragColor = colorToDisplay;
    })";
#else
const std::string kCrosshatchFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; varying vec2 textureCoordinate;
    uniform float crossHatchSpacing;
    uniform float lineWidth;

    const vec3 W = vec3(0.2125, 0.7154, 0.0721);

    void main() {
      float luminance =
          dot(texture2D(inputImageTexture, textureCoordinate).rgb, W);

      vec4 colorToDisplay = vec4(1.0, 1.0, 1.0, 1.0);
      if (luminance < 1.00) {
        if (mod(textureCoordinate.x + textureCoordinate.y, crossHatchSpacing) <=
            lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.75) {
        if (mod(textureCoordinate.x - textureCoordinate.y, crossHatchSpacing) <=
            lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.50) {
        if (mod(textureCoordinate.x + textureCoordinate.y -
                    (crossHatchSpacing / 2.0),
                crossHatchSpacing) <= lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }
      if (luminance < 0.3) {
        if (mod(textureCoordinate.x - textureCoordinate.y -
                    (crossHatchSpacing / 2.0),
                crossHatchSpacing) <= lineWidth) {
          colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
        }
      }

      gl_FragColor = colorToDisplay;
    })";
#endif

std::shared_ptr<CrosshatchFilter> CrosshatchFilter::Create() {
  auto ret = std::shared_ptr<CrosshatchFilter>(new CrosshatchFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool CrosshatchFilter::Init() {
  if (!initWithFragmentShaderString(kCrosshatchFragmentShaderString)) {
    return false;
  }

  setCrossHatchSpacing(0.03);
  registerProperty("crossHatchSpacing", cross_hatch_spacing_,
                   "The fractional width of the image to use as the spacing "
                   "for the crosshatch. The default is 0.03.",
                   [this](float& crossHatchSpacing) {
                     setCrossHatchSpacing(crossHatchSpacing);
                   });

  setLineWidth(0.003);
  registerProperty(
      "lineWidth", line_width_,
      "A relative width for the crosshatch lines. The default is 0.003.",
      [this](float& lineWidth) { setLineWidth(lineWidth); });
  return true;
}

bool CrosshatchFilter::proceed(bool updateSinks, int64_t frametime) {
  _filterProgram->setUniformValue("crossHatchSpacing", cross_hatch_spacing_);
  _filterProgram->setUniformValue("lineWidth", line_width_);
  return Filter::proceed(updateSinks, frametime);
}

void CrosshatchFilter::setCrossHatchSpacing(float crossHatchSpacing) {
  cross_hatch_spacing_ = crossHatchSpacing;
}

void CrosshatchFilter::setLineWidth(float lineWidth) {
  line_width_ = lineWidth;
}

NS_GPUPIXEL_END
