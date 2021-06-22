#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include "GraphNode.h"
template <typename T>
class DynamicArray
{
public:
	DynamicArray(int nInitialSize = 1)
	{
		m_pData = new T[nInitialSize];
		m_nCapicity = nInitialSize;
		m_nUsed = 0;
	}

	~DynamicArray()
	{
		delete[] m_pData;
		m_pData = nullptr;
	}

	void Add(T value)
	{
		CheckForResize();

		m_pData[m_nUsed] = value;
		++m_nUsed;
	}

	void Insert(int nIndex, T value)
	{
		CheckForResize();

		for (int i = m_nUsed - 1; i >= nIndex; --i)
		{
			m_pData[i + 1] = m_pData[i];
		}

		m_pData[nIndex] = value;
		++m_nUsed;
	}

	void Remove(T value)
	{
		int nIndex = Find(value);
		if (nIndex >= 0)
		{
			RemoveAt(nIndex);
		}
	}

	void RemoveAt(int nIndex)
	{
		for (int i = 0; i < m_nUsed; ++i)
		{
			if (m_pData[i] == m_pData[nIndex])
			{
				m_pData[i] = m_pData[m_nUsed - 1];
				m_pData[m_nUsed - 1] = 0;
			}
		}
		--m_nUsed;
	}

	int Find(T value)
	{
		for (int i = 0; i < m_nUsed; ++i)
		{
			if (m_pData[i] == value)
				return i;
		}
	}

	T& operator[](int nIndex)
	{
		if (nIndex >= m_nUsed)
			throw std::out_of_range("out of range");
		return m_pData[nIndex];
	}

	int GetSize()
	{
		return m_nUsed;
	}

	void Clear()
	{
		m_nUsed = 0;
	}

	bool Contains(GraphNode* node)
	{
		for (int i = 0; i < m_nUsed; ++i)
		{
			if (m_pData[i] == node)
				return true;
		}
		return false;
	}

private:
	void CheckForResize()
	{
		if (m_nUsed >= m_nCapicity)
		{
			m_nCapicity *= 2;
			T* pNewData = new T[m_nCapicity];
			memcpy(pNewData, m_pData, sizeof(T) * m_nUsed);

			delete[] m_pData;
			m_pData = pNewData;
		}
	}

	T* m_pData;
	int m_nCapicity;
	int m_nUsed;
};

