#include "Player.h"

Player::Player()
	: sprite_(sf::Sprite()),
	  velocity_(sf::Vector2f(0.0f, 0.0f)),
	  position_(sf::Vector2f(50.0f, 450.0f)),
	  scale_(4.0f)
{
	current_state = JUMP;
}

void Player::load(const char* filepath, resource_cache<sf::Texture>& texture_cache)
{
	FILE* stream;
	char* file_Source = new char[256];

	if (fopen_s(&stream, filepath, "r") != 0)
		return;
	if (fscanf_s(stream, "%s", file_Source, 256) == 0)
		return;

	anim_Data data_;

	texture_cache.load(file_Source);
	const sf::Texture* temp_Texture; //
	texture_cache.get(file_Source, &temp_Texture);//

	data_.texture_ = temp_Texture;

	while (!feof(stream))
	{
		anim_Data::Frame temp_Frame;
		sf::IntRect temp_Rect;

		if (fscanf_s(stream, "%ld", &temp_Frame.id_) == 0)
			return;
		if (fscanf_s(stream, "%ld", &temp_Rect.left) == 0)
			return;
		if (fscanf_s(stream, "%ld", &temp_Rect.top) == 0)
			return;
		if (fscanf_s(stream, "%ld", &temp_Rect.width) == 0)
			return;
		if (fscanf_s(stream, "%ld", &temp_Rect.height) == 0)
			return;
		if (fscanf_s(stream, "%f", &temp_Frame.duration_) == 0)
			return;

		data_.frames_.push_back(temp_Frame);
		data_.rects_.push_back(temp_Rect);
	}
	anims_.push_back(data_);

	fclose(stream);

	sprite_.setScale(scale_, scale_);
}

void Player::set_Animation(int id)
{
	current_Anim_ = id;
	sprite_.setTexture(*anims_[current_Anim_].texture_);
}

void Player::update(float dt)
{
	switch (current_state)
	{
		case RUN:
			if (duration_ <= 0)
			{
				sprite_.setTextureRect(anims_[current_Anim_].rects_[frame_]);
				duration_ = anims_[current_Anim_].frames_[frame_].duration_;
				frame_++;
				if (frame_ >= anims_[current_Anim_].rects_.size())
					frame_ = 0;
			}
			break;

		case JUMP:
			sprite_.setTextureRect(anims_[current_Anim_].rects_[0]);
			velocity_.y -= 5.0f * dt;
			position_ -= velocity_;
			sprite_.setPosition(position_);
			if (velocity_.y < 0)
				current_state = FALL;
			break;

		case FALL:
			sprite_.setTextureRect(anims_[current_Anim_].rects_[1]);
			velocity_.y += 5 * dt;
			position_ += velocity_;
			sprite_.setPosition(position_);
			break;

		case DEATH:
			if (duration_ <= 0)
			{
				if (frame_ >= anims_[current_Anim_].rects_.size())
					frame_ = 0;
				sprite_.setTextureRect(anims_[current_Anim_].rects_[frame_]);
				duration_ = anims_[current_Anim_].frames_[frame_].duration_;
				frame_++;
			}
			break;
	}
	duration_ -= dt;
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite_);
}
