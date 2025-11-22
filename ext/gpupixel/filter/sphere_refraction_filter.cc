/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "sphere_refraction_filter.h"
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

#if defined(GPUPIXEL_GLES_SHADER)
const std::string kSphereRefractionShaderString = R"(

    uniform sampler2D inputImageTexture; uniform highp vec2 center;
    uniform highp float radius;
    uniform highp float aspectRatio;
    uniform highp float refractiveIndex;

    varying highp vec2 textureCoordinate;

    void main() {
      highp vec2 textureCoordinateToUse =
          vec2(textureCoordinate.x,
               (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
      highp float distanceFromCenter = distance(center, textureCoordinateToUse);
      lowp float checkForPresenceWithinSphere =
          step(distanceFromCenter, radius);

      distanceFromCenter = distanceFromCenter / radius;

      highp float normalizedDepth =
          radius * sqrt(1.0 - distanceFromCenter * distanceFromCenter);
      highp vec3 sphereNormal =
          normalize(vec3(textureCoordinateToUse - center, normalizedDepth));

      highp vec3 refractedVector =
          refract(vec3(0.0, 0.0, -1.0), sphereNormal, refractiveIndex);

      gl_FragColor =
          texture2D(inputImageTexture, (refractedVector.xy + 1.0) * 0.5) *
          checkForPresenceWithinSphere;
    }

)";
#elif defined(GPUPIXEL_GL_SHADER)
const std::string kSphereRefractionShaderString = R"(

    uniform sampler2D inputImageTexture; uniform vec2 center;
    uniform float radius;
    uniform float aspectRatio;
    uniform float refractiveIndex;

    varying vec2 textureCoordinate;

    void main() {
      vec2 textureCoordinateToUse =
          vec2(textureCoordinate.x,
               (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
      float distanceFromCenter = distance(center, textureCoordinateToUse);
      float checkForPresenceWithinSphere = step(distanceFromCenter, radius);

      distanceFromCenter = distanceFromCenter / radius;

      float normalizedDepth =
          radius * sqrt(1.0 - distanceFromCenter * distanceFromCenter);
      vec3 sphereNormal =
          normalize(vec3(textureCoordinateToUse - center, normalizedDepth));

      vec3 refractedVector =
          refract(vec3(0.0, 0.0, -1.0), sphereNormal, refractiveIndex);

      gl_FragColor =
          texture2D(inputImageTexture, (refractedVector.xy + 1.0) * 0.5) *
          checkForPresenceWithinSphere;
    }

)";
#endif

std::shared_ptr<SphereRefractionFilter> SphereRefractionFilter::Create() {
  auto ret = std::shared_ptr<SphereRefractionFilter>(new SphereRefractionFilter());

  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool SphereRefractionFilter::Init() {
  if (!initWithFragmentShaderString(kSphereRefractionShaderString)) {
    return false;
  }

  setPositionX(0.5);
  registerProperty("positionX", position_.x,
                   "The position of x about which to apply the distortion, "
                   "with a default of 0.5",
                   [this](float& positionX) { setPositionX(positionX); });

  setPositionY(0.5);
  registerProperty("positionY", position_.y,
                   "The position of y about which to apply the distortion, "
                   "with a default of 0.5",
                   [this](float& positionY) { setPositionY(positionY); });

  SetRadius(0.25);
  registerProperty("radius", radius_,
                   "The radius of the distortion, ranging from 0.0 to 1.0, "
                   "with a default of 0.25",
                   [this](float& radius) { SetRadius(radius); });

  setRefractiveIndex(0.71);
  registerProperty(
      "refractiveIndex", refractive_index_,
      "The index of refraction for the sphere, with a default of 0.71",
      [this](float& refractiveIndex) { setRefractiveIndex(refractiveIndex); });

  return true;
}

bool SphereRefractionFilter::proceed(bool updateSinks, int64_t frametime) {
  _filterProgram->setUniformValue("center", position_);
  _filterProgram->setUniformValue("radius", radius_);
  _filterProgram->setUniformValue("refractiveIndex", refractive_index_);

  float aspectRatio = 1.0;
  std::shared_ptr<GPUPixelFramebuffer> firstInputFramebuffer =
      _inputFramebuffers.begin()->second.frameBuffer;
  aspectRatio = firstInputFramebuffer->getHeight() /
                (float)(firstInputFramebuffer->getWidth());
  _filterProgram->setUniformValue("aspectRatio", aspectRatio);

  return Filter::proceed(updateSinks, frametime);
}

void SphereRefractionFilter::setPositionX(float x) {
  position_.x = x;
}

void SphereRefractionFilter::setPositionY(float y) {
  position_.y = y;
}

void SphereRefractionFilter::SetRadius(float radius) {
  radius_ = radius;
}

void SphereRefractionFilter::setRefractiveIndex(float refractiveIndex) {
  refractive_index_ = refractiveIndex;
}

NS_GPUPIXEL_END
