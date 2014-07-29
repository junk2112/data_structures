#ifndef C_MY_HASH_TABLE_15_04_2014
#define C_MY_HASH_TABLE_15_04_2014

#include "../../AVL_Tree/AVL_Tree/CMyMemoryManager.h"

template<class T, class S>
class CMyHashTable
{
protected:
	struct Node {
		Node(T * key = new T(), S * value = NULL, Node * next = NULL) 
				: m_key(key), m_value(value), m_next(next)
		{

		}
		
		bool empty()
		{
			return (*m_key == T());
		}

		T * m_key;
		S * m_value;
		Node * m_next;
	};

	Node * m_pHashTable; 
	unsigned long long m_TableSize;
	unsigned long long m_CurrentSize;
	CMyMemoryManager<Node> m_Nodes;

	unsigned int m_collisiumCount;
public:
	//хэш функция
	unsigned long int ptrFunc(const T * item)	const
	{
		//CString* str = (CString*)item;
		std::string * str = (std::string*)(item);
		unsigned long hash = 5381;
		for (int i = 0; i < str->length(); ++i)
		{
			hash = ((hash << 5) + hash) + str->operator[](i);
		}
		return hash; 
	}
	//std::string
	int Compare(const T * left, const T * right) const
	{
		std::string str1 = *left;
		std::string str2 = *right;
		return str1.compare(str2);
	}	
	//CString
	/*int Compare(T * left, T * right) const
	{
		return ((CString*)left)->Compare(*((CString*)right));
	}*/	  


	CMyHashTable(long long size = 1000000) 
	{
		m_TableSize = size * 2;
		m_pHashTable = new Node [m_TableSize];
		m_CurrentSize = 0;
		m_collisiumCount = 0;
		for (int i = 0; i < m_TableSize; ++i)
		{
			m_pHashTable[i] = Node();
		}
	};

	~CMyHashTable()
	{
		delete[] m_pHashTable;
	};

	bool Add(T& key, S& value)
	{
		bool isAdded = false;
		unsigned long int hash = ptrFunc(&key);
		unsigned long int idx = hash % m_TableSize;
		Node * current = m_pHashTable + idx;
		while (!isAdded)
			if (current->empty())
			{
				*current = Node(&key, &value);
				isAdded = true;
				m_CurrentSize++;
				break;
			}
			else
			{
				if (!Compare(current->m_key, &key))
				{
					isAdded = false;
					break;
				}
				if (current->m_next == NULL)
				{
					current->m_next = m_Nodes.newData();
					current = current->m_next;
				}
				else
					current = current->m_next;
				//std::cout << "collisium " << idx << std::endl;
				m_collisiumCount++;
			}
		return isAdded;
	}

	//NULL если не нашел
	S * Search(const T& key) const
	{
		unsigned long int hash = ptrFunc(&key);
		unsigned long int idx = hash % m_TableSize;
		Node * current = m_pHashTable + idx;
		while (current != NULL)
		{
			if (!Compare(current->m_key, &key))
			{
				return current->m_value;
			}
			current = current->m_next;
		}
		return NULL;
	}

	unsigned int size()
	{
		return m_CurrentSize;
	}

	unsigned int getCollisiumCount()
	{
		return m_collisiumCount;
	}
};

#endif //#ifndef C_MY_HASH_TABLE_15_04_2014