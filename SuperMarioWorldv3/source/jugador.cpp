#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;
int numGroundChecks = 0;
const int ticksJumpDelay = 10;
int actJumpTicks = 0;

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
	bodyDef.position.Set((posicion.x + posicion.w / 2.0f) * 0.01f, (posicion.y + posicion.h / 2.0f) * 0.01f);
	cuerpoFisico = world->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius = (posicion.w / 2.0f) * 0.01f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	cuerpoFisico->CreateFixture(&fixtureDef);
	cuerpoFisico->SetFixedRotation(true);
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.05, 0.05, b2Vec2(0, 0.12), 0);
	FixtureData* data = new FixtureData;
	data->tipo = TIPO_GROUND_CHECK;
	fixtureDef.shape = &polygonShape;
	fixtureDef.isSensor = true;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(data);
	cuerpoFisico->CreateFixture(&fixtureDef);
	cuerpoFisico->SetFixedRotation(true);
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

void Jugador::Renderizar(int x, bool saltado)
{
	posicion.x = floor(cuerpoFisico->GetPosition().x * 100.0f) - posicion.w / 2.0f;
	posicion.y = floor(cuerpoFisico->GetPosition().y * 100.0f) - posicion.h / 2.0f - 2;
	camara->Actualizar();
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
			if (saltado && numGroundChecks > 0)
				estado = Saltando;
			if (numGroundChecks == 0)
				estado = Cayendo;
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
			if (saltado && numGroundChecks > 0)
				estado = Saltando;	
			if (numGroundChecks == 0)
				estado = Cayendo;	
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
			if (saltado && numGroundChecks > 0)
				estado = Saltando;
			if (numGroundChecks == 0)
				estado = Cayendo;
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
			if (saltado && numGroundChecks > 0)
				estado = Saltando;
			if (!signbit(x) != direccion || x == 0 || abs(cuerpoFisico->GetLinearVelocity().x) < maxVelocidad - 10)
			{
				estado = Corriendo;
			}
			else
				cuerpoFisico->SetLinearVelocity(b2Vec2(velocidad, cuerpoFisico->GetLinearVelocity().y));
			break;
		case Agachado:
			break;
		case Cayendo:
			if (numGroundChecks > 0 && actJumpTicks >= ticksJumpDelay) 
			{				
				//camara->y = cuerpoFisico->GetPosition().y * 100.0f - SCREEN_H / 2.0f;
				estado = Corriendo;
				actJumpTicks = 0;
			}
			else if (actJumpTicks < ticksJumpDelay)
				actJumpTicks++;
			velocidad += accel * x * 0.75f;
			if (velocidad < -maxVelocidad) velocidad = -maxVelocidad;
			if (velocidad > maxVelocidad) velocidad = maxVelocidad;
			cuerpoFisico->SetLinearVelocity(b2Vec2(velocidad, cuerpoFisico->GetLinearVelocity().y));
			if (cuerpoFisico->GetLinearVelocity().y < 0) SDL_RenderCopy(renderer, saltando[direccion + tamanyo], NULL, &posicionDibujo);
			else SDL_RenderCopy(renderer, cayendo[direccion + tamanyo], NULL, &posicionDibujo);
			break;
		case QuietoArriba:
			break;
		case Saltando:
			velocidad += accel * x * 0.75f;
			if (velocidad < -maxVelocidad) velocidad = -maxVelocidad;
			if (velocidad > maxVelocidad) velocidad = maxVelocidad;
			SDL_RenderCopy(renderer, saltando[direccion + tamanyo], NULL, &posicionDibujo);
			cuerpoFisico->ApplyLinearImpulse( b2Vec2(0, -0.12), cuerpoFisico->GetWorldCenter(), true );
			estado = Cayendo;
			break;
		case SaltoCorriendo:
			break;
		case Muerte:
			break;
	}
}

