#pragma once

#include "application.h"
#include "attribute.h"
#include "index_buffer.h"
#include "shader.h"
#include "texture.h"

class Sample1 : public core::Application {
 public:
  Sample1();
  void Initialize() override;
  void Update(float delta_time) override;
  void Render(float aspect_ratio) override;

 private:
  std::unique_ptr<core::Shader> m_shader;
  std::unique_ptr<core::Attribute<Vec3f>> m_vertex_position;
  std::unique_ptr<core::Attribute<Vec3f>> m_vertex_normals;
  std::unique_ptr<core::Attribute<Vec2f>> m_vertex_tex_coords;
  std::unique_ptr<core::IndexBuffer> m_index_buffer;
  std::unique_ptr<core::Texture> m_display_texture;
  float m_rotation;
};