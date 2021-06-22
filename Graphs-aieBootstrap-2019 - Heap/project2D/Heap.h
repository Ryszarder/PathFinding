#pragma once
#include "DynamicArray.h"
#include "GraphNode.h"

class Heap
{
public:
	Heap();
	~Heap();

	void Push(GraphNode* nValue);
	GraphNode* Pop();
	GraphNode* Peek();

	int Size();
	void Clear();

	bool Empty();
	bool Contains(GraphNode* Node);

private:
	int GetParentIndex(int nIndex);
	int GetChild1Index(int nIndex);
	int GetChild2Index(int nIndex);

	DynamicArray<GraphNode*> m_Data;
};

