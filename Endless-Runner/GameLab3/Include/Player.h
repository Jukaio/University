#ifndef __PLAYER__
#define __PLAYER__

#include <SFML/Graphics.hpp>
#include <vector>
#include "resource_cache.h"

struct Player
{
	Player();
	~Player();

	void load(const char* filepath, resource_cache<sf::Texture>& texture_cache);
	void set_Animation(int id);
	void update(float dt);
	void draw(sf::RenderWindow& window);

	sf::Sprite sprite_;
	sf::Vector2f position_;
	sf::Vector2f velocity_;

	enum player_state
	{
		RUN,
		JUMP,
		FALL,
		DEATH
	};
	player_state current_state;

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

	float scale_ = 1;

	std::vector<anim_Data> anims_;
	int current_Anim_ = 0;
	int frame_ = 0;
	float duration_ = 0;
};


#endif // !__PLAYER__

