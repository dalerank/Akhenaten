/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include <algorithm>
#include <cctype>
#include <string>

#include "gl_program.h"
#include "gpupixel_context.h"
#include "../utils/util.h"

NS_GPUPIXEL_BEGIN

std::vector<GLProgram*> GLProgram::_programs;

#if defined(GPUPIXEL_GL_SHADER)
// Desktop GLSL rejects GLSL-ES precision qualifiers. Mesa is strict about this
// (NVIDIA/AMD Windows drivers often accept them anyway). Also pin #version 120
// so a 3.x compatibility context still accepts attribute/varying/texture2D.
static std::string prepareDesktopShaderSource(const std::string& source) {
  std::string stripped;
  stripped.reserve(source.size() + 16);

  const size_t n = source.size();
  size_t i = 0;
  while (i < n) {
    auto isIdentChar = [](unsigned char c) {
      return std::isalnum(c) || c == '_';
    };
    auto matchKeyword = [&](const char* word, size_t len) -> bool {
      if (i + len > n || source.compare(i, len, word) != 0) {
        return false;
      }
      if (i > 0 && isIdentChar(static_cast<unsigned char>(source[i - 1]))) {
        return false;
      }
      if (i + len < n && isIdentChar(static_cast<unsigned char>(source[i + len]))) {
        return false;
      }
      return true;
    };

    if (matchKeyword("precision", 9)) {
      i += 9;
      while (i < n && source[i] != ';') {
        ++i;
      }
      if (i < n) {
        ++i;  // skip ';'
      }
      continue;
    }

    if (matchKeyword("highp", 5) || matchKeyword("mediump", 7) || matchKeyword("lowp", 4)) {
      if (source.compare(i, 5, "highp") == 0) {
        i += 5;
      } else if (source.compare(i, 7, "mediump") == 0) {
        i += 7;
      } else {
        i += 4;
      }
      while (i < n && (source[i] == ' ' || source[i] == '\t')) {
        ++i;
      }
      continue;
    }

    stripped.push_back(source[i]);
    ++i;
  }

  size_t start = stripped.find_first_not_of(" \t\r\n");
  if (start == std::string::npos || stripped.compare(start, 8, "#version") != 0) {
    stripped.insert(0, "#version 120\n");
  }
  return stripped;
}
#endif

GLProgram::GLProgram() : _program(-1) {
  _programs.push_back(this);
}

GLProgram::~GLProgram() {
  GPUPixelContext::getInstance()->runSync([=] {
    std::vector<GLProgram*>::iterator itr =
        std::find(_programs.begin(), _programs.end(), this);
    if (itr != _programs.end()) {
      _programs.erase(itr);
    }

    bool bDeleteProgram = (_program != -1);

    for (auto const& program : _programs) {
      if (bDeleteProgram) {
        if (_program == program->getID()) {
          bDeleteProgram = false;
          break;
        }
      }
    }

    if (bDeleteProgram) {
      glDeleteProgram(_program);
      _program = -1;
    }
  });
}

GLProgram* GLProgram::createByShaderString(
    const std::string& vertexShaderSource,
    const std::string& fragmentShaderSource) {
  GLProgram* ret = new (std::nothrow) GLProgram();
  if (ret) {
    if (!ret->_initWithShaderString(vertexShaderSource, fragmentShaderSource)) {
      delete ret;
      ret = 0;
    }
  }
  return ret;
}

