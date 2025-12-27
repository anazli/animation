#include <iostream>
#ifdef _WIN32
#include "windows.h"
#endif  // _WIN32

int main(int argc, const char** argv) {
#ifdef _WIN32
  return WinMain(GetModuleHandle(nullptr), nullptr, GetCommandLineA(),
                 SW_SHOWDEFAULT);
#endif  // _WIN32
}
