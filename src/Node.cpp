#include "Node.h"
#include <iostream>
#include <sstream>

namespace joblevel
{

NodePtr& Node::GetRoot()
{
	static NodePtr pRoot = new Node;
	return pRoot;
}

Node::Node()
	: m_pParent(nullptr),
	  m_pLeft(nullptr),
	  m_pRight(nullptr),
	  m_pMove(),
	  m_iSequence(0) 
{
}

Node::Node(NodePtr pParent, BaseMovePtr pMove)
	: m_pParent(pParent),
	  m_pLeft(nullptr),
	  m_pRight(nullptr),
	  m_pMove(pMove),
	  m_iSequence(pParent?pParent->getSequence() + 1:0)
{	
}

Node::~Node()
{
	if (hasChildren())
		deleteSubTree();
	for (DataMap::iterator it = m_dataMap.begin(); it != m_dataMap.end(); ++it)
		delete (it->second);
	m_dataMap.clear();
	if (m_pMove != nullptr)
		delete m_pMove;
}

bool Node::isRoot() const
{
	return !hasParent();
}

bool Node::hasParent() const
{
	return m_pParent != nullptr;
}

NodePtr Node::getParent() const
{
	return m_pParent;
}

bool Node::hasLeft() const
{
	return m_pLeft != nullptr;
}

NodePtr Node::getLeft() const
{
	return m_pLeft;
}

NodePtr Node::getLeft(int i)
{
	int iCount = i;
	NodePtr pTraversedNode = this;
	while ((iCount--) && pTraversedNode != nullptr)
		pTraversedNode = pTraversedNode->getLeft();
	return pTraversedNode;
}

bool Node::hasRight() const
{
	return m_pRight != nullptr;
}

NodePtr Node::getRight() const
{
	return m_pRight;
}

NodePtr Node::getRight(int i)
{
	int iCount = i;
	NodePtr pTraversedNode = this;
	while ((iCount--) && pTraversedNode != nullptr)
		pTraversedNode = pTraversedNode->getRight();
	return pTraversedNode;
}

int Node::getIndex() const
{
	NodePtr pTraversedNode = m_pLeft;
	int iIndex = 0;
	while (pTraversedNode != nullptr) {
		pTraversedNode = pTraversedNode->getLeft();
		iIndex++;
	}
	return iIndex;
}

NodePtr Node::getLeftMost()
{
	NodePtr pTraversedNode = this;
	while (pTraversedNode->hasLeft()) 
		pTraversedNode = pTraversedNode->getLeft();
	return pTraversedNode;
}

NodePtr Node::generateChild(BaseMovePtr pMove)
{
	NodePtr pChild = new Node(this, pMove);
	if(getChildrenSize() != 0) {
		pChild->m_pLeft = m_children.back();
		m_children.back()->m_pRight = pChild;
	}
	m_children.push_back(pChild);
	return pChild;
}

NodePtrVector& Node::getChildren()
{
	return m_children;
}

bool Node::hasChildren() const
{
	return !m_children.empty();
}

bool Node::hasChild(size_t index) const
{
	return index < getChildrenSize();
}

size_t Node::getChildrenSize() const
{
	return m_children.size();
}

NodePtr Node::getChild(size_t index) const
{
	if (index >= m_children.size())
		return nullptr;
	return m_children[index];
}

NodePtr Node::getChildWithMove(BaseMovePtr pMove) const
{
	for (NodePtrVector::const_iterator it = m_children.begin(); it != m_children.end(); ++it) {
		if ((*it)->getMove()->isSameMove(pMove))
			return *it;
	}
	return nullptr;
}

int Node::getChildIndex(NodePtr pChild) const
{
	int iIndex = -1;
	for (NodePtrVector::const_iterator it = m_children.begin(); it != m_children.end(); ++it) {
		iIndex++;
		if ((*it) == pChild)
			return iIndex;
	}
	return -1;
}

void Node::deleteSubTree()
{
	for (NodePtrVector::iterator it = m_children.begin(); it != m_children.end(); ++it) {
		NodePtr pChild = *it;
		pChild->deleteSubTree();
		pChild->m_pLeft = nullptr;
		pChild->m_pRight = nullptr;
		pChild->m_pParent = nullptr;
		delete pChild;
	}
	m_children.clear();
}

bool Node::deleteChild(size_t index)
{
	if (index < getChildrenSize()) {
		deleteChild(m_children[index]);
		return true;
	} else {
		return false;
	}
}

bool Node::deleteChild(NodePtr pChild)
{
	for (NodePtrVector::iterator it = m_children.begin(); it != m_children.end(); ++it) {
		if (*it == pChild) {
			pChild->deleteSubTree();
			if (pChild->hasLeft())
				pChild->getLeft()->m_pRight = pChild->getRight();
			if (pChild->hasRight())
				pChild->getRight()->m_pLeft = pChild->getLeft();
			pChild->m_pLeft = nullptr;
			pChild->m_pRight = nullptr;
			pChild->m_pParent = nullptr;
			m_children.erase(it);
			delete pChild;
			return true;
		}
	}
	return false;
}

BaseMovePtr Node::getMove() const
{
	return m_pMove;
}

const Node::DataMap& Node::getDataMap() const
{
	return m_dataMap;
}

BaseDataPtr Node::getData(const std::string& sDataGroup)
{
	if (m_dataMap.find(sDataGroup) == m_dataMap.end())
		return nullptr;
	return m_dataMap[sDataGroup];
}

void Node::setData(const std::string& sDataGroup, BaseDataPtr pData)
{
	m_dataMap[sDataGroup] = pData;
}

void Node::setComment(std::string sComment)
{
	m_sComment = sComment;
}

void Node::appendComment(std::string sComment)
{
	m_sComment += sComment;
}

std::string Node::getComment() const
{
	return m_sComment;
}

int Node::getSequence() const
{
	return m_iSequence;
}

}
