#pragma once

#include <filesystem>

namespace core {
class Texture {
 public:
  Texture();
  Texture(const std::filesystem::path& path);
  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;
  ~Texture();

  void Load(const std::filesystem::path& path);
  void Set(unsigned int uniform, unsigned int texture_index);
  void Unset(unsigned int texture_index);
  unsigned int GetHandle() const;

 protected:
  unsigned int m_handle;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_channels;
};
}  // namespace core