// Render.cpp

#include "Components/Transform_Component.h"
#include "Components/Render_Component.h"
#include "Game_Object.h"
#include "Vector2.h"
#include "Engine/Texture_Manager.h"
#include "Camera.h"
#include "Service.h"
#include "Engine/SDL_Pipeline.h"

// Render component requires Camera and Transform
Render_Component::Render_Component(Game_Object* game_object, Transform_Component* transform, Camera* camera, std::string id)
	: Component(game_object)
	, src_Rect_(SDL_Rect({0, 0, 0, 0}))
	, dst_Rect_(SDL_Rect({0, 0, 0, 0}))
	, texture_(nullptr)
	, camera_(camera)
	, transform_(transform)
	, renderer_(Service<SDL_Pipeline>::Get()->Get_Renderer())
{
	if (id != "")
		texture_ = Service<Texture_Manager>::Get()->Get(id);
}

Render_Component::~Render_Component()
{

}


void Render_Component::Set_Camera(Camera* camera)
{
	camera_ = camera;
}

void Render_Component::Set_Src_Rect(const SDL_Rect& rect)
{
	src_Rect_ = rect;
}

void Render_Component::Set_Dst_Rect(const SDL_Rect& rect)
{
	dst_Rect_ = rect;
}

void Render_Component::Set_Texture(std::string texture_id)
{
	texture_ = Service<Texture_Manager>::Get()->Get(texture_id);
}

SDL_Rect Render_Component::Get_Src_Rect()
{
	return src_Rect_;
}

SDL_Rect Render_Component::Get_Dst_Rect()
{
	return dst_Rect_;
}

void Render_Component::Set_Next_Frame(int start, int end, Render_Component::Animation_Type type)
{
	int previous = src_Rect_.x = src_Rect_.x;
	switch (type)
	{
		case LOOP:
			src_Rect_.x += src_Rect_.w;
			if (src_Rect_.x >= end)
				src_Rect_.x = start;
			break;

		case ONCE:
			src_Rect_.x += src_Rect_.w;
			if (src_Rect_.x >= end)
				src_Rect_.x = previous;
			break;

		case RESET:
			src_Rect_.x = start;
			break;
	}
}



void Render_Component::Render_Square()
{
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer_, &dst_Rect_);
}

void Render_Component::Render_Frame()
{
	Vector2 camera_position = camera_->Get_Position();
	Vector2 position = transform_->Get_Position();

	position -= camera_position;

	Vector2 origin({ transform_->Get_Origin().x_, transform_->Get_Origin().y_ });
	Vector2 size({ transform_->Get_Size().x_, transform_->Get_Size().y_ });

	// Add things for the dest Rect to change the destination size
	SDL_Rect render_dst_Rect_ = SDL_Rect({ (int)(position.x_ - origin.x_) + dst_Rect_.x, (int)(position.y_ - origin.y_) + dst_Rect_.y,
								(int)size.x_, (int)size.y_ });

	SDL_RenderCopyEx(Service<SDL_Pipeline>::Get()->Get_Renderer(), texture_->texture_, &src_Rect_, &render_dst_Rect_, 0, 0, SDL_FLIP_NONE);
}

