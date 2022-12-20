#pragma once
#include "Vector2.cpp"
#include "Game.h"
#include "../Engine.h"

class FlappyBirdGame : public Game {

  private:
    const float pipeSpeed = 3;
    const float pipeSpacing = 2;
    const int pipeGap = 3;
    
    const float gravity = 9.8;
    const float flapVelocity = -5;

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