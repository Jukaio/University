// Render.h

#ifndef __RENDER_COMPONENT__
#define __RENDER_COMPONENT__

#include "Component.h"
#include <string>
#include <SDL2/SDL.h>

struct Camera;

struct Render_Component : Component
{
	Render_Component(Game_Object& game_object);
	~Render_Component();

	SDL_Rect src_Rect_;
	SDL_Rect dst_Rect_;
	std::string id_;
	Camera* camera_;

	void Set_Camera(Camera* camera);
	void Set_Src_Rect(const SDL_Rect& rect);
	void Set_Dst_Rect(const SDL_Rect& rect);
	void Set_Texture_ID(std::string id);

	SDL_Rect Get_Src_Rect();
	SDL_Rect Get_Dst_Rect();
	std::string Get_Texture_ID();

	void Render_Square();
	void Render_Frame();
};


#endif // !__RENDER_COMPONENT__




