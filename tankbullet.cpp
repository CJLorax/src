#include "tankbullet.h"


// Bullet creation method
TankBullet::TankBullet(SDL_Renderer *renderer, string filePath, float x, float y, int dirX, int dirY)
{
	// Set the bullet initial state
	active = false;

	// Set bullet speed
	speed = 800.0;

	// Create the texture from the passed Renderer and created surface
	texture = IMG_LoadTexture(renderer, filePath.c_str());

	// set the width and height of the bullet's rectangle
	// by querying the texture itself
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;

	// Set the x and y positions of the bullet rectangle
	// finishing aligning to the player center using the texture width
	posRect.x = x - (posRect.w/2);
	posRect.y = y;

	// set the float position values of the texture for precision loss
	pos_X = x;
	pos_Y = y;

	// initialize the direction vars for the bullet
	//no X movement, only Y movement (up)
	xDir = dirX;
	yDir = dirY;

}

// Reset the bullet method
void TankBullet::Reset()
{
	// Reset the X position off the screen
	posRect.x = -1000;

	// Update the pos_X for precision
	pos_X = posRect.x;

	// deactivate the bullet
	active = false;
}


// Bullet update method
void TankBullet::Update(float deltaTime) //float delta
{
	// check to see if the bullet is active
	if (active) {

		// Adjust position floats based on speed, direction (-1 for up), and deltaTime
		pos_X += (speed * xDir) * deltaTime;
		pos_Y += (speed * yDir) * deltaTime;

		// Update bullet position with code to account for precision loss
		posRect.x = (int) (pos_X + 0.5f);
		posRect.y = (int) (pos_Y + 0.5f);

		// check to see if the bullet is off the top of the screen
		// and deactivate and move off screen
		if ((posRect.y < (0 - posRect.h)) || (posRect.y > 768) || (posRect.x < (0 - posRect.w)) || (posRect.x > 1024) ) {
			Reset();
		}
	}
}

// Bullet draw method
void TankBullet::Draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}


