#pragma once
#include "Engine.h"

class Game {
public:
	Game() {}

	bool gameOver = false;
	float scoreDisplayAmount = -5;

	virtual void updateLoop(Engine&);
	virtual int getScore();
};