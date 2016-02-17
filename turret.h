// needed includes
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#include <vector>

#if defined(__APPLE__)
	#include "SDL2/SDL.h"
	#include "SDL2_image/SDL_image.h"
	#include "SDL2_mixer/SDL_mixer.h"
	#include "SDL2_ttf/SDL_ttf.h"
#endif

#if defined(_WIN32) || (_WIN64)
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#endif

#if defined(__linux__)
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
	#include "SDL2/SDL_mixer.h"
	#include "SDL2/SDL_ttf.h"

#endif


#include "turretbullet.h"

class Turret {

public:

	// is the turret active - still alive?
	bool active;

	// variable to hold the list of bullets
	vector<TurretBullet> bulletList;

	// string to hold the path to the turret's texture
	string playerPath;

	// turret's texture to hold base and barrel images
	SDL_Texture *tBase;
	SDL_Texture *tBarrel;

	// turret's SDL_Rect for the X, Y, W, and H of base texture
	SDL_Rect baseRect;

	// turret's SDL_Rect for the X, Y, W, and H of barrel texture
	SDL_Rect barrelRect;

	// vars used to get the angel between the turret's position and the tank's position
	float x, y, turretangle;

	// Point that will be used to rotate the turret - relative to the turret barrel's RECT
	SDL_Point center;

	//floats for fireTime and fireRate
	float fireTime = 0.0f;
	float fireRate = 1000.0f; // one second

	//audio sound effect - CHUNK
	Mix_Chunk *fire;

	// Turret's creation method using passed in values for renderer, player number, path to the texture
	// starting position X, starting position Y
	Turret(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y);

	// update the turret using the passed in deltaTime
	void Update(float deltaTime, SDL_Rect tankRect);

	// draw the turret main's passed in renderer
	void Draw(SDL_Renderer *renderer);

	// reset the turret
	void Reset();

	// create a bullet
	void CreateBullet(SDL_Rect target);

};
