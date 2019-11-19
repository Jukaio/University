// HeliumImage.cc

#include "HeliumCore.h"

#include <string.h>

namespace Helium
{
#pragma pack(push,1)
   typedef unsigned short uint16;

   constexpr const uint16 BMP_SIGNATURE = 0x4D42;

   struct BMPFileHeader
   {
      uint16 signature_;
      uint32 size_;
      uint32 reserved_;
      uint32 offset_;
   };

   struct BMPDIBHeader
   {
      uint32 size_;
      uint32 width_;
      uint32 height_;
      uint16 plane_count_;
      uint16 bits_per_pixel_;
      uint32 compression_;
      uint32 bitmap_size_;
      uint32 dpi_horizontal_;
      uint32 dpi_vertical_;
      uint32 palette_color_count_;
      uint32 important_color_count_;
   };
#pragma pack(pop)

   namespace
   {
      BMPFileHeader *get_header(const uint8 *base)
      {
         return (BMPFileHeader *)base;
      }

      BMPDIBHeader *get_dib(const uint8 *base)
      {
         return (BMPDIBHeader *)&get_header(base)[1];
      }

      uint8 *get_data(uint8 *base)
      {
         auto header = get_header(base);
         return base + header->offset_;
      }
   } // anon

   extern void destroy_texture(uint32 id);

   Image::Image()
      : bytes_per_pixel_(0)
      , width_(0)
      , height_(0)
      , data_(nullptr)
      , handle_(0)
   {
   }

   Image::Image(int width, int height)
      : bytes_per_pixel_(4)
      , width_(width)
      , height_(height)
      , data_(new uint8[width * height * bytes_per_pixel_])
      , handle_(0)
   {
   }

   Image::~Image()
   {
      destroy();
   }

   bool Image::is_valid()
   {
      return data_ != nullptr;
   }

   bool Image::load(const FileSystem *file_system, const char *filename)
   {
      if (is_valid())
      {
         destroy();
      }

      uint32 size = 0;
      uint8 *buf = nullptr;
      if (!file_system->read(filename, size, buf))
         return false;

      auto header = get_header(buf);
      if (header->signature_ != BMP_SIGNATURE)
      {
         delete[] buf;

         return false;
      }

      auto dib = get_dib(buf);
      const int width = dib->width_;
      const int height = dib->height_;
      const int bpp = dib->bits_per_pixel_ / 8;

      create(bpp, width, height);

      const int stride = width * bpp;
      const uint8 *src = get_data(buf) + (stride * (height - 1));
      uint8 *dst = data_;

      for (int row = 0; row < height; row++)
      {
         for (int pixel = 0; pixel < stride; pixel += bpp)
         {
            switch (bpp)
            {
               case 3:
               {
                  dst[pixel + 0] = src[pixel + 2];
                  dst[pixel + 1] = src[pixel + 1];
                  dst[pixel + 2] = src[pixel + 0];
               } break;
            }
         }

         dst += stride;
         src -= stride;
      }

      delete[] buf;

      return true;
   }

   bool Image::create(int bytes_per_pixel, int width, int height)
   {
      if (is_valid())
      {
         destroy();
      }

      bytes_per_pixel_ = bytes_per_pixel;
      width_ = width;
      height_ = height;
      data_ = new uint8[width * height * bytes_per_pixel];
      memset(data_, 0, width * height * bytes_per_pixel);

      return true;
   }

   void Image::destroy()
   {
      if (data_)
      {
         delete[] data_;
      }

      if (handle_)
      {
         destroy_texture(handle_);
      }

      bytes_per_pixel_ = 0;
      width_ = 0;
      height_ = 0;
      data_ = nullptr;
      handle_ = 0;
   }
} // Helium
