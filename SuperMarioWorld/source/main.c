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

int main(int argc, char** argv)
{
	romfsInit();
	chdir("romfs:/");
	
	int exit_requested = 0;
	int wait = 25;
	
	SDL_Texture *mario_tex = NULL;
	SDL_Rect pos_mario = {0, 0, 0, 0};
	SDL_Event event;
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);
	
	SDL_Window* window = SDL_CreateWindow("Test Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	
	SDL_Surface* mario = IMG_Load("data/mario/MarioPequenyo/derecha/QuietoDerecha.png");
	if (mario)
	{
		pos_mario.x = 100;
		pos_mario.y = 100;
		pos_mario.w = mario->w;
		pos_mario.h = mario->h;
		mario_tex = SDL_CreateTextureFromSurface(renderer, mario);
		SDL_FreeSurface(mario);
	}
	
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_JoystickOpen(0);
    
    while (!exit_requested && appletMainLoop()) 
	{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);
        
        if (mario_tex)
        	SDL_RenderCopy(renderer, mario_tex, NULL, &pos_mario);
        	
        SDL_RenderPresent(renderer);
        SDL_Delay(wait);
    }
    
    if (mario_tex)
    	SDL_DestroyTexture(mario_tex);
    IMG_Quit();
    SDL_Quit();
    romfsExit();
    return 0;
}
