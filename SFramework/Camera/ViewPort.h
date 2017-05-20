﻿#ifndef _VIEW_PORT_H_
#define _VIEW_PORT_H_

#include <d3dx9.h>
#include "../Utilities.h"
#include <map>
#include <vector>
using namespace std;

namespace s_framework{
	class ViewPort
	{
	private:
		static ViewPort* m_instance;
		//D3DXMATRIX m_matrixTransform;
		FPOINT m_position; // vị trí của viewPort, left top. Vẽ sprite vẽ theo center.
		BOX viewportBoundary;
		std::map<FPOINT, BOX> mapViewport;
		std::vector<BOX> listViewportState;

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

		BOX getViewportBoundary(){ return this->viewportBoundary; }
		void setViewportBoundary(BOX value){
			this->viewportBoundary = value;
		}

		void resetViewport(FPOINT position){

			this->m_position = position;
			this->viewportBoundary = mapViewport[position];
		}

		std::vector<BOX> getListViewportState(){ return this->listViewportState; }

		void setMapViewport(std::map<FPOINT, BOX> value){ this->mapViewport = value; }
		std::map<FPOINT, BOX> getMapViewport(){ return this->mapViewport; }

		D3DXVECTOR3 worldToViewport(D3DXVECTOR3 p);
	};
}
#endif // !_VIEW_PORT_H_
