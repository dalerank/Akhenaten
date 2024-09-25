/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "source_image.h"
#include "../core/gpupixel_context.h"
#include "../utils/util.h"

#ifdef SOURCE_IMAGE_SBTI
#define STBI_NO_PSD
#include "stb_image.h"
#endif // SOURCE_IMAGE_SBTI

USING_NS_GPUPIXEL

SourceImage::SourceImage() {
    _displayProgram = GLProgram::createByShaderString(kDefaultVertexShader, kDefaultFragmentShader);
    _positionAttribLocation = _displayProgram->getAttribLocation("position");
    _texCoordAttribLocation = _displayProgram->getAttribLocation("inputTextureCoordinate");
    _colorMapUniformLocation = _displayProgram->getUniformLocation("textureCoordinate");
    GPUPixelContext::getInstance()->setActiveShaderProgram(_displayProgram);
    CHECK_GL(glEnableVertexAttribArray(_positionAttribLocation));
    CHECK_GL(glEnableVertexAttribArray(_texCoordAttribLocation));
    _backgroundColor = { 0.f, 1.f, 0.f, 0.f };
}

SourceImage::~SourceImage() {
    delete _displayProgram;
    _displayProgram = nullptr;
}

std::shared_ptr<SourceImage> SourceImage::create_from_memory(int width, int height, int channel_count, const unsigned char *pixels) {
    auto sourceImage = std::shared_ptr<SourceImage>(new SourceImage());
    sourceImage->init(width, height, channel_count, pixels);
    return sourceImage;
}

std::shared_ptr<SourceImage> SourceImage::create(const std::string name) {
#ifdef SOURCE_IMAGE_SBTI
    int width, height, channel_count;
    unsigned char *data = stbi_load(name.c_str(), &width, &height, &channel_count, 0);
    //   todo(logo info)
    if (data == nullptr) {
        Util::Log("SourceImage", "SourceImage: input data in null! file name: %s", name.c_str());
        return nullptr;
    }
    auto image = SourceImage::create_from_memory(width, height, channel_count, data);
    stbi_image_free(data);
    return image;
#else 
    return nullptr;
#endif // SOURCE_IMAGE_SBTI 
}

void SourceImage::init(int width, int height, int channel_count, const unsigned char *pixels) {
    if (!_framebuffer || (_framebuffer->getWidth() != width) || (_framebuffer->getHeight() != height)) {
        if (_framebuffer) {
            this->setFramebuffer(nullptr);
        }

        _framebuffer = GPUPixelContext::getInstance()->getFramebufferCache()->fetchFramebuffer(width, height, false);
        this->setFramebuffer(_framebuffer);
    }

    if (!pixels) {
        return;
    }
    
    CHECK_GL(glBindTexture(GL_TEXTURE_2D, this->getFramebuffer()->getTexture()));
    
    if (channel_count == 3) {
        CHECK_GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels));
    } else if (channel_count == 4) {
        CHECK_GL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels));
    }

    CHECK_GL(glBindTexture(GL_TEXTURE_2D, 0));
}

void SourceImage::init(int width, int height, int channel_count, int texid) {
    if (!_framebuffer || (_framebuffer->getWidth() != width) || (_framebuffer->getHeight() != height)) {
        if (_framebuffer) {
            this->setFramebuffer(nullptr);
        }

        _framebuffer = GPUPixelContext::getInstance()->getFramebufferCache()->fetchFramebuffer(width, height, false);
        this->setFramebuffer(_framebuffer);
    }

    GPUPixelContext::getInstance()->setActiveShaderProgram(_displayProgram);
    _framebuffer->active();

    static const GLfloat noRotationTextureCoordinates[] = {
      0.0f, 0.0f,
      1.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
    };

    float scaledWidth = 1.0;
    float scaledHeight = 1.0;

    const GLfloat _displayVertices[8] = {
        -scaledWidth,
        -scaledHeight,
        scaledWidth,
        -scaledHeight,
        -scaledWidth,
        scaledHeight,
        scaledWidth,
        scaledHeight
    };

    CHECK_GL(glClearColor(_backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a));
    CHECK_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    CHECK_GL(glActiveTexture(GL_TEXTURE0));
    CHECK_GL(glBindTexture(GL_TEXTURE_2D, texid));
    CHECK_GL(glUniform1i(_colorMapUniformLocation, 0));
    CHECK_GL(glVertexAttribPointer(_positionAttribLocation, 2, GL_FLOAT, 0, 0, _displayVertices));
    CHECK_GL(glVertexAttribPointer(_texCoordAttribLocation, 2, GL_FLOAT, 0, 0, noRotationTextureCoordinates));
    CHECK_GL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));

    _framebuffer->inactive();
}
