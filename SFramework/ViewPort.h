#ifndef _VIEW_PORT_H_
#define _VIEW_PORT_H_

#include <d3dx9.h>
#include "Utilities.h"

namespace s_framework{
	class ViewPort
	{
	private:
		static ViewPort* m_instance;
		//D3DXMATRIX m_matrixTransform;
		FPOINT m_position; // vị trí của viewPort, left top. Vẽ sprite vẽ theo center.


		/*   method   */
		ViewPort();
	public:
		static ViewPort* getInstance();
		~ViewPort();

		/*-----------------------------------------
		 * GETTERS AND SETTERS
		 *----------------------------------------*/

		FPOINT getPosition();
		void setPosition(FPOINT p);

		D3DXVECTOR3 worldToViewport(D3DXVECTOR3 p);
	};
}
#endif // !_VIEW_PORT_H_




