#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

Interfaz::Interfaz()
{
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(0, 0, RUTA_MARIO_TEXTO));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(0, 0, RUTA_VIDA_INTERFAZ));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(0, 0, RUTA_TIME_INTERFAZ));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(0, 0, RUTA_DINERO_INTERFAZ));
    numVidas = new NumeroVidas(0, 0, 5);
    contenedor = new Contenedor(0, 0, false);
    tiempo = new TiempoInterfaz(0, 0, 300);
    monedas = new MonedasInterfaz(0, 0, 20);
    puntuacion = new PuntuacionInterfaz(0, 0, 54321);
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
