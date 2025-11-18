/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "directional_non_maximum_suppression_filter.h"
#include "core/gpupixel_context.h"
#include "utils/util.h"
NS_GPUPIXEL_BEGIN

#if defined(GPUPIXEL_GLES_SHADER)
const std::string kDirectionalNonmaximumSuppressionFragmentShaderString =
    R"(
        precision mediump float;

        uniform sampler2D inputImageTexture;
        uniform highp float texelWidth;
        uniform highp float texelHeight;
        uniform mediump float upperThreshold;
        uniform mediump float lowerThreshold;

        varying highp vec2 textureCoordinate;

        void main() {
          vec3 currentGradientAndDirection =
              texture2D(inputImageTexture, textureCoordinate).rgb;
          vec2 gradientDirection =
              ((currentGradientAndDirection.gb * 2.0) - 1.0) *
              vec2(texelWidth, texelHeight);

          float firstSampledGradientMagnitude =
              texture2D(inputImageTexture,
                        textureCoordinate + gradientDirection)
                  .r;
          float secondSampledGradientMagnitude =
              texture2D(inputImageTexture,
                        textureCoordinate - gradientDirection)
                  .r;

          float multiplier = step(firstSampledGradientMagnitude,
                                  currentGradientAndDirection.r);
          multiplier = multiplier * step(secondSampledGradientMagnitude,
                                         currentGradientAndDirection.r);

          float thresholdCompliance = smoothstep(lowerThreshold, upperThreshold,
                                                 currentGradientAndDirection.r);
          multiplier = multiplier * thresholdCompliance;

          gl_FragColor = vec4(multiplier, multiplier, multiplier, 1.0);
        })";
#elif defined(GPUPIXEL_GL_SHADER)
const std::string kDirectionalNonmaximumSuppressionFragmentShaderString =
    R"(
        uniform sampler2D inputImageTexture; uniform float texelWidth;
        uniform float texelHeight;
        uniform float upperThreshold;
        uniform float lowerThreshold;

        varying vec2 textureCoordinate;

        void main() {
          vec3 currentGradientAndDirection =
              texture2D(inputImageTexture, textureCoordinate).rgb;
          vec2 gradientDirection =
              ((currentGradientAndDirection.gb * 2.0) - 1.0) *
              vec2(texelWidth, texelHeight);

          float firstSampledGradientMagnitude =
              texture2D(inputImageTexture,
                        textureCoordinate + gradientDirection)
                  .r;
          float secondSampledGradientMagnitude =
              texture2D(inputImageTexture,
                        textureCoordinate - gradientDirection)
                  .r;

          float multiplier = step(firstSampledGradientMagnitude,
                                  currentGradientAndDirection.r);
          multiplier = multiplier * step(secondSampledGradientMagnitude,
                                         currentGradientAndDirection.r);

          float thresholdCompliance = smoothstep(lowerThreshold, upperThreshold,
                                                 currentGradientAndDirection.r);
          multiplier = multiplier * thresholdCompliance;

          gl_FragColor = vec4(multiplier, multiplier, multiplier, 1.0);
        })";
#endif

std::shared_ptr<DirectionalNonMaximumSuppressionFilter>
DirectionalNonMaximumSuppressionFilter::Create() {
  auto ret = std::shared_ptr<DirectionalNonMaximumSuppressionFilter>(
      new DirectionalNonMaximumSuppressionFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool DirectionalNonMaximumSuppressionFilter::Init() {
  if (initWithFragmentShaderString(
          kDirectionalNonmaximumSuppressionFragmentShaderString)) {
    texel_width_uniform_ = _filterProgram->getUniformLocation("texelWidth");
    texel_height_uniform_ = _filterProgram->getUniformLocation("texelHeight");

    _filterProgram->setUniformValue("upperThreshold", (float)0.5);
    _filterProgram->setUniformValue("lowerThreshold", (float)0.1);

    return true;
  }
  return false;
}

bool DirectionalNonMaximumSuppressionFilter::proceed(bool updateSinks, int64_t frametime) {
  float texelWidth = 1.0 / _framebuffer->getWidth();
  float texelHeight = 1.0 / _framebuffer->getHeight();

  std::shared_ptr<GPUPixelFramebuffer> inputFramebuffer =
      _inputFramebuffers.begin()->second.frameBuffer;
  RotationMode inputRotation =
      _inputFramebuffers.begin()->second.rotationMode;

  if (rotationSwapsSize(inputRotation)) {
    texelWidth = 1.0 / _framebuffer->getHeight();
    texelHeight = 1.0 / _framebuffer->getWidth();
  }

  _filterProgram->setUniformValue(texel_width_uniform_, texelWidth);
  _filterProgram->setUniformValue(texel_height_uniform_, texelHeight);

  return Filter::proceed(updateSinks, frametime);
}

NS_GPUPIXEL_END
