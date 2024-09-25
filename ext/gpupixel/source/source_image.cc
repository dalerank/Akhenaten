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

    CHECK_GL(glCopyImageSubData(_framebuffer->getTexture(), GL_TEXTURE_2D, 0, /*src_x*/0, /*src_y*/0, 0, 
                                texid, GL_TEXTURE_2D, 0, /*dst_x*/0, /*dst_y*/0, 0,
                                width, height, 1));
}
