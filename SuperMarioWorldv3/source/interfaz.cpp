#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void Interfaz::CargarTextura(const char* ruta)
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

Interfaz::Interfaz(int tipo, float x, float y, Camara* camara)
{
	posicion.x = x;
	posicion.y = y;
	this->camara = camara;
	switch (tipo)
	{
		case 1:
			CargarTextura(RUTA_MARIO_TEXTO);
			break;
		case 2:
			CargarTextura(RUTA_TIME_INTERFAZ);3
			break;
		case 3:
			CargarTextura(RUTA_VIDA_INTERFAZ);
			break;
		case 4:
			CargarTextura(RUTA_DINERO_INTERFAZ);
			break;
		case 6:
			CargarTextura(RUTA_CONTENEDOR_VACIO);
			break;
		case 7:
			CargarTextura(RUTA_CONTENEDOR_SETA);
			break;
		case 8:
			CargarTextura(RUTA_NUMERO_AMARILLO_0);
			break;
		case 9:
			CargarTextura(RUTA_NUMERO_AMARILLO_1);
			break;
		case 10:
			CargarTextura(RUTA_NUMERO_AMARILLO_2);
			break;
		case 11:
			CargarTextura(RUTA_NUMERO_AMARILLO_3);
			break;
		case 12:
			CargarTextura(RUTA_NUMERO_AMARILLO_4);
			break;
		case 13:
			CargarTextura(RUTA_NUMERO_AMARILLO_5);
			break;
		case 14:
			CargarTextura(RUTA_NUMERO_AMARILLO_6);
			break;
		case 15:
			CargarTextura(RUTA_NUMERO_AMARILLO_7);
			break;
		case 16:
			CargarTextura(RUTA_NUMERO_AMARILLO_8);
			break;
		case 17:
			CargarTextura(RUTA_NUMERO_AMARILLO_9);
			break;
		case 18:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_0);
			break;
		case 19:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_1);
			break;
		case 20:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_2);
			break;
		case 21:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_3);
			break;
		case 22:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_4);
			break;
		case 23:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_5);
			break;
		case 24:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_6);
			break;
		case 25:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_7);
			break;
		case 26:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_8);
			break;
		case 27:
			CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_9);
			break;
	}
}

void Interfaz::Renderizar()
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

void Interfaz::Destruir()
{
	SDL_DestroyTexture(textura);
}
