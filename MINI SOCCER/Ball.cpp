#include "Ball.h"

Ball::Ball(const char * path)
{
	this->texture = TextureManager::LoadTexture(path);
	dstRect.h = dstRect.w = 32;
}

Ball::~Ball()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}	
}

void Ball::init(float x, float y)
{
	position.x = x;
	position.y = y;
	
	dstRect.x = (int)position.x;
	dstRect.y = (int)position.y;

	velocity.x = 0;
	velocity.y = 2;
	maxHeight = (SCREEN_HEIGHT - dstRect.h) / 2.0f;
}

void Ball::update()
{
	/*update position*/
	position.x += velocity.x * Game::speed;
	position.y += velocity.y * Game::speed;

	/*vertical movement of ball*/
	if (velocity.y < 0) /*the ball is going up*/
	{
		if (fabs(velocity.y) < 0.1f) 
		{
			velocity.y = 0.05f;
			maxHeight = (position.y < 100) ? 100 : position.y;
		}
		else
		{
			velocity.y += 0.09f; /*the ball is decelerated*/
		}
		if (position.y <= 0.0f)	/*the ball hits the top margin of window*/
		{
			velocity.y *= -1.5f;
			maxHeight = 120;
		}
	}
	else if (velocity.y > 0) /*the ball is going down*/
	{
		if (position.y >= SCREEN_HEIGHT - GROUND_LINE - dstRect.h) /*the ball hits the ground*/
		{
			if (maxHeight >= SCREEN_HEIGHT - GROUND_LINE - 50) /*if the height from which the ball falls is too small, then it don't rebound*/
			{
				velocity.y = 0.0f;
			}
			else /*if the height from which the ball falls is big enough, then it rebounds*/
			{
				velocity.y = - SCREEN_HEIGHT / maxHeight + 0.5f; /*rebounding is proportional with the height from which the ball is falling*/
			}
		}
		else
		{
			velocity.y += 0.05f; /*the ball is accelerated*/
		}
	}

	/*orizontal movement of ball*/
	velocity.x -= velocity.getSignX()*0.02f; /*orizontal movement of ball is decelerated*/
	if (fabs(velocity.x) < 0.1f) /*the ball stops*/
	{
		velocity.x = 0.0f;
	}
	if (position.x <= 0.0f || position.x >= SCREEN_WIDTH - 32) /*the ball hits the left/right margins of window*/
	{
		velocity.x /= -1.5; /*the ball is rebounded*/
	}

	/* don't allow the ball to go out from the window's area */
	if (position.x > SCREEN_WIDTH - dstRect.w)
	{
		position.x = (float)SCREEN_WIDTH - dstRect.w;
	}
	else if (position.x < 0)
	{
		position.x = 0;
	}
	if (position.y > SCREEN_HEIGHT - GROUND_LINE - dstRect.h)
	{
		position.y = (float)SCREEN_HEIGHT - GROUND_LINE - dstRect.h;
	}
	else if (position.y < 0)
	{
		position.y = 0;
	}
	/* update position on the window */
	dstRect.x = (int)position.x;
	dstRect.y = (int)position.y;
}

void Ball::draw()
{
	TextureManager::DrawTexture(texture, dstRect);
}

float Ball::x() const
{
	return position.x;
}

float Ball::y() const
{
	return position.y;
}

float Ball::getMaxHeight() const
{
	return maxHeight;
}

SDL_Rect Ball::getBox() const
{
	return dstRect;
}

Point2D Ball::getPosition() const
{
	return position;
}

/*display in console position and velocity of the ball*/
std::ostream & operator<<(std::ostream & os, const Ball & ball)
{
	os << ball.position.x << "," << ball.position.y << " (" << ball.velocity.x << "," << ball.velocity.y << ")" << std::endl;
	return os;
}