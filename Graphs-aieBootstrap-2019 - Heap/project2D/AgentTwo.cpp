#include "AgentTwo.h"
#include "Pathfinder.h"
#include <math.h>
#include <Input.h>

//Constructor
AgentTwo::AgentTwo(Pathfinder* pPathfinder, Vector2 v2StartPos)
{
	//Initalise the m_pPathfinder to equal the pathfinder that was passed in
	m_pPathfinder = pPathfinder;

	//Initalise the m_v2Position to equal the v2StartPos that was passed in
	m_v2Position = v2StartPos;

	//Initalise m_v2Destination.x and m_v2Sestination.y with a random value 
	m_v2Destination.x = rand() % /*2000*/ (GRID_SIZE * NODE_SIZE);
	m_v2Destination.y = rand() % /*2000*/(GRID_SIZE * NODE_SIZE);

	//Initalise m_fSpeed
	m_fSpeed = 100.0f;
	//Initalise m_fMaxSpeed
	m_fMaxSpeed = 200.0f;

	//Initalise m_v2Velocity.x and m_v2Velocity.y to 0
	m_v2Velocity.x = 0;
	m_v2Velocity.y = 0;

	//Initalise m_fFood 
	m_fFood = 1000.0f;
}

//Destructor
AgentTwo::~AgentTwo()
{

}

void AgentTwo::Update(float deltaTime)
{
	if (m_fFood < 30)
	{
		m_v2Destination.x = 20;
		m_v2Destination.y = 20;

		m_pPathfinder->AStarPath(m_v2Position, m_v2Destination, m_path);
	}

	if (m_v2Destination.x == 20 && m_v2Destination.y == 20)
	{
		m_fFood = 1000.0f;
	}

	if (m_path.size() < 2)
	{	
		m_v2Destination.x = rand() % /*2000*/ (GRID_SIZE * NODE_SIZE);
		m_v2Destination.y = rand() % /*2000*/(GRID_SIZE * NODE_SIZE);

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
		if (fMag < NODE_SIZE * 0.25f)
		{
			//m_path.clear();

			m_pPathfinder->AStarPath(m_v2Position, m_v2Destination, m_path);
		}
	}

	SetPos(m_v2Position);

	m_fFood = m_fFood - 1;
}

void AgentTwo::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->DrawCircle(m_v2Position.x, m_v2Position.y, 10);

	if (m_path.size() > 0)
	{
		for (int i = 0; i < m_path.size() - 1; ++i)
		{
			pRenderer->DrawLine(m_path[i].x, m_path[i].y, m_path[i + 1].x, m_path[i + 1].y, 5.0f);
		}
	}
}

void AgentTwo::SetPos(Vector2 v2Position)
{
	m_v2Position = v2Position;
}

Vector2 AgentTwo::GetPos()
{
	return m_v2Position;
}