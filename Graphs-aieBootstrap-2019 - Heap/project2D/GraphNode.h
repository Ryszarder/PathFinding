#pragma once
#include "Vector2.h"

#define NEIGHBOUR_COUNT 8

struct GraphNode
{
	int m_nIndexX;
	int m_nIndexY;

	Vector2 m_v2Position;

	GraphNode* m_pPrev;
	int m_nGscore;
	int m_nHscore;
	int m_nFscore;

	GraphNode* m_pNeighbours[NEIGHBOUR_COUNT];

	int m_nCosts[NEIGHBOUR_COUNT];

	bool m_bBlocked;
}; 


