#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void Decoracion::CargarTextura(const char* ruta)
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

Decoracion::Decoracion(int tipo, float x, float y, Camara* camara)
{
	posicion.x = x;
	posicion.y = y;
	this->camara = camara;
	switch (tipo)
	{
		case 1:
			CargarTextura(RUTA_CESPED_1);
			break;
		case 2:
			CargarTextura(RUTA_CESPED_2);
			break;
		case 3:
			CargarTextura(RUTA_CESPED_3);
			break;
		case 4:
			CargarTextura(RUTA_CESPED_4);
			break;
		case 5:
			CargarTextura(RUTA_CESPED_5);
			break;
		case 6:
			CargarTextura(RUTA_CESPED_6);
			break;
		case 7:
			CargarTextura(RUTA_CESPED_7);
			break;
		case 8:
			CargarTextura(RUTA_CARTEL);
			break;
		case 9:
			CargarTextura(RUTA_FINAL_NIVEL);
			break;
	}
}

void Decoracion::Renderizar()
{
	int posicionDibujoX = posicion.x - camara->x;
	int posicionDibujoY = posicion.y - camara->y;
	if (textura && 
		posicionDibujoX + posicion.w > -50 && posicionDibujoX < SCREEN_W + 50 && 
		posicionDibujoY > -50 && posicionDibujoY + posicion.h < SCREEN_H + 50)
	{
		SDL_Rect posicionDibujo;
		posicionDibujo = {posicionDibujoX, posicionDibujoY, posicion.w, posicion.h};
		SDL_RenderCopy(renderer, textura, NULL, &posicionDibujo);
	}
}

void Decoracion::Destruir()
{
	SDL_DestroyTexture(textura);
}
