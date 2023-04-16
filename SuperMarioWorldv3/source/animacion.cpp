#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

SDL_Texture* Animacion::CargarTextura(const char* ruta)
{
	SDL_Surface* img = IMG_Load(ruta);
	SDL_Texture* tex = NULL;
	if (img)
	{
		tex = SDL_CreateTextureFromSurface(renderer, img);
		SDL_FreeSurface(img);
	}
	return tex;
}

Animacion::Animacion()
{
	nFrames = 0; nTicksPorFrame = 0;
	for (int i = 0; i < 64; i++)
		frames[i] = NULL;
	textura = NULL;
	tickActual = 0;
}

void Animacion::CrearAnimacion(int nFrames, int nTicksPorFrame, const char* rutas[])
{
	this->nFrames = nFrames;
	this->nTicksPorFrame = nTicksPorFrame;
	for (int i = 0; i < nFrames; i++)
		frames[i] = CargarTextura(rutas[i]);
	textura = frames[0];
	tickActual = 0;
}

void Animacion::Reiniciar()
{
	textura = frames[0];
	tickActual = 0;
}

void Animacion::Renderizar()
{
	tickActual++;
	if (tickActual >= nFrames * nTicksPorFrame + nTicksPorFrame)
	{
		tickActual = -1;
		textura = frames[0];
		return;
	}
	for (int i = 0; i < nFrames; i++)
	{
		if (tickActual < i * nTicksPorFrame + nTicksPorFrame)
		{
			textura = frames[i];
			break;
		}
	}
	
}

void Animacion::Destruir()
{
	for (int i = 0; i < nFrames; i++)
		SDL_DestroyTexture(frames[i]);
}

