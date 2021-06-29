#include "Agent.h"
#include "Input.h"

Agent::Agent()
{
	m_Texture = new aie::Texture("../bin/textures/Dice.png");

	m_fPosX = 40;
	m_fPosY = 920;

	m_pPathfinder = new Pathfinder();
	m_bFollow = false;
}

Agent::~Agent()
{
	delete m_Texture;
	m_Texture = nullptr;

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
		m_fPosY += 20.0f;
	}

	if (m_Input->WasKeyPressed(aie::INPUT_KEY_S))
	{
		m_fPosY -= 20.0f;
	}

	if (m_Input->WasKeyPressed(aie::INPUT_KEY_A))
	{
		m_fPosX -= 20.0f;
	}

	if (m_Input->WasKeyPressed(aie::INPUT_KEY_D))
	{
		m_fPosX += 20.0f;
	}

	Vector2 start = { m_fPosX, m_fPosY };
	Vector2 end = { 900, 60 };
	m_pPathfinder->AStarPath(start, end, m_vPath);
	m_bFollow = true;

	switch (m_eState)
	{
	case STATE_IDLE:
		/*m_bFollow = false;*/
		if (m_Input->WasKeyPressed(aie::INPUT_KEY_R))
		{
			m_eState = State::STATE_PROTOL;
		}

		else if (m_Input->WasKeyPressed(aie::INPUT_KEY_SPACE))
		{
			m_eState = State::STATE_FOLLOW;
		}

		break;

	case STATE_PROTOL:
		if (m_Input->WasKeyPressed(aie::INPUT_KEY_E))
		{
			m_Texture->Unload();
			m_Texture = new aie::Texture("../bin/textures/ship.png");

			m_eState = State::STATE_IDLE;
		}
		break;

	case STATE_FOLLOW:
		if (m_Input->WasKeyPressed(aie::INPUT_KEY_SPACE))
		{
			/*m_bFollow = true;*/

			/*Vector2 start = { m_posX, m_posY };
			Vector2 end = { 900, 60 };
			m_pPathfinder->AStarPath(start, end, path);*/

			m_eState = State::STATE_PROTOL;
		}
		break;
	}
}

void Agent::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->DrawSprite(m_Texture, m_fPosX, m_fPosY, 32, 32);

	if (m_bFollow && m_vPath.size() > 1)
	{
		for (int i = 0; i < m_vPath.size(); ++i)
		{
			pRenderer->DrawCircle(m_vPath[i].x, m_vPath[i].y, 10);
		}
	}
}