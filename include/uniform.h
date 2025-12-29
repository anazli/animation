#pragma once

#include <vector>

#include "glad/glad.h"
#include "math/mat4.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"

namespace core {
template <typename T>
class Uniform {
 public:
  Uniform() = delete;
  Uniform(const Uniform&) = delete;
  Uniform& operator=(const Uniform&) = delete;
  ~Uniform() = delete;

  static void SetData(unsigned int slot, T& value);
  static void SetData(unsigned int slot, std::vector<T>& vec);
  static void SetData(unsigned int slot, T* array, unsigned int length);
};

#define UNIFORM_IMPL(gl_func, T, D)                                           \
  template <>                                                                 \
  void Uniform<T>::SetData(unsigned int slot, T* data, unsigned int length) { \
    gl_func(slot, static_cast<GLsizei>(length), reinterpret_cast<D*>(data));  \
  }

template Uniform<int>;
template Uniform<float>;
template Uniform<Vec2i>;
template Uniform<Vec2f>;
template Uniform<Vec3i>;
template Uniform<Vec3f>;
template Uniform<Vec4i>;
template Uniform<Vec4f>;
template Uniform<Mat4f>;
template <typename T>

inline void Uniform<T>::SetData(unsigned int slot, T& value) {
  SetData(slot, static_cast<T*>(&value), 1);
}

template <typename T>
inline void Uniform<T>::SetData(unsigned int slot, std::vector<T>& vec) {
  SetData(slot, &vec[0], static_cast<unsigned int>(vec.size()));
}

UNIFORM_IMPL(glUniform1iv, int, int)
UNIFORM_IMPL(glUniform2iv, Vec2i, int)
UNIFORM_IMPL(glUniform3iv, Vec3i, int)
UNIFORM_IMPL(glUniform4iv, Vec4i, int)
UNIFORM_IMPL(glUniform1fv, float, float)
UNIFORM_IMPL(glUniform2fv, Vec2f, float)
UNIFORM_IMPL(glUniform3fv, Vec3f, float)
UNIFORM_IMPL(glUniform4fv, Vec4f, float)

template <>
inline void Uniform<Mat4f>::SetData(unsigned int slot, Mat4f* array,
                                    unsigned int length) {
  glUniformMatrix4fv(slot, static_cast<GLsizei>(length), false,
                     reinterpret_cast<float*>(array));
}
}  // namespace core
