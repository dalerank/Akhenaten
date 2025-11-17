/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#pragma once

#include <memory>

// version
#define GPUPIXEL_SDK_VERSION "v1.2.2"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
      #define GPUPIXEL_WIN
   #else
      //define something for Windows (32-bit only)
      #define GPUPIXEL_WIN
   #endif
#elif __ANDROID__
    // Below __linux__ check should be enough to handle Android,
    // but something may be unique to Android.
    #define GPUPIXEL_ANDROID
#elif __linux__
    // linux
    #define GPUPIXEL_LINUX
#elif __emscripten__
  #define GPUPIXEL_LINUX
#elif __unix__ // all unices not caught above
    // Unix
    #define GPUPIXEL_LINUX
#elif defined(_POSIX_VERSION)
    // POSIX
#   error "Unknown compiler"
    #define GPUPIXEL_POSIX
#else
#   error "Unknown compiler"
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define GPUPIXEL_API

//
#if defined(GPUPIXEL_MAC)
  #import <OpenGL/gl.h>
#elif defined(GPUPIXEL_ANDROID)
  #include <GLES3/gl3.h>
  #include <GLES3/gl3ext.h>
  #include <EGL/egl.h>
  #include <GLES/gl.h>
  #include <GLES/glext.h>
  #include <android/log.h>
  #include <jni.h>
#elif defined(GPUPIXEL_WIN)
#if defined(_WIN32) && !defined(APIENTRY)
#define APIENTRY __stdcall                  // It is customary to use APIENTRY for OpenGL function pointer declarations on all platforms.  Additionally, the Windows OpenGL header needs APIENTRY.
#endif
#if defined(_WIN32) && !defined(WINGDIAPI)
#define WINGDIAPI __declspec(dllimport)     // Some Windows OpenGL headers need this
#endif
#include <gl/GL.h>
#elif defined(GPUPIXEL_LINUX)
#include <GL/gl.h>
#endif

#define NS_GPUPIXEL_BEGIN namespace gpupixel {
#define NS_GPUPIXEL_END }
#define USING_NS_GPUPIXEL using namespace gpupixel;

// Pi
#define PI 3.14159265358979323846264338327950288

//------------- ENABLE_GL_CHECK Begin ------------ //
#define ENABLE_GL_CHECK true
#if ENABLE_GL_CHECK
  #define CHECK_GL(glFunc)                                                     \
  glFunc;                                                                      \
  {                                                                            \
    int e = glGetError();                                                      \
    if (e != 0) {                                                              \
      std::string errorString = "";                                            \
      switch (e) {                                                             \
        case GL_INVALID_ENUM:                                                  \
          errorString = "GL_INVALID_ENUM";                                     \
          break;                                                               \
        case GL_INVALID_VALUE:                                                 \
          errorString = "GL_INVALID_VALUE";                                    \
          break;                                                               \
        case GL_INVALID_OPERATION:                                             \
          errorString = "GL_INVALID_OPERATION";                                \
          break;                                                               \
        case GL_OUT_OF_MEMORY:                                                 \
          errorString = "GL_OUT_OF_MEMORY";                                    \
          break;                                                               \
        default:                                                               \
          break;                                                               \
      }                                                                        \
      gpupixel::Util::Log("ERROR", "GL ERROR 0x%04X %s in func:%s(), in file:%s, at line %i", e, \
                          errorString.c_str(), __FUNCTION__, __FILE__, __LINE__);        \
    }                                                                          \
  }
#else
  #define CHECK_GL(glFunc) glFunc;
#endif

NS_GPUPIXEL_BEGIN

enum RotationMode {
    NoRotation = 0,
    RotateLeft,
    RotateRight,
    FlipVertical,
    FlipHorizontal,
    RotateRightFlipVertical,
    RotateRightFlipHorizontal,
    Rotate180
};

class Source;
using SourcePtr = std::shared_ptr<Source>;

class SourceImage;
using SourceImagePtr = std::shared_ptr<SourceImage>;

class Target;
using TargetPtr = std::shared_ptr<Target>;

class Framebuffer;
using FramebufferPtr = std::shared_ptr<Framebuffer>;
// Compatibility alias for newer version of gpupixel library
using GPUPixelFramebuffer = Framebuffer;

class Source;
using SourcePtr = std::shared_ptr<Source>;

class Filter;
using FilterPtr = std::shared_ptr<Filter>;


NS_GPUPIXEL_END
