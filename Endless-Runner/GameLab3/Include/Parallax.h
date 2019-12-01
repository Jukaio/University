
#ifndef __PARALLAX__
#define __PARALLAX__

#include <SFML/Graphics.hpp>

struct Parallax
{
	Parallax();
	Parallax(const sf::Texture* texture, float scaling, float speed);
	~Parallax();

	void Update();
	void Draw(sf::RenderWindow &window);

	sf::Sprite alpha_Sprite_;
	sf::Sprite beta_Sprite_;
	sf::Sprite gamma_Sprite_;

	float scaling_;
	float speed_;
	float reset_Position_x_;
};

#endif // !__PARALLAX__

