#ifndef __T_HASH_H
#define __T_HASH_H

#include <string>
#include <assert.h>
#include "util\t_iterator.h"

template<class T> class THashEntry
{
public:
	THashEntry(const T& data)
		: m_data(data)
		, m_pNext(nullptr)
	{ }

public:
	T				m_data;
	THashEntry<T>*	m_pNext;
};

template<class T> class THash
{
public:
		THash(int iTableSize)
			: m_pTable(nullptr)
			, m_iEntryCount(0)
			, m_iTableSize(iTableSize)
			, m_bInitialized(false)
		{
			InitTable();
		}

		~THash()
		{
			FlushTableContents();
			if (m_pTable != nullptr)
				delete[] m_pTable;
			m_pTable = nullptr;
		}

		void InitTable()
		{
			if (!m_bInitialized && (m_iTableSize > 0))
			{
				m_pTable = reinterpret_cast<THashEntry<T>**>( new size_t[m_iTableSize] );
				assert(m_pTable);
				memset(m_pTable, 0, sizeof(THashEntry<T>*) * m_iTableSize);
				m_bInitialized = true;
			}
		}

		void FlushTableContents()
		{
			if (m_bInitialized && (m_iTableSize > 0))
			{
				int iCurrInd = 0;
				while (iCurrInd < m_iTableSize)
				{
					THashEntry<T>* pEntry = m_pTable[iCurrInd];
					while (pEntry != nullptr)
					{
						THashEntry<T>* pDelEntry = pEntry;
						pEntry = pEntry->m_pNext;
						if (pDelEntry != nullptr)
							delete pDelEntry;
						pDelEntry = nullptr;
						m_pTable[iCurrInd] = nullptr;
					}
					iCurrInd++;
				}
			}
		}

		void Iterate(TIterator<T>* pIter)
		{
			if (m_bInitialized && (m_iTableSize > 0) && (pIter != nullptr))
			{
				int iCurrInd = 0;
				while ((iCurrInd < m_iTableSize) && !pIter->ShouldStop())
				{
					THashEntry<T>* pEntry = m_pTable[iCurrInd];
					while (pEntry != nullptr)
					{
						pIter->Do(pEntry->m_data);
						pEntry = pEntry->m_pNext;
					}
					iCurrInd++;
				}
			}
		}

		unsigned int ComputeHash(const T* pItem) const
		{
			return (pItem->Hash() % m_iTableSize);
		}

		T* Add(const T& rItem)
		{
			return Add(&rItem);
		}

		T* Add(const T* pItem)
		{
			T* pRet = nullptr;
			if (pItem != nullptr)
			{
				unsigned int hash = ComputeHash(pItem);
				if (m_pTable[hash] != nullptr)
					m_iCollisions++;
				
				THashEntry<T>* pEntry = new THashEntry<T>(*pItem);
				pEntry->m_pNext = m_pTable[hash];
				m_pTable[hash] = pEntry;
				pRet = &(pEntry->m_data);
			}

			return pRet;
		}

		T* Find(const T* pItem) const
		{
			if (pItem != nullptr)
			{
				unsigned int hash = ComputeHash(pItem);
				THashEntry<T>* pEntry = m_pTable[hash];
				while (pEntry != nullptr)
				{
					if (pEntry->m_data == *pItem)
						return &(pEntry->m_data);
					pEntry = pEntry->m_pNext;
				}
			}
			return nullptr;
		}

		T* Find(const T& rItem) const
		{
			return Find(&rItem);
		}

		static int StringHashValue(const std::string& str)
		{
			unsigned long hash = 5381;
			for (unsigned int i = 0; i < str.length(); ++i)
			{
				int c = str[i];
				hash = (((hash << 5) + hash) ^ c);
			}
			return hash;
		}

private:
	THashEntry<T>**  m_pTable;
	int				 m_iTableSize;
	int				 m_iEntryCount;
	int				 m_iCollisions;
	bool			 m_bInitialized;
};

#endif // __T_HASH_H