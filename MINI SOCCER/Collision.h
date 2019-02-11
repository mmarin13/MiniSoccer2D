#pragma once
#include <SDL.h>
#include "Button.h"

/*Forward declarations*/
class Button;

class Collision
{
public:
	Collision() = delete;
	Collision(const Collision&) = delete;
	Collision(Collision&&) = delete;
	Collision& operator=(const Collision&) = delete;
	Collision& operator=(Collision&&) = delete;
	~Collision() = delete;

	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const Button* button, int mouseX, int mouseY);
	static bool AABB_GoalL(const SDL_Rect& recBall, const SDL_Rect& recGateL);
	static bool AABB_GoalR(const SDL_Rect& recBall, const SDL_Rect& recGateR);
	static bool AABB_GateR(const SDL_Rect& recBall, const SDL_Rect& recGateR);
	static bool AABB_GateL(const SDL_Rect& recBall, const SDL_Rect& recGateL);
};

