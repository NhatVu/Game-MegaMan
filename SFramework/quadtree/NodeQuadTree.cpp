#include "NodeQuadTree.h"

s_framework::NodeQuadTree::NodeQuadTree()
{
	this->mId = 0;
	this->mX = 0.0f;
	this->mY = 0.0f;
	this->mHeight = 0.0f;
	this->mWidth = 0.0f;
	this->mListObject = new vector<int>();
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
}

s_framework::NodeQuadTree::~NodeQuadTree()
{
	if (mListObject)
	{
		mListObject->clear();
		delete mListObject;
	}
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
	this->mListObject = new vector<int>();
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
	this->mNodeTL = nullptr;
}

RECT * s_framework::NodeQuadTree::getBound()
{
	RECT* rect = new RECT();
	rect->top = this->mX;
	rect->left = this->mY;
	rect->bottom = rect->top + this->mHeight;
	rect->right = rect->left + this->mWidth;
	return rect;
}

RECT * s_framework::NodeQuadTree::getBound(BOX  box)
{
	RECT* rect = new RECT();
	rect->top = box.x;
	rect->left = box.y;
	rect->bottom = box.x + box.height;
	rect->right = box.y + box.width;
	return rect;
}

void s_framework::NodeQuadTree::clipObject(NodeObject *& gameObject)
{

	if (gameObject->getGameObject())
	{
		RECT* objectRect = this->getBound(gameObject->getGameObject()->getCollisionBox());
		if (isOverlay(objectRect, this->getBound()))
		{
			if (this->mNodeTL)
			{
				this->mNodeTL->clipObject(gameObject);
				this->mNodeTR->clipObject(gameObject);
				this->mNodeBL->clipObject(gameObject);
				this->mNodeBR->clipObject(gameObject);
			}
			else
			{
				// TT
				// kiem tra co phai la nut la hay k
				//if(this->GetHeight > )
				//{}
				this->mListObject->push_back(gameObject->getGameObject()->getObjectID());
			}
		}
	}
}

void s_framework::NodeQuadTree::deleteObjectFromThisNode(NodeObject *& gameObject)
{
	if (gameObject)
	{
		RECT* objectRect = this->getBound(gameObject->getGameObject()->getCollisionBox()); 
		if (isOverlay(objectRect, this->getBound()))
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
				if (this->mListObject)
				{
					int size = this->mListObject->size();
					for (int i = 0; i < this->mListObject->size(); ++i)
					{
						int id = this->mListObject->at(i);
						if (this->mListObject->at(i))
						{
							if (id == gameObject->getGameObject()->getObjectID())
							{
								this->mListObject->erase(this->mListObject->begin() + i);
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

bool s_framework::NodeQuadTree::isOverlay(RECT *first, RECT *second)
{
	return !(first->left < second->right 
		|| first->right > second->left
		||first->top > second->bottom || first->bottom < second->top);
}
