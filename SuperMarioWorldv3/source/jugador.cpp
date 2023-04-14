#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

SDL_Texture* Jugador::CargarTextura(const char* ruta)
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

void Jugador::IniciarCuerpoFisico(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.1f, (posicion.y + posicion.h / 2.0f) * 0.1f);
	cuerpoFisico = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((posicion.w / 2.0f) * 0.1f, (posicion.h / 2.0f) * 0.1f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
	cuerpoFisico->CreateFixture(&fixtureDef);
}

Jugador::Jugador(Camara* camara, b2World* world)
{
	int nTickPorFrame = 4;
	this->camara = camara;
	estado = Quieto;
	tamanyo = 0;
	direccion = 0;
	velocidad = 0;
	posicion.x = 20;
	posicion.y = 20;
	posicion.w = 16;
	posicion.h = 24;
	
	IniciarCuerpoFisico(world);
	agachado[0] = CargarTextura(RUTA_MARIO_PEQUENYO_DERECHA_AGACHADO);
	agachado[1] = CargarTextura(RUTA_MARIO_PEQUENYO_IZQUIERDA_AGACHADO);
	agachado[2] = CargarTextura(RUTA_MARIO_GRANDE_DERECHA_AGACHADO);
	agachado[3] = CargarTextura(RUTA_MARIO_GRANDE_IZQUIERDA_AGACHADO);
	cambioDir[0] = CargarTextura(RUTA_MARIO_PEQUENYO_DERECHA_CAMBIO_DIRECCION);
	cambioDir[1] = CargarTextura(RUTA_MARIO_PEQUENYO_IZQUIERDA_CAMBIO_DIRECCION);
	cambioDir[2] = CargarTextura(RUTA_MARIO_GRANDE_DERECHA_CAMBIO_DIRECCION);
	cambioDir[3] = CargarTextura(RUTA_MARIO_GRANDE_IZQUIERDA_CAMBIO_DIRECCION);
	cayendo[0] = CargarTextura(RUTA_MARIO_PEQUENYO_DERECHA_CAYENDO);
	cayendo[1] = CargarTextura(RUTA_MARIO_PEQUENYO_IZQUIERDA_CAYENDO);
	cayendo[2] = CargarTextura(RUTA_MARIO_GRANDE_DERECHA_CAYENDO);
	cayendo[3] = CargarTextura(RUTA_MARIO_GRANDE_IZQUIERDA_CAYENDO);
	const char* corriendo0[] = {
		RUTA_MARIO_PEQUENYO_DERECHA_QUIETO,
		RUTA_MARIO_PEQUENYO_DERECHA_CORRIENDO
	};
	corriendo[0].CrearAnimacion(2, nTickPorFrame, corriendo0);
	const char* corriendo1[] = {
		RUTA_MARIO_PEQUENYO_IZQUIERDA_QUIETO,
		RUTA_MARIO_PEQUENYO_IZQUIERDA_CORRIENDO
	};
	corriendo[1].CrearAnimacion(2, nTickPorFrame, corriendo1);
	const char* corriendo2[] {
		RUTA_MARIO_GRANDE_DERECHA_QUIETO,
		RUTA_MARIO_GRANDE_DERECHA_CORRIENDO_1,
		RUTA_MARIO_GRANDE_DERECHA_CORRIENDO_2,
		RUTA_MARIO_GRANDE_DERECHA_CORRIENDO_1
	};
	corriendo[2].CrearAnimacion(4, nTickPorFrame, corriendo2);
	const char* corriendo3[] {
		RUTA_MARIO_GRANDE_IZQUIERDA_QUIETO,
		RUTA_MARIO_GRANDE_IZQUIERDA_CORRIENDO_1,
		RUTA_MARIO_GRANDE_IZQUIERDA_CORRIENDO_2,
		RUTA_MARIO_GRANDE_IZQUIERDA_CORRIENDO_1
	};
	corriendo[3].CrearAnimacion(4, nTickPorFrame, corriendo3);
	quieto[0] = CargarTextura(RUTA_MARIO_PEQUENYO_DERECHA_QUIETO);
	quieto[1] = CargarTextura(RUTA_MARIO_PEQUENYO_IZQUIERDA_QUIETO);
	quieto[2] = CargarTextura(RUTA_MARIO_GRANDE_DERECHA_QUIETO);
	quieto[3] = CargarTextura(RUTA_MARIO_GRANDE_IZQUIERDA_QUIETO);
	quietoArriba[0] = CargarTextura(RUTA_MARIO_PEQUENYO_DERECHA_QUIETO_ARRIBA);
	quietoArriba[1] = CargarTextura(RUTA_MARIO_PEQUENYO_IZQUIERDA_QUIETO_ARRIBA);
	quietoArriba[2] = CargarTextura(RUTA_MARIO_GRANDE_DERECHA_QUIETO_ARRIBA);
	quietoArriba[3] = CargarTextura(RUTA_MARIO_GRANDE_IZQUIERDA_QUIETO_ARRIBA);
	saltando[0] = CargarTextura(RUTA_MARIO_PEQUENYO_DERECHA_SALTANDO);
	saltando[1] = CargarTextura(RUTA_MARIO_PEQUENYO_IZQUIERDA_SALTANDO);
	saltando[2] = CargarTextura(RUTA_MARIO_GRANDE_DERECHA_SALTANDO);
	saltando[3] = CargarTextura(RUTA_MARIO_GRANDE_IZQUIERDA_SALTANDO);
	saltoCorriendo[0] = CargarTextura(RUTA_MARIO_PEQUENYO_DERECHA_SALTO_CORRIENDO);
	saltoCorriendo[1] = CargarTextura(RUTA_MARIO_PEQUENYO_IZQUIERDA_SALTO_CORRIENDO);
	saltoCorriendo[2] = CargarTextura(RUTA_MARIO_GRANDE_DERECHA_SALTO_CORRIENDO);
	saltoCorriendo[3] = CargarTextura(RUTA_MARIO_GRANDE_IZQUIERDA_SALTO_CORRIENDO);
	const char* sprint0[] = {
		RUTA_MARIO_PEQUENYO_DERECHA_SPRINT_1,
		RUTA_MARIO_PEQUENYO_DERECHA_SPRINT_2
	};
	sprint[0].CrearAnimacion(2, nTickPorFrame, sprint0);
	const char* sprint1[] = {
		RUTA_MARIO_PEQUENYO_IZQUIERDA_SPRINT_1,
		RUTA_MARIO_PEQUENYO_IZQUIERDA_SPRINT_2
	};
	sprint[1].CrearAnimacion(2, nTickPorFrame, sprint1);
	const char* sprint2[] = {
		RUTA_MARIO_GRANDE_DERECHA_SPRINT_1,
		RUTA_MARIO_GRANDE_DERECHA_SPRINT_2,
		RUTA_MARIO_GRANDE_DERECHA_SPRINT_3,
		RUTA_MARIO_GRANDE_DERECHA_SPRINT_2
	};
	sprint[2].CrearAnimacion(4, nTickPorFrame, sprint2);
	const char* sprint3[] = {
		RUTA_MARIO_GRANDE_IZQUIERDA_SPRINT_1,
		RUTA_MARIO_GRANDE_IZQUIERDA_SPRINT_2,
		RUTA_MARIO_GRANDE_IZQUIERDA_SPRINT_3,
		RUTA_MARIO_GRANDE_IZQUIERDA_SPRINT_2
	};
	sprint[2].CrearAnimacion(4, nTickPorFrame, sprint3);
	const char* muerte0[] = {
		RUTA_MARIO_PEQUENYO_DERECHA_MUERTE,
		RUTA_MARIO_PEQUENYO_IZQUIERDA_MUERTE
	};
	muerte.CrearAnimacion(2, nTickPorFrame, muerte0);
}

