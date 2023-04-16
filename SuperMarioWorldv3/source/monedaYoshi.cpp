#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void MonedaYoshi::CargarTextura(const char* ruta)
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

void MonedaYoshi::IniciarCuerpoFisico(b2World* world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.01f, (posicion.y + posicion.h / 2.0f) * 0.01f);
	cuerpoFisico = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox((posicion.w / 2.0f) * 0.01f, (posicion.h / 2.0f)  * 0.01f);
	cuerpoFisico->CreateFixture(&groundBox, 0.0f);
}

MonedaYoshi::MonedaYoshi(float x, float y, Camara* camara, b2World* world)
{
	posicion.x = x;
	posicion.y = y;
	this->camara = camara;
	CargarTextura(RUTA_MONEDA_YOSHI_1);
	const char* rutas[] = {
		RUTA_MONEDA_YOSHI_1,
		RUTA_MONEDA_YOSHI_2,
		RUTA_MONEDA_YOSHI_3,
		RUTA_MONEDA_YOSHI_4,
		RUTA_MONEDA_YOSHI_3,
		RUTA_MONEDA_YOSHI_2
	};
	animacion.CrearAnimacion(6, 6, rutas);
}

void MonedaYoshi::Renderizar()
{
	animacion.Renderizar();
	textura = animacion.textura;
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

void MonedaYoshi::Destruir()
{
	SDL_DestroyTexture(textura);
}
