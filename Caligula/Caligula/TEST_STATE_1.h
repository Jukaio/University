#pragma once

#include "State.h"
#include "TEST_BALL.h"
#include "TEST_PADDLE.h"
#include <array>
#include "Player.h"

struct SDL_Renderer;
class Sound;

class TEST_STATE_1 : public State
{
	unsigned int m_playerOneScore;
	unsigned int m_playerTwoScore;
	SDL_Renderer* m_renderer;
	TEST_BALL m_ball;
	TEST_PADDLE m_playerOnePaddle;
	TEST_PADDLE m_playerTwoPaddle;
	TEST_PADDLE* m_servingPlayer;
	Player player;
	Sound* m_sound;
	int m_timer;
public:
	TEST_STATE_1(SDL_Renderer& p_renderer); 
	void Enter();
	bool Update();
	void Exit();
};
