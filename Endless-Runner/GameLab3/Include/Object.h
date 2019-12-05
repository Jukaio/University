#ifndef __OBJECT__
#define __OBJECT__

#include <SFML/Graphics.hpp>
#include <vector>
#include "resource_cache.h"

struct Object
{
	Object();
	~Object();

	void load(const char* filepath, resource_cache<sf::Texture>& texture_cache);
	void update(float dt, float speed);
	void draw(sf::RenderWindow& window);

	sf::Sprite sprite_;
	sf::Vector2f position_;

	struct anim_Data
	{
		struct Frame
		{
			int id_;
			float duration_;
		};
		std::vector<Frame> frames_;
		std::vector <sf::IntRect> rects_;
		const sf::Texture* texture_;
	};
	anim_Data anim_Data_;
	float scale_ = 1;
	int frame_ = 0;
	float duration_ = 0;
};


#endif // !__OBJECT__
