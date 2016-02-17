#include "turret.h"

// Turret creation Method
Turret::Turret(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y)
{
	// activate the player
	active = false;

	fire = Mix_LoadWAV((audioPath + "fire.wav").c_str());

	//Create the turret base file path
	string basePath = filePath + "turretBase.png";

	// load the image into the texture
	tBase = IMG_LoadTexture(renderer, basePath.c_str());

	//Create the turret base file path
	string barrelPath = filePath + "turretBarrel.png";

	// load the image into the texture
	tBarrel = IMG_LoadTexture(renderer, barrelPath.c_str());

	// set the SDL_Rect X and Y for the base image
	baseRect.x = x;
	baseRect.y = y;

	// Use SDL_QueryTexture to get the W and H of the base's texture
	int w, h;
	SDL_QueryTexture(tBase, NULL, NULL, &w, &h);
	baseRect.w = w;
	baseRect.h = h;

	// set the SDL_Rect X and Y for the barrel (used Photoshop to find this info)
	barrelRect.x = x + 34;
	barrelRect.y = y + 34;

	// Use SDL_QueryTexture to get the W and H of the barrel's texture
	SDL_QueryTexture(tBarrel, NULL, NULL, &w, &h);
	barrelRect.w = w;
	barrelRect.h = h;

	// Create the center point of the barrel texture for rotation (used Photoshop to find this info)
	center.x = 12;
	center.y = 12;

	// String to create the path to the player's bullet image
	string bulletPath = filePath + "tBullet.png";

	//Create the turret's bullet pool
	for (int i = 0; i < 10; i++)
	{
		// create the bullet and move offscreen, out of the game play area
		TurretBullet tmpBullet(renderer, bulletPath, 500, 500);

		// add to bulletlist
		bulletList.push_back(tmpBullet);
	}

	// random null init
	srand(time(NULL));
}


// Tank Update method
void Turret::Update(float deltaTime, SDL_Rect tankRect)
{
	//get the angle between the tank and the turret
	x = (tankRect.x + (tankRect.w/2)) - (baseRect.x + (baseRect.w/2));
	y = (tankRect.y + (tankRect.h/2)) - (baseRect.y + (baseRect.h/2));
	turretangle = atan2(y,x) * 180 / 3.14;

	if(SDL_GetTicks() > fireTime){

		CreateBullet(tankRect);

		fireTime = SDL_GetTicks() + (rand() % 3 + 1) * 1000;
	}

	// Update the turret's bullets
	for (int i = 0; i < bulletList.size(); i++)
	{
		// check to see if the bullet is active
		if(bulletList[i].active){

			// update bullet
			bulletList[i].Update(deltaTime);
		}
	}
}

// Turret Draw method
void Turret::Draw(SDL_Renderer *renderer)
{
	// draw the turret's bullets
	for (int i = 0; i < bulletList.size(); i++)
	{
		// check to see if the bullet is active
		if(bulletList[i].active){

			// Draw Bullet
			bulletList[i].Draw(renderer);
		}
	}

	// Draw the base
	SDL_RenderCopy(renderer, tBase, NULL, &baseRect);

	// Draw the barrel texture using the vars texture and posRect
	SDL_RenderCopyEx( renderer, tBarrel, NULL, &barrelRect, turretangle, &center, SDL_FLIP_NONE );
}

// create a bullet
void Turret::CreateBullet(SDL_Rect target)
{
	// see if there is a bullet active to fire
	for (int i = 0; i < bulletList.size(); i++)
	{
		// see if the bullet is not active
		if(bulletList[i].active == false){

			bulletList[i].Start(target, baseRect);

			// Play the Over Sound - plays fine through levels, must pause for QUIT
			Mix_PlayChannel(-1, fire, 0);

			// set bullet to active
			bulletList[i].active = true;

			// use some math in the x position to get the bullet close to
			// the center of the turret
			bulletList[i].posRect.x = ((baseRect.x + (baseRect.w/2)) - (bulletList[i].posRect.w/2));
			bulletList[i].posRect.y = ((baseRect.y + (baseRect.h/2)) - (bulletList[i].posRect.h/2));

			// Set the x and y positions of the bullet's float positions
			bulletList[i].pos_X = bulletList[i].posRect.x;
			bulletList[i].pos_Y = bulletList[i].posRect.y;

			// once bullet is found, break out of loop
			break;
		}
	}
}




