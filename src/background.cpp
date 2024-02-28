#include "background.h"
#include "LEAGUE/engine.h"

Background::Background(){
	x = 0;
	y = 0;
	x_vel = 0;
	y_vel = 0;
	loadImage("./assets/tileable_old_school_video_game_grass.jpg");
}

Background::~Background(){

}

void Background::draw(SDL_Renderer* renderer){
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = rect.w;
	dest.h = rect.h;
	int result = SDL_RenderCopy(renderer, texture, NULL, &dest);
	if(result != 0){
		std::cout << SDL_GetError() << std::endl;
	}
}
