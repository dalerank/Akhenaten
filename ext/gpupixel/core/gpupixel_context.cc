#include "gpupixel_context.h"
#include "../utils/util.h"

#define IMGL3W_IMPL
#include "opengl3_loader.h"

NS_GPUPIXEL_BEGIN

GPUPixelContext *GPUPixelContext::_instance = 0;
std::mutex GPUPixelContext::_mutex;

GPUPixelContext::GPUPixelContext()
    : _curShaderProgram(0),
    isCapturingFrame(false),
    captureUpToFilter(0),
    capturedFrameData(0) {
    _framebufferCache = new FramebufferCache();
    task_queue_ = std::make_shared<LocalDispatchQueue>();
    init();
}

GPUPixelContext::~GPUPixelContext() {
    releaseContext();
    delete _framebufferCache;
}

GPUPixelContext *GPUPixelContext::getInstance() {
    if (!_instance) {
        std::unique_lock<std::mutex> lock(_mutex);
        if (!_instance) {
            _instance = new (std::nothrow) GPUPixelContext;
        }
    }
    return _instance;
};

void GPUPixelContext::destroy() {
    if (_instance) {
        delete _instance;
        _instance = 0;
    }
}

void GPUPixelContext::init() {
    runSync([=] {
        Util::Log("INFO", "start init GPUPixelContext");
        this->createContext();
    });
}

FramebufferCache *GPUPixelContext::getFramebufferCache() const {
    return _framebufferCache;
}

void GPUPixelContext::setActiveShaderProgram(GLProgram *shaderProgram) {
    if (_curShaderProgram != shaderProgram) {
        _curShaderProgram = shaderProgram;
        shaderProgram->use();
    }
}

void GPUPixelContext::purge() {
    _framebufferCache->purge();
}

void GPUPixelContext::createContext() {
}

void GPUPixelContext::initOpengl() {
    gpl3wInit();
}

void GPUPixelContext::useAsCurrent() {
}

void GPUPixelContext::presentBufferForDisplay() {
}

void GPUPixelContext::releaseContext() {
}

void GPUPixelContext::runSync(std::function<void(void)> func) {
    // todo fix android 
    task_queue_->add([=] () {
        useAsCurrent();
        func();
    });
    task_queue_->processOne();
}

NS_GPUPIXEL_END
