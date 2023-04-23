#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

SDL_Texture* NumeroVidas::CargarTextura(const char* ruta)
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

void NumeroVidas::CargarTexturas()
{
	numeros[0] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_0);
	numeros[1] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_1);
	numeros[2] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_2);
	numeros[3] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_3);
	numeros[4] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_4);
	numeros[5] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_5);
	numeros[6] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_6);
	numeros[7] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_7);
	numeros[8] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_8);
	numeros[9] = CargarTextura(RUTA_NUMERO_BLANCO_PEQUENYO_9);

}

NumeroVidas::NumeroVidas(float x, float y, int numVidasInicial)
{
	posicion[0].x = x;
	posicion[0].y = y;
	posicion[1].x = x + 20;
	posicion[1].y = y;
	numVidas = numVidasInicial;
	CargarTexturas();
	switch(numVidas / 10)
	{
		case 0:
			vidas[0] = numeros[0];
			break;
		case 1:
			vidas[0] = numeros[1];
			break;
		case 2:
			vidas[0] = numeros[2];
			break;
		case 3:
			vidas[0] = numeros[3];
			break;
		case 4:
			vidas[0] = numeros[4];
			break;
		case 5:
			vidas[0] = numeros[5];
			break;
		case 6:
			vidas[0] = numeros[6];
			break;
		case 7:
			vidas[0] = numeros[7];
			break;
		case 8:
			vidas[0] = numeros[8];
			break;
		case 9:
			vidas[0] = numeros[9];
			break;
	}
	
	switch(numVidas % 10)
	{
		case 0:
			vidas[1] = numeros[0];
			break;
		case 1:
			vidas[1] = numeros[1];
			break;
		case 2:
			vidas[1] = numeros[2];
			break;
		case 3:
			vidas[1] = numeros[3];
			break;
		case 4:
			vidas[1] = numeros[4];
			break;
		case 5:
			vidas[1] = numeros[5];
			break;
		case 6:
			vidas[1] = numeros[6];
			break;
		case 7:
			vidas[1] = numeros[7];
			break;
		case 8:
			vidas[1] = numeros[8];
			break;
		case 9:
			vidas[1] = numeros[9];
			break;
	}
}

void NumeroVidas::CambiarVida(int incremento)
{
	numVidas = numVidas + incremento;
}

void NumeroVidas::Renderizar()
{
	if (vidas[0])
		SDL_RenderCopy(renderer, vidas[0], NULL, &posicion[0]);
	if (vidas[1])
		SDL_RenderCopy(renderer, vidas[1], NULL, &posicion[1]);
}

void NumeroVidas::Destruir()
{
	for (int i = 0; i < 10; i++)
	{
		SDL_DestroyTexture(numeros[i]);
	}
}
