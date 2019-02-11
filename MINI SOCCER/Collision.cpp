#include "Collision.h"

/*Axis Aligned Bounding Box Collisions*/
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) 
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}
	return false;
}

bool Collision::AABB(const Button* button, int mouseX, int mouseY)
{
	if (mouseX > button->getBox().x && mouseX <button->getBox().x + button->getBox().w &&
		mouseY > button->getBox().y && mouseY < button->getBox().y + button->getBox().h)
	{
		return true;
	}
	return false;
}

bool Collision::AABB_GoalL(const SDL_Rect& recBall, const SDL_Rect& recGateL)
{
	int barDim = 5;
	if (recBall.y > recGateL.y + barDim && recBall.x < recGateL.w - recBall.w - 30)
	{
		return true;
	}
	return false;
}

bool Collision::AABB_GoalR(const SDL_Rect& recBall, const SDL_Rect& recGateR)
{
	int barDim = 5;
	if (recBall.y > recGateR.y + barDim && recBall.x > recGateR.x)
	{
		return true;
	}
	return false;
}

bool Collision::AABB_GateR(const SDL_Rect & recBall, const SDL_Rect & recGateR)
{
	if (recBall.x + recBall.w > recGateR.x && recBall.y + recBall.h >= recGateR.y && recBall.y < recGateR.y)
	{
		return true;
	}
	return false;
}

bool Collision::AABB_GateL(const SDL_Rect & recBall, const SDL_Rect & recGateL)
{
	if (recBall.x < recGateL.w - 30 && recBall.y + recBall.h >= recGateL.y && recBall.y < recGateL.y)
	{
		return true;
	}
	return false;
}

