#include "turretbullet.h"

// Bullet creation method
TurretBullet::TurretBullet(SDL_Renderer *renderer, string filePath, float x,
		float y) {

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
	posRect.x = x;
	posRect.y = y;

	// set the float position values of the texture for precision loss
	pos_X = x;
	pos_Y = y;

}

// Reset the bullet method
void TurretBullet::Start(SDL_Rect playerPos, SDL_Rect turretPos) {

	player.x = playerPos.x;
	player.y = playerPos.y;

	turret.x = turretPos.x;
	turret.y = turretPos.y;

	distance = sqrt(
			(player.x - turret.x) * (player.x - turret.x) + (player.y - turret.y) * (player.y - turret.y));
}

// Reset the bullet method
void TurretBullet::Reset()
{
	// Reset the X position off the screen
	posRect.x = -1000;

	// Update the pos_X for precision
	pos_X = posRect.x;

	// deactivate the bullet
	active = false;
}

// Bullet update method
void TurretBullet::Update(float deltaTime) //float delta
{
	float vX = ((player.x - 32) - turret.x) / distance;
	float vY = ((player.y - 32) - turret.y) / distance;

	//Increment the bullet position by vX and vY each frame
	pos_X += (vX * speed * deltaTime);
	pos_Y += (vY * speed * deltaTime);

	// Update bullet position with code to account for precision loss
	posRect.x = (int) (pos_X + 0.5f);
	posRect.y = (int) (pos_Y + 0.5f);

	// check to see if the bullet is off the top of the screen
	// and deactivate and move off screen
	if ((posRect.y < (0 - posRect.h)) || (posRect.y > 768) || (posRect.x < (0 - posRect.w)) || (posRect.x > 1024)) {
		Reset();
	}
}

// Bullet draw method
void TurretBullet::Draw(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

