#pragma once

namespace core {
enum PrimitiveType {
  POINTS,
  LINE_STRIP,
  LINE_LOOP,
  LINES,
  TRIANGLES,
  TRIANGLE_STRIP,
  TRIANGLE_FAN
};

class IndexBuffer;

void Draw(IndexBuffer& index_buffer, PrimitiveType type);
void Draw(unsigned int vertex_count, PrimitiveType type);

void DrawInstanced(IndexBuffer& index_buffer, PrimitiveType type,
                   unsigned int instance_count);
void DrawInstanced(unsigned int vertex_count, PrimitiveType type,
                   unsigned int instance_count);
}  // namespace core