#pragma once
#include "Vector2.cpp"
#include "Game.h"
#include "../Engine.h"

class SpaceGame : public Game {
	
private:
	// Difficulty settings:
	const float enemySpeed = 6;
	const float spawnDelayStart = 2;
	const float spawnDelayEnd = .5;
	const float difficultyDuration = 18*2;
	const float delayBetweenShots = .2;
	const float playerSpeed = 8.5;

	Vector2 playerPos;
	Vector2 bullets[16];
	Vector2 enemies[32];

	int numEnemies;
	int numBullets;
	int numEnemiesDestroyed;
	float timeToNextEnemySpawn;
	float lastShootTime;
	float elapsedTime;
	
	
public:
	SpaceGame();
	virtual void updateLoop(Engine&);
	virtual int getScore();
};