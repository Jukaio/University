// HeliumMain_Win32.cc

#include "HeliumCore.h"

#include <stdio.h>

#define WIN32_MEAN_AND_LEAN
#define NOMINMAX
#include <Windows.h>
#include <Windowsx.h>
#include <gl/gl.h>

// @global-state
static HWND global_window_handle = NULL;
static DWORD global_window_style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
static int global_window_width = 1024;
static int global_window_height = 640;
static bool opengl_vsync_enabled = false;

// @file
int load_file(const char *filename, unsigned char *&dst)
{
   DWORD size = 0;
   HANDLE handle = CreateFileA(filename,
                               GENERIC_READ,
                               FILE_SHARE_READ,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);
   if (handle == INVALID_HANDLE_VALUE)
   {
      goto on_error;
   }

   size = GetFileSize(handle, NULL);
   if (size == INVALID_FILE_SIZE)
   {
      goto on_error;
   }

   dst = new unsigned char[size];
   if (!dst)
   {
      goto on_error;
   }

   if (ReadFile(handle, dst, size, NULL, NULL) == FALSE)
   {
      goto on_error;
   }

   CloseHandle(handle);

   return size;

on_error:
   HELIUM_ASSERT(!"error reading file!");

   delete[] dst;
   dst = nullptr;

   CloseHandle(handle);

   return 0;
}

// @helper-functions
template <typename T> T min(T a, T b) { return a < b ? a : b; }
template <typename T> T max(T a, T b) { return a > b ? a : b; }

// @helper-structs
template <int N>
struct frame_timer_cache
{
   frame_timer_cache()
   {
      for (auto &value : values_)
         value = 1000.0f / 60.0f;
   }

   void push(float timing)
   {
      min_ = min(min_, timing);
      max_ = max(max_, timing);
      values_[index_] = timing;
      index_ = (index_ + 1) % N;
   }

   float average()
   {
      float result = 0.0f;
      for (auto &value : values_)
         result += value;
      return result / float(N);
   }

   int index_ = 0;
   float min_ = 1000.0f;
   float max_ = 0.0f;
   float values_[N] = {};
};

Helium::Size win32_window_size()
{
   return { global_window_width, global_window_height };
}

struct InputState
{
   struct
   {
      bool prev_[Helium::Keyboard::COUNT];
      bool curr_[Helium::Keyboard::COUNT];
   } keyboard_ = {};

   struct
   {
      int x_;
      int y_;
      bool prev_[Helium::Mouse::COUNT];
      bool curr_[Helium::Mouse::COUNT];
   } mouse_ = {};
};

// @windows
static int
win32_error_message(const char *message)
{
   MessageBoxA(NULL, message, "ERROR!", MB_OK | MB_ICONERROR);
   return 0;
}

static void 
win32_input_state_event(InputState &state, MSG msg)
{
   switch (msg.message)
   {
      case WM_MOUSEMOVE:
      {
         state.mouse_.x_ = GET_X_LPARAM(msg.lParam);
         state.mouse_.y_ = GET_Y_LPARAM(msg.lParam);
      } break;
      case WM_LBUTTONDOWN:
      case WM_LBUTTONUP:
      {
         bool down = (msg.message == WM_LBUTTONDOWN) ? true : false;
         state.mouse_.curr_[Helium::Mouse::LEFT] = down;
      } break;
      case WM_RBUTTONDOWN:
      case WM_RBUTTONUP:
      {
         bool down = (msg.message == WM_RBUTTONDOWN) ? true : false;
         state.mouse_.curr_[Helium::Mouse::RIGHT] = down;
      } break;
      case WM_KEYDOWN:
      case WM_KEYUP:
      {
         bool down = (msg.message == WM_KEYDOWN) ? true : false;
         state.keyboard_.curr_[0xFF & msg.wParam] = down;
      } break;
   }
}

