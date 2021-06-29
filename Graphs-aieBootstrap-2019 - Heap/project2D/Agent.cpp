#include "Agent.h"
#include "Input.h"

Agent::Agent()
{
	m_texture = new aie::Texture("../bin/textures/Dice.png");

	m_posX = 40;
	m_posY = 920;

	m_pPathfinder = new Pathfinder();
	m_bFollow = false;
}

Agent::~Agent()
{
	delete m_texture;
	m_texture = nullptr;

	delete m_pPathfinder;
	m_pPathfinder = nullptr;
}

void Agent::Update(float deltaTime)
{
	aie::Input* m_Input = aie::Input::GetInstance();

	if (m_Input->WasMouseButtonPressed(0))
	{
		Vector2 mousePos = { m_Input->GetMouseX(), m_Input->GetMouseY() };
		GraphNode* pNode = m_pPathfinder->GetNodeByPos(mousePos);

		if (pNode)
		{
			pNode->m_bBlocked = true;
		}
	}

	if (m_Input->WasMouseButtonPressed(1))
	{
		Vector2 mousePos = { m_Input->GetMouseX(), m_Input->GetMouseY() };
		GraphNode* pNode = m_pPathfinder->GetNodeByPos(mousePos);

		if (pNode)
		{
			pNode->m_bBlocked = false;
		}
	}

	if (m_Input->WasKeyPressed(aie::INPUT_KEY_W))
	{
		m_posY += 20.0f;
	}

	if (m_Input->WasKeyPressed(aie::INPUT_KEY_S))
	{
		m_posY -= 20.0f;
	}

	if (m_Input->WasKeyPressed(aie::INPUT_KEY_A))
	{
		m_posX -= 20.0f;
	}

	if (m_Input->WasKeyPressed(aie::INPUT_KEY_D))
	{
		m_posX += 20.0f;
	}
	Vector2 start = { m_posX, m_posY };
	Vector2 end = { 900, 60 };
	m_pPathfinder->AStarPath(start, end, path);
	m_bFollow = true;
	switch (state)
	{
	case STATE_IDLE:
		/*m_bFollow = false;*/
		if (m_Input->WasKeyPressed(aie::INPUT_KEY_R))
		{
			state = State::STATE_PROTOL;
		}

		else if (m_Input->WasKeyPressed(aie::INPUT_KEY_SPACE))
		{
			state = State::STATE_FOLLOW;
		}

		break;

	case STATE_PROTOL:
		if (m_Input->WasKeyPressed(aie::INPUT_KEY_E))
		{
			m_texture->Unload();
			m_texture = new aie::Texture("../bin/textures/ship.png");

			state = State::STATE_IDLE;
		}
		break;

	case STATE_FOLLOW:
		if (m_Input->WasKeyPressed(aie::INPUT_KEY_SPACE))
		{
			/*m_bFollow = true;*/

			/*Vector2 start = { m_posX, m_posY };
			Vector2 end = { 900, 60 };
			m_pPathfinder->AStarPath(start, end, path);*/

			state = State::STATE_PROTOL;
		}
		break;
	}
}

void Agent::Draw(aie::Renderer2D* renderer)
{
	renderer->DrawSprite(m_texture, m_posX, m_posY, 32, 32);

	if (m_bFollow && path.size() > 1)
	{
		for (int i = 0; i < path.size(); ++i)
		{
			renderer->DrawCircle(path[i].x, path[i].y, 10);
		}
	}
}