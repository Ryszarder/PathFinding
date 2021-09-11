#pragma once
#include "Renderer2D.h"
#include "Vector2.h"
#include <vector>

class Pathfinder;

class Controller
{
public:
	//Constructor that takes in Pathfinder and Vector2
	Controller(Pathfinder* pPathfinder, Vector2 v2Position);
	
	//Destructor
	~Controller();

	//Update function that takes DeltaTime
	void Update(float DeltaTime);

	//Draw function that takes in Renderer2D
	void Draw(aie::Renderer2D* pRenderer);

	//Set position that takes Vector2
	void SetPos(Vector2 v2Position);
	
	//Get postion of a Vector2
	Vector2 GetPos();


private:
	Pathfinder* m_pPathfinder;
	std::vector<Vector2> m_vPath;
	Vector2 m_v2Position;
};

