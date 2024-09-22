/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include "../core/gl_program.h"
#include "target.h"

NS_GPUPIXEL_BEGIN
class TargetView : public Target {
 public:
  enum FillMode {
    Stretch = 0,  // Stretch to fill the view, and may distort the image
    PreserveAspectRatio = 1,  // preserve the aspect ratio of the image
    PreserveAspectRatioAndFill =
        2  // preserve the aspect ratio, and zoom in to fill the view
  };

 public:
  TargetView();
  ~TargetView();

  static std::shared_ptr<TargetView> create() { return std::make_shared<TargetView>(); }

  void init();
  virtual void setInputFramebuffer(std::shared_ptr<Framebuffer> framebuffer,
                                   RotationMode rotationMode = NoRotation,
                                   int texIdx = 0) override;
  void setFillMode(FillMode fillMode);
  void setMirror(bool mirror);
  void onSizeChanged(int width, int height);
  uint32_t getWidth() const { return _viewWidth; }
  uint32_t getHeight() const { return _viewHeight; }
  unsigned char *getPixels() { return _capturedFrameData; }
  uint32_t getDataSize() { return _viewWidth * _viewHeight * 4; }
  virtual void update(int64_t frameTime) override;

 private:
  std::shared_ptr<Framebuffer> _framebuffer;
  int _viewWidth;
  int _viewHeight;
  FillMode _fillMode;
  bool _mirror = false;
  GLProgram* _displayProgram;
  GLuint _positionAttribLocation;
  GLuint _texCoordAttribLocation;
  GLuint _colorMapUniformLocation;
  struct {
    float r;
    float g;
    float b;
    float a;
  } _backgroundColor;

  GLfloat _displayVertices[8];
  unsigned char *_capturedFrameData;

  void _updateDisplayVertices();
  const GLfloat* _getTexureCoordinate(RotationMode rotationMode);
};

NS_GPUPIXEL_END
