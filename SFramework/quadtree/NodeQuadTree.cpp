#include "NodeQuadTree.h"

s_framework::NodeQuadTree::NodeQuadTree()
{
	this->mId = 1;
	this->mX = 0.0f;
	this->mY = 0.0f;
	this->mHeight = 0.0f;
	this->mWidth = 0.0f;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mListObject = new vector<int>();
}

s_framework::NodeQuadTree::~NodeQuadTree()
{
	mListObject->clear();
	if (this->mNodeTL)
	{
		this->mNodeTL->~NodeQuadTree();
		this->mNodeTR->~NodeQuadTree();
		this->mNodeBL->~NodeQuadTree();
		this->mNodeBR->~NodeQuadTree();
	}
	else
	{
		delete this;
	}
}

s_framework::NodeQuadTree::NodeQuadTree(int id, float x, float y, float width, float height)
{
	this->mId = id;
	this->mX = x;
	this->mY = y;
	this->mHeight = height;
	this->mWidth = width;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mListObject = new vector<int>();
}

RECT s_framework::NodeQuadTree::getBound()
{
	RECT rect;
	rect.top = this->mY;
	rect.left = this->mX;
	rect.bottom = rect.top - this->mHeight;
	rect.right = rect.left + this->mWidth;
	return rect;
}

void s_framework::NodeQuadTree::deleteObjectFromThisNode(GameObject * gameObject)
{
	if (gameObject)
	{
		if (intersect(gameObject->getBound(), this->getBound()))
		{
			if (this->mNodeTL)
			{
				this->mNodeTL->deleteObjectFromThisNode(gameObject);
				this->mNodeTR->deleteObjectFromThisNode(gameObject);
				this->mNodeBL->deleteObjectFromThisNode(gameObject);
				this->mNodeBR->deleteObjectFromThisNode(gameObject);
			}
			else
			{
				if (mListObject->size()>0)
				{
					int size = mListObject->size();
					for (int i = 0; i < mListObject->size(); ++i)
					{
						int id = mListObject->at(i);
						if (mListObject->at(i))
						{
							if (id == gameObject->getObjectID())
							{
								mListObject->erase(mListObject->begin() + i);
							}
						}
					}
				}
			}
		}
	}
}

void s_framework::NodeQuadTree::clear()
{
	if (this->mNodeTL)
		this->mNodeTL->clear();
	if (this->mNodeTR)
		this->mNodeTR->clear();
	if (this->mNodeBL)
		this->mNodeBL->clear();
	if (this->mNodeBR)
		this->mNodeBR->clear();
	if (!this->mNodeTL &&
		!this->mNodeTR &&
		!this->mNodeBL &&
		!this->mNodeBR)
	{
		//delete this;
		return;
	}
}

boolean s_framework::NodeQuadTree::intersect(RECT first, RECT second)
{
	return (first.left < second.right
		&& first.right > second.left
		&& first.top > second.bottom 
		&& first.bottom < second.top);
}

boolean s_framework::NodeQuadTree::isContain(RECT region, RECT entity)
{
	return region.top >= entity.top
		&& region.bottom <= entity.bottom
		&& region.left <= entity.left
		&& region.right >= entity.right;
}