#include "gameEngine.h"

using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

Interfaz::Interfaz()
{
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(16, 15, RUTA_MARIO_TEXTO));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(26, 24, RUTA_VIDA_INTERFAZ));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(152, 15, RUTA_TIME_INTERFAZ));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(202, 15, RUTA_DINERO_INTERFAZ));
    objetosEstaticos.push_back(new ObjetoInterfazEstatico(72, 23, RUTA_ESTRELLAS_INTERFAZ));
    vidas = new NumeroVidas(34, 24, 1);
	estrellas = new EstrellasInterfaz(96, 16, 0);
    contenedor = new Contenedor(114, 10, false);
    tiempo = new TiempoInterfaz(153, 24, 300);
    monedas = new MonedasInterfaz(226, 15, 0);
    puntuacion = new PuntuacionInterfaz(186, 24, 0);
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

void Interfaz::CambiarNumeroEstrellas(int numEstrellas)
{
	estrellas->CambiarEstrellas(numEstrellas);
}

void Interfaz::CambiarContenedor()
{
	contenedor->CambiarSeta();
}

void Interfaz::Renderizar()
{
	for (std::size_t i = 0; i < objetosEstaticos.size(); i++)
		objetosEstaticos[i]->Renderizar();

	vidas->Renderizar();
	estrellas->Renderizar();
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
	estrellas->Destruir();
	contenedor->Destruir();
	tiempo->Destruir();
	monedas->Destruir();
	puntuacion->Destruir();
}
