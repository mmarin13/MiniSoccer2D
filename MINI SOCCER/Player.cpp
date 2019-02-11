#include "Player.h"

Player::Player(const char * path, Score* sc)
{ 
	this->texture = TextureManager::LoadTexture(path);
	position.x = position.y = 0;
	scoreBoard = sc;
	dstRect.h = 120;
	dstRect.w = 80;
}

Player::~Player()
{ 
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	if (scoreBoard != nullptr)
	{
		delete scoreBoard;
		scoreBoard = nullptr;
	}	
}

void Player::init(float x, float y)
{
	position.x = x;
	position.y = y;

	velocity.x = 0;
	velocity.y = 0;
	
	dstRect.x = (int)position.x;
	dstRect.y = (int)position.y;

	jump = 0;
	isRunning = false;
	isShooting = false;
	isJumping = false;
	isFalling = false;
}

void Player::update()
{
	if (isJumping)
	{
		velocity.y = -1;
		position.y += velocity.y * Game::speed;
		jump++;
		if (jump == MAX_JUMP)
		{
			isJumping = false;
			isFalling = true;
		}
	}
	else if(isFalling)
	{
		velocity.y = 1; 
		position.y += velocity.y * Game::speed;
		jump--;
		if (jump == 0)
		{
			isFalling = false;
		}
	}
	position.x += velocity.x * Game::speed;

	/* don't allow the player to go out from window'a area */
	if (position.x > SCREEN_WIDTH - (float)dstRect.w)
	{
		position.x = SCREEN_WIDTH - (float)dstRect.w;
	}		
	else if (position.x < 0)
	{
		position.x = 0;
	}
	if (position.y > SCREEN_HEIGHT - (float)dstRect.h)
	{
		position.y = SCREEN_HEIGHT - (float)dstRect.h;
	}
	else if (position.y < 0)
	{
		position.y = 0;
	}

	/* update position on the windows */
	dstRect.x = (int)position.x;
	dstRect.y = (int)position.y;
}

void Player::draw()
{
	TextureManager::DrawTexture(texture, dstRect);
}

void Player::setTexture(const char* path)
{
	SDL_DestroyTexture(texture);
	texture = TextureManager::LoadTexture(path);
}

void Player::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

SDL_Rect Player::getBox() const
{
	return dstRect;
}

Point2D Player::getPosition() const
{
	return position;
}

void Player::hitsTheBall(Ball* ball)
{
	/*the ball hits the player*/
	ball->velocity.x /= -1.5f; /*the ball orizontal movement is decelerated*/
	if (ball->getPosition().x < this->position.x && ball->getPosition().y > this->position.y) /*the ball is on left side of player*/
	{	
		ball->velocity.x -= 0.2f;	/*the ball is rebounded*/
	}
	if (ball->getPosition().x > this->position.x && ball->getPosition().y > this->position.y) /*the ball is on left right of player*/
	{
		ball->velocity.x += 0.2f;	/*the ball is rebounded*/
	}
	if (ball->velocity.y >= 0)
	{
		ball->velocity.y = -SCREEN_HEIGHT / ball->getMaxHeight() / 1.5f;  /*rebounding is proportional with the height from which the ball is falling*/
	}
	if (this->isRunning) /*the player hits the ball while he is running */
	{
		if (this->position.x <= ball->getPosition().x) /*the ball is on right side of player */
		{
			ball->velocity.x += 2;
		}
		else  /*the ball is on left side of player */
		{
			ball->velocity.x -= 2;
		}
	}
	if (this->isJumping && ball->getPosition().y < this->position.y) /*the players jumps while he is hitting the ball*/
	{
		ball->velocity.y -= 1.5;
	}
	if (this->isShooting && (this->position.y + this->getBox().h) - (ball->getPosition().y + ball->getBox().h) < 30) /*the player shoots*/
	{	
		if (Game::volumeOn == true)
		{
			Mix_PlayChannel(-1, Game::sound->shoot, 0); /*sound effect of shoot*/
		}		
		ball->velocity.y -= 3;
		if (this->position.x < ball->getPosition().x)	/*the ball is on right side of player */
		{
			ball->velocity.x += 3;
		}
		else /*the ball is on left side of player */
		{
			ball->velocity.x -= 3;
		}
	}
}

/*display in console position and velocity of a player*/
std::ostream & operator<<(std::ostream & os, const Player & player)
{
	os << player.position.x << "," << player.position.y << " (" << player.velocity.x << "," << player.velocity.y << ")" << std::endl;
	return os;
}
