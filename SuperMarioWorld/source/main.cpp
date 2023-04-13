#include <time.h>
#include <unistd.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

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
/*
#define SCREEN_W 256
#define SCREEN_H 224
*/
#define SCREEN_W 1920
#define SCREEN_H 1080

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
	
	void Normalizar()
	{
		float aux = sqrt(x * x + y * y);
		x /= aux;
		y /= aux;
	}
};

Vector2D& operator +(const Vector2D &v1, const Vector2D &v2)
{
	return *(new Vector2D(v1.x + v2.x, v1.y + v2.y));
}

Vector2D& operator *(const Vector2D &v1, const float &f1)
{
	return *(new Vector2D(v1.x * f1, v1.y * f1));
}

struct Entidad
{
	SDL_Texture *textura;
	SDL_Rect posicion;	

	Entidad()
	{
		textura = NULL;
		posicion = {0, 0, 0, 0};
		
	}
	
	void Ubicar(const Vector2D pos)
	{
		posicion.x = int(pos.x);
		posicion.y = int(pos.y);
	}
	
	void Ubicar(const float x, const float y)
	{
		posicion.x = int(x);
		posicion.y = int(y);
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
};

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

struct EntidadDinamicaAnimada : EntidadDinamica
{
	SDL_Texture* frames[64];
	int nFrames;
	int nTicksPorFrame;
	int tickActual;
	
	EntidadDinamicaAnimada() : EntidadDinamica()
	{}
	
	SDL_Texture* ObtenerTextura(const char* ruta)
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
	
	void CrearAnimacion(const int nFrames, const int nTicksPorFrame, const char* rutas[])
	{
		this->nFrames = nFrames;
		this->nTicksPorFrame = nTicksPorFrame;
		for (int i = 0; i < nFrames; i++)
		{
			frames[i] = ObtenerTextura(rutas[i]);
		}
		tickActual = 0;
	}
	
	void Renderizar()
	{
		tickActual++;
		for (int i = 0; i < nFrames; i++)
		{
			if (tickActual <= i * nTicksPorFrame + nTicksPorFrame)
			{
				textura = frames[i];
				break;
			}
		}
		if (tickActual > nFrames * nTicksPorFrame + nTicksPorFrame)
		{
			tickActual = 0;
			textura = frames[0];
		}
		EntidadDinamica::Renderizar();
	}
};

struct Mapa
{
	int ancho;
	int alto;
	Entidad tiles_suelo1[8];
	std::vector<Entidad> tiles_suelo;
	
	SDL_Texture* CargarTextura(const char* ruta)
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
	
	void CargarTexturaSuelos()
	{	
		tiles_suelo1[0].CargarTextura("data/suelos/suelo/Tile_1.png");
		tiles_suelo1[1].CargarTextura("data/suelos/suelo/Tile_2.png");
		tiles_suelo1[2].CargarTextura("data/suelos/suelo/Tile_3.png");
		tiles_suelo1[3].CargarTextura("data/suelos/suelo/Tile_4.png");
		tiles_suelo1[4].CargarTextura("data/suelos/suelo/Tile_5.png");
		tiles_suelo1[5].CargarTextura("data/suelos/suelo/Tile_6.png");
		tiles_suelo1[6].CargarTextura("data/suelos/suelo/Tile_7.png");
		tiles_suelo1[7].CargarTextura("data/suelos/suelo/Tile_8.png");
	}
	
	Mapa(const char* ruta)
	{
		CargarTexturaSuelos();
		std::ifstream mapa;
		mapa.open(ruta, std::ios::in);
		mapa >> ancho >> alto;
		int pixeles = 16, act = 0;
		for (int i = 0; i < alto; i++)
		{
			for (int j = 0; j < ancho; j++)
			{
				mapa >> act;
				if (act != 0)
				{
					act--;
					tiles_suelo1[act].Ubicar(j * pixeles, i * pixeles);
					tiles_suelo.push_back(tiles_suelo1[act]);
				}
			}
		}
		mapa.close();
	}
	
	void Renderizar()
	{
		for (std::size_t i = 0; i < tiles_suelo.size(); i++)
			tiles_suelo[i].Renderizar();
	}
	
	void Destruir()
	{
		for (std::size_t i = 0; i < tiles_suelo.size(); i++)
			tiles_suelo[i].Destruir();
	}
};

int main(int argc, char** argv)
{
	romfsInit();
	chdir("romfs:/");
	
	int exit_requested = 0;
	int wait = 25;
	
	EntidadDinamica mario;
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
    Mapa* mundo1 = new Mapa("data/mapas/mundo1/mundo1.dat");

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
    	
    	Vector2D mov = *(new Vector2D(x, y));
    	mov.Normalizar();
    	mov = mov * joystick_speed;
    	mario.Mover(mov);
    	
    	mario.Renderizar();
    	mundo1->Renderizar();
        
    	SDL_RenderPresent(renderer);
    	SDL_Delay(wait);
    }
    
    mario.Destruir();
    IMG_Quit();
    SDL_Quit();
    romfsExit();
    return 0;
}

