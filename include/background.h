#ifndef		__H__BACKGROUND__
#define		__H__BACKGROUND__

#include <iostream>
#include "LEAGUE/common_data_structures.h"

class Background : public Drawable{
	public:
		Background();
		~Background();
		void draw(SDL_Renderer* renderer) override;

	private:
		int x_vel;
		int y_vel;
};



#endif
