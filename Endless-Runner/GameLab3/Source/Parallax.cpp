#include "Parallax.h"

Parallax::Parallax()
{

}

Parallax::Parallax(const sf::Texture* texture, float scaling, float speed)
{
	scaling_ = scaling;
	speed_ = speed;



	alpha_Sprite_.setTexture(*texture);
	alpha_Sprite_.setScale(scaling, scaling);

	beta_Sprite_ = alpha_Sprite_;
	gamma_Sprite_ = alpha_Sprite_;

	alpha_Sprite_.setPosition(0, 0);
	beta_Sprite_.setPosition(alpha_Sprite_.getPosition().x + alpha_Sprite_.getTextureRect().width * scaling_, 0);
	gamma_Sprite_.setPosition(beta_Sprite_.getPosition().x + beta_Sprite_.getTextureRect().width * scaling_, 0);

	reset_Position_x_ = scaling * texture->getSize().x;
}

Parallax::~Parallax()
{
}

void Parallax::Update()
{
	alpha_Sprite_.setPosition(alpha_Sprite_.getPosition().x - speed_, 0);
	beta_Sprite_.setPosition(beta_Sprite_.getPosition().x - speed_, 0);
	gamma_Sprite_.setPosition(gamma_Sprite_.getPosition().x - speed_, 0);


	if (alpha_Sprite_.getPosition().x <= -(reset_Position_x_))
	{
		alpha_Sprite_.setPosition(reset_Position_x_ * 2, 0);
	}

	if (beta_Sprite_.getPosition().x <= -(reset_Position_x_))
	{
		beta_Sprite_.setPosition(reset_Position_x_ * 2, 0);
	}

	if (gamma_Sprite_.getPosition().x <= -(reset_Position_x_))
	{
		gamma_Sprite_.setPosition(reset_Position_x_ * 2, 0);
	}

}


void Parallax::Draw(sf::RenderWindow &window)
{
	window.draw(alpha_Sprite_);
	window.draw(beta_Sprite_);
	window.draw(gamma_Sprite_);
}
