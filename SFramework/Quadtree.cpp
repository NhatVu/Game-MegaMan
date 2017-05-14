#include "Quadtree.h"

using namespace s_framework;

Quadtree::Quadtree()
{
}


Quadtree::~Quadtree()
{
}

void Quadtree::Clear()
{
	//Clear all nodes
	if (m_nodes)
	{
		for (int i = 0; i < 4; i++)
		{
			m_nodes[i]->Clear();
			delete m_nodes[i];
		}
		delete[] m_nodes;
	}

	//Clear current quadtree
	m_objects_list.clear;

	m_objects_list.remove;

	delete m_region;
}

bool Quadtree::IsContain(GameObject* entity)
{
	BOX* bound = entity->getCollisionBox;

	return !(bound->x + bound->width < m_region->x ||
		bound->y + bound->height < m_region->y ||
		bound->x > m_region->x + m_region->width ||
		bound->y > m_region->y + m_region->height);
}

void Quadtree::Split()
{
	m_nodes = new Quadtree*[4];

	m_nodes[0] = new Quadtree(m_level + 1,
		new BOX(m_region->x, m_region->y, m_region->width / 2, m_region->height / 2));
	m_nodes[1] = new Quadtree(m_level + 1,
		new BOX(m_region->x + m_region->width / 2, m_region->y, m_region->width / 2, m_region->height / 2));
	m_nodes[2] = new Quadtree(m_level + 1,
		new BOX(m_region->x, m_region->y + m_region->height / 2, m_region->width / 2, m_region->height / 2));
	m_nodes[3] = new Quadtree(m_level + 1,
		new BOX(m_region->x + m_region->width / 2,
			m_region->y + m_region->height / 2, m_region->width / 2, m_region->height / 2));
}

void Quadtree::Insert(GameObject* entity)
{
	//Insert entity into corresponding nodes
	if (m_nodes)
	{
		if (m_nodes[0]->IsContain(entity))
			m_nodes[0]->Insert(entity);
		if (m_nodes[1]->IsContain(entity))
			m_nodes[1]->Insert(entity);
		if (m_nodes[2]->IsContain(entity))
			m_nodes[2]->Insert(entity);
		if (m_nodes[3]->IsContain(entity))
			m_nodes[3]->Insert(entity);

		return; // Return here to ignore rest.
	}

	//Insert entity into current quadtree
	if (this->IsContain(entity))
		m_objects_list.push_back(entity);

	//Split and move all objects in list into it’s corresponding nodes
	if (m_objects_list.size() > MAX_OBJECT_IN_REGION && m_level < MAX_LEVEL)
	{
		Split();

		while (!m_objects_list.empty())
		{
			if (m_nodes[0]->IsContain(m_objects_list.back()))
				m_nodes[0]->Insert(m_objects_list.back());
			if (m_nodes[1]->IsContain(m_objects_list.back()))
				m_nodes[1]->Insert(m_objects_list.back());
			if (m_nodes[2]->IsContain(m_objects_list.back()))
				m_nodes[2]->Insert(m_objects_list.back());
			if (m_nodes[3]->IsContain(m_objects_list.back()))
				m_nodes[3]->Insert(m_objects_list.back());

			m_objects_list.pop_back();
		}
	}
}

Quadtree* s_framework::Quadtree::CreateQuadTree(list<GameObject*> game_objects)
{
	Quadtree* quadtree = new Quadtree(1, new BOX(0, 0, 800, 600));


	for (auto i = game_objects.begin(); i != game_objects.end(); i++)
		quadtree->Insert(*i);
	return quadtree;
}

list<GameObject*> Quadtree::Retrieve(list<GameObject*> return_objects_list, GameObject* entity)
{
	if (m_nodes)
	{
		if (m_nodes[0]->IsContain(entity))
			m_nodes[0]->Retrieve(return_objects_list, entity);
		if (m_nodes[1]->IsContain(entity))
			m_nodes[1]->Retrieve(return_objects_list, entity);
		if (m_nodes[2]->IsContain(entity))
			m_nodes[2]->Retrieve(return_objects_list, entity);
		if (m_nodes[3]->IsContain(entity))
			m_nodes[3]->Retrieve(return_objects_list, entity);

		return; // Return here to ignore rest.
	}

	//Add all entities in current region into return_objects_list
	if (this->IsContain(entity))
	{
		for (auto i = m_objects_list.begin(); i != m_objects_list.end(); i++)
		{
			if (entity != *i)
				return_objects_list.push_back(*i);
		}
	}
}

void s_framework::Quadtree::Release()
{
	this->Release();
}
