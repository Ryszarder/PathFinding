#include "AgentTwo.h"
#include "Pathfinder.h"
#include <math.h>
#include <Input.h>

AgentTwo::AgentTwo(Pathfinder* pPathfinder, Vector2 v2StartPos)
{
	m_pPathfinder = pPathfinder;
	m_v2Position = v2StartPos;

	m_v2Destination.x = rand() % /*2000*/ (GRID_SIZE * NODE_SIZE);
	m_v2Destination.y = rand() % /*2000*/(GRID_SIZE * NODE_SIZE);

	m_fSpeed = 100.0f;
	m_fMaxSpeed = 200.0f;

	m_v2Velocity.x = 0;
	m_v2Velocity.y = 0;
}

AgentTwo::~AgentTwo()
{

}

void AgentTwo::Update(float deltaTime)
{
	aie::Input* input = aie::Input::GetInstance();

	Vector2 v2Mouse;
	v2Mouse.x = input->GetMouseX();
	v2Mouse.y = input->GetMouseY();

	//Seek behaviours
	Vector2 v2Dir = v2Mouse - m_v2Position;
	v2Dir = v2Dir.get_normalised();

	Vector2 vDesiredVelocity = v2Dir * m_fMaxSpeed;
	Vector2 v2SteeringForce = m_v2Destination - m_v2Velocity;

	m_v2Velocity += v2SteeringForce * deltaTime;
	m_v2Velocity += m_v2Velocity * deltaTime;

	/*m_v2Velocity += v3Dir * m_fSpeed * deltaTime;
	if (m_v2Velocity.get_magnitude() > 200)
	{
		m_v2Velocity = m_v2Velocity.get_normalised();
		m_v2Velocity = m_v2Velocity * m_fMaxSpeed;
	}*/

	//Flee Behaviours
	Vector2 v2Dir = m_v2Position - v2Mouse;
	v2Dir = v2Dir.get_normalised();

	Vector2 vDesiredVelocity = v2Dir * m_fMaxSpeed;
	Vector2 v2SteeringForce = m_v2Destination - m_v2Velocity;

	m_v2Velocity += v2SteeringForce * deltaTime;
	m_v2Velocity += m_v2Velocity * deltaTime;

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
