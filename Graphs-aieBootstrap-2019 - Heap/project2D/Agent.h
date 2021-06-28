#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Pathfinder.h"

class Agent
{
public:
	Agent();
	~Agent();

	void Update(/*float deltaTime*/);
	void Draw(aie::Renderer2D* renderer);

	enum State
	{
		STATE_IDLE,
		STATE_PROTOL,
		STATE_FOLLOW
	};

private:
	aie::Texture* m_texture;
	aie::Renderer2D* m_2dRenderer;

	State state = State::STATE_IDLE;

	float m_posX;
	float m_posY;

	Pathfinder* m_pPathfinder;
};