static void
win32_input_state_keyboard(InputState &state, Helium::Keyboard &keyboard)
{
   for (int index = 0; index < Helium::Keyboard::COUNT; index++)
   {
      keyboard.key_[index].pressed_ = false;
      keyboard.key_[index].released_ = false;

      if (state.keyboard_.curr_[index] && !state.keyboard_.prev_[index])
      {
         if (state.keyboard_.curr_[index])
         {
            keyboard.key_[index].down_ = true;
            keyboard.key_[index].pressed_ = true;
         }
         else
         {
            keyboard.key_[index].down_ = false;
            keyboard.key_[index].released_ = true;
         }
      }

      state.keyboard_.prev_[index] = state.keyboard_.curr_[index];
   }
}

static void
win32_input_state_mouse(InputState &state, Helium::Mouse &mouse)
{
   mouse.x_ = state.mouse_.x_;
   mouse.y_ = state.mouse_.y_;

   for (int index = 0; index < Helium::Mouse::COUNT; index++)
   {
      mouse.button_[index].pressed_ = false;
      mouse.button_[index].released_ = false;

      if (state.mouse_.curr_[index] != state.mouse_.prev_[index])
      {
         if (state.mouse_.curr_[index])
         {
            mouse.button_[index].down_ = true;
            mouse.button_[index].pressed_ = true;
         }
         else
         {
            mouse.button_[index].down_ = false;
            mouse.button_[index].released_ = true;
         }
      }

      state.mouse_.prev_[index] = state.mouse_.curr_[index];
   }
}

static LRESULT CALLBACK
win32_main_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch (uMsg)
   {
      case WM_CLOSE:
         PostQuitMessage(0);
         break;
      default:
         return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }

   return 0;
}

static bool
win32_register_class(HINSTANCE hInstance, const wchar_t *class_name)
{
   WNDCLASSEX window_class = { 0 };
   window_class.cbSize = sizeof(WNDCLASSEXW);
   window_class.hInstance = hInstance;
   window_class.hbrBackground = CreateSolidBrush(0x00000000);
   window_class.lpfnWndProc = win32_main_proc;
   window_class.lpszClassName = class_name;
   window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
   window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
   if (!RegisterClassEx(&window_class))
      return false;

   return true;
}

static bool
win32_window_create(HWND *window_handle,
                    HINSTANCE hInstance,
                    const wchar_t *class_name,
                    const wchar_t *caption,
                    int width,
                    int height)
{
   RECT window_rect = { 0, 0, width, height };
   if (!AdjustWindowRect(&window_rect, global_window_style, 0))
      return false;

   int window_width = window_rect.right - window_rect.left;
   int window_height = window_rect.bottom - window_rect.top;
   *window_handle = CreateWindowEx(0,
                                   class_name,
                                   caption,
                                   global_window_style,
                                   CW_USEDEFAULT, CW_USEDEFAULT,
                                   window_width, window_height,
                                   NULL, NULL,
                                   hInstance,
                                   NULL);
   if (!*window_handle)
      return false;

   global_window_width = width;
   global_window_height = height;

   return true;
}

static bool
win32_create_opengl_context(HDC device_context_handle)
{
   PIXELFORMATDESCRIPTOR pfd = {};
   pfd.nSize = sizeof(pfd);
   pfd.nVersion = 1;
   pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
   pfd.iPixelType = PFD_TYPE_RGBA;
   pfd.cColorBits = 32;
   pfd.cDepthBits = 24;
   pfd.cStencilBits = 8;
   pfd.iLayerType = PFD_MAIN_PLANE;

   int pixel_format_index = ChoosePixelFormat(device_context_handle, &pfd);
   if (!SetPixelFormat(device_context_handle, pixel_format_index, &pfd))
      return false;

   HGLRC render_context_handle = wglCreateContext(device_context_handle);
   if (!wglMakeCurrent(device_context_handle, render_context_handle))
      return false;

   typedef BOOL WINAPI wglSwapIntervalEXT_t(int interval);
   wglSwapIntervalEXT_t *wglSwapIntervalEXT = (wglSwapIntervalEXT_t *)wglGetProcAddress("wglSwapIntervalEXT");
   if (wglSwapIntervalEXT)
      opengl_vsync_enabled = wglSwapIntervalEXT(1);

   glEnable(GL_TEXTURE_2D);

   //glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   //glEnableClientState(GL_VERTEX_ARRAY);
   //glEnableClientState(GL_COLOR_ARRAY);

   return true;
}

