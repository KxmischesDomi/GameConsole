#pragma once
#include "Game.h"
#include "../Engine.h"

class SnakeGame : public Game {

private:
	const float timeBetweenMoves = .2;
	const int foodSpawnMillisMin = 400;
	const int foodSpawnMillisMax = 2000;

	unsigned char x[Engine::width * Engine::height];
	unsigned char y[Engine::width * Engine::height];

	int snakeLength;
	float timeSinceLastMove;

	int dirX;
	int dirY;
	int nextDirX;
	int nextDirY;

	bool foodExists;
	float timeRemainingToNextFoodSpawn;
	int foodX;
	int foodY;

	void placeFood();
	int sign(float);

public:
	SnakeGame();
	virtual void updateLoop(Engine&);
	virtual int getScore();
};