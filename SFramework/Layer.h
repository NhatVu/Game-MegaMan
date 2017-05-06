#ifndef _LAYER_H_
#define _LAYER_H_

#include "Node.h"

namespace s_framework
{
	class Layer: public Node
	{
	public:
		Layer();
		~Layer();

		virtual void update(long delta)override;
	};
}
#endif // !_LAYER_H_



