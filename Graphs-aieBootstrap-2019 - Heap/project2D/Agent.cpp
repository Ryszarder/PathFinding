#include "Agent.h"
#include "Input.h"

Agent::Agent()
{
	m_texture = new aie::Texture("../bin/textures/Dice.png");

	m_posX = 60;
	m_posY = 60;
}

Agent::~Agent()
{
	delete m_texture;
	m_texture = nullptr;
}

enum State
{
	STATE_IDLE,
	STATE_PROTOL,
	STATE_FOLLOW
};

void Agent::Update(float deltaTime)
{
	aie::Input* input = aie::Input::GetInstance();

	switch (i)
	{
	case STATE_IDLE:
		if (input->WasKeyPressed(aie::INPUT_KEY_W))
		{
			i = 1;
		}

		/*else if (input->IsKeyDown(aie::INPUT_KEY_D))
		{
		}*/

		break;

	case STATE_PROTOL:
		if (input->WasKeyPressed(aie::INPUT_KEY_W))
		{
			i = 2;
		}
		break;

	case STATE_FOLLOW:
		if (input->WasKeyPressed(aie::INPUT_KEY_W))
		{
			m_posX += 500.0f * deltaTime;
			i = 1;
		}
		break;
	}
}

void Agent::Draw(aie::Renderer2D* renderer)
{
	renderer->DrawSprite(m_texture, m_posX, m_posY, 32, 32);
}
