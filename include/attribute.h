#pragma once

#include <vector>

#include "glad/glad.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"

namespace core {
template <typename T>
class Attribute {
 public:
  Attribute();
  ~Attribute();
  Attribute(const Attribute&) = delete;
  Attribute& operator=(const Attribute&) = delete;

  void SetData(T* input, unsigned int length);
  void SetData(std::vector<T>& input);
  void BindTo(unsigned int slot);
  void UnbindFrom(unsigned int slot);
  unsigned int GetHandle() const;
  unsigned int GetDataCount() const;

  void SetAttribPointer(unsigned int slot);

 protected:
  unsigned int m_handle;
  unsigned int m_data_count;
};

template <typename T>
inline core::Attribute<T>::Attribute() : m_data_count(0) {
  glGenBuffers(1, &m_handle);
}

template <typename T>
core::Attribute<T>::~Attribute() {
  glDeleteBuffers(1, &m_handle);
}

template <typename T>
inline void Attribute<T>::SetData(T* input, unsigned int length) {
  m_data_count = length;
  unsigned int size = sizeof(T);
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glBufferData(GL_ARRAY_BUFFER, size * m_data_count, input, GL_STREAM_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <typename T>
inline void Attribute<T>::SetData(std::vector<T>& input) {
  SetData(&input[0], static_cast<unsigned int>(input.size()));
}

template <typename T>
inline void Attribute<T>::BindTo(unsigned int slot) {
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glEnableVertexAttribArray(slot);
  SetAttribPointer(slot);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <typename T>
inline void Attribute<T>::UnbindFrom(unsigned int slot) {
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glDisableVertexAttribArray(slot);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <typename T>
inline unsigned int Attribute<T>::GetHandle() const {
  return m_handle;
}

template <typename T>
inline unsigned int Attribute<T>::GetDataCount() const {
  return m_data_count;
}

template <>
inline void Attribute<int>::SetAttribPointer(unsigned int slot) {
  glVertexAttribIPointer(slot, 1, GL_INT, 0, (void*)0);
}

template <>
inline void Attribute<float>::SetAttribPointer(unsigned int slot) {
  glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, 0, 0);
}

template <>
inline void Attribute<Vec2f>::SetAttribPointer(unsigned int slot) {
  glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

template <>
inline void Attribute<Vec3f>::SetAttribPointer(unsigned int slot) {
  glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

template <>
inline void Attribute<Vec4f>::SetAttribPointer(unsigned int slot) {
  glVertexAttribPointer(slot, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

}  // namespace core