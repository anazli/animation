#pragma once

#include <filesystem>
#include <memory>

#include "glad/glad.h"

namespace core {
class Application {
 public:
  virtual ~Application() = default;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

  GLuint& GetVertexArrayObject();
  const GLuint& GetVertexArrayObject() const;

  virtual void Initialize();
  virtual void Update(float delta_time);
  virtual void Render(float aspect_ratio);
  virtual void Shutdown();

  static Application* Instance();
  static std::unique_ptr<Application> CreateSample1();
  static std::filesystem::path GetAssetsPath();
  static std::filesystem::path GetShadersPath();

 protected:
  Application();

  static std::unique_ptr<Application> m_instance;
  GLuint m_vertex_array_obj;
};
}  // namespace core