void Jugador::Movimiento(int x)
{
	cuerpoFisico->SetLinearVelocity(b2Vec2(x * maxVelocidad, cuerpoFisico->GetLinearVelocity().y));
}

void Jugador::Renderizar(int x)
{
	posicion.x = cuerpoFisico->GetPosition().x * 10.0f - posicion.w / 2.0f;
	posicion.y = cuerpoFisico->GetPosition().y * 10.0f - posicion.h / 2.0f;
	camara->x = cuerpoFisico->GetPosition().x * 10.0f - SCREEN_W / 2.0f;
	camara->y = cuerpoFisico->GetPosition().y * 10.0f - SCREEN_H / 2.0f;
	int posicionDibujoX = posicion.x - camara->x;
	int posicionDibujoY = posicion.y - camara->y;
	SDL_Rect posicionDibujo;
	posicionDibujo = {posicionDibujoX, posicionDibujoY, posicion.w, posicion.h};
	
	if (abs(cuerpoFisico->GetLinearVelocity().x) < 0.01)
		cuerpoFisico->SetLinearVelocity(b2Vec2(0.0f, cuerpoFisico->GetLinearVelocity().y));
	
	switch (estado)
	{
		case Quieto:
			SDL_RenderCopy(renderer, quieto[direccion + tamanyo], NULL, &posicionDibujo);
			if (cuerpoFisico->GetLinearVelocity().x > 0 && x > 0)
			{
				direccion = 0;
				estado = Corriendo;
			}
			else if (cuerpoFisico->GetLinearVelocity().x < 0 && x < 0)
			{
				direccion = 1;
				estado = Corriendo;
			}
			velocidad = x;
			cuerpoFisico->SetLinearVelocity(b2Vec2(velocidad, cuerpoFisico->GetLinearVelocity().y));
			break;
		case Corriendo:
			for (int i = 0; i < 4; i++)
				corriendo[i].Renderizar();
			SDL_RenderCopy(renderer, corriendo[direccion + tamanyo].textura, NULL, &posicionDibujo);
			if (cuerpoFisico->GetLinearVelocity().x == 0)
			{
				estado = Quieto;
				break;
			}
			velocidad += accel * x;
			if (x != 0 && signbit(x) != direccion)
			{
				estado = CambioDir;
				direccion = (direccion + 1) % 2;
			}
			if (x == 0)
			{
				if (velocidad > 0)
				{
					velocidad -= accel;
					if (velocidad <= 0) 
					{
						velocidad = 0;
						estado = Quieto;
					}
				}
				else if (velocidad < 0)
				{
					velocidad += accel;
					if (velocidad >= 0)
					{
						velocidad = 0;
						estado = Quieto;
					}
				}
			}
			if (abs(velocidad) >= maxVelocidad)
			{
				if (velocidad > 0) velocidad = maxVelocidad;
				if (velocidad < 0) velocidad = -maxVelocidad;
			}
			cuerpoFisico->SetLinearVelocity(b2Vec2(velocidad, cuerpoFisico->GetLinearVelocity().y));
			break;
		case CambioDir:
			SDL_RenderCopy(renderer, cambioDir[direccion + tamanyo], NULL, &posicionDibujo);
			if ((direccion == 0 && x <= 0) || (direccion == 1 && x >= 0))
			{
				direccion = (direccion + 1) % 2;
				estado = Corriendo;
			}
			else if ((direccion == 0 && velocidad > 0 ) || (direccion == 1 && velocidad < 0))
				estado = Corriendo;
			velocidad += accel * x * 2;
			cuerpoFisico->SetLinearVelocity(b2Vec2(velocidad, cuerpoFisico->GetLinearVelocity().y));
			break;
		case Sprint:
			for (int i = 0; i < 4; i++)
				sprint[i].Renderizar();
			SDL_RenderCopy(renderer, sprint[direccion + tamanyo].textura, NULL, &posicionDibujo);
			if (!signbit(x) != direccion || x == 0 || abs(cuerpoFisico->GetLinearVelocity().x) < maxVelocidad - 10)
			{
				estado = Corriendo;
			}
			else
				cuerpoFisico->SetLinearVelocity(b2Vec2(velocidad, cuerpoFisico->GetLinearVelocity().y));
			break;
	}
}

