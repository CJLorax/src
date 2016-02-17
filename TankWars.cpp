#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <ctime>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// deltaTime var intialization - for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

#include "tank.h"
#include "turret.h"

#if defined(__APPLE__)
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
	#include <SDL2_mixer/SDL_mixer.h>
	#include <SDL2_ttf/SDL_ttf.h>

	string currentWorkingDirectory(getcwd(NULL, 0));
	string images_dir = currentWorkingDirectory + "/src/";
	string audio_dir = currentWorkingDirectory + "/src/";
#endif

#if defined(_WIN32) || (_WIN64)
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"

	#include <direct.h>
	#define getcwd _getcwd

	string currentWorkingDirectory(getcwd(NULL, 0));
	string images_dir = currentWorkingDirectory + "\\src\\";
	string audio_dir = currentWorkingDirectory + "\\src\\";
#endif


#if defined(__linux__)
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
	#include "SDL2/SDL_mixer.h"
	#include "SDL2/SDL_TTF.h"

	#include <unistd.h>

	string currentWorkingDirectory(getcwd(NULL,0));
	string images_dir = currentWorkingDirectory +"/src/";
	string audio_dir = currentWorkingDirectory +"/src/";
#endif


// Main Start ************************************************
int main() {

	// ******************* Create the SDL Window - START *******************
	// Start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create a SDL Window reference - pointer
	SDL_Window *window = nullptr;

	// Create a SDL RenderTarget - pointer
	SDL_Renderer *renderer = nullptr;

	// Create a SDL Window in the middle of the screen
	window = SDL_CreateWindow("Tank Wars!",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	// Create an SDL RenderTarget
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// ******************* Create the SDL Window - END *******************


	// ******************* variable creation - start *******************
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	// ******************* variable creation - end *******************


	// ***** Turn on Game Controller Events *****
	SDL_GameControllerEventState(SDL_ENABLE);

	// ***** set up a Game Controller variable for player 1 *****
	SDL_GameController* gGameController0 = NULL;

	// ***** Open Game Controller for player 1 *****
	gGameController0 = SDL_GameControllerOpen(0);

    // Open Audio Channel
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    //Load a MUSIC file
	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "background.mp3").c_str());

	// IF the MUSIC file is not playing - Play it.
	if(!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);


	// *********************************** Create Players - START **************************
	Tank tank1 = Tank(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 50.0f, 50.0f);

	// *********************************** Create Turrets - START **************************
	Turret turret1 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 800.0f, 500.0f);


	// MAIN GAME LOOP START *****************************************

	while( !quit )
	{
		// Create deltaTime - for frame rate independence
		thisTime = SDL_GetTicks();
		deltaTime = (float) (thisTime - lastTime) / 1000;
		lastTime = thisTime;

		// Handle Events on Queue - Keypresses and such START *****************************************
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			switch (e.type) {
			case SDL_CONTROLLERBUTTONDOWN:

				if (e.cdevice.which == 0) {

					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {

						tank1.OnControllerButton(e.cbutton);
						break;
					}
				}

				break;

			case SDL_CONTROLLERAXISMOTION:

				tank1.OnControllerAxis(e.caxis);

				break;
			}
		}
		// Handle Events on Queue - Keypresses and such END *****************************************

		// ******************* Start the Update Process *******************
		tank1.Update(deltaTime);
		turret1.Update(deltaTime, tank1.posRect);
		// ******************* End the Update Process *******************


		// ******************* Start the SDL Draw Process *******************
		// Clear the SDL RenderTarget
		SDL_RenderClear(renderer);
		tank1.Draw(renderer);
		turret1.Draw(renderer);
		SDL_RenderPresent(renderer);

		// ******************* End the SDL Draw Process *******************
	}

	// MAIN LOOP END

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

	return 0;
}
