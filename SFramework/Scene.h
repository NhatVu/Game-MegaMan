#ifndef _SCENE_H_
#define _SCENE_H_

#include "Node.h"

namespace s_framework
{
	class Scene : public Node
	{
	public:
		Scene();
		~Scene();

		//void render() override;
		virtual void update(long delta) override;
	};

}
#endif // !_SCENE_H_


