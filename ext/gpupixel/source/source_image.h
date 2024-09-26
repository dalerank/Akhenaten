/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include <string>

#include "source.h"
#include "../core/gl_program.h"

NS_GPUPIXEL_BEGIN

class SourceImage : public Source {
public:
    SourceImage();
    ~SourceImage();

    void init(int width, int height, int channel_count, const unsigned char *pixels);
    void init(int width, int height, int channel_count, int texid);
    static SourceImagePtr create(const std::string name);

    static SourceImagePtr create_from_memory(int width, int height, int channel_count, const unsigned char *pixels);
private:

#if defined(GPUPIXEL_ANDROID)
    static std::shared_ptr<SourceImage> createImageForAndroid(std::string name);
#endif

    GLProgram *_displayProgram = nullptr;
    GLuint _positionAttribLocation;
    GLuint _texCoordAttribLocation;
    GLuint _colorMapUniformLocation;
    struct { float r, g, b, a; } _backgroundColor;
};

NS_GPUPIXEL_END
