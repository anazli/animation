#include "application.h"

std::unique_ptr<core::Application> core::Application::m_instance = nullptr;

GLuint& core::Application::GetVertexArrayObject() { return m_vertex_array_obj; }

const GLuint& core::Application::GetVertexArrayObject() const {
  return m_vertex_array_obj;
}

void core::Application::Initialize() {}

void core::Application::Update(float inDeltaTime) {}

void core::Application::Render(float inAspectRation) {}

void core::Application::Shutdown() {}

core::Application* core::Application::Instance() {
  if (!m_instance) {
    m_instance.reset(new Application());
  }
  return m_instance.get();
}

core::Application::Application() : m_vertex_array_obj(0) {}
