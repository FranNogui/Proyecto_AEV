#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void Plataforma::CargarTextura(const char* ruta)
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

void Plataforma::IniciarCuerpoFisico(b2World* world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.01f, (posicion.y + posicion.h / 2.0f) * 0.01f);
	cuerpoFisico = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox((posicion.w / 2.0f) * 0.01f, (posicion.h / 2.0f)  * 0.01f);
	cuerpoFisico->CreateFixture(&groundBox, 0.0f);
}

Plataforma::Plataforma(int tipo, float x, float y, Camara* camara, b2World* world)
{
	posicion.x = x;
	posicion.y = y;
	this->camara = camara;
	cuerpoFisico = NULL;
	switch (tipo)
	{
		case 1:
			CargarTextura(RUTA_PLATAFORMA_1);
			IniciarCuerpoFisico(world);
			break;
		case 2:
			CargarTextura(RUTA_PLATAFORMA_2);
			IniciarCuerpoFisico(world);
			break;
		case 3:
			CargarTextura(RUTA_PLATAFORMA_3);
			IniciarCuerpoFisico(world);
			break;
		case 4:
			CargarTextura(RUTA_PLATAFORMA_4);
			break;
		case 5:
			CargarTextura(RUTA_PLATAFORMA_5);
			break;
		case 6:
			CargarTextura(RUTA_PLATAFORMA_6);
			break;
	}
}

void Plataforma::Renderizar()
{
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

void Plataforma::Destruir()
{
	SDL_DestroyTexture(textura);
}