// @external-functions
extern void win32_create_debug_font();

// @entry-point
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
   const int window_width = 1280;
   const int window_height = 720;

   const wchar_t *class_name = L"heliumClassName";
   if (!win32_register_class(hInstance, class_name))
      return win32_error_message("could not register window class!");

   HWND window_handle = NULL;
   if (!win32_window_create(&window_handle,
                            hInstance,
                            class_name,
                            L"HELIUM",
                            window_width,
                            window_height))
   {
      return win32_error_message("could not create window!");
   }

   HDC device_context_handle = GetDC(window_handle);
   if (!win32_create_opengl_context(device_context_handle))
      return win32_error_message("could not create opengl context!");

   HGLRC render_context_handle = wglGetCurrentContext();
   (void)render_context_handle;

   win32_create_debug_font();

   // note: global variables
   global_window_handle = window_handle;

   // note: frame timing stuff
   long long timing_start_tick = 0;
   QueryPerformanceCounter((LARGE_INTEGER *)&timing_start_tick);
   long long timing_previous_tick = timing_start_tick;

   double timing_factor = 0.0;
   {
      LARGE_INTEGER frequency = { 0 };
      QueryPerformanceFrequency(&frequency);
      timing_factor = frequency.QuadPart / 1000.0;
   }

   InputState input_state;
   Helium::Mouse mouse;
   Helium::Keyboard keyboard;

   Helium::FileSystem file_system;

   Helium::Renderer renderer;
   Helium::Application *app = Helium::create_application();
   if (!app)
   {
      return win32_error_message("could not create application!");
   }

   if (!app->init(&file_system))
   {
      return win32_error_message("could not initialize application!");
   }

   ShowWindow(window_handle, SW_NORMAL);

   frame_timer_cache<64> frame_times;
   bool running = true;
   while (running)
   {
      // note: poll events
      MSG msg= { 0 };
      while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
         if (msg.message == WM_QUIT)
            running = false;

         win32_input_state_event(input_state, msg);

         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      win32_input_state_mouse(input_state, mouse);
      win32_input_state_keyboard(input_state, keyboard);

      // note: frame timing
      long long timing_current_tick = 0;
      QueryPerformanceCounter((LARGE_INTEGER *)&timing_current_tick);

      long long app_ticks = timing_current_tick - timing_start_tick;
      double app_time = (app_ticks / timing_factor) * 0.001;

      long long delta_ticks = timing_current_tick - timing_previous_tick;
      double deltatime = (delta_ticks / timing_factor) * 0.001;
      timing_previous_tick = timing_current_tick;

      // note: update application
      running = running && app->tick(app_time, 
                                     (float)deltatime,
                                     &mouse,
                                     &keyboard);

      // note: draw application
      app->draw(&renderer);

      // note: present back buffer (double buffering)
      SwapBuffers(device_context_handle);

      // note: we usually don't want to do this, but saving the 
      //       environment is a good thing!
      Sleep(10);

      // note: some extra information in the window title
      {
         frame_times.push((float)(deltatime * 1000.0));

         wchar_t window_title_ex[512] = { 0 };
         swprintf_s(window_title_ex,
                    sizeof(window_title_ex) / sizeof(wchar_t),
                    L"HELIUM [%dx%d, VSync: %s, Frame: %.3fms] (%d,%d)",
                    window_width,
                    window_height,
                    opengl_vsync_enabled ? L"on" : L"off",
                    frame_times.average(),
                    input_state.mouse_.x_,
                    input_state.mouse_.y_);
         SetWindowTextW(window_handle, window_title_ex);
      }
   }

   return 0;
}
