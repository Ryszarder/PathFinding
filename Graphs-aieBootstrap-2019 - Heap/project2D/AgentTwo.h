#pragma once
#include "Renderer2D.h"
#include "Vector2.h"
#include <vector>

class Pathfinder; //foward-declare

class AgentTwo
{
public:
	AgentTwo(Pathfinder* pPathfinder, Vector2 v2StartPos);
	~AgentTwo();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* pRenderer);

	void SetPos(Vector2 v2Position);
	Vector2 GetPos();

private:
	Vector2 m_v2Position;
	std::vector<Vector2> m_path;
	Pathfinder* m_pPathfinder;
	Vector2 m_v2Destination;
	Vector2 m_v2Velocity;
	float m_fSpeed;
	float m_fMaxSpeed;
};

