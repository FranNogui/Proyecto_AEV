#include <time.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <switch.h>

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

SDL_Renderer* renderer;
SDL_Window* window;

struct Vector2D
{
	float x;
	float y;
	
	Vector2D(const float x, const float y)
	{
		this->x = x; this->y = y;
	}
};

Vector2D& operator +(const Vector2D &v1, const Vector2D &v2)
{
	return *(new Vector2D(v1.x + v2.x, v1.y + v2.y));
};

struct Entidad
{
	SDL_Texture *textura;
	SDL_Rect posicion;
	
	void Ubicar(const Vector2D pos)
	{
		posicion.x = pos.x;
		posicion.y = pos.y;
	}
	
	void Ubicar(const float x, const float y)
	{
		posicion.x = x;
		posicion.y = y;
	}
	
	void Mover(const Vector2D mov)
	{
		posicion.x += mov.x;
		posicion.y += mov.y;
	}
	
	void Mover(const float x, const float y)
	{
		posicion.x += x;
		posicion.y += y;
	}
	
	void CargarTextura(const char* ruta)
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
	
	void Renderizar()
	{
		if (textura)
        	SDL_RenderCopy(renderer, textura, NULL, &posicion);
	}
	
	void Destruir()
	{
		SDL_DestroyTexture(textura);
	}
	
	Entidad()
	{
		textura = NULL;
		posicion = {0, 0, 0, 0};
	}
};

int main(int argc, char** argv)
{
	romfsInit();
	chdir("romfs:/");
	
	int exit_requested = 0;
	int wait = 25;
	
	Entidad mario;
	SDL_Event event;

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
    
    mario.CargarTextura("data/mario/marioPequenyo/derecha/QuietoDerecha.png");
    mario.Ubicar(100.0f, 100.0f);
    
    while (!exit_requested && appletMainLoop()) 
	{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);
        

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    	SDL_RenderClear(renderer);
    
    	// Manejar la entrada del joystick
    	SDL_JoystickUpdate();
    	int x = SDL_JoystickGetAxis(joystick, 0);
    	int y = SDL_JoystickGetAxis(joystick, 1);
    
   	 	// Actualizar la posición de la imagen en función de la entrada del joystick
    	if (x >= -joystick_deadzone && x <= joystick_deadzone)
        	x = 0;
    	if (y >= -joystick_deadzone && y <= joystick_deadzone)
        	y = 0;
    	mario.Mover(x, y);
    	
    	mario.Renderizar();
        
    	SDL_RenderPresent(renderer);
    	SDL_Delay(wait);
    }
    
    mario.Destruir();
    IMG_Quit();
    SDL_Quit();
    romfsExit();
    return 0;
}

