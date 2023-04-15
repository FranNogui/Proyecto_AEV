#ifndef GAME_ENGINE
#define GAME_ENGINE

#include "rutas.h"
#include "constantes.h"

#include <time.h>
#include <unistd.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <switch.h>

#include <box2d/box2d.h>

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

struct Camara
{
	float x;
	float y;
	
	Camara(float x, float y);
};

struct Animacion
{
	SDL_Texture* textura;
	SDL_Texture* frames[64];
	int nFrames;
	int nTicksPorFrame;
	int tickActual;
	
	Animacion();
	void CrearAnimacion(int nFrames, int nTicksPorFrame, const char* rutas[]);
	void Reiniciar();
	void Renderizar();
	void Destruir();
private:
	SDL_Texture* CargarTextura(const char* ruta);
};

struct Jugador
{	
	enum Estado
	{
		Agachado,
		CambioDir,
		Cayendo,
		Corriendo,
		Quieto,
		QuietoArriba,
		Saltando,
		SaltoCorriendo,
		Sprint,
		Muerte	
	};
	
	const float maxVelocidad = 2.0f;
	const float accel = 0.05f;
	float velocidad;
	Camara* camara;
	b2Body* cuerpoFisico;
	SDL_Texture* agachado[4];
	SDL_Texture* cambioDir[4];
	SDL_Texture* cayendo[4];
	Animacion corriendo[4];
	SDL_Texture* quieto[4];
	SDL_Texture* quietoArriba[4];
	SDL_Texture* saltando[4];
	SDL_Texture* saltoCorriendo[4];
	Animacion sprint[4];
	Animacion growUp[4];
	Animacion muerte;
	SDL_Rect posicion;
	int tamanyo;
	int direccion;
	Estado estado;
	
	Jugador(Camara* camara, b2World* world);
	void Movimiento(int x);
	void Renderizar(int x);
private:
	SDL_Texture* CargarTextura(const char* ruta);
	void IniciarCuerpoFisico(b2World* world);
};

struct Suelo
{
	Camara* camara;
	SDL_Texture *textura;
	SDL_Rect posicion;
	b2Body* cuerpoFisico;
	
	Suelo(int tipo, float x, float y, Camara* camara, b2World* world);
	void Renderizar();
	void Destruir();
private:
	void CargarTextura(const char* ruta);
	void IniciarCuerpoFisico(b2World* world);
};

struct Mapa
{
	int fondoR;
	int fondoG;
	int fondoB;
	int ancho;
	int alto;
	vector<Suelo> suelos;
	
	Mapa(const char* ruta, Camara* camara, b2World* world);
	void Renderizar();
	void Destruir();
};

#endif
