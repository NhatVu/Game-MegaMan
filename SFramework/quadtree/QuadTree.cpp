#include "QuadTree.h"
#include "../Trace.h"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str();

using namespace s_framework;

char * __quadtree_file = "..//quadtree.log";

QuadTree::QuadTree()
{
	this->mRoot = new NodeQuadTree();
	this->mRoot->setId(1);
}

s_framework::QuadTree::QuadTree(float width, float height)
{
	this->mRoot = new NodeQuadTree(1, 0, height, width, height);
}

QuadTree::~QuadTree()
{
	this->mRoot->~NodeQuadTree();
}

void QuadTree::rebuildQuadTree(vector<GameObject*>& listQuadObj)
{
	// Kiem tra danh sach cac doi tuong.
	if (!listQuadObj.empty())
	{
		int size = listQuadObj.size();
		GameObject* nodeObj;
		for (int i = 0; i < size; i++)
		{
			nodeObj = listQuadObj.at(i);
			if (nodeObj)
			{
				// Neu doi tuong k con Alive, xoa doi tuong khoi node.
				if (nodeObj->getState() == EState::DIE)
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

boolean isLeaf(NodeQuadTree* node)
{
	return (node->getNodeTL()==NULL && node->getNodeTR() == NULL && node->getNodeBL() == NULL && node->getNodeBR() == NULL);
}

void buildFile(NodeQuadTree * node)
{
	fstream f;
	f.open(__quadtree_file, ios::app);
	//std::string data;

	if (node == NULL)
	{
		return;
	}

	f << node->getId() << '\t'
		<< node->getX() << '\t'
		<< node->getY() << '\t'
		<< node->getWidth() << '\t'
		<< node->getHeight() << '\t';

	if (node->getListObject()->size()>0)
	{
		for (std::vector<int>::iterator it = node->getListObject()->begin(); it != node->getListObject()->end(); ++it) {
			f << *it << '\t';
		}
	}

	f << '\n';
	f.close();

	buildFile(node->getNodeTL());
	buildFile(node->getNodeTR());
	buildFile(node->getNodeBL());
	buildFile(node->getNodeBR());
}

void QuadTree::exportFile()
{
	fstream f;
	f.open(__quadtree_file, ios::out);
	f.clear();
	f.close();
	buildFile(mRoot);
}

NodeQuadTree* buildRecursiveEmptyQuadTree(NodeQuadTree* root, int id, float x, float y, float width, float height, int depth)
{
	if (depth == 5)
	{
		return new NodeQuadTree(id, x, y, width, height);
	}

	if (root == NULL)
	{
		root = new NodeQuadTree(id, x, y, width, height);
	}

	root->setNodeTL(buildRecursiveEmptyQuadTree(root->getNodeTL(), id * 8 + 1, x, y, width / 2, height / 2, depth + 1));
	root->setNodeTR(buildRecursiveEmptyQuadTree(root->getNodeTR(), id * 8 + 2, x + width / 2, y, width / 2, height / 2, depth + 1));
	root->setNodeBL(buildRecursiveEmptyQuadTree(root->getNodeBL(), id * 8 + 3, x, y - height / 2, width / 2, height / 2, depth + 1));
	root->setNodeBR(buildRecursiveEmptyQuadTree(root->getNodeBR(), id * 8 + 4, x + width / 2, y - height / 2, width / 2, height / 2, depth + 1));
}

void QuadTree::builEmptyQuadTree()
{
	buildRecursiveEmptyQuadTree(mRoot, mRoot->getId(), mRoot->getX(), mRoot->getY(), mRoot->getWidth(), mRoot->getHeight(), 1);
	int a = 3;
}

void insertNodeToQuadTree(NodeQuadTree* root, GameObject * gameObj, int depth)
{
	if (depth == 5)
	{
		root->getListObject()->push_back(gameObj->getObjectID());
		return;
	}

	if (NodeQuadTree::intersect(root->getNodeTL()->getBound(), gameObj->getBound()))
	{
		insertNodeToQuadTree(root->getNodeTL(), gameObj, depth + 1);
	}
	else if (NodeQuadTree::intersect(root->getNodeTR()->getBound(), gameObj->getBound()))
	{
		insertNodeToQuadTree(root->getNodeTR(), gameObj, depth + 1);
	}
	else if (NodeQuadTree::intersect(root->getNodeBL()->getBound(), gameObj->getBound()))
	{
		insertNodeToQuadTree(root->getNodeBL(), gameObj, depth + 1);
	}
	else if (NodeQuadTree::intersect(root->getNodeBR()->getBound(), gameObj->getBound()))
	{
		insertNodeToQuadTree(root->getNodeBR(), gameObj, depth + 1);
	}
	else
	{
		root->getListObject()->push_back(gameObj->getObjectID());
	}
}

void QuadTree::insert(vector<GameObject*> listObject)
{
	for (std::vector<GameObject*>::iterator it = listObject.begin(); it != listObject.end(); ++it)
	{
		insertNodeToQuadTree(mRoot, *it, 1);
	}

	int b = 5;
}

bool contain(int ID, const std::vector<int> list)
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

void addNodeToQuadTree(NodeQuadTree* root, NodeQuadTree * node)
{
	int a = 5;
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
			root->setNodeTL(new NodeQuadTree());
			root->getNodeTL()->setId(root->getId() * 8 + 1);
		}

		if (!root->getNodeTR())
		{
			root->setNodeTR(new NodeQuadTree());
			root->getNodeTR()->setId(root->getId() * 8 + 2);
		}

		if (!root->getNodeBL())
		{
			root->setNodeBL(new NodeQuadTree());
			root->getNodeBL()->setId(root->getId() * 8 + 3);
		}

		if (!root->getNodeBR())
		{
			root->setNodeBR(new NodeQuadTree());
			root->getNodeBR()->setId(root->getId() * 8 + 4);
		}

		addNodeToQuadTree(root->getNodeTL(), node);
		addNodeToQuadTree(root->getNodeTR(), node);
		addNodeToQuadTree(root->getNodeBL(), node);
		addNodeToQuadTree(root->getNodeBR(), node);
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

void QuadTree::rebuildQuadTree()
{
	//Thong tin co ban cua mot node
	int id;
	float x;
	float y;
	float width;
	float height;

	//
	vector<string> result = FileUtil::getInstance()->loadFromFile(__quadtree_file);
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

				addNodeToQuadTree(mRoot, node);
			}
		}
	}
}

void addIdToList(NodeQuadTree * root, vector<int>* listIdObject)
{
	vector<int>* listItem = root->getListObject();
	if (listItem && listItem->size() > 0)
	{
		int size = listItem->size();
		int id;
		for (int i = 0; i < size; i++)
		{
			id = listItem->at(i);
			bool found = (find(listIdObject->begin(), listIdObject->end(), id) != listIdObject->end());
			if (!found)
			{
				// Add danh sach doi tuong vao danh sach doi tuong tren man hinh.
				listIdObject->push_back(id);
			}
		}
	}
}

void getListObjectIntersectViewPort(RECT viewBox, NodeQuadTree * root, vector<int>* listIdObj)
{
	if (isLeaf(root))
	{
		addIdToList(root, listIdObj);
		return;
	}

	addIdToList(root, listIdObj);

	if (NodeQuadTree::intersect(viewBox, root->getNodeTL()->getBound()))
	{
		getListObjectIntersectViewPort(viewBox, root->getNodeTL(), listIdObj);
	}

	if (NodeQuadTree::intersect(viewBox, root->getNodeTR()->getBound()))
	{
		getListObjectIntersectViewPort(viewBox, root->getNodeTR(), listIdObj);
	}

	if (NodeQuadTree::intersect(viewBox, root->getNodeBL()->getBound()))
	{
		getListObjectIntersectViewPort(viewBox, root->getNodeBL(), listIdObj);
	}

	if (NodeQuadTree::intersect(viewBox, root->getNodeBR()->getBound()))
	{
		getListObjectIntersectViewPort(viewBox, root->getNodeBR(), listIdObj);
	}
}

vector<int>* QuadTree::getListObjectOnscreen(RECT viewBox, vector<int>* listIdObj)
{
	// Xen viewPort voi node.
	getListObjectIntersectViewPort(viewBox, mRoot, listIdObj);
	return listIdObj;
}

void QuadTree::deleteGameObjectFromQuadTree(GameObject * gameObject)
{
	if (this->mRoot)
	{
		this->mRoot->deleteObjectFromThisNode(gameObject);
	}
}

void QuadTree::clear()
{
	this->mRoot->clear();
}
