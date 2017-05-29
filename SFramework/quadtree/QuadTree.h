#pragma once
#include "NodeQuadTree.h"
#include "NodeObject.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../File/FileUtil.h"


using namespace std;
namespace s_framework
{
	class QuadTree
	{
	private:
		NodeQuadTree* mRoot;
		int mMaxId;
	public:
		QuadTree();
		~QuadTree();
		void rebuildQuadTree(std::vector<NodeObject*>& listQuadObj);
		void rebuildQuadTree(const std::string& file);
		void buildQuadTree();
		void addNode(NodeQuadTree*&, NodeQuadTree*&);
		void getListObjectOnscreen(RECT*, NodeQuadTree*&, std::vector<int>&);
		void addGameObjectToQuadTree(GameObject*&);
		void addGameObjectToQuadTree(NodeObject* quadObj);
		void deleteGameObjectFromQuadTree(NodeObject*);
		void clear();
		NodeQuadTree *& searchNode(int iDNode, NodeQuadTree *& node)
		{
			NodeQuadTree* result = nullptr;
			if (iDNode == node->getId())
			{
				return node;
			}
			else
			{
				if (iDNode / 8 != node->getId() / 8)
				{
					if (node->getNodeTL() && !this->searchNode(iDNode, node->getNodeTL()) &&
						node->getNodeTR() && !this->searchNode(iDNode, node->getNodeTR()) &&
						node->getNodeBL() && !this->searchNode(iDNode, node->getNodeBL()) &&
						node->getNodeBR())
					{

						this->searchNode(iDNode, node->getNodeBR());
					}
				}
			}
			return result;
		}
	public:
		NodeQuadTree*& getRoot() { return this->mRoot; };
		void setMaxId(int maxID) { this->mMaxId = maxID; };
	private: 
		bool contain(int ID, const std::vector<int>& list);
	};
}

