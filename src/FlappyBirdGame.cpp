#include "FlappyBirdGame.h"
#include "Arduino.h"
#include "Engine.h"

FlappyBirdGame::FlappyBirdGame() {
  birdX = 2;
  birdY = 3;
  birdVelocity = 0;
  timeSinceLastPipe = 0;
  numPipes = 0;
  pipesSurvived = 0;
  elapsedTime = 0;
}

void FlappyBirdGame::updateLoop(Engine& engine) {
  elapsedTime += engine.deltaTime;

  // Player Input
  if (engine.buttonDownThisFrame) {
    birdVelocity = flapVelocity; 
    engine.playSound(400, 100);
  }
  birdVelocity += gravity * engine.deltaTime;
  birdY += birdVelocity * engine.deltaTime;

  if (birdY < 0) {
    birdY = 0;
    birdVelocity = 0;
  } else if (birdY > Engine::height - 1) {
    birdY = Engine::height - 1;
    birdVelocity = 0;
  }
  
  // Update pipes
  for (int i = numPipes - 1; i >= 0; i--) {
    pipes[i].x -= pipeSpeed * engine.deltaTime;
    if (pipes[i].x < 0) {
      numPipes--;
      pipes[i].x = pipes[numPipes].x;
			pipes[i].y = pipes[numPipes].y;
      pipeSurvived[i] = false;
    }
  }

  float pipeSpacingPercent = min(1, elapsedTime / timeForEndPipeSpacing);
  float pipeSpacing = startpipeSpacing + (pipeSpacingPercent - 0)/(1-0) * (endPipeSpacing-startpipeSpacing);

  timeSinceLastPipe += engine.deltaTime;
  if (timeSinceLastPipe > pipeSpacing) {
    timeSinceLastPipe = timeSinceLastPipe - pipeSpacing;
    pipes[numPipes].x = Engine::width;
    int maxY = Engine::height - pipeGap + 1;
    pipes[numPipes].y = rand() % maxY;
    numPipes++;
  }

  for (int i = 0; i < numPipes; i++) {
    if ((int) birdX == (int) pipes[i].x) {
      if ((int) birdY < (int) pipes[i].y || (int) birdY >= (int) pipes[i].y + pipeGap) {
        gameOver = true;
        engine.playSound(200, 1000);
        return;
      } else if (!pipeSurvived[i]) {
        pipeSurvived[i] = true;
        pipesSurvived++;
        engine.playSound(600, 100);
      }
    }
  }

  engine.setPixel(birdX, birdY);

  // Render the pipes
  for (int i = 0; i < numPipes; i++) {
    for (int y = 0; y < Engine::height; y++) {
      if (y < pipes[i].y || y >= pipes[i].y + pipeGap) {
        engine.setPixel(pipes[i].x, y);
      }
    }
  }
  
}

int FlappyBirdGame::getScore() {
	return pipesSurvived;
}