
#ifndef __PARALLAX__
#define __PARALLAX__

#include <SFML/Graphics.hpp>
#include <vector>

struct Parallax
{
	Parallax();
	Parallax(const sf::Texture* texture, float scaling, float speed,float x_Offset, float y_Offset, sf::IntRect rect, int window_Width);
	~Parallax();

	void Update(float dt);
	void Draw(sf::RenderWindow &window);

	std::vector<sf::Sprite> sprites_;
	sf::IntRect rect_;
	std::vector<sf::Vector2f> sprites_Positions_;
	sf::Vector2f sprites_Position_;


	float scaling_;
	float speed_;

	sf::Vector2f offset_;
	sf::Vector2f reset_Position_;
};

#endif // !__PARALLAX__

