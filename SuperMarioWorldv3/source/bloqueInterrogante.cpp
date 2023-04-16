#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void BloqueInterrogante::CargarTextura(const char* ruta)
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

void BloqueInterrogante::IniciarCuerpoFisico(b2World* world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.01f, (posicion.y + posicion.h / 2.0f) * 0.01f);
	cuerpoFisico = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox((posicion.w / 2.0f) * 0.01f, (posicion.h / 2.0f)  * 0.01f);
	cuerpoFisico->CreateFixture(&groundBox, 0.0f);
}

BloqueInterrogante::BloqueInterrogante(float x, float y, Camara* camara, b2World* world)
{
	posicion.x = x;
	posicion.y = y;
	this->camara = camara;
	CargarTextura(RUTA_BLOQUE_INTERROGANTE_1);
	const char* rutas[] = {
		RUTA_BLOQUE_INTERROGANTE_1,
		RUTA_BLOQUE_INTERROGANTE_2,
		RUTA_BLOQUE_INTERROGANTE_3,
		RUTA_BLOQUE_INTERROGANTE_4,
	};
	animacion.CrearAnimacion(4, 6, rutas);
	IniciarCuerpoFisico(world);
}

void BloqueInterrogante::Renderizar()
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

void BloqueInterrogante::Destruir()
{
	SDL_DestroyTexture(textura);
}
