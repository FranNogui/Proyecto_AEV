#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern Interfaz* interfaz;

void Moneda::CargarTextura(const char* ruta)
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

void Moneda::IniciarCuerpoFisico(b2World* world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.01f, (posicion.y + posicion.h / 2.0f) * 0.01f);
	b2PolygonShape groundBox;
	groundBox.SetAsBox((posicion.w / 2.0f) * 0.01f, (posicion.h / 2.0f)  * 0.01f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.isSensor = true;
	FixtureData* data = new FixtureData;
	data->tipo = TIPO_MONEDA;
	data->moneda = this;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(data);
	cuerpoFisico = world->CreateBody(&groundBodyDef);
	cuerpoFisico->CreateFixture(&fixtureDef);
}

Moneda::Moneda(float x, float y, Camara* camara, b2World* world)
{
	posicion.x = x;
	posicion.y = y;
	recogida = false;
	this->camara = camara;
	CargarTextura(RUTA_MONEDA_1);
	const char* rutas[] = {
		RUTA_MONEDA_1,
		RUTA_MONEDA_2,
		RUTA_MONEDA_3,
		RUTA_MONEDA_2
	};
	animacion.CrearAnimacion(4, 6, rutas);
	IniciarCuerpoFisico(world);
}

void Moneda::Recoger()
{
	if (!recogida)
	{
		interfaz->CambiarPuntuacion(100);
		recogida = true;
	}
}

void Moneda::Renderizar()
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

void Moneda::Destruir()
{
	SDL_DestroyTexture(textura);
}
