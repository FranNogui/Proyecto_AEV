#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern Interfaz* interfaz;

void Hongo::CargarTextura(const char* ruta)
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

void Hongo::IniciarCuerpoFisico(b2World* world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.01f, (posicion.y + posicion.h / 2.0f) * 0.01f);
	b2PolygonShape groundBox;
	groundBox.SetAsBox((posicion.w / 2.0f) * 0.01f, (posicion.h / 2.0f)  * 0.01f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.isSensor = true;
	FixtureData* data = new FixtureData;
	data->tipo = TIPO_HONGO;
	data->hongo = this;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(data);
	cuerpoFisico = world->CreateBody(&groundBodyDef);
	cuerpoFisico->CreateFixture(&fixtureDef);
}

Hongo::Hongo(float x, float y, Camara* camara, b2World* world)
{
	posicion.x = x;
	posicion.y = y;
	recogido = false;
	this->camara = camara;
	CargarTextura(RUTA_HONGO);
	IniciarCuerpoFisico(world);
}

void Hongo::Recoger()
{
	if (!recogido)
	{
		interfaz->CambiarContenedor();
		recogido = true;
	}
}

void Hongo::Renderizar()
{
	if (recogido) return;
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

void Hongo::Destruir()
{
	SDL_DestroyTexture(textura);
}
