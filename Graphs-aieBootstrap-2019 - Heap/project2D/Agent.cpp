#include "Agent.h"

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

void Agent::Update(float deltaTime)
{
}

void Agent::Draw(aie::Renderer2D* renderer)
{
	renderer->DrawSprite(m_texture, m_posX, m_posY, 32, 32);
}
