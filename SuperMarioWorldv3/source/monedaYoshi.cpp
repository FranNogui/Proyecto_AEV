#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern Interfaz* interfaz;

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
	b2PolygonShape groundBox;
	groundBox.SetAsBox((posicion.w / 2.0f) * 0.01f, (posicion.h / 2.0f)  * 0.01f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.isSensor = true;
	FixtureData* data = new FixtureData;
	data->tipo = TIPO_MONEDA_YOSHI;
	data->monedaYoshi = this;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(data);
	cuerpoFisico = world->CreateBody(&groundBodyDef);
	cuerpoFisico->CreateFixture(&fixtureDef);
}

MonedaYoshi::MonedaYoshi(float x, float y, Camara* camara, b2World* world)
{
	posicion.x = x;
	posicion.y = y;
	recogida = false;
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
	IniciarCuerpoFisico(world);
}

void MonedaYoshi::Recoger()
{
	if (!recogida)
	{
		interfaz->CambiarNumeroEstrellas(1);
		interfaz->CambiarPuntuacion(500);
		recogida = true;
	}
}

void MonedaYoshi::Renderizar()
{
	if (recogida) return;
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
