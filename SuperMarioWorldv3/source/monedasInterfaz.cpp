#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

SDL_Texture* MonedasInterfaz::CargarTextura(const char* ruta)
{
	SDL_Surface* img = IMG_Load(ruta);
	SDL_Texture* tex = NULL;
	if (img)
	{
		tex = SDL_CreateTextureFromSurface(renderer, img);
		for (int i = 0; i < 2; i++)
		{
			posicion[i].w = img->w;
			posicion[i].h = img->h;
		}
		SDL_FreeSurface(img);
	}
	return tex;
}

void MonedasInterfaz::CargarTexturas()
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

MonedasInterfaz::MonedasInterfaz(float x, float y, int monedasInicial)
{
	monedasAct = monedasInicial;
	CargarTexturas();
	for (int i = 0; i < 2; i++)
	{
		posicion[i].x = x + posicion[i].w * i;
		posicion[i].y = y;
	}
	switch(monedasAct / 10)
	{
		case 0:
			monedas[0] = numeros[0];
			break;
		case 1:
			monedas[0] = numeros[1];
			break;
		case 2:
			monedas[0] = numeros[2];
			break;
		case 3:
			monedas[0] = numeros[3];
			break;
		case 4:
			monedas[0] = numeros[4];
			break;
		case 5:
			monedas[0] = numeros[5];
			break;
		case 6:
			monedas[0] = numeros[6];
			break;
		case 7:
			monedas[0] = numeros[7];
			break;
		case 8:
			monedas[0] = numeros[8];
			break;
		case 9:
			monedas[0] = numeros[9];
			break;
	}
	
	switch(monedasAct % 10)
	{
		case 0:
			monedas[1] = numeros[0];
			break;
		case 1:
			monedas[1] = numeros[1];
			break;
		case 2:
			monedas[1] = numeros[2];
			break;
		case 3:
			monedas[1] = numeros[3];
			break;
		case 4:
			monedas[1] = numeros[4];
			break;
		case 5:
			monedas[1] = numeros[5];
			break;
		case 6:
			monedas[1] = numeros[6];
			break;
		case 7:
			monedas[1] = numeros[7];
			break;
		case 8:
			monedas[1] = numeros[8];
			break;
		case 9:
			monedas[1] = numeros[9];
			break;
	}
}

void MonedasInterfaz::CambiarMonedas(int incremento)
{
	monedasAct = monedasAct + incremento;
	
	switch(monedasAct / 10)
	{
		case 0:
			monedas[0] = numeros[0];
			break;
		case 1:
			monedas[0] = numeros[1];
			break;
		case 2:
			monedas[0] = numeros[2];
			break;
		case 3:
			monedas[0] = numeros[3];
			break;
		case 4:
			monedas[0] = numeros[4];
			break;
		case 5:
			monedas[0] = numeros[5];
			break;
		case 6:
			monedas[0] = numeros[6];
			break;
		case 7:
			monedas[0] = numeros[7];
			break;
		case 8:
			monedas[0] = numeros[8];
			break;
		case 9:
			monedas[0] = numeros[9];
			break;
	}
	
	switch(monedasAct % 10)
	{
		case 0:
			monedas[1] = numeros[0];
			break;
		case 1:
			monedas[1] = numeros[1];
			break;
		case 2:
			monedas[1] = numeros[2];
			break;
		case 3:
			monedas[1] = numeros[3];
			break;
		case 4:
			monedas[1] = numeros[4];
			break;
		case 5:
			monedas[1] = numeros[5];
			break;
		case 6:
			monedas[1] = numeros[6];
			break;
		case 7:
			monedas[1] = numeros[7];
			break;
		case 8:
			monedas[1] = numeros[8];
			break;
		case 9:
			monedas[1] = numeros[9];
			break;
	}
}

void MonedasInterfaz::Renderizar()
{
	if (monedas[0])
		SDL_RenderCopy(renderer, monedas[0], NULL, &posicion[0]);
	if (monedas[1])
		SDL_RenderCopy(renderer, monedas[1], NULL, &posicion[1]);
}

void MonedasInterfaz::Destruir()
{
	for (int i = 0; i < 10; i++)
	{
		SDL_DestroyTexture(numeros[i]);
	}
}
