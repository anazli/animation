#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

#include "glad/glad.h"
#endif  // _WIN32

#include <iostream>

#include "application.h"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#endif  // _WIN32

int main(int argc, const char** argv) {
  return WinMain(GetModuleHandle(nullptr), nullptr, GetCommandLineA(),
                 SW_SHOWDEFAULT);
}
