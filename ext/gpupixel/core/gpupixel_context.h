#pragma once

#include <mutex>
#include <functional>
#include "framebuffer_cache.h"
#include "gpupixel_macros.h"
#include "../utils/dispatch_queue.h"

#include "filter.h"
#include "gl_program.h"
#include "opengl3_loader.h"

class Filter;

NS_GPUPIXEL_BEGIN

class GPUPIXEL_API GPUPixelContext {
 public:
  static GPUPixelContext* getInstance();
  static void destroy();

  FramebufferCache* getFramebufferCache() const;
  //todo(zhaoyou)
  void setActiveShaderProgram(GLProgram* shaderProgram);
  void purge();

  void runSync(std::function<void(void)> func);
  void runAsync(std::function<void(void)> func);
  void useAsCurrent(void);
  void presentBufferForDisplay();

  static void initOpengl();
 
#if defined(GPUPIXEL_MAC)
  NSOpenGLContext* getOpenGLContext() const { return imageProcessingContext; };
#elif defined(GPUPIXEL_WIN) || defined(GPUPIXEL_LINUX)
  //GLFWwindow* GetGLContext() const { return gl_context_; };
#endif
 
  // used for capturing a processed frame data
  bool isCapturingFrame;
  std::shared_ptr<Filter> captureUpToFilter;
  unsigned char* capturedFrameData;
  int captureWidth;
  int captureHeight;

 private:
  GPUPixelContext();
  ~GPUPixelContext();

  void init();

  void createContext();
  void releaseContext();
 private:
  static GPUPixelContext* _instance;
  static std::mutex _mutex;
  FramebufferCache* _framebufferCache;
  GLProgram* _curShaderProgram;
  std::shared_ptr<LocalDispatchQueue> task_queue_;
  
#if defined(GPUPIXEL_ANDROID)
  bool context_inited = false;
  int m_surfacewidth;
  int m_surfaceheight;
  _gpu_context_t* m_gpu_context;
#elif defined(GPUPIXEL_MAC)
  NSOpenGLContext* imageProcessingContext;
  NSOpenGLPixelFormat* _pixelFormat;
#elif defined(GPUPIXEL_WIN) || defined(GPUPIXEL_LINUX)
  //GLFWwindow* gl_context_ = nullptr;
#endif

};

NS_GPUPIXEL_END
