#ifndef _SCENE_H_
#define _SCENE_H_

#include "Node.h"
#include <vector>
#include "GameObject.h"

using namespace std;

namespace s_framework
{
	class Scene : public Node
	{
	private:
		//vector<GameObject*> mListObject;
	public:
		Scene();
		~Scene();

		//void render() override;
		virtual void update(long delta) override;
		//void addGameObject(GameObject* object);
		//void addGameObjects(vector<GameObject*> listObject);
		//vector<GameObject*> getListGameObject(){ return this->mListObject; };
	};

}
#endif // !_SCENE_H_


