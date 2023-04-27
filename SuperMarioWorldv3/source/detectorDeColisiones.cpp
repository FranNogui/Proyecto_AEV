#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern int numGroundChecks;

void DetectorDeColisiones::BeginContact(b2Contact* contact)
{
	FixtureData* data;
	
	if (contact->GetFixtureA()->GetUserData().pointer != 0)
	{
		data = reinterpret_cast<FixtureData*>(contact->GetFixtureA()->GetUserData().pointer);
		switch (data->tipo)
		{
			case TIPO_GROUND_CHECK:
				numGroundChecks++;
				break;
			case TIPO_MONEDA_YOSHI:
				data->monedaYoshi->Recoger();
				break;
			case TIPO_MONEDA:
				data->moneda->Recoger();
				break;
		}
	}
	
	if (contact->GetFixtureB()->GetUserData().pointer != 0)
	{
		data = reinterpret_cast<FixtureData*>(contact->GetFixtureB()->GetUserData().pointer);
		switch (data->tipo)
		{
			case TIPO_GROUND_CHECK:
				numGroundChecks++;
				break;
			case TIPO_MONEDA_YOSHI:
				data->monedaYoshi->Recoger();
				break;
			case TIPO_MONEDA:
				data->moneda->Recoger();
				break;
		}
	}
}

void DetectorDeColisiones::EndContact(b2Contact* contact)
{
	FixtureData* data;
	
	if (contact->GetFixtureA()->GetUserData().pointer != 0)
	{
		data = reinterpret_cast<FixtureData*>(contact->GetFixtureA()->GetUserData().pointer);
		switch (data->tipo)
		{
			case TIPO_GROUND_CHECK:
				numGroundChecks--;
				break;
		}
	}
	
	if (contact->GetFixtureB()->GetUserData().pointer != 0)
	{
		data = reinterpret_cast<FixtureData*>(contact->GetFixtureB()->GetUserData().pointer);
		switch (data->tipo)
		{
			case TIPO_GROUND_CHECK:
				numGroundChecks--;
				break;
		}
	}
}
