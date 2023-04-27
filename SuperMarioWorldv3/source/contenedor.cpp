#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

SDL_Texture* Contenedor::CargarTextura(const char* ruta)
{
	SDL_Surface* img = IMG_Load(ruta);
	SDL_Texture* tex = NULL;
	if (img)
	{
		tex = SDL_CreateTextureFromSurface(renderer, img);
		posicion.w = img->w;
		posicion.h = img->h;
		SDL_FreeSurface(img);
	}
	return tex;
}

void Contenedor::CargarTexturas()
{
	contenedores[0] = CargarTextura(RUTA_CONTENEDOR_VACIO);
	contenedores[1] = CargarTextura(RUTA_CONTENEDOR_SETA);
}

Contenedor::Contenedor(float x, float y, bool conSeta)
{
	posicion.x = x;
	posicion.y = y;
	CargarTexturas();
	if (conSeta)
		contenedor = contenedores[1];
	else
		contenedor = contenedores[0];
}

void Contenedor::CambiarSeta()
{
	if (conSeta)
		conSeta = false;
	else
		conSeta = true;
}

void Contenedor::Renderizar()
{
	if (!conSeta)
		SDL_RenderCopy(renderer, contenedores[0], NULL, &posicion);
	else
		SDL_RenderCopy(renderer, contenedores[1], NULL, &posicion);
}

void Contenedor::Destruir()
{
	SDL_DestroyTexture(contenedores[0]);
	SDL_DestroyTexture(contenedores[1]);
}
