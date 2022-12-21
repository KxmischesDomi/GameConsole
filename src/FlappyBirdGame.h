#pragma once
#include "Vector2.cpp"
#include "Game.h"
#include "Engine.h"

class FlappyBirdGame : public Game {

  private:
    const float pipeSpeed = 3;
    const float pipeGap = 3;
    const float startpipeSpacing = 2.5;
    const float endPipeSpacing = 1.5;
    const float timeForEndPipeSpacing = 60;

    const float gravity = 15;
    const float flapVelocity = -8;

    float elapsedTime;

    float birdX;
    float birdY;
    float birdVelocity;
    float timeSinceLastPipe;

    int numPipes;
    Vector2 pipes[5] = {};
    bool pipeSurvived[5] = {};

    int pipesSurvived;

  public:
    FlappyBirdGame();
    virtual void updateLoop(Engine& engine);
    virtual int getScore();

};