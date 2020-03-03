// Render.cpp

#include "Components/Render_Component.h"
#include "Renderer.h"
#include "Components/Transform_Component.h"
#include "Game_Object.h"
#include "Vector2.h"
#include "Texture_Manager.h"


Render_Component::Render_Component(Game_Object& game_object)
	: Component(game_object)
	, src_Rect_(SDL_Rect({0, 0, 0, 0}))
	, dst_Rect_(SDL_Rect({0, 0, 0, 0}))
	, id_("")
{

}

Render_Component::~Render_Component()
{

}


void Render_Component::Set_Src_Rect(const SDL_Rect& rect)
{
	src_Rect_ = rect;
}

void Render_Component::Set_Dst_Rect(const SDL_Rect& rect)
{
	dst_Rect_ = rect;
}

void Render_Component::Set_Texture_ID(std::string id)
{
	id_ = id;
}

SDL_Rect Render_Component::Get_Src_Rect()
{
	return src_Rect_;
}

SDL_Rect Render_Component::Get_Dst_Rect()
{
	return dst_Rect_;
}

std::string Render_Component::Get_Texture_ID()
{
	return id_;
}



void Render_Component::Render_Square()
{
	Transform_Component* transform = game_Object_.Get_Component<Transform_Component>();

	SDL_SetRenderDrawColor(Renderer::Get_Renderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Renderer::Get_Renderer(), &dst_Rect_);
}

void Render_Component::Render_Frame()
{
	Transform_Component* transform = game_Object_.Get_Component<Transform_Component>();
	Texture_Data* texture = Texture_Manager::Get(id_);
	
	Vector2 position({ transform->Get_Position().x_, transform->Get_Position().y_ });
	Vector2 origin({ transform->Get_Origin().x_, transform->Get_Origin().y_ });
	Vector2 size({ transform->Get_Size().x_, transform->Get_Size().y_ });

	// Add things for the dest Rect to change the destination size
	SDL_Rect render_dst_Rect_ = SDL_Rect({ (int)(position.x_ - origin.x_) + dst_Rect_.x, (int)(position.y_ - origin.y_) + dst_Rect_.y,
								(int)size.x_, (int)size.y_ });

	SDL_RenderCopyEx(Renderer::Get_Renderer(), texture->texture_, &src_Rect_, &render_dst_Rect_, 0, 0, SDL_FLIP_NONE);
}

