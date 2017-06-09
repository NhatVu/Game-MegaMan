#pragma once
#include "NodeQuadTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "../File/FileUtil.h"


using namespace std;
namespace s_framework
{
	class QuadTree
	{
	private:
		NodeQuadTree* mRoot;
	public:
		QuadTree();
		QuadTree(float width, float height);
		~QuadTree();
		void rebuildQuadTree(std::vector<GameObject*>& listQuadObj);
		void rebuildQuadTree();
		void builEmptyQuadTree();
		void insert(vector<GameObject*> listObject);
		vector<int>* getListObjectOnscreen(RECT, std::vector<int>*);
		void deleteGameObjectFromQuadTree(GameObject*);
		void clear();
		void exportFile();

		NodeQuadTree *& searchNode(int iDNode, NodeQuadTree * node)
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
		NodeQuadTree* getRoot() { return mRoot;};
	};
}

