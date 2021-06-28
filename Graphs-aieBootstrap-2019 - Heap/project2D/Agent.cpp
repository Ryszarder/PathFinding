#include "Agent.h"
#include "Input.h"

Agent::Agent()
{
	m_texture = new aie::Texture("../bin/textures/Dice.png");

	m_posX = 300;
	m_posY = 600; 
	
	m_pPathfinder = new Pathfinder();
	m_2dRenderer = new aie::Renderer2D();
}

Agent::~Agent()
{
	delete m_texture;
	m_texture = nullptr;
}

void Agent::Update(/*float deltaTime*/)
{
	aie::Input* input = aie::Input::GetInstance();

	switch (state)
	{
	case STATE_IDLE:
		if (input->WasKeyPressed(aie::INPUT_KEY_W))
		{
			state = State::STATE_PROTOL;
		}

		else if (input->WasKeyPressed(aie::INPUT_KEY_D))
		{
			state = State::STATE_FOLLOW;
		}

		break;

	case STATE_PROTOL:
		if (input->WasKeyPressed(aie::INPUT_KEY_W))
		{
			m_texture->Unload();
			m_texture = new aie::Texture("../bin/textures/ship.png");
			state = State::STATE_IDLE;
		}
		break;

	case STATE_FOLLOW:
		if (input->WasKeyPressed(aie::INPUT_KEY_W))
		{
			m_2dRenderer->Begin();

			m_pPathfinder->Render(m_2dRenderer);
			std::vector<Vector2> path;
			Vector2 start = { 300, 600 };
			Vector2 end = { 700, 80 };
			m_pPathfinder->AStarPath(start, end, path);
			for (int i = 0; i < path.size(); ++i)
			{
				m_2dRenderer->DrawCircle(path[i].x, path[i].y, 10);
			}
			m_2dRenderer->End();
			state = State::STATE_PROTOL;
		}
		break;
	}
}

void Agent::Draw(aie::Renderer2D* renderer)
{
	renderer->DrawSprite(m_texture, m_posX, m_posY, 32, 32);
}

