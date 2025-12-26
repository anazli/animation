#pragma once

namespace core {
class Application {
 public:
  Application();
  virtual ~Application() = default;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

  virtual void Initialize();
  virtual void Update(float inDeltaTime);
  virtual void Render(float inAspectRation);
  virtual void Shutdown();

 private:
};
}  // namespace core
