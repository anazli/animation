#include "index_buffer.h"

#include "glad/glad.h"

core::IndexBuffer::IndexBuffer() : m_data_count(0) {
  glGenBuffers(1, &m_handle);
}

core::IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_handle); }

void core::IndexBuffer::SetData(unsigned int* data, unsigned int length) {
  m_data_count = length;
  unsigned int size = sizeof(unsigned int);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * m_data_count, data,
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void core::IndexBuffer::SetData(std::vector<unsigned int>& input) {
  SetData(&input[0], static_cast<unsigned int>(input.size()));
}

unsigned int core::IndexBuffer::GetHandle() const { return m_handle; }

unsigned int core::IndexBuffer::GetDataCount() const { return m_data_count; }
