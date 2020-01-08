// resource_cache.inl

#include <cassert>

// note: template implementation
template <typename T>
resource_cache<T>::resource_cache()
{
}

template <typename T>
resource_cache<T>::~resource_cache()
{
   unload_all();
}

template <typename T>
bool resource_cache<T>::load(const std::string &filename)
{
   auto iter = resources_.find(filename);
   
   if (iter == resources_.end())
   {
      resource_type *resource = new resource_type;
      if (!resource->loadFromFile(filename))
      {
         delete resource;
         assert(!"could not load resource from file");

         return false;
      }
      resources_.insert(std::pair<std::string, resource_type *>(filename, resource));
   }

   return true;
}

template <typename T>
void resource_cache<T>::unload(const std::string &filename)
{
   auto iter = resources_.find(filename);
   if (iter == resources_.end())
      return;

   delete iter->second;
   resources_.erase(iter);
}

template <typename T>
void resource_cache<T>::unload_all()
{
   for (auto &iter : resources_)
      delete iter.second;

   resources_.clear();
}

template <typename T>
bool resource_cache<T>::get(const std::string &filename,
                            const resource_type **resource)
{
   auto iter = resources_.find(filename);
   if (iter == resources_.end())
      return false;

   *resource = iter->second;

   return true;
}

