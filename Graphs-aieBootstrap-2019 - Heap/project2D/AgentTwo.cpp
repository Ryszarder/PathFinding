#include "AgentTwo.h"
#include "Pathfinder.h"
#include <math.h>

AgentTwo::AgentTwo(Pathfinder* pPathfinder, Vector2 v2StartPos)
{
	m_pPathfinder = pPathfinder;
	m_v2Position = v2StartPos;

	m_v2Destination.x = rand() % 2000 /*(GRID_SIZE * NODESIZE)*/;
	m_v2Destination.y = rand() % 2000/*(GRID_SIZE * NODESIZE)*/;

	m_fSpeed = 100f;
}

AgentTwo::~AgentTwo()
{

}

void AgentTwo::Update(float deltaTime)
{
	if (m_path.size() < 2)
	{	
		m_pPathfinder->AStarPath(m_v2Position, m_v2Destination, m_path);
	}

	if (m_path.size() > 1)
	{
		Vector2 v2Destination = m_path[m_path.size() - 2];

		Vector2 v2Dir;
		v2Dir.x = v2Destination.x - m_v2Position.x;
		v2Dir.y = v2Destination.y - m_v2Position.y;

		//Normalize
		float fMag = sqrtf(v2Dir.x * v2Dir.x + v2Dir.y * v2Dir.y);
		if (fMag != 0.0f)
		{
			v2Dir.x /= fMag;
			v2Dir.y /= fMag;
		}

		//Move the actor
		m_v2Position.x += v2Dir.x * m_fSpeed * deltaTime;
		m_v2Position.y += v2Dir.y * m_fSpeed * deltaTime;

		//Check if we have arrived at node
		if (fMag < NODE_Size * 0.25f)
		{
			m_path.clear();

			m_pPathfinder->AStarPath(m_v2Position, m_v2Destination, m_path);
		}
	}
}

void AgentTwo::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->DrawCircle(m_v2Position.x, m_v2Position.y, 10);

	if (m_path.size > 0)
	{
		for (int i = 0; i < m_path.size() - 1; ++i)
		{
			pRenderer->DrawLine(m_path[i].x, m_path[i].y, m_path[i + 1].x, m_path[i + 1].y, 5.0f);
		}
	}
	
}
