#include "Player.h"
#include "Collider.h"
#include "Sprite.h"
#include "Service.h"
#include "SpriteHandler.h"

Player::Player()
{
	m_x = 0; m_y = 0;
	m_scale = 1.0f;
	m_active = false;
	m_visible = false;
	m_sprite = nullptr;
	m_collider = nullptr;
}

void Player::Create(int x, int y, float scale, bool active, bool visible, const char* file_Path,
					Collider* collider, EntityType type)
{
	m_x = 0; m_y = 0;
	m_scale = 1.0f;
	m_active = active;
	m_visible = visible;
	m_sprite = Service<SpriteHandler>::Get()->CreateSprite(file_Path, 0, 0, 100, 100);
	m_collider = collider;
	m_type = type;
}

void Player::Update()
{

}

void Player::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst = { m_x, m_y, m_sprite->GetArea().w, m_sprite->GetArea().h };
	SDL_RenderCopy(renderer, m_sprite->GetTexture(), &m_sprite->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	SDL_RenderDrawRect(renderer, &m_collider->GetBounds());
}
