// resource_caches.h

#ifndef RESOURCE_CACHES_H_INCLUDED
#define RESOURCE_CACHES_H_INCLUDED

#include "resource_cache.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

typedef resource_cache<sf::Texture> texture_cache;
typedef resource_cache<sf::SoundBuffer> sound_buffer_cache;
typedef resource_cache<sf::Font> font_cache;

#endif // RESOURCE_CACHES_H_INCLUDED
