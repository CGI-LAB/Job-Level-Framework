#include "SearchTree.h"
#include <fstream>
#include <iostream>

namespace joblevel
{

SearchTree::SearchTree()
	: m_pRoot(Node::GetRoot()),
	  m_pCurrentNode(m_pRoot)
{
}

SearchTree::~SearchTree()
{
	m_pRoot->deleteSubTree();
}

NodePtr SearchTree::getRoot() const
{
	return m_pRoot;
}

NodePtr SearchTree::getCurrentNode() const
{
	return m_pCurrentNode;
}

void SearchTree::setCurrentNode(NodePtr pNode)
{
	if (pNode != nullptr)
		m_pCurrentNode = pNode;
}

bool SearchTree::loadSgfFile(std::string sFileName)
{
	return false;
}

bool SearchTree::saveSgfFile(std::string sFileName)
{
	std::ofstream fout(sFileName.c_str());
	if (!fout)
		return false;
	fout << m_sgfSerializer.serialize() << std::endl;
	fout.close();
	return true;
}

}
