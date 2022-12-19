#pragma once
#include "Game.h"
#include "../Engine.h"

class PongGame : public  Game {

private:
	const float playerSpeed = 8.5;
	const float botSpeed = 5.2;
	const float ballSpeed = 8.5;

	int points;

	float ballVelX;
	float ballVelY;
	float ballX;
	float ballY;

	float player1Y;
	float player2Y;

	void drawPlayer(Engine& engine, int x, int y);

public:
	PongGame();
	virtual void updateLoop(Engine&);
	virtual int getScore();
};