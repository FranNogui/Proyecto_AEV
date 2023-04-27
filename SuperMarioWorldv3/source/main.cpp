#include "gameEngine.h"

SDL_Renderer* renderer;
SDL_Window* window;
Interfaz* interfaz;

int main(int argc, char** argv)
{
	romfsInit();
	chdir("romfs:/");
	
	b2Vec2 gravity(0.0, 10.0f);
	b2World world(gravity);
	DetectorDeColisiones detector;
	world.SetContactListener(&detector);
	
	int exit_requested = 0;

	int joystick_deadzone = 8000;
	int joystick_speed = 1;
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);
	
	window = SDL_CreateWindow("Test Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
    if (!joystick) 
	{
        printf("Error: no se pudo abrir el joystick.\n");
        return 1;
    }
	
	interfaz = new Interfaz();
	Camara camara(0.0f, 0.0f);
	Mapa mundo1(RUTA_MAPA_MUNDO_1, &camara, &world);
	Jugador mario(&camara, &world);
	camara.AsignarJugador(&mario);
	
    while (!exit_requested && appletMainLoop()) 
	{
        SDL_SetRenderDrawColor(renderer, mundo1.fondoR, mundo1.fondoG, mundo1.fondoB, 0xFF);
        SDL_RenderClear(renderer);
    
    	// Manejar la entrada del joystick
    	SDL_JoystickUpdate();
    	int x = SDL_JoystickGetAxis(joystick, 0);
    	int y = SDL_JoystickGetAxis(joystick, 1);
    
   	 	// Actualizar la posición de la imagen en función de la entrada del joystick
    	if (x < -joystick_deadzone)
    		x = -joystick_speed;
    	else if (x > joystick_deadzone)
    		x = joystick_speed;
    	else
    		x = 0;
    	
    	if (y < -joystick_deadzone)
    		y = -joystick_speed;
    	else if (y> joystick_deadzone)
    		y = joystick_speed;
    	else
    		y = 0;
    		
    	//camara.x += 6 * x;
    	//camara.y += 6 * y;

		mundo1.Renderizar();
		interfaz->Renderizar();
		mario.Renderizar(x, SDL_JoystickGetButton(joystick, 0));

    	world.Step(1.0f / 60.0f, 6, 2);
    	SDL_RenderPresent(renderer);
    }
    
    mundo1.Destruir();
	interfaz->Destruir();
    IMG_Quit();
    SDL_Quit();
    romfsExit();
    return 0;
}

