#pragma once

#include <vector>

namespace core {
template <typename T>
class Attribute {
 public:
  Attribute();
  ~Attribute();
  Attribute(const Attribute&) = delete;
  Attribute& operator=(const Attribute&) = delete;

  void SetData(T* input, unsigned int length);
  void SetData(std::vector<T>& input);
  void BindTo(unsigned int slot);
  void UnbindFrom(unsigned int slot);
  unsigned int GetHandle() const;
  unsigned int GetDataCount() const;

 protected:
  unsigned int m_handle;
  unsigned int m_data_count;
};
}  // namespace core