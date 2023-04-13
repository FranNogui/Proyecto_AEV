#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern int fondoR, fondoG, fondoB;

Vector2D::Vector2D(const float x, const float y)
{
	this->x = x; this->y = y;
}

void Vector2D::Normalizar()
{
	float aux = sqrt(x * x + y * y);
	x /= aux; y /= aux;
}

Vector2D& operator +(const Vector2D &v1, const Vector2D &v2)
{ return *(new Vector2D(v1.x + v2.x, v1.y + v2.y)); }

Vector2D& operator *(const Vector2D &v1, const float &f1)
{ return *(new Vector2D(v1.x * f1, v1.y * f1)); }

EntidadSimple::EntidadSimple()
{
	textura = NULL; posicion = {0, 0, 0, 0};
}

void EntidadSimple::CrearFisicas(b2World world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(posicion.x, posicion.y);
	groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(8.0f, 8.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void EntidadSimple::Ubicar(const Vector2D pos)
{
	posicion.x = int(pos.x);
	posicion.y = int(pos.y);
}

void EntidadSimple::Ubicar(const float x, const float y)
{
	posicion.x = int(x);
	posicion.y = int(y);
}

void EntidadSimple::CargarTextura(const char* ruta)
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

void EntidadSimple::Renderizar()
{
	if (textura) SDL_RenderCopy(renderer, textura, NULL, &posicion);
}

void EntidadSimple::Destruir()
{
	SDL_DestroyTexture(textura);
}

SDL_Texture* Mapa::CargarTextura(const char* ruta)
{
	SDL_Surface* img = IMG_Load(ruta);
	SDL_Texture* tex = NULL;
	if (img)
	{
		tex = SDL_CreateTextureFromSurface(renderer, img);
		SDL_FreeSurface(img);
	}
	return tex;
}

void Mapa::CargarTexturaSuelos1()
{
	tiles_suelo1[0].CargarTextura(RUTA_SUELO_1);
	tiles_suelo1[1].CargarTextura(RUTA_SUELO_2);
	tiles_suelo1[2].CargarTextura(RUTA_SUELO_3);
	tiles_suelo1[3].CargarTextura(RUTA_SUELO_4);
	tiles_suelo1[4].CargarTextura(RUTA_SUELO_5);
	tiles_suelo1[5].CargarTextura(RUTA_SUELO_6);
	tiles_suelo1[6].CargarTextura(RUTA_SUELO_7);
	tiles_suelo1[7].CargarTextura(RUTA_SUELO_8);
}

void Mapa::CargarTexturaTuberias()
{
	tuberias[0].CargarTextura(RUTA_TUBERIA_GRANDE_AZUL_CUERPO);
	tuberias[1].CargarTextura(RUTA_TUBERIA_GRANDE_AZUL_CABEZA);
	tuberias[2].CargarTextura(RUTA_TUBERIA_GRANDE_GRIS_CUERPO);
	tuberias[3].CargarTextura(RUTA_TUBERIA_GRANDE_GRIS_CABEZA);
	tuberias[4].CargarTextura(RUTA_TUBERIA_GRANDE_VERDE_CUERPO);
	tuberias[5].CargarTextura(RUTA_TUBERIA_GRANDE_VERDE_CABEZA);
	tuberias[6].CargarTextura(RUTA_TUBERIA_PEQUENYA_VERDE_SUELO);
	tuberias[7].CargarTextura(RUTA_TUBERIA_PEQUENYA_VERDE_CUERPO);
	tuberias[8].CargarTextura(RUTA_TUBERIA_PEQUENYA_VERDE_CABEZA);
}

void Mapa::CargarFondos()
{
	fondos[0].CargarTextura(RUTA_FONDO);
}

Mapa::Mapa(const char* ruta)
{
	CargarTexturaSuelos1();
	CargarTexturaTuberias();
	CargarFondos();
	std::ifstream mapa;
	mapa.open(ruta, std::ios::in);
	mapa >> ancho >> alto;
	int pixeles = 16, act = 0, nCapas = 0;
	// Capa Suelos
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{
				act--;
				tiles_suelo1[act].Ubicar(j * pixeles, i * pixeles);
				tiles_suelo.push_back(tiles_suelo1[act]);
			}
		}
	}
	// Capa Tuberias
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{
				act--;
				tuberias[act].Ubicar(j * pixeles, i * pixeles);
				tuberias2.push_back(tuberias[act]);
			}
		}
	}
	// Capa Bloques
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{
				act--;

			}
		}
	}
	// Capa Fondo
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{
				act--;

			}
		}
	}
	// Capa Items
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			mapa >> act;
			if (act != 0)
			{
				act--;

			}
		}
	}
	mapa >> nCapas;
	// Capa plataformas
	for (int k = 0; k < nCapas; k++)
	{
		for (int i = 0; i < alto; i++)
		{
			for (int j = 0; j < ancho; j++)
			{
				mapa >> act;
				if (act != 0)
				{
					act--;

				}
			}
		}
	}
	mapa >> fondoR >> fondoG >> fondoB;
	int fondoAct, posFondo = 0;
	mapa >> fondoAct;
	while (posFondo < ancho * 16)
	{
		fondos[fondoAct].Ubicar(posFondo, 0);
		fondo.push_back(fondos[fondoAct]);
		posFondo += 512;
	}
	mapa.close();
}

void Mapa::Renderizar()
{
	for (std::size_t i = 0; i < fondo.size(); i++)
		fondo[i].Renderizar();
	for (std::size_t i = 0; i < tiles_suelo.size(); i++)
		tiles_suelo[i].Renderizar();
	for (std::size_t i = 0; i < tuberias2.size(); i++)
		tuberias2[i].Renderizar();
}

void Mapa::Destruir()
{
	for (std::size_t i = 0; i < tiles_suelo.size(); i++)
		tiles_suelo[i].Destruir();
	for (std::size_t i = 0; i < tuberias2.size(); i++)
		tuberias2[i].Destruir();
}


Jugador::Jugador()
{
	textura = NULL; posicion = {0, 0, 0, 0};
}

void Jugador::CrearFisicas(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(10.0f, 10.0f);
	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
}

void Jugador::Ubicar(const Vector2D pos)
{
	posicion.x = int(pos.x);
	posicion.y = int(pos.y);
}

void Jugador::Ubicar(const float x, const float y)
{
	posicion.x = int(x);
	posicion.y = int(y);
}

void Jugador::CargarTextura(const char* ruta)
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

void Jugador::Renderizar()
{
	posicion.x = body->GetPosition().x;
	posicion.y = body->GetPosition().y;
	if (textura) SDL_RenderCopy(renderer, textura, NULL, &posicion);
}

void Jugador::Destruir()
{
	SDL_DestroyTexture(textura);
}



