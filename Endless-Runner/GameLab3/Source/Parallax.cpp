#include "Parallax.h"

Parallax::Parallax()
{

}

Parallax::Parallax(const sf::Texture* texture, float scaling, float speed,float x_Offset, float y_Offset, sf::IntRect rect, int window_Width)
{
	speed_ = speed;

	offset_.x = x_Offset;
	offset_.y = y_Offset;

	float width = rect.width * scaling + offset_.x;
	for (int i = 0; ; i ++)
	{
		sprites_.push_back(sf::Sprite(*texture, rect));
		sprites_[i].setScale(scaling, scaling);
		sprites_[i].setPosition(i * width, y_Offset);
		if (i * (width) > window_Width)
			break;
	}

	reset_Position_.x = width;
	reset_Position_.y = y_Offset;
}

Parallax::~Parallax()
{
}

void Parallax::Update(float dt)
{
	float speed = speed_ * dt;

	sprites_Position_.x -= speed;
	if (sprites_Position_.x < -reset_Position_.x)
	{
		sprites_Position_.x += reset_Position_.x;
	}
}


void Parallax::Draw(sf::RenderWindow &window)
{
	sf::RenderStates state;
	state.transform.translate(sprites_Position_);
	for (auto &sprite : sprites_)
		window.draw(sprite, state);
}
