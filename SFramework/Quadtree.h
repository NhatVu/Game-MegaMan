#define MAX_LEVEL                5
#define MAX_OBJECT_IN_REGION     4

#include <d3d9.h>
#include <d3dx9.h>

#include <list>
#include "GameObject.h"

using namespace std;
namespace s_framework {
	class Quadtree
	{
	private:
		int            m_level;
		BOX*          m_region;
		list<GameObject*> m_objects_list;
		Quadtree**     m_nodes;

		bool           IsContain(GameObject* entity);
		void           Split();
	public:
		Quadtree();
		
		Quadtree(int level, BOX* region);
		~Quadtree();

		void           Clear();
		void           Insert(GameObject* entity);
		static Quadtree* CreateQuadTree(list<GameObject*> game_objects);
		list<GameObject*>          Retrieve(list<GameObject*> return_objects_list, GameObject* entity);
		void Release();
	};
}



