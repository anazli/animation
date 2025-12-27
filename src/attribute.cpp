#include "attribute.h"

#include "glad/glad.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"

template core::Attribute<int>;
template core::Attribute<float>;
template core::Attribute<Vec2D>;
template core::Attribute<Vec3D>;
template core::Attribute<Vec4D>;

template <typename T>
inline core::Attribute<T>::Attribute() : m_data_count(0) {
  glGenBuffers(1, &m_handle);
}

template <typename T>
core::Attribute<T>::~Attribute() {
  glDeleteBuffers(1, &m_handle);
}
