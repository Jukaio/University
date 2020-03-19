// Render.h

#ifndef __RENDER_COMPONENT__
#define __RENDER_COMPONENT__

#include "Component.h"
#include <string>
#include <SDL2/SDL.h>

struct Camera;
struct Transform_Component;
struct Texture_Data;

struct Render_Component : Component
{
	enum Animation_Type
	{
		LOOP,
		ONCE,
		RESET
	};


	Render_Component(Game_Object* game_object, Transform_Component* transform, Camera* camera = nullptr, std::string id = "");
	~Render_Component();

	void Set_Camera(Camera* camera);
	void Set_Src_Rect(const SDL_Rect& rect);
	void Set_Dst_Rect(const SDL_Rect& rect);
	void Set_Texture(std::string texture_id);

	SDL_Rect Get_Src_Rect();
	SDL_Rect Get_Dst_Rect();
	void Set_Next_Frame(int start, int end, Animation_Type type);

	void Render_Square();
	void Render_Frame();

private:
	// Rendering
	SDL_Renderer* renderer_;
	Camera* camera_;

	// Destination on Screen
	SDL_Rect dst_Rect_;	
	Transform_Component* transform_;

	// Source from Texture
	SDL_Rect src_Rect_;
	Texture_Data* texture_;
};


#endif // !__RENDER_COMPONENT__




