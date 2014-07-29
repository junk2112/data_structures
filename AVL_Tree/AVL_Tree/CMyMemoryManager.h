#ifndef C_MY_MEMORY_MANAGER_15_03_2014
#define C_MY_MEMORY_MANAGER_15_03_2014

#include "CMyList.h"
template<class T>
class CMyMemoryManager
{
private:
	int m_BlkSize;
	CMyList <T*> m_Data;
	T* m_pCurrentData;
	T* m_pCurrentBlk;

public:
	CMyMemoryManager(int blkSize = 1024) : m_BlkSize(blkSize), m_pCurrentBlk(NULL), m_pCurrentData(NULL) 
	{

	};

	~CMyMemoryManager()
	{
		for (CMyList<T*>::CIterator it = m_Data.begin(); it != m_Data.end(); ++it)
		{
			T* pData = *it;
			*it = NULL;
			delete[] pData;
		}
	};

	T* newData()
	{
		if (m_pCurrentBlk == NULL || (m_pCurrentData - m_pCurrentBlk) >= m_BlkSize)
		{
			T* pData = new T[m_BlkSize];
			m_Data.addBack(pData);
			m_pCurrentBlk = pData;
			m_pCurrentData = pData;
		}
		return m_pCurrentData++;
	};

};

#endif//#ifndef C_MY_MEMORY_MANAGER_15_03_2014