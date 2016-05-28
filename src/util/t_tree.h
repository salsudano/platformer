#ifndef __T_RTREE_H
#define __T_RTREE_H

#include <assert.h>
#include <vector>

#include "util\t_rect.h"

static const int MaxNodeChildren = 2;
static const int MaxNodeData	 = 2;

template<typename T> class BranchNode;

template<typename T> 
class Node
{
public:
	Node() : m_pParent(nullptr) { }
	Node(const T* pData, const Node* pParent = nullptr)
		: m_BoundingBox((pData != nullptr) ? pData->BoundingBox() : TRect<float>())
		, m_pParent(pParent)
	{ }
	virtual	~Node() { }

	virtual int	  Render(sf::RenderWindow& window) = 0;

	virtual bool  FindCollisions(const TRect<float>& rect, std::vector<T>& lsCollisions) const = 0;

	virtual bool  Add(const T* pData, BranchNode<T>* pParentBranch) = 0;
	virtual bool  IsFull() const									= 0;

	const Node<T>*		 Parent()		const { return m_pParent;	  }
	const TRect<float>&	 BoundingBox()	const { return m_BoundingBox; }

	bool ExpandBoundingBox(const TRect<float>& rect)
	{
		if (m_BoundingBox.IsEmpty())
		{
			m_BoundingBox = rect;
			return false;
		}
		m_BoundingBox.Include(rect);
		return true;
	}

protected:
	const Node<T>*	m_pParent;
	TRect<float>	m_BoundingBox;
};

template<typename T> 
class LeafNode : public Node<T>
{
public:
	LeafNode(const T* pData, const Node* pParent)
		: Node<T>(pData, pParent)
	{
		m_lsData.push_back(pData);
		ExpandBoundingBox(pData->BoundingBox());
	}

	~LeafNode() 
	{ 
	}
	
	int Render(sf::RenderWindow& window) override
	{
		sf::RectangleShape rectShape;
		rectShape.setPosition(m_BoundingBox.PtA());
		rectShape.setSize(TPoint<float>(m_BoundingBox.Width(), m_BoundingBox.Height()));
		rectShape.setOutlineColor(sf::Color::Red);
		rectShape.setFillColor(sf::Color::Transparent);
		rectShape.setOutlineThickness(7);
		window.draw(rectShape);

		for (const auto& data : m_lsData)
		{
			sf::RectangleShape rectShape2;
			rectShape2.setPosition(data->BoundingBox().PtA());
			rectShape2.setSize(TPoint<float>(data->BoundingBox().Width(), data->BoundingBox().Height()));
			rectShape2.setOutlineColor(sf::Color::White);
			rectShape2.setFillColor(sf::Color::Transparent);
			rectShape2.setOutlineThickness(5);
			window.draw(rectShape2);
		}
		return 0;
	}

	bool Add(const T* pData, BranchNode<T>* pParentBranch)
	{
		if (!this->IsFull())
		{
			m_lsData.push_back(pData);
			ExpandBoundingBox(pData->BoundingBox());
		}
		else 
		{
			float minOverlapArea = std::numeric_limits<float>::max();
			int idxA = -1; int idxB = -1;
			// need to split this leaf. We're already at the data limit.
			for (unsigned int i = 0; i < m_lsData.size(); ++i)
			{
				const T* pA = m_lsData[i];
				const TRect<float>& rectA = pA->BoundingBox();
				for (unsigned int j = i + 1; j < m_lsData.size(); ++j)
				{
					const T* pB = m_lsData[j];
					const TRect<float>& rectB = pB->BoundingBox();
					float overlapArea = rectA.Intersection(rectB).Area();
					if (overlapArea < minOverlapArea)
					{
						idxA = i; idxB = j;
						minOverlapArea = overlapArea;
					}
				}
			}

			assert(idxA >= 0 && idxB >= 0);
			
			BranchNode<T>* pBranch = new BranchNode<T>();
			pBranch->AddChild(new LeafNode(m_lsData[idxA], pBranch));
			pBranch->AddChild(new LeafNode(m_lsData[idxB], pBranch));

			for (unsigned int i = 0; i < m_lsData.size(); ++i)
			{
				if (i == idxA || i == idxB)
					continue;
				pBranch->Add(m_lsData[i], pBranch);
			}

			pParentBranch->ReplaceChild(this, pBranch);
		}
		return true;
	}

	bool FindCollisions(const TRect<float>& rect, std::vector<T>& lsCollisions) const override
	{
		unsigned int initialCount = lsCollisions.size();
		if (m_BoundingBox.Intersects(rect))
		{
			for (const auto& pNode : m_lsData)
			{
				if (pNode->BoundingBox().Intersects(rect))
					lsCollisions.push_back(*pNode);
			}
		}

		return initialCount < lsCollisions.size();
	}

