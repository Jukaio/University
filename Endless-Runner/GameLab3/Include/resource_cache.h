// resource_cache.h

#ifndef RESOURCE_CACHE_H_INCLUDED
#define RESOURCE_CACHE_H_INCLUDED

#include <string>
#include <map>

template <typename T>
struct resource_cache
{
   typedef T resource_type;

   resource_cache();
   ~resource_cache();

   bool load(const std::string &filename);
   void unload(const std::string &filename);
   void unload_all();

   bool get(const std::string &filename,
            const resource_type **resource);

private:
   std::map<std::string, resource_type *> resources_;
};

#include "resource_cache.inl"

#endif // RESOURCE_CACHE_H_INCLUDED

