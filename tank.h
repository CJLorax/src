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


#include "tankbullet.h"

class Tank {

public:

	// is the player active - still alive?
	bool active;

	// variable to hold the list of bullets
	vector<TankBullet> bulletList;

	// string to hold the path to the player's texture
	string playerPath;

	// Integer for the player's number
	int playerNum;

	// player's texture to hold img
	SDL_Texture *texture;

	// player's SDL_Rect for the X, Y, W, and H of texture
	SDL_Rect posRect;

	// floats to hold the joystaick axis (-1 or 0 or 1)
	float xDir, xDirOld;
	float yDir, yDirOld;

	// float for player speed
	float speed;

	//float for the player's position to avoid precision loss
	float pos_X, pos_Y;

	// vars used to get the angel between the tank's position and the turret's position
	float x, y, tankangle;

	// Point that will be used to rotate the turret - relative to the turret barrel's RECT
	SDL_Point center;

	float oldAngle;

	//audio sound effect - CHUNK
	Mix_Chunk *fire;


	// Player's creation method using passed in values for renderer, player number, path to the texture
	// starting position X, starting position Y
	Tank(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y);

	// Method to allow the player the move via joystick axis
	void OnControllerAxis(const SDL_ControllerAxisEvent event);

	// Method to allow the player interact with joystick buttons
	void OnControllerButton(const SDL_ControllerButtonEvent event);

	// update the player using the passed in deltaTime
	void Update(float deltaTime);

	// draw the player main's passed in renderer
	void Draw(SDL_Renderer *renderer);

	// reset the player
	void Reset();

private:

	void CreateBullet();

};
