#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

SDL_Texture* TiempoInterfaz::CargarTextura(const char* ruta)
{
	SDL_Surface* img = IMG_Load(ruta);
	SDL_Texture* tex = NULL;
	if (img)
	{
		tex = SDL_CreateTextureFromSurface(renderer, img);
		for (int i = 0; i < 3; i++)
		{
			posicion[i].w = img->w;
			posicion[i].h = img->h;
		}
		SDL_FreeSurface(img);
	}
	return tex;
}

void TiempoInterfaz::CargarTexturas()
{
	numeros[0] = CargarTextura(RUTA_NUMERO_AMARILLO_0);
	numeros[1] = CargarTextura(RUTA_NUMERO_AMARILLO_1);
	numeros[2] = CargarTextura(RUTA_NUMERO_AMARILLO_2);
	numeros[3] = CargarTextura(RUTA_NUMERO_AMARILLO_3);
	numeros[4] = CargarTextura(RUTA_NUMERO_AMARILLO_4);
	numeros[5] = CargarTextura(RUTA_NUMERO_AMARILLO_5);
	numeros[6] = CargarTextura(RUTA_NUMERO_AMARILLO_6);
	numeros[7] = CargarTextura(RUTA_NUMERO_AMARILLO_7);
	numeros[8] = CargarTextura(RUTA_NUMERO_AMARILLO_8);
	numeros[9] = CargarTextura(RUTA_NUMERO_AMARILLO_9);
}


TiempoInterfaz::TiempoInterfaz(float x, float y, int tiempoInicial)
{
	CargarTexturas();
	for (int i = 0; i < 3; i++)
	{
		posicion[i].x = x + posicion[i].w * i;
		posicion[i].y = y;
	}
	tiempoReal = tiempoInicial;
	tiempoAct = tiempoInicial;

	switch(tiempoAct / 100)
	{
		case 0:
			tiempo[0] = numeros[0];
			break;
		case 1:
			tiempo[0] = numeros[1];
			break;
		case 2:
			tiempo[0] = numeros[2];
			break;
		case 3:
			tiempo[0] = numeros[3];
			break;
		case 4:
			tiempo[0] = numeros[4];
			break;
		case 5:
			tiempo[0] = numeros[5];
			break;
		case 6:
			tiempo[0] = numeros[6];
			break;
		case 7:
			tiempo[0] = numeros[7];
			break;
		case 8:
			tiempo[0] = numeros[8];
			break;
		case 9:
			tiempo[0] = numeros[9];
			break;
	}

	switch (tiempoAct / 10 % 10)
	{
		case 0:
			tiempo[1] = numeros[0];
			break;
		case 1:
			tiempo[1] = numeros[1];
			break;
		case 2:
			tiempo[1] = numeros[2];
			break;
		case 3:
			tiempo[1] = numeros[3];
			break;
		case 4:
			tiempo[1] = numeros[4];
			break;
		case 5:
			tiempo[1] = numeros[5];
			break;
		case 6:
			tiempo[1] = numeros[6];
			break;
		case 7:
			tiempo[1] = numeros[7];
			break;
		case 8:
			tiempo[1] = numeros[8];
			break;
		case 9:
			tiempo[1] = numeros[9];
			break;
	}

	switch (tiempoAct % 10)
	{
		case 0:
			tiempo[2] = numeros[0];
			break;
		case 1:
			tiempo[2] = numeros[1];
			break;
		case 2:
			tiempo[2] = numeros[2];
			break;
		case 3:
			tiempo[2] = numeros[3];
			break;
		case 4:
			tiempo[2] = numeros[4];
			break;
		case 5:
			tiempo[2] = numeros[5];
			break;
		case 6:
			tiempo[2] = numeros[6];
			break;
		case 7:
			tiempo[2] = numeros[7];
			break;
		case 8:
			tiempo[2] = numeros[8];
			break;
		case 9:
			tiempo[2] = numeros[9];
			break;
	}
}

void TiempoInterfaz::Renderizar()
{
	tiempoReal -= 1.0f / 60.0f;
	tiempoAct = int(tiempoReal);
	
	switch(tiempoAct / 100)
	{
		case 0:
			tiempo[0] = numeros[0];
			break;
		case 1:
			tiempo[0] = numeros[1];
			break;
		case 2:
			tiempo[0] = numeros[2];
			break;
		case 3:
			tiempo[0] = numeros[3];
			break;
		case 4:
			tiempo[0] = numeros[4];
			break;
		case 5:
			tiempo[0] = numeros[5];
			break;
		case 6:
			tiempo[0] = numeros[6];
			break;
		case 7:
			tiempo[0] = numeros[7];
			break;
		case 8:
			tiempo[0] = numeros[8];
			break;
		case 9:
			tiempo[0] = numeros[9];
			break;
	}

	switch (tiempoAct / 10 % 10)
	{
		case 0:
			tiempo[1] = numeros[0];
			break;
		case 1:
			tiempo[1] = numeros[1];
			break;
		case 2:
			tiempo[1] = numeros[2];
			break;
		case 3:
			tiempo[1] = numeros[3];
			break;
		case 4:
			tiempo[1] = numeros[4];
			break;
		case 5:
			tiempo[1] = numeros[5];
			break;
		case 6:
			tiempo[1] = numeros[6];
			break;
		case 7:
			tiempo[1] = numeros[7];
			break;
		case 8:
			tiempo[1] = numeros[8];
			break;
		case 9:
			tiempo[1] = numeros[9];
			break;
	}

	switch (tiempoAct % 10)
	{
		case 0:
			tiempo[2] = numeros[0];
			break;
		case 1:
			tiempo[2] = numeros[1];
			break;
		case 2:
			tiempo[2] = numeros[2];
			break;
		case 3:
			tiempo[2] = numeros[3];
			break;
		case 4:
			tiempo[2] = numeros[4];
			break;
		case 5:
			tiempo[2] = numeros[5];
			break;
		case 6:
			tiempo[2] = numeros[6];
			break;
		case 7:
			tiempo[2] = numeros[7];
			break;
		case 8:
			tiempo[2] = numeros[8];
			break;
		case 9:
			tiempo[2] = numeros[9];
			break;
	}
	
	if (tiempo[0])
		SDL_RenderCopy(renderer, tiempo[0], NULL, &posicion[0]);
	if (tiempo[1])
		SDL_RenderCopy(renderer, tiempo[1], NULL, &posicion[1]);
	if (tiempo[2])
		SDL_RenderCopy(renderer, tiempo[2], NULL, &posicion[2]);
}

void TiempoInterfaz::Destruir()
{
	for (int i = 0; i < 10; i++)
	{
		SDL_DestroyTexture(numeros[i]);
	}
}
