#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include "InputHandler.h"
#include "Sound.h"
#include <iostream>
#include "Config.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) : m_renderer(&p_renderer),
	m_ball("../Assets/less_pretty_ball.png", 0, 0, 32, 32, 0, 0, 32, 32, 100, 100, 3, 3),
	m_playerOnePaddle("../Assets/paddle.bmp",32,Config::SCREEN_HEIGHT / 2 - 64,32,128,5,SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_D),
	m_playerTwoPaddle("../Assets/paddle.bmp", Config::SCREEN_WIDTH - 64, Config::SCREEN_HEIGHT / 2 - 64, 32, 128, 5, SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_J)
{
	m_sound = Service<SoundHandler>::Get()->CreateSound("../Assets/plopp.wav");
	m_name = "TEST_STATE_1";
	player.Create(0, 0, 1.0f, true, true, "../Assets/Zelda_Player.png", nullptr, EntityType::PADDLE);
	
}

void TEST_STATE_1::Enter()
{
	std::cout << "TEST_STATE_1::Enter" << std::endl;
}

bool TEST_STATE_1::Update()
{
	m_ball.Update();
	m_playerOnePaddle.Update();
	m_playerTwoPaddle.Update();

	if (m_ball.IsOutside())
	{
		if (m_ball.GetPositionX() < 0)
		{
			m_playerTwoScore++;
			m_servingPlayer = &m_playerOnePaddle;
			std::cout << "PLAYER 2 SCORES" << std::endl;
		}
		else if (m_ball.GetPositionX() > Config::SCREEN_WIDTH)
		{
			m_playerOneScore++;
			m_servingPlayer = &m_playerTwoPaddle;
			std::cout << "PLAYER 1 SCORES" << std::endl;
		}
		m_ball.Reset();
	}

	if (m_ball.IsActive() == false)
	{
		if (m_servingPlayer->IsServePressed())
		{
			m_ball.Serve();
		}
	}
	if (Service<CollisionHandler>::Get()->IsColliding(m_ball.GetCollider(), m_playerOnePaddle.GetCollider()))
	{
		m_ball.OnCollision(&m_playerOnePaddle);
		m_playerOnePaddle.OnCollision(&m_ball);
		m_sound->Play(0);
	}
	if (Service<CollisionHandler>::Get()->IsColliding(m_ball.GetCollider(), m_playerTwoPaddle.GetCollider()))
	{
		m_ball.OnCollision(&m_playerTwoPaddle);
		m_playerTwoPaddle.OnCollision(&m_ball);
		m_sound->Play(0);
	}

	m_ball.Render(m_renderer);
	m_playerOnePaddle.Render(m_renderer);
	m_playerTwoPaddle.Render(m_renderer);
	player.Render(m_renderer);

	m_timer++;

	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}
