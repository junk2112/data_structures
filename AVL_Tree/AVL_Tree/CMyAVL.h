#ifndef C_MY_AVL_16_04_2014
#define C_MY_AVL_16_04_2014

#include "CMyMemoryManager.h"
struct pair
{
	pair(std::string _key = "", std::string _value = "") : key(_key), value(_value) {}
	std::string key, value;
};

//Compare возвращает >0, если first > second
//					 <0, если first < second
//					  0, если first == second


template <class T, class S>
class CMyAVL
{
	struct Node
	{

		T * m_key;
		S * m_value;

		Node * m_left; //указатель на левое поддерево
		Node * m_right; //указатель на правое поддерево
		Node * m_parent; //указатель на родителя
		short int m_height;	//высота дерева с этой вершины

		Node(T * key, S * value, Node * parent = NULL) : m_key(key), m_value(value), 
				m_left(NULL), m_right(NULL), m_height(0), m_parent(parent)
		{

		}

		Node() : m_key (new T()), m_value(NULL),
			m_left(NULL), m_right(NULL), m_height(0), m_parent(NULL)
		{

		}

		short int getBFactor()
		{
			if (m_left && m_right)
				return m_left->m_height - m_right->m_height;
			if (!(m_left || m_right))
				return 0;
			if (!m_left)
				return -1 - m_right->m_height;
			if (!m_right)
				return m_left->m_height + 1;	
		}

		void updateHeight()
		{
			if (m_left && m_right)
				m_height = m_left->m_height > m_right->m_height ? 
						   m_left->m_height + 1 : m_right->m_height + 1;
			else
			if (!(m_left || m_right))
			{
				m_height = 0;
			}
			else
			if (!m_left)
			{
				m_height = m_right->m_height + 1;
			}
			else
			if (!m_right)
			{
				m_height = m_left->m_height + 1;
			}
		}

	};

	CMyMemoryManager<Node> m_memManager;
	Node * m_pHead;
	int m_size;

	int Compare(pair * left, pair * right) const
	{	
		//CString
		//return ((CString)left).Compare(((CString)right));
		//std::string
		
		int result1 = left->key.compare(right->key);
		if (result1)
			return result1;
		return left->value.compare(right->value);

		
	}

public:
	int getHeight()
	{
		return m_pHead->m_height;
	}

	int size() const
	{
		return 	m_size;
	}

	CMyAVL()
	{
		m_pHead = NULL;
		m_size = 0;
	}

	CMyAVL(T * key, S * value)
	{
		m_pHead = m_memManager.newData();//new Node(key, value);
		*m_pHead = Node(key, value);
		m_size = 1;
	}

	bool insert(T& key, S& value)
	{
		if (m_pHead == NULL)
		{
			m_pHead = m_memManager.newData();//new Node(key, value);
			*m_pHead = Node(&key, &value);
			m_size = 1;
			return true;
		}
		else
		{
			Node * current = m_pHead;
			while (true)
			{
				int resCompare = Compare(current->m_key, &key);
				if (resCompare == 0) //Элемент с таким ключем уже добавлен
					return false;
				if (resCompare > 0)
				{	//двигаемся налево
					if (current->m_left != NULL)
					{
						current = current->m_left;
					}
					else
					{
						current->m_left = m_memManager.newData();//new Node(key, value);
						*current->m_left = Node(&key, &value, current);

						update(current->m_left);
						break;
					}
				}
				if (resCompare < 0)
				{	//двигаемся направо
					if (current->m_right != NULL)
					{
						current = current->m_right;
					}
					else
					{
						current->m_right = m_memManager.newData();//new Node(key, value);
						*current->m_right = Node(&key, &value, current);

						update(current->m_right);
						break;
					}
				}
			}
			m_size++;
			return true;
		}
	}

	bool value(T& key)
	{
		//if (!m_size)
		//	return NULL;
		Node * current = m_pHead;
		while (true)
		{
			int resCompare = Compare(current->m_key, &key);
			if (resCompare == 0)
			{
				return true;
			}
			if (resCompare > 0)
			{	//налево
				if (current->m_left != NULL)
					current = current->m_left;
				else
					return false;
			}
			if (resCompare < 0)
			{	//направо
				if (current->m_right != NULL)
					current = current->m_right;
				else
					return false;
			}
		}
	}

	void update(Node * current)
	{
		do		
		{
			current = current->m_parent;
			current->updateHeight();
			short int bFactor = current->getBFactor();
			if (abs(bFactor) > 1)
			{
				if (bFactor > 1)
				{
					short int leftBFactor = current->m_left->getBFactor();
					if (leftBFactor == 1)
						simpleRightRotation(current);
					else
					{
						simpleLeftRotation(current->m_left);
						simpleRightRotation(current);
					}
				}
				if (bFactor < -1)
				{
					short int rightBFactor = current->m_right->getBFactor();
					if (rightBFactor == -1)
						simpleLeftRotation(current);
					else
					{
						simpleRightRotation(current->m_right);
						simpleLeftRotation(current);
					}
				}
			}
			
		} while (current != m_pHead);
	}

	void simpleRightRotation(Node * parent)
	{
		Node * left = parent->m_left;
		parent->m_left = left->m_right;	
		if (left->m_right)
			left->m_right->m_parent = parent;
		left->m_right = parent;
		left->m_parent = parent->m_parent;
		
		if (!parent->m_parent)
		{
			m_pHead = left;
		}
		else
		{
			if (parent->m_parent->m_right == parent)
				parent->m_parent->m_right = left;
			else
				parent->m_parent->m_left = left;
		}

		parent->m_parent = left;
		parent->updateHeight();
		left->updateHeight();

	}

	void simpleLeftRotation(Node * parent)
	{
		Node * right = parent->m_right;
		parent->m_right = right->m_left;
		if (right->m_left)
			right->m_left->m_parent = parent;
		right->m_left = parent;
		right->m_parent = parent->m_parent;

		if (!parent->m_parent)
		{
			m_pHead = right;
		}
		else
		{
			if (parent->m_parent->m_left == parent)
				parent->m_parent->m_left = right;
			else
				parent->m_parent->m_right = right;
		}

		parent->m_parent = right;
		parent->updateHeight();
		right->updateHeight();
	}


};


#endif //#ifndef C_MY_AVL_16_04_2014