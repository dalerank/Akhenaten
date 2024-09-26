#pragma once

#include <functional>
#include <map>

#include "../target/target.h"

NS_GPUPIXEL_BEGIN

class Source {
public:
    Source();
    virtual ~Source();
    virtual SourcePtr addTarget(TargetPtr target);
    virtual SourcePtr addTarget(TargetPtr target, int texIdx);
#if defined(GPUPIXEL_IOS) || defined(GPUPIXEL_MAC)
    virtual Ptr addTarget(id<GPUPixelTarget> target);
#endif
    virtual void removeTarget(TargetPtr target);
    virtual void removeAllTargets();
    virtual bool hasTarget(const TargetPtr target) const;
    virtual std::map<TargetPtr, int> &getTargets() { return _targets; };

    virtual void setFramebuffer(FramebufferPtr fb, RotationMode outputRotation = RotationMode::NoRotation);
    virtual FramebufferPtr getFramebuffer() const;
    virtual void releaseFramebuffer(bool returnToCache = true);

    void setFramebufferScale(float framebufferScale) {
        _framebufferScale = framebufferScale;
    }
    int getRotatedFramebufferWidth() const;
    int getRotatedFramebufferHeight() const;

    virtual bool proceed(bool bUpdateTargets = true, int64_t frameTime = 0);
    virtual void updateTargets(int64_t frameTime);

    virtual unsigned char *captureAProcessedFrameData(FilterPtr upToFilter, int width = 0, int height = 0);

protected:
    FramebufferPtr _framebuffer;
    RotationMode _outputRotation;
    std::map<TargetPtr, int> _targets;
    float _framebufferScale;
};

NS_GPUPIXEL_END
