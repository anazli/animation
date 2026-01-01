#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

namespace core {
class Shader {
 public:
  enum ShaderType { VERTEX, FRAGMENT };
  Shader();
  Shader(const std::filesystem::path& vertex,
         const std::filesystem::path& fragment);
  ~Shader();
  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  void Bind();
  void Unbind();
  unsigned int GetAttribute(const std::string& name);
  unsigned int GetUniform(const std::string& name);
  unsigned int GetHandle();

 private:
  void Load(const std::filesystem::path& vertex,
            const std::filesystem::path& fragment);
  std::string ReadFile(const std::filesystem::path& path);
  unsigned int CompileShader(const std::string& shader, ShaderType type);
  bool LinkShaders(unsigned int vertex, unsigned int fragment);
  void PopulateAttributes();
  void PopulateUniforms();

  unsigned int m_handle;
  std::unordered_map<std::string, unsigned int> m_attributes;
  std::unordered_map<std::string, unsigned int> m_uniforms;
};
}  // namespace core
