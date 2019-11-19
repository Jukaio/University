// HeliumCore.h

#ifndef HELIUM_CORE_H_INCLUDED
#define HELIUM_CORE_H_INCLUDED

#define HELIUM_ASSERT(cond) if (!(cond)) { *(int *)0=0; }

namespace Helium
{
   // @primitive-typedefs
   typedef unsigned char uint8;
   typedef unsigned int  uint32;

   // @misc-types
   struct Point
   {
      int x_;
      int y_;
   };

   struct Size
   {
      int width_;
      int height_;
   };

   struct Rectangle
   {
      int x_;
      int y_;
      int width_;
      int height_;
   };

   struct Color
   {
      uint8 red_;
      uint8 green_;
      uint8 blue_;
      uint8 alpha_;
   };

   // @math-types
   struct Vector2
   {
      Vector2();
      Vector2(const Vector2 &rhs);
      Vector2(const float x, const float y);
      
      Vector2 operator-() const;
      Vector2 &operator=(const Vector2 &rhs);
      Vector2 operator+(const Vector2 &rhs) const;
      Vector2 operator-(const Vector2 &rhs) const;
      Vector2 operator*(const Vector2 &rhs) const;
      Vector2 operator*(const float rhs) const;
      Vector2 operator/(const float rhs) const;

      Vector2 perp_right() const;
      Vector2 perp_left() const;
      Vector2 unit() const;
      float length() const;
      float length_squared() const;
      float dot(const Vector2 &rhs) const;
      // note: this is also called perp-product
      float cross(const Vector2 &rhs) const;
      void normalize();
	  float distance(const Vector2& rhs) const;

      float x_;
      float y_;
   };

   struct Matrix3
   {
      static Matrix3 translate(const Vector2 &position);
      static Matrix3 translate(const float x, const float y);
      static Matrix3 scale(const Vector2 &axis);
      static Matrix3 scale(const float x, const float y);
      static Matrix3 rotate(const float degrees);

      Matrix3();
      Matrix3(const Matrix3 &rhs);
      Matrix3(const float m00, const float m01, const float m02,
              const float m10, const float m11, const float m12,
              const float m20, const float m21, const float m22);

      Matrix3 &operator=(const Matrix3 &rhs);
      Matrix3 operator*(const Matrix3 &rhs) const;

      Vector2 transform(const Vector2 &rhs) const;
      Vector2 transform_direction(const Vector2 &rhs) const;

      float m00_, m01_, m02_;
      float m10_, m11_, m12_;
      float m20_, m21_, m22_;
   };

   // @file-system
   struct FileSystem
   {
      bool exists(const char *filename) const;
      bool read(const char *filename, uint32 &size, uint8 *&dst)  const;
      bool write(const char *filename, uint32 size, const uint8 *src) const;
   };

   // @input
   struct Mouse
   {
      enum Button
      {
         LEFT,
         RIGHT,
         COUNT,
      };

      Mouse();

      int x_;
      int y_;
      struct
      {
         bool down_;
         bool pressed_;
         bool released_;
      } button_[COUNT] = {};
   };

