#pragma once
#include "GraphNode.h"
#include "Renderer2D.h"
#include <vector>
#include "Heap.h"

#define GRID_SIZE 50

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	bool DijkstrasPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& finalPath);
	bool AStarPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& finalPath);

	GraphNode* GetNodeByPos(Vector2 v2Pos);

	void Render(aie::Renderer2D* pRenderer);

private:
	GraphNode* GetNeighbour(int nCurrentX, int nCurrentY, int nNeighbour);

	int GetHueristic(GraphNode* pNeighbour, GraphNode* pEnd);

	GraphNode* m_pNodes[GRID_SIZE][GRID_SIZE];
	Heap m_OpenList;
	bool m_bClosedList[GRID_SIZE][GRID_SIZE];
};


