/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "filter.h"

NS_GPUPIXEL_BEGIN
class GPUPIXEL_API FaceReshapeFilter : public Filter {
 public:
  static std::shared_ptr<FaceReshapeFilter> Create();
  FaceReshapeFilter();
  ~FaceReshapeFilter();

  bool Init();
  bool proceed(bool updateSinks = true, int64_t frametime = 0) override;

  void SetFaceSlimLevel(float level);
  void SetEyeZoomLevel(float level);
  void SetFaceLandmarks(std::vector<float> landmarks);

 private:
  float thin_face_delta_ = 0.0;
  float big_eye_delta_ = 0.0;

  std::vector<float> face_landmarks_;
  int has_face_ = 0;
};

NS_GPUPIXEL_END
