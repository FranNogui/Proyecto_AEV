#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void Tuberia::CargarTextura(const char* ruta)
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

void Tuberia::IniciarCuerpoFisico(b2World* world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.01f, (posicion.y + posicion.h / 2.0f) * 0.01f);
	cuerpoFisico = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox((posicion.w / 2.0f) * 0.01f, (posicion.h / 2.0f)  * 0.01f);
	cuerpoFisico->CreateFixture(&groundBox, 0.0f);
}

Tuberia::Tuberia(int tipo, float x, float y, Camara* camara, b2World* world)
{
	posicion.x = x;
	posicion.y = y;
	this->camara = camara;
	switch (tipo)
	{
		case 1:
			CargarTextura(RUTA_TUBERIA_GRANDE_AZUL_CUERPO);
			break;
		case 2:
			CargarTextura(RUTA_TUBERIA_GRANDE_AZUL_CABEZA);
			break;
		case 3:
			CargarTextura(RUTA_TUBERIA_GRANDE_GRIS_CUERPO);
			break;
		case 4:
			CargarTextura(RUTA_TUBERIA_GRANDE_GRIS_CABEZA);
			break;
		case 5:
			CargarTextura(RUTA_TUBERIA_GRANDE_VERDE_CUERPO);
			break;
		case 6:
			CargarTextura(RUTA_TUBERIA_GRANDE_VERDE_CABEZA);
			break;
		case 7:
			CargarTextura(RUTA_TUBERIA_PEQUENYA_VERDE_SUELO);
			break;
		case 8:
			CargarTextura(RUTA_TUBERIA_PEQUENYA_VERDE_CUERPO);
			break;
		case 9:
			CargarTextura(RUTA_TUBERIA_PEQUENYA_VERDE_CABEZA);
			break;
	}
	IniciarCuerpoFisico(world);
}

void Tuberia::Renderizar()
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

void Tuberia::Destruir()
{
	SDL_DestroyTexture(textura);
}
