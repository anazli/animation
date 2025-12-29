#include "texture.h"

#include "glad/glad.h"
#include "stb/stb_image.h"

core::Texture::Texture() : m_width(0), m_height(0), m_channels(0) {
  glGenTextures(1, &m_handle);
}

core::Texture::Texture(const std::filesystem::path& path) {
  glGenTextures(1, &m_handle);
  Load(path);
}

core::Texture::~Texture() { glDeleteTextures(1, &m_handle); }

void core::Texture::Load(const std::filesystem::path& path) {
  glBindTexture(GL_TEXTURE_2D, m_handle);
  int width, height, channels;
  unsigned char* data =
      stbi_load(path.string().c_str(), &width, &height, &channels, 4);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  m_width = width;
  m_height = height;
  m_channels = channels;
}

void core::Texture::Set(unsigned int uniform, unsigned int texture_index) {
  glActiveTexture(GL_TEXTURE0 + texture_index);
  glBindTexture(GL_TEXTURE_2D, m_handle);
  glUniform1i(uniform, texture_index);
}

void core::Texture::Unset(unsigned int texture_index) {
  glActiveTexture(GL_TEXTURE0 + texture_index);
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE0);
}

unsigned int core::Texture::GetHandle() const { return m_handle; }
