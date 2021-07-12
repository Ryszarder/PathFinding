#include "Controller.h"
#include "Pathfinder.h"
#include "Input.h"

Controller::Controller(Pathfinder* pPathefinder, Vector2 v2Position)
{
	m_pPathfinder = pPathefinder;
	m_v2Position = v2Position;
}

Controller::~Controller()
{
}

void Controller::Update(float DeltaTime)
{
	aie::Input* m_input = aie::Input::GetInstance();

	if (m_input->WasKeyPressed(aie::INPUT_KEY_W))
	{
		m_v2Position.y += 20.0f;
	}

	if (m_input->WasKeyPressed(aie::INPUT_KEY_S))
	{
		m_v2Position.y -= 20.0f;
	}

	if (m_input->WasKeyPressed(aie::INPUT_KEY_A))
	{
		m_v2Position.x -= 20.0f;
	}

	if (m_input->WasKeyPressed(aie::INPUT_KEY_D))
	{
		m_v2Position.x += 20.0f;
	}

	SetPos(m_v2Position);
}

void Controller::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->DrawBox(m_v2Position.x, m_v2Position.y, 15, 15);
}

void Controller::SetPos(Vector2 v2Position)
{
	m_v2Position = v2Position;
}

Vector2 Controller::GetPos()
{
	return m_v2Position;
}
