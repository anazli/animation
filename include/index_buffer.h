#pragma once

#include <vector>

namespace core {
class IndexBuffer {
 public:
  IndexBuffer();
  IndexBuffer(const IndexBuffer&) = delete;
  IndexBuffer& operator=(const IndexBuffer&) = delete;
  ~IndexBuffer();

  void SetData(unsigned int* data, unsigned int length);
  void SetData(std::vector<unsigned int>& input);

  unsigned int GetHandle() const;
  unsigned int GetDataCount() const;

 private:
  unsigned int m_handle;
  unsigned int m_data_count;
};
}  // namespace core