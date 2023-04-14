#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

Mapa::Mapa(const char* ruta, Camara* camara, b2World* world)
{
	std::ifstream mapa;
	mapa.open(ruta, std::ios::in);
	mapa >> ancho >> alto;
	int pixeles = 16, act = 0, nCapas = 0, fondoAct, posFondo = 0;
	
	// Capa de suelos
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
				suelos.push_back(*(new Suelo(act, j * pixeles, i * pixeles, camara, world)));
		}
	}
	
	// Capa de tuberias
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{}
		}
	}
	
	// Capa de bloques
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{}
		}
	}
	
	// Capa de fondo
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{}
		}
	}
	
	// Capa de items
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{}
		}
	}
	
	// Capas de plataformas
	mapa >> nCapas;
	for (int k = 0; k < nCapas; k++)
	{
		for (int i = 0; i < alto; i++)
		{
			for (int j = 0; j < ancho; j++)
			{
				mapa >> act;
				if (act != 0)
				{}
			}
		}
	}
	
	// Fondos
	mapa >> fondoR >> fondoG >> fondoB;
	mapa >> fondoAct;
	while (posFondo < ancho * pixeles)
	{
		
	}
	mapa.close();
}

void Mapa::Renderizar()
{
	for (std::size_t i = 0; i < suelos.size(); i++)
		suelos[i].Renderizar();
}

void Mapa::Destruir()
{
	for (std::size_t i = 0; i < suelos.size(); i++)
		suelos[i].Destruir();
}

