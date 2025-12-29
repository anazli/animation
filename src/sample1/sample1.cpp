#include "sample1.h"

#include "draw.h"
#include "math/mat4.h"
#include "uniform.h"

Sample1::Sample1():core::Application() {}

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

void Sample1::Render(float aspect_ratio) {
  auto projection = perspective(60.f, aspect_ratio, 0.01f, 1000.f);
  auto view = Mat4f();
  view.LookAt(Vec3f(0.f, 0.f, -5.f), Vec3f(0.f, 0.f, 0.f),
              Vec3f(0.f, 1.f, 0.f));
  auto model = Mat4f(Vec4f(1.f, 1.f, 1.f, 1.f), Vec4f(1.f, 1.f, 1.f, 1.f),
                     Vec4f(1.f, 1.f, 1.f, 1.f), Vec4f(1.f, 1.f, 1.f, 1.f));
  auto light = Vec3f(0.f, 0.f, 1.f);

  m_shader->Bind();
  m_vertex_position->BindTo(m_shader->GetAttribute("position"));
  m_vertex_normals->BindTo(m_shader->GetAttribute("normal"));
  m_vertex_tex_coords->BindTo(m_shader->GetAttribute("texCoord"));

  core::Uniform<Mat4f>::SetData(m_shader->GetUniform("model"), model);
  core::Uniform<Mat4f>::SetData(m_shader->GetUniform("view"), view);
  core::Uniform<Mat4f>::SetData(m_shader->GetUniform("projection"), projection);
  core::Uniform<Vec3f>::SetData(m_shader->GetUniform("light"), light);
  m_display_texture->Set(m_shader->GetUniform("tex0"), 0.f);
  core::Draw(*m_index_buffer, core::PrimitiveType::TRIANGLES);
  m_display_texture->Unset(0);

  m_vertex_position->UnbindFrom(m_shader->GetAttribute("position"));
  m_vertex_normals->UnbindFrom(m_shader->GetAttribute("normal"));
  m_vertex_tex_coords->UnbindFrom(m_shader->GetAttribute("texCoord"));
  m_shader->Unbind();
}