   struct Keyboard
   {
      enum KeyCode
      {
         BACK = 0x08,
         TAB = 0x09,
         CLEAR = 0x0C,
         RETURN = 0x0D,
         SHIFT = 0x10,
         CONTROL = 0x11,
         MENU = 0x12,
         PAUSE = 0x13,
         CAPITAL = 0x14,
         KANA = 0x15,
         JUNJA = 0x17,
         FINAL = 0x18,
         HANJA = 0x19,
         ESCAPE = 0x1B,
         CONVERT = 0x1C,
         NONCONVERT = 0x1D,
         ACCEPT = 0x1E,
         MODECHANGE = 0x1F,
         SPACE = 0x20,
         PRIOR = 0x21,
         NEXT = 0x22,
         END = 0x23,
         HOME = 0x24,
         LEFT = 0x25,
         UP = 0x26,
         RIGHT = 0x27,
         DOWN = 0x28,
         SELECT = 0x29,
         PRINT = 0x2A,
         EXECUTE = 0x2B,
         SNAPSHOT = 0x2C,
         INSERT = 0x2D,
         DELETE = 0x2E,
         HELP = 0x2F,
         KEY_0 = 0x30,
         KEY_1 = 0x31,
         KEY_2 = 0x32,
         KEY_3 = 0x33,
         KEY_4 = 0x34,
         KEY_5 = 0x35,
         KEY_6 = 0x36,
         KEY_7 = 0x37,
         KEY_8 = 0x38,
         KEY_9 = 0x39,
         KEY_A = 0x41,
         KEY_B = 0x42,
         KEY_C = 0x43,
         KEY_D = 0x44,
         KEY_E = 0x45,
         KEY_F = 0x46,
         KEY_G = 0x47,
         KEY_H = 0x48,
         KEY_I = 0x49,
         KEY_J = 0x4A,
         KEY_K = 0x4B,
         KEY_L = 0x4C,
         KEY_M = 0x4D,
         KEY_N = 0x4E,
         KEY_O = 0x4F,
         KEY_P = 0x50,
         KEY_Q = 0x51,
         KEY_R = 0x52,
         KEY_S = 0x53,
         KEY_T = 0x54,
         KEY_U = 0x55,
         KEY_V = 0x56,
         KEY_W = 0x57,
         KEY_X = 0x58,
         KEY_Y = 0x59,
         KEY_Z = 0x5A,
         LWIN = 0x5B,
         RWIN = 0x5C,
         APPS = 0x5D,
         SLEEP = 0x5F,
         NUMPAD0 = 0x60,
         NUMPAD1 = 0x61,
         NUMPAD2 = 0x62,
         NUMPAD3 = 0x63,
         NUMPAD4 = 0x64,
         NUMPAD5 = 0x65,
         NUMPAD6 = 0x66,
         NUMPAD7 = 0x67,
         NUMPAD8 = 0x68,
         NUMPAD9 = 0x69,
         MULTIPLY = 0x6A,
         ADD = 0x6B,
         SEPARATOR = 0x6C,
         SUBTRACT = 0x6D,
         DECIMAL = 0x6E,
         DIVIDE = 0x6F,
         F1 = 0x70,
         F2 = 0x71,
         F3 = 0x72,
         F4 = 0x73,
         F5 = 0x74,
         F6 = 0x75,
         F7 = 0x76,
         F8 = 0x77,
         F9 = 0x78,
         F10 = 0x79,
         F11 = 0x7A,
         F12 = 0x7B,
         F13 = 0x7C,
         F14 = 0x7D,
         F15 = 0x7E,
         F16 = 0x7F,
         F17 = 0x80,
         F18 = 0x81,
         F19 = 0x82,
         F20 = 0x83,
         F21 = 0x84,
         F22 = 0x85,
         F23 = 0x86,
         F24 = 0x87,
         NUMLOCK = 0x90,
         SCROLL = 0x91,
         LSHIFT = 0xA0,
         RSHIFT = 0xA1,
         LCONTROL = 0xA2,
         RCONTROL = 0xA3,
         LMENU = 0xA4,
         RMENU = 0xA5,
         BROWSER_BACK = 0xA6,
         BROWSER_FORWARD = 0xA7,
         BROWSER_REFRESH = 0xA8,
         BROWSER_STOP = 0xA9,
         BROWSER_SEARCH = 0xAA,
         BROWSER_FAVORITES = 0xAB,
         BROWSER_HOME = 0xAC,
         VOLUME_MUTE = 0xAD,
         VOLUME_DOWN = 0xAE,
         VOLUME_UP = 0xAF,
         MEDIA_NEXT_TRACK = 0xB0,
         MEDIA_PREV_TRACK = 0xB1,
         MEDIA_STOP = 0xB2,
         MEDIA_PLAY_PAUSE = 0xB3,
         LAUNCH_MAIL = 0xB4,
         MEDIA_SELECT = 0xB5,
         LAUNCH_APP1 = 0xB6,
         LAUNCH_APP2 = 0xB7,
         OEM_1 = 0xBA,
         OEM_PLUS = 0xBB,
         OEM_COMMA = 0xBC,
         OEM_MINUS = 0xBD,
         OEM_PERIOD = 0xBE,
         OEM_2 = 0xBF,
         OEM_3 = 0xC0,
         ABNT_C1 = 0xC1,
         ABNT_C2 = 0xC2,
         OEM_4 = 0xDB,
         OEM_5 = 0xDC,
         OEM_6 = 0xDD,
         OEM_7 = 0xDE,
         OEM_8 = 0xDF,
         OEM_102 = 0xE2,
         PROCESSKEY = 0xE5,
         PACKET = 0xE7,
         ATTN = 0xF6,
         CRSEL = 0xF7,
         EXSEL = 0xF8,
         EREOF = 0xF9,
         PLAY = 0xFA,
         ZOOM = 0xFB,
         NONAME = 0xFC,
         PA1 = 0xFD,
         OEM_CLEAR = 0xFE,
         COUNT = 256,
         INVALID = 0xFFFF,
      };

      Keyboard();

      struct
      {
         bool down_;
         bool pressed_;
         bool released_;
      } key_[COUNT] = {};
   };

   // @image
   struct Image
   {
      // note: non-copyable
      Image(const Image &) = delete;
      Image(Image &&) = delete;
      Image &operator=(const Image &) = delete;
      Image &operator=(Image &&) = delete;

      Image();
      explicit Image(int width, int height);
      ~Image();

      bool is_valid();
      bool load(const FileSystem *file_system, const char *filename);
      bool create(int bytes_per_pixel, int width, int height);
      void destroy();

      int bytes_per_pixel_;
      int width_;
      int height_;
      uint8 *data_;
      uint32 handle_;
   };

   // @render-api
   struct Renderer
   {
      enum ScreenOrigin
      {
         CENTER,
         TOP_LEFT,
      };

      void set_screen_origin(ScreenOrigin mode) const;

      void clear(const Color &color) const;
      void draw_point(const Vector2 &point, const Color &color) const;
      void draw_line(const Vector2 &start, const Vector2 &end, const Color &color) const;
      void draw_line_strip(const uint32 count, const Vector2 *lines, const Color &color) const;
      void draw_circle(const Vector2 &center, const float radius, const Color &color) const;
      void draw_rectangle(const Vector2 &start, const Vector2 &end, const Color &color) const;
      void draw_image(const Image &image, const Vector2 &at) const;
      void draw_text(const Point &point, const Color &color, const char *format, ...) const;
   };

   // @application
   struct Application
   {
      virtual ~Application() {}

      virtual bool init(const FileSystem *file_system) = 0;
      virtual void exit() = 0;
      virtual bool tick(double apptime, 
                        float deltatime, 
                        const Mouse *mouse, 
                        const Keyboard *keyboard) = 0;
      virtual void draw(const Renderer *renderer) = 0;
   };

   Application *create_application();
} // Helium

#endif // HELIUM_CORE_H_INCLUDED
