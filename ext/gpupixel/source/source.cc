#include "source.h"

#include "../core/gpupixel_context.h"
#include "../core/framebuffer.h"
#include "../utils/util.h"

#include "../../../src/core/profiler.h"

NS_GPUPIXEL_BEGIN

Source::Source() : _framebuffer(0), _outputRotation(RotationMode::NoRotation), _framebufferScale(1.0) {
}

Source::~Source() {
    removeAllTargets();
}

SourcePtr Source::addTarget(TargetPtr target) {
    int targetTexIdx = target->getNextAvailableTextureIndex();
    return addTarget(target, targetTexIdx);
}

SourcePtr Source::addTarget(TargetPtr target, int texIdx) {
    if (!hasTarget(target)) {
        _targets[target] = texIdx;
        target->setInputFramebuffer(_framebuffer, RotationMode::NoRotation, texIdx);
    }
    return std::dynamic_pointer_cast<Source>(target);
}

#if defined(GPUPIXEL_IOS) || defined(GPUPIXEL_MAC)
std::shared_ptr<Source> Source::addTarget(id<GPUPixelTarget> target) {
    auto ios_target = std::shared_ptr<Target>(new ObjcTarget(target));
    addTarget(ios_target);
    return 0;
}
#endif

bool Source::hasTarget(const TargetPtr target) const {
    if (_targets.find(target) != _targets.end()) {
        return true;
    } else {
        return false;
    }
}

void Source::removeTarget(TargetPtr target) {
    auto itr = _targets.find(target);
    if (itr != _targets.end()) {
        _targets.erase(itr);
    }
}

void Source::removeAllTargets() {
    _targets.clear();
}

bool Source::proceed(bool bUpdateTargets /* = true*/, int64_t frameTime /* = 0*/) {
    if (bUpdateTargets) {
        updateTargets(frameTime);
    }
    return true;
}

void Source::updateTargets(int64_t frameTime) {
    OZZY_PROFILER_FUNCTION();
    for (auto &it : _targets) {
        auto target = it.first;
        target->setInputFramebuffer(_framebuffer, _outputRotation, _targets[target]);
        if (target->isPrepared()) {
            target->update(frameTime);
            target->unPrepear();
        }
    }
}

unsigned char *Source::captureAProcessedFrameData(FilterPtr upToFilter, int width /* = 0*/, int height /* = 0*/) {
    if (GPUPixelContext::getInstance()->isCapturingFrame) {
        return 0;
    }

    if (width <= 0 || height <= 0) {
        if (!_framebuffer) {
            return 0;
        }
        width = getRotatedFramebufferWidth();
        height = getRotatedFramebufferHeight();
    }

    GPUPixelContext::getInstance()->isCapturingFrame = true;
    GPUPixelContext::getInstance()->captureWidth = width;
    GPUPixelContext::getInstance()->captureHeight = height;
    GPUPixelContext::getInstance()->captureUpToFilter = upToFilter;

    proceed(true);
    uint8_t *processedFrameData = GPUPixelContext::getInstance()->capturedFrameData.data();

    GPUPixelContext::getInstance()->capturedFrameData.resize(0);
    GPUPixelContext::getInstance()->captureWidth = 0;
    GPUPixelContext::getInstance()->captureHeight = 0;
    GPUPixelContext::getInstance()->isCapturingFrame = false;

    return processedFrameData;
}

void Source::setFramebuffer(FramebufferPtr fb, RotationMode outputRotation /* = RotationMode::NoRotation*/) {
    _framebuffer = fb;
    _outputRotation = outputRotation;
}

int Source::getRotatedFramebufferWidth() const {
    if (_framebuffer) {
        if (rotationSwapsSize(_outputRotation)) {
            return _framebuffer->getHeight();
        } else {
            return _framebuffer->getWidth();
        }
    } else {
        return 0;
    }
}

int Source::getRotatedFramebufferHeight() const {
    if (_framebuffer) {
        if (rotationSwapsSize(_outputRotation)) {
            return _framebuffer->getWidth();
        } else {
            return _framebuffer->getHeight();
        }
    } else {
        return 0;
    }
}

FramebufferPtr Source::getFramebuffer() const {
    return _framebuffer;
}

void Source::releaseFramebuffer(bool returnToCache /* = true*/) {}

NS_GPUPIXEL_END
