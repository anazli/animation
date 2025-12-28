#include "draw.h"

#include <cassert>

#include "glad/glad.h"
#include "index_buffer.h"

namespace {
GLenum MapPrimitiveTypeToGLenum(core::PrimitiveType type) {
  switch (type) {
    case core::POINTS:
      return GL_POINTS;
    case core::LINE_STRIP:
      return GL_LINE_STRIP;
    case core::LINE_LOOP:
      return GL_LINE_LOOP;
    case core::LINES:
      return GL_LINES;
    case core::TRIANGLES:
      return GL_TRIANGLES;
    case core::TRIANGLE_STRIP:
      return GL_TRIANGLE_STRIP;
    case core::TRIANGLE_FAN:
      return GL_TRIANGLE_FAN;
    default:
      assert(false);
  }
}
}  // namespace

void core::Draw(IndexBuffer& index_buffer, PrimitiveType type) {
  auto handle = index_buffer.GetHandle();
  auto num_indices = index_buffer.GetDataCount();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
  glDrawElements(MapPrimitiveTypeToGLenum(type), num_indices, GL_UNSIGNED_INT,
                 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void core::Draw(unsigned int vertex_count, PrimitiveType type) {
  glDrawArrays(MapPrimitiveTypeToGLenum(type), 0, vertex_count);
}

void core::DrawInstanced(IndexBuffer& index_buffer, PrimitiveType type,
                         unsigned int instance_count) {
  auto handle = index_buffer.GetHandle();
  auto num_indices = index_buffer.GetDataCount();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
  glDrawElementsInstanced(MapPrimitiveTypeToGLenum(type), num_indices,
                          GL_UNSIGNED_INT, 0, instance_count);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void core::DrawInstanced(unsigned int vertex_count, PrimitiveType type,
                         unsigned int instance_count) {
  glDrawArraysInstanced(MapPrimitiveTypeToGLenum(type), 0, vertex_count,
                        instance_count);
}
