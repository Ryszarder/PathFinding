#pragma once
#include "Renderer2D.h"
#include "Vector2.h"
#include <vector>

class Pathfinder;

class Controller
{
public:
	Controller(Pathfinder* pPathfinder, Vector2 v2Position);
	~Controller();

	void Update(float DeltaTime);
	void Draw(aie::Renderer2D* pRenderer);

	void SetPos(Vector2 v2Position);
	Vector2 GetPos();


private:
	Pathfinder* m_pPathfinder;
	std::vector<Vector2> m_vPath;
	Vector2 m_v2Position;
};

