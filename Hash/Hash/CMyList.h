#ifndef MYLIST_2013_02_27
#define MYLIST_2013_02_27

#include <iostream>
#include <vector>

template<class T>
class CMyList
{
public:

	class CNode
	{
		friend class CMyList;
	private:
		T m_data;
		CNode * m_next, *m_prev;

	public:
		CNode(T _data, CNode * _prev = NULL, CNode * _next = NULL) 
			: m_data(_data), m_prev(_prev), m_next(_next)
		{
		}
	};

	class CIterator
	{
	public:
		CNode* m_p;

		CIterator() : m_p(NULL)
		{
	
		}

		CIterator(CNode * _p) : m_p(_p)
		{
			
		}

		~CIterator()
		{
			
		}

		void operator=(CNode * _p)
		{
			m_p = _p;
		}

		void operator=(T * _p)
		{
			m_p = _p;
		}

		bool operator==(CNode * _p)  const
		{
			return m_p == _p;
		}

		bool operator!=(CNode * _p)	const
		{
			return m_p != _p;
		}

		bool operator!=(const CIterator&  it) const
		{
			return m_p != it.m_p;
		}

		bool operator!=(int it)	const
		{
			if (it == NULL)
				return m_p != NULL; 
			return true;
		}

		void operator++()
		{
			m_p = m_p->m_next;
		}

		void operator--()
		{
			m_p = m_p->m_prev;
		}

		CNode * operator->()
		{
			return m_p;
		}

		const T& operator* ()  const
		{
			return m_p->m_data;
		}

		T& operator* ()
		{
			return m_p->m_data;
		}

		
	};


private:
	CNode* m_begin,* m_end;
	int m_size;


public:

	CMyList()
	{
		m_begin = NULL;
		m_end = NULL;
		m_size = 0;
	};

	~CMyList()
	{
		if (m_size == 0)
			return;
		CIterator it = this->m_begin;
		while (it != NULL)
		{
			it = it->m_next;
			if (it != NULL)
				delete it->m_prev;
		}
		delete this->m_end;
	};

	void addBack(T data)
	{
		// if its first element, this->end == NULL
		CNode * n = new CNode(data, this->m_end, NULL);
		if (m_size > 0)
			this->m_end->m_next = n;
		else
			this->m_begin = n;
		this->m_end = n;
		m_size++;
	}
	
	void addFront(T data)
	{
		CNode * n = new CNode(data, NULL, this->m_begin);
		if (m_size > 0)
			this->m_begin->m_prev = n;
		else
			this->m_end = n;
		this->m_begin = n;
		m_size++;
	}			  

	CNode * getNode(int index) const
	{
		if (index + 1 > m_size || m_size == 0)
			return NULL;
		CMyList::CIterator result = this->m_begin;
		for (int i = 0; i < index; ++i)
		{
			++result;
		}
		return result.m_p;
	}

	bool remove(int index)
	{
		CNode * n = getNode(index);
		if (n == NULL)
			return false;
		if (m_size == 1)//n is only
		{
			this->m_begin = NULL;
			this->m_end = NULL;
		}
		else
		if (n->m_prev == NULL) //n is first
		{
			this->m_begin = n->m_next;
			n->m_next->m_prev = NULL;
		}
		else
		if (n->m_next == NULL) //n is last
		{
			this->m_end = n->m_prev;
			n->m_prev->m_next = NULL;
		}
		else
		{
			n->m_prev->m_next = n->m_next;
			n->m_next->m_prev = n->m_prev;
		}
		m_size--;
		delete n;
		return true;
	}

	void printData() const
	{
		if (m_size == 0)
			return;
		int count = 0;
		CMyList::CIterator n = this->m_begin;
		while (n != this->m_end)
		{
			std::cout << count << ": " << n->m_data << std::endl;
			n = n->m_next;
			count++;
		}
		std::cout << count << ": " << n->data << std::endl;
	}

	void clear()
	{
		while (m_size > 0)
			this->remove(0);
	}

	CIterator begin()
	{
		return CIterator(this->m_begin);
	}

	CIterator end()
	{
		return CIterator(NULL);
	}
};

#endif //#ifndef MYLIST_2013_02_27