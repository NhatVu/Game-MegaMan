#pragma once
#include <stdio.h>
#include <vector>
#include "../Utilities.h"
#include "../GameObject.h"
#include "../Trace.h"

using namespace std;
namespace s_framework {
	class NodeQuadTree
	{
	private:
		// ID of node
		int mId;

		// position
		float mX;
		float mY;

		// width and height
		float mWidth;
		float mHeight;

		// 4 nodes
		NodeQuadTree* mNodeTL;
		NodeQuadTree* mNodeTR;
		NodeQuadTree* mNodeBL;
		NodeQuadTree* mNodeBR;

		vector<int>* mListObject;
	public:
		NodeQuadTree();
		~NodeQuadTree();
		NodeQuadTree(int id, float x, float y, float width, float height);

		RECT getBound();
		void deleteObjectFromThisNode(GameObject*);
		void clear();
		
		// detect intersect between 2 RECT
		static boolean intersect(RECT first, RECT second);
		static boolean isContain(RECT region, RECT entity);
	public:
		// Getter and setter 
		int getId() { 
			return this->mId;
		}

		void setId(int id) { 
			this->mId = id;
		}

		float getX() {
			return this->mX;
		}

		void setX(float x)
		{
			this->mX = x;
		}

		float getY() {
			return this->mY;
		}

		void setY(float y)
		{
			this->mY = y;
		}

		float getWidth()
		{
			return mWidth;
		}

		void setWidth(float width)
		{
			this->mWidth = width;
		}

		float getHeight()
		{
			return mHeight;
		}

		void setHeight(float height)
		{
			this->mHeight = height;
		}

		NodeQuadTree*& getNodeTL()
		{
			return this->mNodeTL;
		}

		void setNodeTL(NodeQuadTree* node)
		{
			this->mNodeTL = node;
		}

		NodeQuadTree* getNodeTR()
		{
			return this->mNodeTR;
		}

		void setNodeTR(NodeQuadTree* node)
		{
			this->mNodeTR = node;
		}

		NodeQuadTree* getNodeBL()
		{
			return this->mNodeBL;
		}

		void setNodeBL(NodeQuadTree* node)
		{
			this->mNodeBL = node;
		}

		NodeQuadTree* getNodeBR()
		{
			return this->mNodeBR;
		}

		void setNodeBR(NodeQuadTree* node)
		{
			this->mNodeBR = node;
		}

		vector<int>* getListObject()
		{
			return mListObject;
		}

		void setListObject(vector<int>* list)
		{
			this->mListObject = list;
		}
	};
}

