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
    vidas = new NumeroVidas(0, 0, 5);
    contenedor = new Contenedor(40, 0, false);
    tiempo = new TiempoInterfaz(80, 0, 300);
    monedas = new MonedasInterfaz(120, 0, 0);
    puntuacion = new PuntuacionInterfaz(160, 0, 0);
}

void Interfaz::CambiarPuntuacion(int numPuntos)
{
	puntuacion->CambiarPuntuacion(numPuntos);
}

void Interfaz::CambiarNumeroMonedas(int numMonedas)
{
	monedas->CambiarMonedas(numMonedas);
}

void Interfaz::CambiarNumeroVidas(int numVidas)
{
	vidas->CambiarVida(numVidas);
}

void Interfaz::Renderizar()
{
	for (std::size_t i = 0; i < objetosEstaticos.size(); i++)
		objetosEstaticos[i]->Renderizar();

	vidas->Renderizar();
	contenedor->Renderizar();
	tiempo->Renderizar();
	monedas->Renderizar();
	puntuacion->Renderizar();
}

void Interfaz::Destruir()
{
	for (std::size_t i = 0; i < objetosEstaticos.size(); i++)
		objetosEstaticos[i]->Destruir();
	
	vidas->Destruir();
	contenedor->Destruir();
	tiempo->Destruir();
	monedas->Destruir();
	puntuacion->Destruir();
}
