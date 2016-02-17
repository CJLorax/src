#include <string>
#include <iostream>
#include <math.h>
using namespace std;

#if defined (_WIN32) ||  (_WIN64)
	#include <SDL.h>
	#include <SDL_image.h>
#endif

#if defined (__APPLE__)
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#endif

#if defined (__linux__)
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
#endif


class TurretBullet {

public:

	// Boolean for the state of the bullet
	bool active;

	// Bullet texture
	SDL_Texture *texture;

	// Bullet rectangle for position (X,Y) and size (W,H)
	SDL_Rect posRect;

	// Bullet speed
	float speed;

	// Bullet float positions to prevent precision loss
	float pos_X, pos_Y;

	// position for the turret and player
	SDL_Point turret, player;

	// distance between the 2
	float distance;


	// Bullet creation method. Requires the renderer, a path to the needed image, an X position, a Y position
	TurretBullet(SDL_Renderer *renderer, string filePath, float x, float y);

	// Bullet Update - requires deltaTime be passed
	void Update(float deltaTime);

	// Bullet Draw - requires renderer be passed
	void Draw(SDL_Renderer *renderer);

	// Bullet Reset
	void Reset();

	// Bullet Start
	void Start(SDL_Rect playerPos, SDL_Rect turretPos);

};


