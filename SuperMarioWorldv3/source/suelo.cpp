#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void Suelo::CargarTextura(const char* ruta)
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

void Suelo::IniciarCuerpoFisico(b2World* world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.1f, (posicion.y + posicion.h / 2.0f) * 0.1f);
	cuerpoFisico = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox((posicion.w / 2.0f) * 0.1f, (posicion.h / 2.0f)  * 0.1f);
	cuerpoFisico->CreateFixture(&groundBox, 0.0f);
}

Suelo::Suelo(int tipo, float x, float y, Camara* camara, b2World* world)
{
	posicion.x = x;
	posicion.y = y;
	this->camara = camara;
	cuerpoFisico = NULL;
	switch (tipo)
	{
		case 1:
			CargarTextura(RUTA_SUELO_1);
			IniciarCuerpoFisico(world);
			break;
		case 2:
			CargarTextura(RUTA_SUELO_2);
			IniciarCuerpoFisico(world);
			break;
		case 3:
			CargarTextura(RUTA_SUELO_3);
			IniciarCuerpoFisico(world);
			break;
		case 4:
			CargarTextura(RUTA_SUELO_4);
			IniciarCuerpoFisico(world);
			break;
		case 5:
			CargarTextura(RUTA_SUELO_5);
			break;
		case 6:
			CargarTextura(RUTA_SUELO_6);
			IniciarCuerpoFisico(world);
			break;
		case 7:
			CargarTextura(RUTA_SUELO_7);
			break;
		case 8:
			CargarTextura(RUTA_SUELO_8);
			break;
	}
}

void Suelo::Renderizar()
{
	int posicionDibujoX = posicion.x - camara->x;
	int posicionDibujoY = posicion.y - camara->y;
	if (textura && 
		posicionDibujoX > -50 && posicionDibujoX < SCREEN_W + 50 && 
		posicionDibujoY > -50 && posicionDibujoY < SCREEN_H + 50)
	{
		SDL_Rect posicionDibujo;
		posicionDibujo = {posicionDibujoX, posicionDibujoY, posicion.w, posicion.h};
		SDL_RenderCopy(renderer, textura, NULL, &posicionDibujo);
	}
}

void Suelo::Destruir()
{
	SDL_DestroyTexture(textura);
}
