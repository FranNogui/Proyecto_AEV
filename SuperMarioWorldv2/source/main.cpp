#include "gameEngine.h"

#define JOY_A     0
#define JOY_B     1
#define JOY_X     2
#define JOY_Y     3
#define JOY_PLUS  10
#define JOY_MINUS 11
#define JOY_LEFT  12
#define JOY_UP    13
#define JOY_RIGHT 14
#define JOY_DOWN  15

#define SCREEN_W 256
#define SCREEN_H 224

/*
#define SCREEN_W 1920
#define SCREEN_H 1080
*/

/*
struct EntidadDinamica : Entidad
{
	EntidadDinamica() : Entidad()
	{}
	
	void Mover(const Vector2D mov)
	{
		posicion.x += int(mov.x);
		posicion.y += int(mov.y);
	}
	
	void Mover(const float x, const float y)
	{
		posicion.x += int(x);
		posicion.y += int(y);
	}
};
*/

SDL_Renderer* renderer;
SDL_Window* window;
int fondoR, fondoG, fondoB;

int main(int argc, char** argv)
{
	romfsInit();
	chdir("romfs:/");
	
	b2Vec2 gravity(0.0, 10.0f);
	b2World world(gravity);
	
	int exit_requested = 0;
	int wait = 25;

	int joystick_deadzone = 8000;
	int joystick_speed = 5;
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);
	
	window = SDL_CreateWindow("Test Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
    if (!joystick) {
        printf("Error: no se pudo abrir el joystick.\n");
        return 1;
    }
    
    Jugador mario;
    mario.CargarTextura(RUTA_MARIO_PEQUENYO_DERECHA_QUIETO);
    mario.Ubicar(100.0f, 100.0f);
    mario.CrearFisicas(&world);
    Mapa mundo1(RUTA_MAPA_MUNDO_1);
	Vector2D mov = *(new Vector2D(0, 0));
	
    while (!exit_requested && appletMainLoop()) 
	{
        SDL_SetRenderDrawColor(renderer, fondoR, fondoG, fondoB, 0xFF);
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
    		
    	mov.x = x;
    	mov.y = y;
    	mov.Normalizar();
    	mov = mov * joystick_speed;
    	//mario.Mover(mov);
    	
    	world.Step(1.0f / 60.0f, 6, 2);
    	mario.Renderizar();
    	//mundo1.Renderizar();
    	SDL_RenderPresent(renderer);
    }
    
    mario.Destruir();
	mundo1.Destruir();
    IMG_Quit();
    SDL_Quit();
    romfsExit();
    return 0;
}

