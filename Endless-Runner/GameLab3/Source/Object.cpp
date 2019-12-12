#include "Object.h"

Object::Object()
	: sprite_(sf::Sprite()),
	position_(sf::Vector2f(0.0f, 0.0f)),
	scale_(4.0f)
{
}

Object::~Object()
{
}

void Object::load(const char* filepath, resource_cache<sf::Texture>& texture_cache)
{
	FILE* stream;
	char file_Source[256];

	if (fopen_s(&stream, filepath, "r") != 0)
		return;
	if (fscanf_s(stream, "%s", file_Source, 256) == 0)
		return;

	anim_Data data_;

	texture_cache.load(file_Source);
	const sf::Texture* temp_Texture; //
	texture_cache.get(file_Source, &temp_Texture);//

	sprite_.setTexture(*temp_Texture);

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
	anim_Data_ = data_;
	fclose(stream);
	sprite_.setScale(scale_, scale_);
}

void Object::update(float dt, float speed)
{
	if (duration_ <= 0)
	{
		sprite_.setTextureRect(anim_Data_.rects_[frame_]);
		duration_ = anim_Data_.frames_[frame_].duration_;
		frame_++;
		if (frame_ >= anim_Data_.rects_.size())
			frame_ = 0;
	}
	duration_ -= dt;
	position_.x -= speed * dt;
	if (position_.x <= 0 - sprite_.getTextureRect().width)
		position_.x = 1280;
	sprite_.setPosition(position_);
}

void Object::draw(sf::RenderWindow& window)
{
	window.draw(sprite_);
}
