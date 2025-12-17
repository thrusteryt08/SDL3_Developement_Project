#define SDL_MAIN_USE_CALLBACKS 1
#include <iostream>
#include <string>

#include "../SDL3_Developement_Project/Include/Func.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

Window window("Window", 1000, 500);


//Startup
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	SDL_SetAppMetadata("App", "1.0", "com.example.renderer-clear");
	SDL_Init(SDL_INIT_VIDEO);

	return SDL_APP_CONTINUE;
}

//Input
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	return SDL_APP_CONTINUE;
}

//While
SDL_AppResult SDL_AppIterate(void* appstate)
{
	return SDL_APP_CONTINUE;
}

//Exit
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{

}