bool GLProgram::_initWithShaderString(const std::string& vertexShaderSource,
                                      const std::string& fragmentShaderSource) {
#if defined(GPUPIXEL_GL_SHADER)
  const std::string preparedVertex = prepareDesktopShaderSource(vertexShaderSource);
  const std::string preparedFragment = prepareDesktopShaderSource(fragmentShaderSource);
  const char* vertexShaderSourceStr = preparedVertex.c_str();
  const char* fragmentShaderSourceStr = preparedFragment.c_str();
#else
  const char* vertexShaderSourceStr = vertexShaderSource.c_str();
  const char* fragmentShaderSourceStr = fragmentShaderSource.c_str();
#endif

  if (_program != -1) {
    CHECK_GL(glDeleteProgram(_program));
    _program = -1;
  }
  CHECK_GL(_program = glCreateProgram());

  CHECK_GL(GLuint vertShader = glCreateShader(GL_VERTEX_SHADER));
  CHECK_GL(glShaderSource(vertShader, 1, &vertexShaderSourceStr, NULL));
  CHECK_GL(glCompileShader(vertShader));

  GLint compileSuccess = GL_FALSE;
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compileSuccess);
  if (compileSuccess == GL_FALSE) {
    GLchar messages[256];
    glGetShaderInfoLog(vertShader, sizeof(messages), 0, &messages[0]);
#if defined(GPUPIXEL_IOS) || defined(GPUPIXEL_MAC)
    NSString* messageString = [NSString stringWithUTF8String:messages];
    NSLog(@"%@", messageString);
#endif
    gpupixel::Util::Log("ERROR", "GL ERROR GLProgram::_initWithShaderString vertex shader %s", messages);
    return false;
  }

  CHECK_GL(GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER));
  CHECK_GL(glShaderSource(fragShader, 1, &fragmentShaderSourceStr, NULL));
  CHECK_GL(glCompileShader(fragShader));

  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compileSuccess);
  if (compileSuccess == GL_FALSE) {
    GLchar messages[256];
    glGetShaderInfoLog(fragShader, sizeof(messages), 0, &messages[0]);
#if defined(GPUPIXEL_IOS) || defined(GPUPIXEL_MAC)
    NSString* messageString = [NSString stringWithUTF8String:messages];
    NSLog(@"%@", messageString);
#endif
    gpupixel::Util::Log("ERROR", "GL ERROR GLProgram::_initWithShaderString frag shader %s", messages);
    return false;
  }

  CHECK_GL(glAttachShader(_program, vertShader));
  CHECK_GL(glAttachShader(_program, fragShader));

  CHECK_GL(glLinkProgram(_program));

  GLint linkSuccess = GL_FALSE;
  glGetProgramiv(_program, GL_LINK_STATUS, &linkSuccess);
  if (linkSuccess == GL_FALSE) {
    GLchar messages[256];
    glGetProgramInfoLog(_program, sizeof(messages), 0, &messages[0]);
    gpupixel::Util::Log("ERROR", "GL ERROR GLProgram::_initWithShaderString link %s", messages);
    CHECK_GL(glDeleteShader(vertShader));
    CHECK_GL(glDeleteShader(fragShader));
    return false;
  }

  CHECK_GL(glDeleteShader(vertShader));
  CHECK_GL(glDeleteShader(fragShader));

  return true;
}

void GLProgram::use() {
  CHECK_GL(glUseProgram(_program));
}

GLuint GLProgram::getAttribLocation(const std::string& attribute) {
  return glGetAttribLocation(_program, attribute.c_str());
}

GLuint GLProgram::getUniformLocation(const std::string& uniformName) {
  return glGetUniformLocation(_program, uniformName.c_str());
}

void GLProgram::setUniformValue(const std::string& uniformName, int value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  setUniformValue(getUniformLocation(uniformName), value);
}

void GLProgram::setUniformValue(const std::string& uniformName, float value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  setUniformValue(getUniformLocation(uniformName), value);
}

void GLProgram::setUniformValue(const std::string& uniformName, Matrix4 value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  setUniformValue(getUniformLocation(uniformName), value);
}

void GLProgram::setUniformValue(const std::string& uniformName, Vector2 value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  setUniformValue(getUniformLocation(uniformName), value);
}

void GLProgram::setUniformValue(const std::string& uniformName, Matrix3 value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  setUniformValue(getUniformLocation(uniformName), value);
}

void GLProgram::setUniformValue(const std::string& uniformName,
                                const void* value,
                                int length) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  setUniformValue(getUniformLocation(uniformName), value, length);
}

void GLProgram::setUniformValue(int uniformLocation, int value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  CHECK_GL(glUniform1i(uniformLocation, value));
}

void GLProgram::setUniformValue(int uniformLocation, float value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  CHECK_GL(glUniform1f(uniformLocation, value));
}

void GLProgram::setUniformValue(int uniformLocation, Matrix4 value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  CHECK_GL(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, (GLfloat*)&value));
}

void GLProgram::setUniformValue(int uniformLocation, Vector2 value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  CHECK_GL(glUniform2f(uniformLocation, value.x, value.y));
}

void GLProgram::setUniformValue(int uniformLocation, Matrix3 value) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  CHECK_GL(glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, (GLfloat*)&value));
}

void GLProgram::setUniformValue(int uniformLocation,
                                const void* value,
                                int length) {
  GPUPixelContext::getInstance()->setActiveShaderProgram(this);
  CHECK_GL(glUniform1fv(uniformLocation, length, (GLfloat*)value));
}

NS_GPUPIXEL_END
