#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void ObjetoInterfazEstatico::CargarTextura(const char* ruta)
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

ObjetoInterfazEstatico::ObjetoInterfazEstatico(float x, float y, const char* ruta)
{
	posicion.x = x;
	posicion.y = y;
	CargarTextura(ruta);
}

void ObjetoInterfazEstatico::Renderizar()
{
	if (textura)
		SDL_RenderCopy(renderer, textura, NULL, &posicion);
}

void ObjetoInterfazEstatico::Destruir()
{
	SDL_DestroyTexture(textura);
}
