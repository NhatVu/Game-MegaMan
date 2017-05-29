#include "QuadTree.h"

s_framework::QuadTree::QuadTree()
{
	this->mMaxId = 0;
	this->mRoot = new NodeQuadTree();
	this->mRoot->setId(1);
}

s_framework::QuadTree::~QuadTree()
{
	this->mRoot->~NodeQuadTree();
}

void s_framework::QuadTree::rebuildQuadTree(vector<NodeObject*>& listQuadObj)
{
	// Kiem tra danh sach cac doi tuong.
	if (!listQuadObj.empty())
	{
		int size = listQuadObj.size();
		NodeObject* nodeObj;
		for (int i = 0; i < size; i++)
		{
			nodeObj = listQuadObj.at(i);
			if (nodeObj)
			{
				// Neu doi tuong k con Alive, xoa doi tuong khoi node.
				if (!nodeObj->getGameObject()->IsAlive())
				{
					// Xoa khoi danh sach doi tuong cua node
					this->mRoot->deleteObjectFromThisNode(nodeObj);
					// Xoa khoi danh sach doi tuong
					delete listQuadObj.at(i);
					listQuadObj.erase(listQuadObj.begin() + i);
				}
			}
		}
	}
}

void s_framework::QuadTree::rebuildQuadTree(const string & file)
{
	//Thong tin co ban cua mot node
	int id;
	float x;
	float y;
	float width;
	float height;

	//
	vector<string> result = FileUtil::getInstance()->loadFromFile(file);
	int size = result.size();

	if (size > 0)
	{

		string line;
		vector<string> dataInfo;
		for (int i = 0; i < size; i++)
		{
			line = result.at(i);
			dataInfo = FileUtil::getInstance()->split(line, '\t');
			vector<int>* listIDObject = new vector<int>();
			if (!dataInfo.empty())
			{
				int size = dataInfo.size();
				id = atoi(dataInfo.at(0).c_str());
				x = atof(dataInfo.at(1).c_str());
				y = atof(dataInfo.at(2).c_str());
				width = atof(dataInfo.at(3).c_str());
				height = atof(dataInfo.at(4).c_str());
				if (size > 5)
				{
					for (int j = 5; j < size; j++)
					{

						listIDObject->push_back(atoi(dataInfo.at(j).c_str()));
					}
				}
				NodeQuadTree* node = new NodeQuadTree(id, x, y, width, height);
				node->setListObject(listIDObject);
				this->addNode(node, this->mRoot);
			}
		}
	}
}

void s_framework::QuadTree::buildQuadTree()
{
}

void s_framework::QuadTree::addNode(NodeQuadTree *& node, NodeQuadTree *& root)
{
	if (node->getId() == root->getId())
	{
		//Update thong tin
		root->setX(node->getX());
		root->setY(node->getY());
		root->setWidth(node->getWidth());
		root->setHeight(node->getHeight());
		root->setListObject(node->getListObject());
		return;
	}
	if (node->getId() > root->getId() * 8)
	{
		if (!root->getNodeTL())
		{
			root->getNodeTL() = new NodeQuadTree();
			root->getNodeTL()->setId(root->getId() * 8 + 1);
		}
		if (!root->getNodeTR()) 
		{
			root->getNodeTR() = new NodeQuadTree();
			root->getNodeTR()->setId(root->getId() * 8 + 2);
		}
		if (!root->getNodeBL())
		{
			root->getNodeBL() = new NodeQuadTree();
			root->getNodeBL()->setId(root->getId() * 8 + 3);
		}
		if (!root->getNodeBR())
		{
			root->getNodeBR() = new NodeQuadTree();
			root->getNodeBR()->setId(root->getId() * 8 + 4);
		}

		this->addNode(node, root->getNodeTL());
		this->addNode(node, root->getNodeTR());
		this->addNode(node, root->getNodeBL());
		this->addNode(node, root->getNodeBR());
	}
	else if (node->getId() / 8 == root->getId())
	{
		switch (node->getId() % 8)
		{
		case 1:
		{
			root->setNodeTL(node);
			break;
		}
		case 2:
		{
			root->setNodeTR(node);
			break;
		}
		case 3:
		{
			root->setNodeBL(node);
			break;
		}
		case 4:
		{
			root->setNodeBR(node);
			break;
		}
		}
	}
}

void s_framework::QuadTree::getListObjectOnscreen(RECT * viewBox, NodeQuadTree *& node, vector<int>& listIdObj)
{
	if (viewBox && node)
	{
		// Xen viewPort voi node.
		if (node->isOverlay(viewBox, node->getBound()))
		{
			if (node->getNodeTL())
			{
				this->getListObjectOnscreen(viewBox, node->getNodeTL(), listIdObj);
				this->getListObjectOnscreen(viewBox, node->getNodeTR(), listIdObj);
				this->getListObjectOnscreen(viewBox, node->getNodeBL(), listIdObj);
				this->getListObjectOnscreen(viewBox, node->getNodeBR(), listIdObj);
			}
			// Neu node la node la'
			else
			{
				// Get danh sach doi tuong cua node.
				vector<int>* listItem = node->getListObject();
				if (listItem)
				{
					int size = listItem->size();
					int id;
					for (int i = 0; i < size; i++)
					{
						id = listItem->at(i);
						// Kiem tra doi tuong da ton tai trong d/s doi tuong xen voi viewport hay chua.
						if (!this->contain(id, listIdObj))
						{
							// Add danh sach doi tuong vao danh sach doi tuong tren man hinh.
							listIdObj.push_back(id);
						}
					}
				}
			}
		}
	}
}

void s_framework::QuadTree::addGameObjectToQuadTree(GameObject *& gameObj)
{
	NodeObject* quadObj = new NodeObject(++this->mMaxId, gameObj);
	if (this->mRoot && gameObj)
	{
		this->mRoot->clipObject(quadObj);
	}
}

void s_framework::QuadTree::addGameObjectToQuadTree(NodeObject * gameObj)
{
	this->mRoot->clipObject(gameObj);
}

void s_framework::QuadTree::deleteGameObjectFromQuadTree(NodeObject * gameObject)
{
	if (this->mRoot)
	{
		this->mRoot->deleteObjectFromThisNode(gameObject);
	}
}

void s_framework::QuadTree::clear()
{
	this->mRoot->clear();
}

bool s_framework::QuadTree::contain(int ID, const std::vector<int>& list)
{
	if (!list.empty())
	{
		int size = list.size();
		for (int i = 0; i < size; i++)
		{
			if (list.at(i) == ID)
			{
				return true;
			}
		}
	}
	return false;
}
