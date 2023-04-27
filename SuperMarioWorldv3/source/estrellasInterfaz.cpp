#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

SDL_Texture* EstrellasInterfaz::CargarTextura(const char* ruta)
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

void EstrellasInterfaz::CargarTexturas()
{
	numeros[0] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_0);
	numeros[1] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_1);
	numeros[2] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_2);
	numeros[3] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_3);
	numeros[4] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_4);
	numeros[5] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_5);
	numeros[6] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_6);
	numeros[7] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_7);
	numeros[8] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_8);
	numeros[9] = CargarTextura(RUTA_NUMERO_BLANCO_GRANDE_9);

}

EstrellasInterfaz::EstrellasInterfaz(float x, float y, int estrellasInicial)
{
	estrellasAct = estrellasInicial;
	CargarTexturas();
	for (int i = 0; i < 2; i++)
	{
		posicion[i].x = x + posicion[i].w * i;
		posicion[i].y = y;
	}
	switch(estrellasAct / 10)
	{
		case 0:
			estrellas[0] = numeros[0];
			break;
		case 1:
			estrellas[0] = numeros[1];
			break;
		case 2:
			estrellas[0] = numeros[2];
			break;
		case 3:
			estrellas[0] = numeros[3];
			break;
		case 4:
			estrellas[0] = numeros[4];
			break;
		case 5:
			estrellas[0] = numeros[5];
			break;
		case 6:
			estrellas[0] = numeros[6];
			break;
		case 7:
			estrellas[0] = numeros[7];
			break;
		case 8:
			estrellas[0] = numeros[8];
			break;
		case 9:
			estrellas[0] = numeros[9];
			break;
	}
	
	switch(estrellasAct % 10)
	{
		case 0:
			estrellas[1] = numeros[0];
			break;
		case 1:
			estrellas[1] = numeros[1];
			break;
		case 2:
			estrellas[1] = numeros[2];
			break;
		case 3:
			estrellas[1] = numeros[3];
			break;
		case 4:
			estrellas[1] = numeros[4];
			break;
		case 5:
			estrellas[1] = numeros[5];
			break;
		case 6:
			estrellas[1] = numeros[6];
			break;
		case 7:
			estrellas[1] = numeros[7];
			break;
		case 8:
			estrellas[1] = numeros[8];
			break;
		case 9:
			estrellas[1] = numeros[9];
			break;
	}
}

void EstrellasInterfaz::CambiarEstrellas(int incremento)
{
	estrellasAct = estrellasAct + incremento;
	
	switch(estrellasAct / 10)
	{
		case 0:
			estrellas[0] = numeros[0];
			break;
		case 1:
			estrellas[0] = numeros[1];
			break;
		case 2:
			estrellas[0] = numeros[2];
			break;
		case 3:
			estrellas[0] = numeros[3];
			break;
		case 4:
			estrellas[0] = numeros[4];
			break;
		case 5:
			estrellas[0] = numeros[5];
			break;
		case 6:
			estrellas[0] = numeros[6];
			break;
		case 7:
			estrellas[0] = numeros[7];
			break;
		case 8:
			estrellas[0] = numeros[8];
			break;
		case 9:
			estrellas[0] = numeros[9];
			break;
	}
	
	switch(estrellasAct % 10)
	{
		case 0:
			estrellas[1] = numeros[0];
			break;
		case 1:
			estrellas[1] = numeros[1];
			break;
		case 2:
			estrellas[1] = numeros[2];
			break;
		case 3:
			estrellas[1] = numeros[3];
			break;
		case 4:
			estrellas[1] = numeros[4];
			break;
		case 5:
			estrellas[1] = numeros[5];
			break;
		case 6:
			estrellas[1] = numeros[6];
			break;
		case 7:
			estrellas[1] = numeros[7];
			break;
		case 8:
			estrellas[1] = numeros[8];
			break;
		case 9:
			estrellas[1] = numeros[9];
			break;
	}
}

void EstrellasInterfaz::Renderizar()
{
	if (estrellas[0])
		SDL_RenderCopy(renderer, estrellas[0], NULL, &posicion[0]);
	if (estrellas[1])
		SDL_RenderCopy(renderer, estrellas[1], NULL, &posicion[1]);
}

void EstrellasInterfaz::Destruir()
{
	for (int i = 0; i < 10; i++)
	{
		SDL_DestroyTexture(numeros[i]);
	}
}
