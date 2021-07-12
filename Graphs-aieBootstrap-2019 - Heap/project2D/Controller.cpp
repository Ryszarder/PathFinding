#include "Controller.h"
#include "Pathfinder.h"

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
}

void Controller::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->DrawBox(m_v2Position.x, m_v2Position.y, 15, 15);
}
