#include "windows.h"

#include <iostream>

#include "application.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC,
                                                         const int*);
typedef const char*(WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int);
typedef int(WINAPI* PFNWGLGETSWAPINTERVALEXTPROC)(void);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, PSTR cmd_line,
                   int cmd_show) {
  auto application = core::Application::CreateSample1();
  WNDCLASSEX wndclass;
  wndclass.cbSize = sizeof(WNDCLASSEX);
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc = WndProc;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.hInstance = instance;
  wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
  wndclass.lpszMenuName = 0;
  wndclass.lpszClassName = "Win32 Game Window";
  RegisterClassEx(&wndclass);

  int screenWidth = GetSystemMetrics(SM_CXSCREEN);
  int screenHeight = GetSystemMetrics(SM_CYSCREEN);
  int clientWidth = 800;
  int clientHeight = 600;
  RECT windowRect;
  SetRect(&windowRect, (screenWidth / 2) - (clientWidth / 2),
          (screenHeight / 2) - (clientHeight / 2),
          (screenWidth / 2) + (clientWidth / 2),
          (screenHeight / 2) + (clientHeight / 2));

  DWORD style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |
                 WS_MAXIMIZEBOX);  // WS_THICKFRAME to resize
  AdjustWindowRectEx(&windowRect, style, FALSE, 0);
  HWND hwnd = CreateWindowEx(
      0, wndclass.lpszClassName, "Game Window", style, windowRect.left,
      windowRect.top, windowRect.right - windowRect.left,
      windowRect.bottom - windowRect.top, NULL, NULL, instance, cmd_line);
  HDC hdc = GetDC(hwnd);

  PIXELFORMATDESCRIPTOR pfd;
  memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 32;
  pfd.cStencilBits = 8;
  pfd.iLayerType = PFD_MAIN_PLANE;
  int pixelFormat = ChoosePixelFormat(hdc, &pfd);
  SetPixelFormat(hdc, pixelFormat, &pfd);

  HGLRC tempRC = wglCreateContext(hdc);
  wglMakeCurrent(hdc, tempRC);
  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
  wglCreateContextAttribsARB =
      (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress(
          "wglCreateContextAttribsARB");

  const int attribList[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB,
      3,
      WGL_CONTEXT_MINOR_VERSION_ARB,
      3,
      WGL_CONTEXT_FLAGS_ARB,
      0,
      WGL_CONTEXT_PROFILE_MASK_ARB,
      WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0,
  };

  HGLRC hglrc = wglCreateContextAttribsARB(hdc, 0, attribList);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(tempRC);
  wglMakeCurrent(hdc, hglrc);

  if (!gladLoadGL()) {
    std::cout << "Could not initialize GLAD\n";
  } else {
    std::cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor
              << " loaded\n";
  }

  PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT =
      (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress(
          "wglGetExtensionsStringEXT");
  bool swapControlSupported =
      strstr(_wglGetExtensionsStringEXT(), "WGL_EXT_swap_control") != 0;

  int vsynch = 0;
  if (swapControlSupported) {
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
        (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT =
        (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress(
            "wglGetSwapIntervalEXT");

    if (wglSwapIntervalEXT(1)) {
      std::cout << "Enabled vsynch\n";
      vsynch = wglGetSwapIntervalEXT();
    } else {
      std::cout << "Could not enable vsynch\n";
    }
  } else {  // !swapControlSupported
    std::cout << "WGL_EXT_swap_control not supported\n";
  }

  auto verter_array_obj = application->GetVertexArrayObject();
  glGenVertexArrays(1, &verter_array_obj);
  glBindVertexArray(verter_array_obj);

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);
  application->Initialize();

  DWORD lastTick = GetTickCount();
  MSG msg;
  while (true) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    DWORD thisTick = GetTickCount();
    float deltaTime = float(thisTick - lastTick) * 0.001f;
    lastTick = thisTick;
    if (application) {
      application->Update(deltaTime);
      RECT clientRect;
      GetClientRect(hwnd, &clientRect);
      clientWidth = clientRect.right - clientRect.left;
      clientHeight = clientRect.bottom - clientRect.top;
      glViewport(0, 0, clientWidth, clientHeight);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_CULL_FACE);
      glPointSize(5.0f);
      glBindVertexArray(verter_array_obj);

      glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
              GL_STENCIL_BUFFER_BIT);

      float aspect = (float)clientWidth / (float)clientHeight;
      application->Render(aspect);
      SwapBuffers(hdc);
      if (vsynch != 0) {
        glFinish();
      }
    }
  }  // End of game loop

  if (application) {
    std::cout << "Expected application to be null on exit\n";
  }

  return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
  auto application = core::Application::Instance();
  auto vertex_array_obj = application->GetVertexArrayObject();
  switch (iMsg) {
    case WM_CLOSE:
      if (application) {
        application->Shutdown();
        application = 0;
        DestroyWindow(hwnd);
      } else {
        std::cout << "Already shut down!\n";
      }
      break;
    case WM_DESTROY:
      if (vertex_array_obj != 0) {
        HDC hdc = GetDC(hwnd);
        HGLRC hglrc = wglGetCurrentContext();

        glBindVertexArray(0);
        glDeleteVertexArrays(1, &vertex_array_obj);
        vertex_array_obj = 0;

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hglrc);
        ReleaseDC(hwnd, hdc);

        PostQuitMessage(0);
      } else {
        std::cout << "Got multiple destroy messages\n";
      }
      break;
    case WM_PAINT:
    case WM_ERASEBKGND:
      return 0;
  }

  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}