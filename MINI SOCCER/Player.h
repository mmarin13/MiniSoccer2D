#pragma once
#include "Point2D.h"
#include "Game.h"

#define MAX_JUMP 25

/*Forward declarations*/
class Ball;
class Score;

class Player
{
	Point2D position;
	SDL_Texture* texture;
	SDL_Rect dstRect;
	int jump;

public:
	bool isJumping;
	bool isFalling;
	bool isRunning;
	bool isShooting;
	Point2D velocity;
	Score* scoreBoard;

	Player(const Player&) = delete;
	Player(Player &&) = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player &&) = delete;

	Player(const char* path, Score* sc);
	~Player();

	void init(float x, float y);
	void update();
	void draw();

	void setTexture(const char* path);
	void setPosition(float x, float y);

	SDL_Rect getBox() const;
	Point2D getPosition() const;

	void hitsTheBall(Ball* ball);

	friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

