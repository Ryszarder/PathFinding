#include "Pathfinder.h"

#define NODE_SIZE 20
#define NODE_DRAW_SIZE 15

Pathfinder::Pathfinder()
{
	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			m_pNodes[x][y] = new GraphNode();

			m_pNodes[x][y]->m_nIndexX = x;
			m_pNodes[x][y]->m_nIndexY = y;

			m_pNodes[x][y]->m_v2Position.x = (float)x * NODE_SIZE;
			m_pNodes[x][y]->m_v2Position.y = (float)y * NODE_SIZE;

			m_pNodes[x][y]->m_pPrev = nullptr;
			m_pNodes[x][y]->m_nGscore = 0;
			m_pNodes[x][y]->m_nFscore = 0;
			m_pNodes[x][y]->m_nHscore = 0;

			m_pNodes[x][y]->m_bBlocked = false;

			if (x == 20 && y != 20)
				m_pNodes[x][y]->m_bBlocked = true;
		}
	}

	//Connect all the node together
	// [0][1][2]
	// [3][x][4]
	// [5][6][7]
	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
			{
				m_pNodes[x][y]->m_pNeighbours[n] = GetNeighbour(x, y, n);

				if (n == 0 || n == 2 || n == 5 || n == 7)
					m_pNodes[x][y]->m_nCosts[n] = 14;
				else
					m_pNodes[x][y]->m_nCosts[n] = 10;
			}
		}
	}
}

Pathfinder::~Pathfinder()
{
	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			delete m_pNodes[x][y];
			m_pNodes[x][y] = nullptr;
		}
	}
}

GraphNode* Pathfinder::GetNeighbour(int nCurrentX, int nCurrentY, int nNeighbour)
{
	int x = nCurrentX;
	int y = nCurrentY;

	switch (nNeighbour)
	{
		case 0: --x; --y; break;
		case 1:		 --y; break;
		case 2: ++x; --y; break;
		case 3: --x;	  break;
		case 4: ++x;	  break;
		case 5: --x; ++y; break;
		case 6:		 ++y; break;
		case 7: ++x; ++y; break;
	}

	if (x < 0 || x >= GRID_SIZE)
		return nullptr;

	if (y < 0 || y >= GRID_SIZE)
		return nullptr;

	return m_pNodes[x][y];
}


GraphNode* Pathfinder::GetNodeByPos(Vector2 v2Pos)
{
	int x = (int)((v2Pos.x / NODE_SIZE) + 0.5f);
	int y = (int)((v2Pos.y / NODE_SIZE) + 0.5f);

	if (x < 0 || x >= GRID_SIZE)
		return nullptr;

	if (y < 0 || y >= GRID_SIZE)
		return nullptr;

	return m_pNodes[x][y];
}

bool Pathfinder::DijkstrasPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& FinalPath)
{
	//Get start and end nodes
	GraphNode* pStart = GetNodeByPos(v2Start);
	GraphNode* pEnd = GetNodeByPos(v2End);

	//Clear path
	FinalPath.clear();

	//Error checking
	if (pStart == nullptr)
		return false;
	if (pEnd == nullptr)
		return false;
	if (pEnd->m_bBlocked)
		return false;
	if (pStart == pEnd)
	{
		FinalPath.push_back(pEnd->m_v2Position);
		return true;
	}
	
	//Setup
	m_OpenList.Clear(); //Clear open list
	memset(m_bClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE); // Clear closed list

	//Restart start node
	pStart->m_nFscore = 0;
	pStart->m_pPrev = nullptr;
	m_OpenList.Push(pStart);

	//The Algoritm!!!
	while (!m_OpenList.Empty())
	{
		//Get cheapest node from list and remove it
		GraphNode* pCurrent = m_OpenList.Pop();

		//add to close list
		m_bClosedList[pCurrent->m_nIndexX][pCurrent->m_nIndexY] = true;

		//If we've just added end node to the closed list than path has been found
		if (pCurrent == pEnd)
		{
			FinalPath.push_back(pCurrent->m_v2Position);
			while (pCurrent->m_pPrev != nullptr)
			{
				pCurrent = pCurrent->m_pPrev;
				FinalPath.push_back(pCurrent->m_v2Position);
			}
			return true;
		}

		//process all neighbours
		for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
		{
			//Get Neighbour
			GraphNode* pNeighbour = pCurrent->m_pNeighbours[n];

			//Sanity Check
			if (pNeighbour == nullptr)
				continue;
			if (pNeighbour->m_bBlocked) //Dont wal through wall
				continue;
			if (m_bClosedList[pNeighbour->m_nIndexX][pNeighbour->m_nIndexY]) //Alread closed
				continue;

			//Check if in open list
			if (m_OpenList.Contains(pNeighbour))
			{
				//Check if we found a chaper path
				int newG = pCurrent->m_nFscore + pCurrent->m_nCosts[n];
				if (newG < pNeighbour->m_nFscore)
				{
					//We found a chaper path
					pNeighbour->m_nFscore = newG;
					pNeighbour->m_pPrev = pCurrent;
				}
			}
			else
			{
				//Calaulate cost and add to open list
				pNeighbour->m_nFscore = pCurrent->m_nFscore + pCurrent->m_nCosts[n];
				pNeighbour->m_pPrev = pCurrent;
				m_OpenList.Push(pNeighbour);
			}
		}
	}

	return false;
}

