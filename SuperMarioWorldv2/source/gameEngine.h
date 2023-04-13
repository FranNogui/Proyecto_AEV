#ifndef GAME_ENGINE
#define GAME_ENGINE

#include "rutas.h"

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
extern int fondoR, fondoG, fondoB;

struct Camara
{
	float x;
	float y;
};

struct Vector2D
{
	float x;
	float y;
	
	Vector2D(const float x, const float y);
	void Normalizar();
};

Vector2D& operator +(const Vector2D &v1, const Vector2D &v2);
Vector2D& operator *(const Vector2D &v1, const float &f1);

struct EntidadSimple
{
	SDL_Texture *textura;
	SDL_Rect posicion;
	b2Body* groundBody;	
	
	EntidadSimple();
	void CrearFisicas(b2World world);
	void Ubicar(const Vector2D pos);
	void Ubicar(const float x, const float y);
	void CargarTextura(const char* ruta);
	void Renderizar();
	void Destruir();
};

struct Mapa
{
	int ancho;
	int alto;
	EntidadSimple tiles_suelo1[8];
	EntidadSimple tuberias[9];
	EntidadSimple fondos[1];
	vector<EntidadSimple> tiles_suelo;
	vector<EntidadSimple> tuberias2;
	vector<EntidadSimple> fondo;
	
	SDL_Texture* CargarTextura(const char* ruta);
	void CargarTexturaSuelos1();
	void CargarTexturaTuberias();
	void CargarFondos();
	Mapa(const char* ruta);
	void Renderizar();
	void Destruir();
};

struct Jugador
{
	SDL_Texture *textura;
	SDL_Rect posicion;
	b2Body* body;	
	
	Jugador();
	void CrearFisicas(b2World* world);
	void Ubicar(const Vector2D pos);
	void Ubicar(const float x, const float y);
	void CargarTextura(const char* ruta);
	void Renderizar();
	void Destruir();
};

#endif
