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
				suelos.push_back(new Suelo(act, j * pixeles, i * pixeles, camara, world));
		}
	}
	
	// Capa de tuberias
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
				tuberias.push_back(new Tuberia(act, j * pixeles, i * pixeles, camara, world));
		}
	}
	
	// Capa de bloques
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{
				switch (act)
				{
					case 1:
						bGiratorios.push_back(new BloqueGiratorio(j * pixeles, i * pixeles, camara, world));
						break;
					case 2:
						bInterrogantes.push_back(new BloqueInterrogante(j * pixeles, i * pixeles, camara, world));
						break;
					case 3:
						bNubes.push_back(new BloqueNube(j * pixeles, i * pixeles, camara, world));
						break;
					case 4:
						bPiedras.push_back(new BloquePiedra(j * pixeles, i * pixeles, camara, world));
						break;
				}
			}
		}
	}
	
	// Capa de fondo
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
				decoraciones.push_back(new Decoracion(act, j * pixeles, i * pixeles, camara));
		}
	}
	
	// Capa de items
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
				monedasYoshi.push_back(new MonedaYoshi(j * pixeles, i * pixeles, camara, world));
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
					plataformas.push_back(new Plataforma(act, j * pixeles, i * pixeles, camara, world));
			}
		}
	}
	
	// Fondos
	mapa >> fondoR >> fondoG >> fondoB;
	mapa >> fondoAct;
	while (posFondo < ancho * pixeles)
	{
		fondos.push_back(new Fondo(fondoAct, posFondo, 0.0f, camara));
		posFondo += 512;
	}
	mapa.close();
}

void Mapa::Renderizar()
{
	for (std::size_t i = 0; i < fondos.size(); i++)
		fondos[i]->Renderizar();
	for (std::size_t i = 0; i < decoraciones.size(); i++)
		decoraciones[i]->Renderizar();
	for (std::size_t i = 0; i < suelos.size(); i++)
		suelos[i]->Renderizar();
	for (std::size_t i = 0; i < plataformas.size(); i++)
		plataformas[i]->Renderizar();
	for (std::size_t i = 0; i < tuberias.size(); i++)
		tuberias[i]->Renderizar();
	for (std::size_t i = 0; i < bGiratorios.size(); i++)
		bGiratorios[i]->Renderizar();
	for (std::size_t i = 0; i < bInterrogantes.size(); i++)
		bInterrogantes[i]->Renderizar();
	for (std::size_t i = 0; i < bNubes.size(); i++)
		bNubes[i]->Renderizar();
	for (std::size_t i = 0; i < bPiedras.size(); i++)
		bPiedras[i]->Renderizar();
	for (std::size_t i = 0; i < monedasYoshi.size(); i++)
		monedasYoshi[i]->Renderizar();
}

void Mapa::Destruir()
{
	for (std::size_t i = 0; i < fondos.size(); i++)
		fondos[i]->Destruir();
	for (std::size_t i = 0; i < decoraciones.size(); i++)
		decoraciones[i]->Destruir();
	for (std::size_t i = 0; i < suelos.size(); i++)
		suelos[i]->Destruir();
	for (std::size_t i = 0; i < plataformas.size(); i++)
		plataformas[i]->Destruir();
	for (std::size_t i = 0; i < tuberias.size(); i++)
		tuberias[i]->Destruir();
	for (std::size_t i = 0; i < bGiratorios.size(); i++)
		bGiratorios[i]->Destruir();
	for (std::size_t i = 0; i < bInterrogantes.size(); i++)
		bInterrogantes[i]->Destruir();
	for (std::size_t i = 0; i < bNubes.size(); i++)
		bNubes[i]->Destruir();
	for (std::size_t i = 0; i < bPiedras.size(); i++)
		bPiedras[i]->Destruir();
	for (std::size_t i = 0; i < monedasYoshi.size(); i++)
		monedasYoshi[i]->Destruir();
}

