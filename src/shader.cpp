#include "shader.h"

#include <fstream>
#include <iostream>

#include "glad/glad.h"

core::Shader::Shader() : m_handle(glCreateProgram()) {}

core::Shader::Shader(const std::filesystem::path& vertex,
                     const std::filesystem::path& fragment)
    : m_handle(glCreateProgram()) {
  Load(vertex, fragment);
}

core::Shader::~Shader() { glDeleteProgram(m_handle); }

void core::Shader::Load(const std::filesystem::path& vertex,
                        const std::filesystem::path& fragment) {
  auto vert_source = ReadFile(vertex);
  if (vert_source.empty()) {
    std::cout << "ERROR: Failed to read vertex shader file: " << vertex
              << std::endl;
    return;
  }

  auto frag_source = ReadFile(fragment);
  if (frag_source.empty()) {
    std::cout << "ERROR: Failed to read fragment shader file: " << fragment
              << std::endl;
    return;
  }

  unsigned int v = CompileShader(vert_source, VERTEX);
  unsigned int f = CompileShader(frag_source, FRAGMENT);

  if (LinkShaders(v, f)) {
    PopulateAttributes();
    PopulateUniforms();
  }
}

void core::Shader::Bind() { glUseProgram(m_handle); }

void core::Shader::Unbind() { glUseProgram(0); }

unsigned int core::Shader::GetAttribute(const std::string& name) {
  auto iter = m_attributes.find(name);
  if (iter == m_attributes.end()) {
    std::cout << "Bad attribute index!" << std::endl;
    return 0;
  }
  return iter->second;
}

unsigned int core::Shader::GetUniform(const std::string& name) {
  auto iter = m_uniforms.find(name);
  if (iter == m_uniforms.end()) {
    std::cout << "Bad uniform index!" << std::endl;
    return 0;
  }
  return iter->second;
}

unsigned int core::Shader::GetHandle() { return m_handle; }

std::string core::Shader::ReadFile(const std::filesystem::path& path) {
  std::ifstream file;
  file.open(path);
  std::stringstream content;
  content << file.rdbuf();
  file.close();
  return content.str();
}

unsigned int core::Shader::CompileShader(const std::string& shader,
                                         ShaderType type) {
  unsigned int handle = type == VERTEX ? glCreateShader(GL_VERTEX_SHADER)
                                       : glCreateShader(GL_FRAGMENT_SHADER);
  const char* source = shader.c_str();
  glShaderSource(handle, 1, &source, nullptr);
  glCompileShader(handle);
  int success = 0;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(handle, 512, nullptr, info_log);
    std::string str_type = type == VERTEX ? "vertex" : "fragment";
    std::cout << str_type << " shader compilation failed!" << std::endl;
    std::cout << "\t" << info_log << std::endl;
    glDeleteShader(handle);
    return 0;
  }
  return handle;
}

bool core::Shader::LinkShaders(unsigned int vertex, unsigned int fragment) {
  glAttachShader(m_handle, vertex);
  glAttachShader(m_handle, fragment);
  glLinkProgram(m_handle);
  int success = 0;
  glGetProgramiv(m_handle, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(m_handle, 512, nullptr, info_log);
    std::cout << "ERROR: Shader linking failed!" << std::endl;
    std::cout << "\t" << info_log << std::endl;
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return false;
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  return true;
}

void core::Shader::PopulateAttributes() {
  int count = -1;
  int length;
  char name[128];
  int size;
  GLenum type;
  glUseProgram(m_handle);
  glGetProgramiv(m_handle, GL_ACTIVE_ATTRIBUTES, &count);

  for (int i = 0; i < count; ++i) {
    memset(name, 0, sizeof(char) * 128);
    glGetActiveAttrib(m_handle, static_cast<GLuint>(i), 128, &length, &size,
                      &type, name);
    int attribute = glGetAttribLocation(m_handle, name);
    if (attribute >= 0) {
      m_attributes[name] = attribute;
    }
  }
  glUseProgram(0);
}

void core::Shader::PopulateUniforms() {
  int count = -1;
  int length;
  char name[128];
  int size;
  GLenum type;
  char test_name[256];
  glUseProgram(m_handle);
  glGetProgramiv(m_handle, GL_ACTIVE_UNIFORMS, &count);

  for (int i = 0; i < count; ++i) {
    memset(name, 0, sizeof(char) * 128);
    glGetActiveUniform(m_handle, static_cast<GLuint>(i), 128, &length, &size,
                       &type, name);
    int uniform = glGetUniformLocation(m_handle, name);
    if (uniform >= 0) {
      std::string uniform_name = name;
      std::size_t array_found = uniform_name.find('[');
      if (array_found != std::string::npos) {
        uniform_name.erase(uniform_name.begin() + array_found,
                           uniform_name.end());
        unsigned int uniform_index = 0;
        while (true) {
          memset(test_name, 0, sizeof(char) * 256);
          sprintf(test_name, "%s[%d]", uniform_name.c_str(), uniform_index++);
          int uniform_location = glGetUniformLocation(m_handle, test_name);
          if (uniform_location < 0) {
            break;
          }
          m_uniforms[test_name] = uniform_location;
        }
      }
      m_uniforms[uniform_name] = uniform;
    }
  }
  glUseProgram(0);
}
