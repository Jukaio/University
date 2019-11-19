// HeliumRenderer.cc

#include "HeliumCore.h"

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#include <gl/gl.h>

#include <math.h>

extern Helium::Size win32_window_size();

namespace Helium
{
   static void opengl_check_errors()
   {
      GLenum err = glGetError();
      if (err != GL_NO_ERROR)
      {
         HELIUM_ASSERT(!"OpenGL error!");
      }
   }

   struct TextureResult
   {
      bool success_;
      GLuint handle_;
      GLenum error_;
   };

   TextureResult create_texture(int width, int height, const void *data)
   {
      GLuint id = 0;

      glGenTextures(1, &id);
      glBindTexture(GL_TEXTURE_2D, id);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glBindTexture(GL_TEXTURE_2D, 0);

      opengl_check_errors();

      /*GLenum err = glGetError();
      if (err != GL_NO_ERROR)
      {
         glDeleteTextures(1, &id);

         return { false, 0, err };
      }*/

      return { true, id, GL_NO_ERROR };
   }

   void destroy_texture(uint32 id)
   {
      glDeleteTextures(1, &id);
      opengl_check_errors();
   }

   void Renderer::set_screen_origin(Helium::Renderer::ScreenOrigin mode) const
   {
      Size size = win32_window_size();
      glViewport(0, 0, size.width_, size.height_);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      switch (mode)
      {
         case Helium::Renderer::CENTER:
         {
            GLdouble half_window_width = size.width_ * 0.5;
            GLdouble half_window_height = size.height_ * 0.5;

            glOrtho(-half_window_width,
                    half_window_width,
                    -half_window_height,
                    half_window_height,
                    -1.0,
                    1.0f);
         } break;
         case Helium::Renderer::TOP_LEFT:
         {
            glOrtho(0.0,
               (GLdouble)size.width_,
                    (GLdouble)size.height_,
                    0.0,
                    -1.0,
                    1.0f);
         } break;
      }
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
   }

   void Renderer::clear(const Color &color) const
   {
      GLclampf red = color.red_ / 255.0f;
      GLclampf green = color.green_ / 255.0f;
      GLclampf blue = color.blue_ / 255.0f;
      GLclampf alpha = color.alpha_ / 255.0f;

      glClearColor(red, green, blue, alpha);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      opengl_check_errors();
   }

   void Renderer::draw_point(const Vector2 &point, const Color &color) const
   {
      glColor4ubv((const GLubyte *)&color);
      glBegin(GL_POINTS);
      glVertex2f(point.x_, point.y_);
      glEnd();

      opengl_check_errors();
   }

   void Renderer::draw_line(const Vector2 &start, const Vector2 &end, const Color &color) const
   {
      glColor4ubv((const GLubyte *)&color);
      glBegin(GL_LINES);
      glVertex2f(start.x_, start.y_);
      glVertex2f(end.x_, end.y_);
      glEnd();

      opengl_check_errors();
   }

   void Renderer::draw_line_strip(const uint32 count, const Vector2 *lines, const Color &color) const
   {
      glColor4ubv((const GLubyte *)&color);
      glBegin(GL_LINE_STRIP);
      for (uint32 index = 0; index < count; index++)
      {
         glVertex2f(lines[index].x_, lines[index].y_);
      }
      glEnd();

      opengl_check_errors();
   }

   void Renderer::draw_circle(const Vector2 &center, const float radius, const Color &color) const
   {
      // source: http://slabode.exofire.net/circle_draw.shtml
      const int segment_count = (int)(radius * 0.35f) + 8;
      const float theta = 2 * 3.141592f / (float)segment_count;
      const float c = cosf(theta);
      const float s = sinf(theta);

      float t = 0.0f;
      float x = radius;
      float y = 0.0f;

      glColor4ubv((const GLubyte *)&color);
      glBegin(GL_LINE_LOOP);
      for (int index = 0; index < segment_count; index++)
      {
         glVertex2f(center.x_ + x, center.y_ + y);

         t = x;
         x = c * x - s * y;
         y = s * t + c * y;
      }
      glEnd();

      opengl_check_errors();
   }

   void Renderer::draw_rectangle(const Vector2 &start, const Vector2 &end, const Color &color) const
   {
      const Vector2 corners[] =
      {
         { start.x_, start.y_ },
         { end.x_  , start.y_ },
         { end.x_  ,   end.y_ },
         { start.x_,   end.y_ },
      };

      glColor4ubv((const GLubyte *)&color);
      glBegin(GL_LINE_LOOP);
      for (auto &vertex : corners)
      {
         glVertex2f(vertex.x_, vertex.y_);
      }
      glEnd();

      opengl_check_errors();
   }

   void Renderer::draw_image(const Image &image, const Vector2 &at) const
   {
      if (!image.handle_)
      {
         TextureResult result = create_texture(image.width_, image.height_, image.data_);
         HELIUM_ASSERT(result.success_);

         *const_cast<uint32 *>(&image.handle_) = result.handle_;
      }

      Vector2 to(at.x_ + image.width_, at.y_ + image.height_);

      glBindTexture(GL_TEXTURE_2D, image.handle_);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f);  glVertex2f(at.x_, at.y_);
      glTexCoord2f(1.0f, 0.0f);  glVertex2f(to.x_, at.y_);
      glTexCoord2f(1.0f, 1.0f);  glVertex2f(to.x_, to.y_);
      glTexCoord2f(0.0f, 1.0f);  glVertex2f(at.x_, to.y_);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, 0);

      opengl_check_errors();
   }
} // Helium
