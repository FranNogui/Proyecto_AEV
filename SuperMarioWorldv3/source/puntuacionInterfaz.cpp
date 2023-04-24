#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

SDL_Texture* PuntuacionInterfaz::CargarTextura(const char* ruta)
{
	SDL_Surface* img = IMG_Load(ruta);
	SDL_Texture* tex = NULL;
	if (img)
	{
		tex = SDL_CreateTextureFromSurface(renderer, img);
		for (int i = 0; i < 7; i++)
		{
			posicion[i].w = img->w;
			posicion[i].h = img->h;
		}
		SDL_FreeSurface(img);
	}
	return tex;
}

void PuntuacionInterfaz::CargarTexturas()
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

PuntuacionInterfaz::PuntuacionInterfaz(float x, float y, int puntuacionInicial)
{
	puntuacionAct = puntuacionInicial;
	CargarTexturas();
	for (int i = 0; i < 7; i++)
	{
		posicion[i].x = x + posicion[i].w * i;
		posicion[i].y = y;
	}
	for(int i = 6; i > 0; i--){
		switch(puntuacionAct % 10)
		{
			case 0:
				puntuacion[i] = numeros[0];
				break;
			case 1:
				puntuacion[i] = numeros[1];
				break;
			case 2:
				puntuacion[i] = numeros[2];
				break;
			case 3:
				puntuacion[i] = numeros[3];
				break;
			case 4:
				puntuacion[i] = numeros[4];
				break;
			case 5:
				puntuacion[i] = numeros[5];
				break;
			case 6:
				puntuacion[i] = numeros[6];
				break;
			case 7:
				puntuacion[i] = numeros[7];
				break;
			case 8:
				puntuacion[i] = numeros[8];
				break;
			case 9:
				puntuacion[i] = numeros[9];
				break;
		
		}
		puntuacionAct = puntuacionAct / 10;
	}
	
}

void PuntuacionInterfaz::CambiarPuntuacion(int incremento)
{
	puntuacionAct = puntuacionAct + incremento;
}

void PuntuacionInterfaz::Renderizar()
{
	if (puntuacion[0])
		SDL_RenderCopy(renderer, puntuacion[0], NULL, &posicion[0]);
	if (puntuacion[1])
		SDL_RenderCopy(renderer, puntuacion[1], NULL, &posicion[1]);
	if (puntuacion[2])
		SDL_RenderCopy(renderer, puntuacion[2], NULL, &posicion[2]);
	if (puntuacion[3])
		SDL_RenderCopy(renderer, puntuacion[3], NULL, &posicion[3]);
	if (puntuacion[4])
		SDL_RenderCopy(renderer, puntuacion[4], NULL, &posicion[4]);
	if (puntuacion[5])
		SDL_RenderCopy(renderer, puntuacion[5], NULL, &posicion[5]);
	if (puntuacion[6])
		SDL_RenderCopy(renderer, puntuacion[6], NULL, &posicion[6]);
}

void PuntuacionInterfaz::Destruir()
{
	for (int i = 0; i < 10; i++)
	{
		SDL_DestroyTexture(numeros[i]);
	}
}