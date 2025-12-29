#include "sample1.h"

void Sample1::Initialize() {
  m_rotation = 0.f;
  m_shader = std::make_unique<core::Shader>("shaders/basic.vert",
                                            "shaders/basic.frag");
  m_display_texture = std::make_unique<core::Texture>("assets/uv.png");

  m_vertex_position = std::make_unique<core::Attribute<Vec3f>>();
  m_vertex_normals = std::make_unique<core::Attribute<Vec3f>>();
  m_vertex_tex_coords = std::make_unique<core::Attribute<Vec2f>>();
  m_index_buffer = std::make_unique<core::IndexBuffer>();

  std::vector<Vec3f> positions;
  positions.push_back(Vec3f(-1.f, -1.f, 0.f));
  positions.push_back(Vec3f(-1.f, 1.f, 0.f));
  positions.push_back(Vec3f(1.f, -1.f, 0.f));
  positions.push_back(Vec3f(1.f, 1.f, 0.f));
  m_vertex_position->SetData(positions);

  std::vector<Vec3f> normals;
  normals.resize(4, Vec3f(0.f, 0.f, 1.f));
  m_vertex_normals->SetData(normals);

  std::vector<Vec2f> uvs;
  uvs.push_back(Vec2f(0.f, 0.f));
  uvs.push_back(Vec2f(0.f, 1.f));
  uvs.push_back(Vec2f(1.f, 0.f));
  uvs.push_back(Vec2f(1.f, 1.f));
  m_vertex_tex_coords->SetData(uvs);

  std::vector<unsigned int> indices;
  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);
  indices.push_back(2);
  indices.push_back(1);
  indices.push_back(3);
  m_index_buffer->SetData(indices);
}

void Sample1::Update(float delta_time) {
  m_rotation += delta_time * 45.f;
  while (m_rotation > 360.f) {
    m_rotation -= 360.f;
  }
}

void Sample1::Render(float aspect_ratio) {}
