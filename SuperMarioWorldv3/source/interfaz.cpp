#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

Interfaz::Interfaz()
{
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(0, 20, RUTA_MARIO_TEXTO));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(40, 20, RUTA_VIDA_INTERFAZ));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(80, 20, RUTA_TIME_INTERFAZ));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(120, 20, RUTA_DINERO_INTERFAZ));
    numVidas = new NumeroVidas(0, 0, 5);
    contenedor = new Contenedor(40, 0, false);
    tiempo = new TiempoInterfaz(80, 0, 300);
    monedas = new MonedasInterfaz(120, 0, 20);
    puntuacion = new PuntuacionInterfaz(160, 0, 54321);
}

void Interfaz::Renderizar()
{
	for (std::size_t i = 0; i < objetosEstaticos.size(); i++)
		objetosEstaticos[i]->Renderizar();

	numVidas->Renderizar();
	contenedor->Renderizar();
	tiempo->Renderizar();
	monedas->Renderizar();
	puntuacion->Renderizar();
}

void Interfaz::Destruir()
{
	for (std::size_t i = 0; i < objetosEstaticos.size(); i++)
		objetosEstaticos[i]->Destruir();
	
	numVidas->Destruir();
	contenedor->Destruir();
	tiempo->Destruir();
	monedas->Destruir();
	puntuacion->Destruir();
}
