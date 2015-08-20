#ifndef JL_NODE_H
#define JL_NODE_H

#include <map>
#include <string>
#include <vector>
#include "BaseMove.h"
#include "BaseData.h"

namespace joblevel
{

class Node
{
public:
	typedef Node* NodePtr;
	typedef std::map<std::string, BaseDataPtr> DataMap;
	typedef std::vector<NodePtr> NodePtrVector;

	static const NodePtr NULL_NODE_PTR;
	static NodePtr& GetRoot();

public:
	~Node();

	bool isRoot() const;

	//  nodeptr accessor
	bool hasParent() const;
	NodePtr getParent() const;
	bool hasLeft() const;
	NodePtr getLeft() const;
	// get N'th left, 0 is self
	NodePtr getLeft(int i);
	bool hasRight() const;
	NodePtr getRight() const;
	// get N'th right, 0 is self
	NodePtr getRight(int i);
	int getIndex() const;
	NodePtr getLeftMost();

	// children
	NodePtr generateChild(BaseMovePtr pMove);
	NodePtrVector& getChildren();
	bool hasChildren() const;
	bool hasChild(size_t index) const;
	size_t getChildrenSize() const;
	NodePtr getChild(size_t index) const;
	NodePtr getChildWithMove(BaseMovePtr pMove) const;
	int getChildIndex(NodePtr pChild) const;

	// delete
	void deleteSubTree();
	bool deleteChild(size_t index);
	bool deleteChild(NodePtr pChild);

	// move
	BaseMovePtr getMove() const;

	// data
	const DataMap& getDataMap() const;
	BaseDataPtr getData(const std::string& sDataGroup);
	void setData(const std::string& sDataGroup, BaseDataPtr pData);
	
	// comment
	void setComment(std::string sComment);
	void appendComment(std::string sComment);
	std::string getComment() const;

	// sequence
	int getSequence() const;

private:
	Node();
	Node(NodePtr pParent, BaseMovePtr pMove);
	Node(const Node&);
	Node& operator=(const Node&);

private:
	NodePtr m_pParent;
	NodePtr m_pLeft;
	NodePtr m_pRight;
	NodePtrVector m_children;
	
	BaseMovePtr m_pMove;
	DataMap m_dataMap;
	std::string m_sComment;
	int m_iSequence;
};

typedef Node* NodePtr;
typedef std::vector<NodePtr> NodePtrVector;

}

#endif
