// HeliumFileSystem.cc

#include "HeliumCore.h"

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

namespace Helium
{
   bool FileSystem::exists(const char *filename) const
   {
      DWORD attrib = GetFileAttributesA(filename);

      return (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY));
   }

   bool FileSystem::read(const char *filename, uint32 &size, uint8 *&dst) const
   {
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
         size = 0;
         dst = nullptr;
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

      return true;

   on_error:
      HELIUM_ASSERT(!"error reading file!");

      size = 0;
      delete[] dst;
      dst = nullptr;

      CloseHandle(handle);

      return false;
   }

   bool FileSystem::write(const char *filename, uint32 size, const uint8 *src) const
   {
      HANDLE handle = CreateFileA(filename,
                                  GENERIC_WRITE,
                                  0,
                                  NULL,
                                  CREATE_NEW,
                                  FILE_ATTRIBUTE_NORMAL,
                                  NULL);
      if (handle == INVALID_HANDLE_VALUE)
         return false;

      BOOL result = WriteFile(handle, src, size, NULL, NULL);
      CloseHandle(handle);

      return result == TRUE;
   }
} // Helium