	bool IsFull() const 
	{
		return (m_lsData.size() >= MaxNodeData);
	}

private:
	std::vector<const T*> m_lsData;
};


template<typename T> 
class BranchNode : public Node<T>
{
public:
	BranchNode() { }
	BranchNode(const T* pData, const Node* pParent = nullptr)
		: Node(pData, pParent)
	{
		LeafNode<T>* pLeaf = new LeafNode<T>(pData, pParent);
		m_lsChildren.push_back(pLeaf);
	}

	~BranchNode()
	{
		for (auto& pChild : m_lsChildren)
		{
			delete pChild;
			pChild = nullptr;
		}
	}

	int Render(sf::RenderWindow& window) override
	{
		sf::RectangleShape rectShape;
		rectShape.setPosition(m_BoundingBox.PtA());
		rectShape.setSize(TPoint<float>(m_BoundingBox.Width(), m_BoundingBox.Height()));
		rectShape.setOutlineColor(sf::Color::Green);
		rectShape.setFillColor(sf::Color::Transparent);
		rectShape.setOutlineThickness(10);
		window.draw(rectShape);

		for (auto& child : m_lsChildren)
			child->Render(window);

		return 0;
	}

	bool AddChild(Node<T>* pNode)
	{
		assert(!IsFull());
		m_lsChildren.push_back(pNode);
		ExpandBoundingBox(pNode->BoundingBox());
		return true;
	}

	bool ReplaceChild(const LeafNode<T>* pLeaf, BranchNode<T>* pBranch)
	{
		for (auto& pChild : m_lsChildren)
		{
			// address compare
			if (pChild == pLeaf)
			{
				delete pChild;
				pChild = pBranch;
				return true;
			}
		}
		return false;
	}

	bool Add(const T* pData, BranchNode<T>* pParentBranch)
	{
		bool ret = false;

		if (m_lsChildren.size() == 0)
			m_lsChildren.push_back(new LeafNode<T>(pData, this));
		else
		{
			float maxOverlapArea = 0;
			float minExpansionArea = std::numeric_limits<float>::max();
			const TRect<float>& dataRect = pData->BoundingBox();

			Node<T>* pBestChild = nullptr;
			for (const auto& pChild : m_lsChildren)
			{
				const TRect<float>& childRect = pChild->BoundingBox();
				if (childRect.Contains(dataRect))
				{
					pBestChild = pChild;
					break;
				}
				else if (childRect.Intersects(dataRect))
				{
					const float overlapArea = childRect.Intersection(dataRect).Area();
					if (overlapArea > maxOverlapArea)
					{
						maxOverlapArea = overlapArea;
						pBestChild = pChild;
					}
				}
				else if (maxOverlapArea == 0)
				{
					TRect<float> expandedRect = childRect;
					expandedRect.Include(dataRect);
					const float expansionArea = expandedRect.Area() - childRect.Area();
					if (expansionArea < minExpansionArea)
					{
						minExpansionArea = expansionArea;
						pBestChild = pChild;
					}
				}
			}

			if (maxOverlapArea == 0)
				m_lsChildren.push_back(new LeafNode<T>(pData, this));
			else if (pBestChild != nullptr)
				ret = pBestChild->Add(pData, this);
		}

		ExpandBoundingBox(pData->BoundingBox());

		return true;
	}

	bool FindCollisions(const TRect<float>& rect, std::vector<T>& lsCollisions) const override
	{
		bool ret = false;
		for (const auto& pNode : m_lsChildren)
			ret |= pNode->FindCollisions(rect, lsCollisions);
		return ret;
	}

private:
	bool IsFull() const
	{
		return m_lsChildren.size() >= MaxNodeChildren;
	}

private:
	std::vector<Node<T>*> m_lsChildren;
};

template<typename T> class RTree
{
public:
	RTree()
		: m_pRoot(nullptr)
	{ }

	~RTree() 
	{
		if (m_pRoot != nullptr)
			delete m_pRoot;
		m_pRoot = nullptr;
	}

	int Render(sf::RenderWindow& window)
	{
		if (m_pRoot != nullptr)
			return m_pRoot->Render(window);
		return 0;
	}

	bool Insert(const T* pData)
	{
		if (m_pRoot == nullptr)
			m_pRoot = new BranchNode<T>();
		return m_pRoot->Add(pData, m_pRoot);
	}

	bool FindCollisions(const TRect<float>& rect, std::vector<T>& lsCollisions) const
	{
		if (m_pRoot != nullptr)
			return m_pRoot->FindCollisions(rect, lsCollisions);
		return false;
	}

private:
	BranchNode<T>*	 m_pRoot;
};

#endif // __T_RTREE_H