#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

Camara::Camara(float x, float y)
{
	this->x = x;
	this->y = y;
}