bool Pathfinder::AStarPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& FinalPath)
{
	//Get start and end nodes
	GraphNode* pStart = GetNodeByPos(v2Start);
	GraphNode* pEnd = GetNodeByPos(v2End);

	//Clear path
	FinalPath.clear();

	//Error checking
	if (pStart == nullptr)
		return false;
	if (pEnd == nullptr)
		return false;
	if (pEnd->m_bBlocked)
		return false;
	if (pStart == pEnd)
	{
		FinalPath.push_back(pEnd->m_v2Position);
		return true;
	}

	//Setup
	m_OpenList.Clear(); //Clear open list
	memset(m_bClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE); // Clear closed list

	//Restart start node
	pStart->m_nGscore = 0;
	pStart->m_nFscore = 0;
	pStart->m_nHscore = 0;
	pStart->m_pPrev = nullptr;
	m_OpenList.Push(pStart);

	//The Algoritm!!!
	while (!m_OpenList.Empty())
	{
		//Get cheapest node from list and remove it
		GraphNode* pCurrent = m_OpenList.Pop();

		//add to close list
		m_bClosedList[pCurrent->m_nIndexX][pCurrent->m_nIndexY] = true;

		//If we've just added end node to the closed list than path has been found
		if (pCurrent == pEnd)
		{
			FinalPath.push_back(pCurrent->m_v2Position);
			while (pCurrent->m_pPrev != nullptr)
			{
				pCurrent = pCurrent->m_pPrev;
				FinalPath.push_back(pCurrent->m_v2Position);
			}
			return true;
		}

		//process all neighbours
		for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
		{
			//Get Neighbour
			GraphNode* pNeighbour = pCurrent->m_pNeighbours[n];

			//Sanity Check
			if (pNeighbour == nullptr)
				continue;
			if (pNeighbour->m_bBlocked) //Dont wal through wall
				continue;
			if (m_bClosedList[pNeighbour->m_nIndexX][pNeighbour->m_nIndexY]) //Alread closed
				continue;

			//Check if in open list
			if (m_OpenList.Contains(pNeighbour))
			{
				//Check if we found a chaper path
				int newG = pCurrent->m_nGscore + pCurrent->m_nCosts[n];
				if (newG < pNeighbour->m_nGscore)
				{
					//We found a chaper path
					pNeighbour->m_nGscore = newG;
					pNeighbour->m_nFscore = pNeighbour->m_nGscore + pNeighbour->m_nHscore;
					pNeighbour->m_pPrev = pCurrent;
				}
			}
			else
			{
				//Calaulate cost and add to open list
				pNeighbour->m_nGscore = pCurrent->m_nGscore + pCurrent->m_nCosts[n];
				pNeighbour->m_nHscore = GetHueristic(pNeighbour, pEnd);
				pNeighbour->m_nFscore = pNeighbour->m_nGscore + pNeighbour->m_nHscore;
				pNeighbour->m_pPrev = pCurrent;
				m_OpenList.Push(pNeighbour);
			}
		}
	}

	return false;
}

int Pathfinder::GetHueristic(GraphNode* pNeighbour, GraphNode* pEnd)
{
	int dx = abs(pNeighbour->m_nIndexX - pEnd->m_nIndexX);
	int dy = abs(pNeighbour->m_nIndexY - pEnd->m_nIndexY);

	if(dx > dy)
	{
		return (14 * dy) + 10 * (dx - dy);
	}
	else
	{
		return (14 * dx) + 10 * (dy - dx);
	}
}

void Pathfinder::Render(aie::Renderer2D* pRenderer)
{
	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			GraphNode* pNode = m_pNodes[x][y];

			//Draws connection
			pRenderer->SetRenderColour(0.5f, 0.0f, 0.0f, 1.0f);
			for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
			{
				GraphNode* pNeighbour = pNode->m_pNeighbours[n];
				if (pNeighbour)
				{
					pRenderer->DrawLine(pNode->m_v2Position.x, pNode->m_v2Position.y,
										pNeighbour->m_v2Position.x, pNeighbour->m_v2Position.y);
				}
			}
		}
	}

	for (int y = 0; y < GRID_SIZE; ++y)
	{
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			GraphNode* pNode = m_pNodes[x][y];

			//Draws node
			if (pNode->m_bBlocked)
				pRenderer->SetRenderColour(0.0f, 0.0f, 0.5f); //Blue
			else
				pRenderer->SetRenderColour(0.0f, 0.8f, 0.0f, 0.7f); //Green

			pRenderer->DrawBox(pNode->m_v2Position.x, pNode->m_v2Position.y, NODE_SIZE / 2, NODE_SIZE / 2);
		}
	}

	//Reset colour back to default
	pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f); //White
}

