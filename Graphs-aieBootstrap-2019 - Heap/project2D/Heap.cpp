#include "Heap.h"

Heap::Heap()
{
}

Heap::~Heap()
{
}

void Heap::Push(GraphNode* nValue)
{
	m_Data.Add(nValue);
	int nCurrentIndex = m_Data.GetSize() - 1;
	int nParentIndex = GetParentIndex(nCurrentIndex);

	//Chech if child is less than parent
	while (m_Data[nCurrentIndex]->m_nFscore < m_Data[nParentIndex]->m_nFscore)
	{
		//Swap
		GraphNode* temp = m_Data[nCurrentIndex];
		m_Data[nCurrentIndex] = m_Data[nParentIndex];
		m_Data[nParentIndex] = temp;

		//Update indices
		nCurrentIndex = nParentIndex;
		nParentIndex = GetParentIndex(nCurrentIndex);
	}
}

GraphNode* Heap::Pop()
{
	if (Size() == 0)
		return nullptr;

	//Get the data so we can return it later
	GraphNode* nResult = m_Data[0];

	//Remove data
	m_Data[0] = m_Data[Size() - 1];

	//Reorder the tree
	int nCurrentIndex = 0;
	int nChild1Index = GetChild1Index(nCurrentIndex);
	int nChild2Index = GetChild2Index(nCurrentIndex);

	//Find smallest child
	int nSmallestIndex = nChild1Index;
	if (m_Data[nChild2Index]->m_nFscore < m_Data[nSmallestIndex]->m_nFscore)
		nSmallestIndex = nChild2Index;

	//Chech if smallest child is less than parent
	while (m_Data[nSmallestIndex]->m_nFscore < m_Data[nCurrentIndex]->m_nFscore)
	{
		//Swap nodes
		GraphNode* temp = m_Data[nSmallestIndex];
		m_Data[nSmallestIndex] = m_Data[nCurrentIndex];
		m_Data[nCurrentIndex] = temp;

		//Update indices
		nCurrentIndex = nSmallestIndex;
		int nChild1Index = GetChild1Index(nCurrentIndex);
		int nChild2Index = GetChild2Index(nCurrentIndex);

		//Find smallest child
		int nSmallestIndex = nChild1Index;
		if (m_Data[nChild2Index]->m_nFscore < m_Data[nSmallestIndex]->m_nFscore)
			nSmallestIndex = nChild2Index;
	}

	m_Data.RemoveAt(Size() - 1);
	return nResult;
}

GraphNode* Heap::Peek()
{
	if (Size() > 0)
		return m_Data[0];

	return nullptr;
}

int Heap::Size()
{
	return m_Data.GetSize();
}

void Heap::Clear()
{
	m_Data.Clear();
}

bool Heap::Empty()
{
	if (Size() > 0)
		return false;
	return true;
}

bool Heap::Contains(GraphNode* Node)
{
	return m_Data.Contains(Node);
}

int Heap::GetParentIndex(int nIndex)
{
	return (nIndex - 1) / 2;
}

int Heap::GetChild1Index(int nIndex)
{
	int nResult = (2 * nIndex) + 1;
	if (nResult < Size())
		return nResult;

	//out of range
	return nIndex;
}

int Heap::GetChild2Index(int nIndex)
{
	int nResult = (2 * nIndex) + 2;
	if (nResult < Size())
		return nResult;

	//Out of range
	return nIndex;
}

