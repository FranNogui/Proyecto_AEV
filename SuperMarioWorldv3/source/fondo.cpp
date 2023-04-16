#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void Fondo::CargarTextura(const char* ruta)
{
	SDL_Surface* img = IMG_Load(ruta);
	if (img)
	{
		posicion.w = img->w;
		posicion.h = img->h;
		textura = SDL_CreateTextureFromSurface(renderer, img);
		SDL_FreeSurface(img);
	}
}

Fondo::Fondo(int tipo, float x, float y, Camara* camara)
{
	posicion.x = x;
	posicion.y = y;
	this->camara = camara;
	CargarTextura(RUTA_FONDO);
}

void Fondo::Renderizar()
{
	int posicionDibujoX = posicion.x - camara->x * 0.5f;
	int posicionDibujoY = posicion.y - camara->y;
	if (true)
	{
		SDL_Rect posicionDibujo;
		posicionDibujo = {posicionDibujoX, posicionDibujoY, posicion.w, posicion.h};
		SDL_RenderCopy(renderer, textura, NULL, &posicionDibujo);
	}
}

void Fondo::Destruir()
{
	SDL_DestroyTexture(textura);
}
