#include "Engine.h"
#include "src/SnakeGame.h"
#include "src/SpaceGame.h"
#include "src/PongGame.h"
#include "src/FlappyBirdGame.h"
#include "src/Game.h";

const bool showStartupSequence = true;
const int numGames = 4;

int activeGameIndex = 0;
unsigned long timeOld;

Engine engine = Engine();
Game* game = new FlappyBirdGame();

void setup() {
  Serial.begin(115200);

  engine.setDisplayBrightness(4);

  if (showStartupSequence) {
    startupSequence();
  }
  
  timeOld = millis();
}

void loop() {
  // Calculate delta time
  unsigned long frameStartTime = millis();
  unsigned long deltaTimeMillis = frameStartTime - timeOld;
  float deltaTime = deltaTimeMillis/1000.0;
  timeOld = frameStartTime;

  // Update
  engine.clearScreen();
  engine.updateLoop(deltaTime);
  handleGames(deltaTime);
  engine.drawToDisplay();

  // Wait for target fps
  unsigned long endTime = millis();
  unsigned long frameTime = endTime - frameStartTime;

  const unsigned long targetDelay = 16;
  if (frameTime < targetDelay) {
    unsigned long waitForFPSTime = targetDelay - frameTime;
    delay(waitForFPSTime);
  }

}

void handleGames(float deltaTime) {

  if (!game->gameOver) {
    game->updateLoop(engine);
  } else {
		game->scoreDisplayAmount += engine.deltaTime * 10;
		for (int i = 0; i < min(game->getScore(), (int)game->scoreDisplayAmount); i ++) {
			int x = i % 8;
			int y = i / 8;
			engine.setPixel(x,y);
		}
  }

  if (engine.buttonUpThisFrame) {
    const float switchGameButtonHoldTime = 0.75;
    if (engine.buttonDownDuration > switchGameButtonHoldTime) {
      // Next Game
      nextGame();
    } else if (game->gameOver) {
      // Restart
      switchGame(activeGameIndex);
    }
  }

}

void nextGame() {
  activeGameIndex += 1;
  activeGameIndex %= numGames;
  switchGame(activeGameIndex);
}

void switchGame(int index) {
  activeGameIndex = index;
  delete game;

  Serial.print("Switch Game: ");
  Serial.println(activeGameIndex);

  switch (activeGameIndex) {
  case 0:
    Serial.println("Switch to Snake");
    game = new SnakeGame();
    break;
  case 1:
    Serial.println("Switch to Space");
    game = new SpaceGame();
    break;
  case 2:
    Serial.println("Switch to Pong");
    game = new PongGame();
    break;  
  case 3:
    Serial.println("Switch to FlappyBird");
    game = new FlappyBirdGame();
    break;  
  default:
    Serial.println("Game Index Overflow!");
    break;
  }
  
}

void startupSequence() {
  // Frame 1
  for (int y = 0; y < 8; y ++) {
    for (int x = 0; x < 8; x ++) {
      if (!(x <= y || x-8 >= y)) {
        engine.setPixel(x,y);
      }
    }
  }
  engine.drawToDisplay();
  engine.playSound(330, 240);
  delay(320);

  // Frame 2
  for (int y = 0; y < 8; y ++) {
    for (int x = 0; x < 8; x ++) {
      if (x <= y) {
        engine.setPixel(x,y);
      }
    }
  }
  engine.drawToDisplay();
  engine.playSound(392, 240);
  delay(320);

  // Frame 3
  for (int y = 0; y < 8; y ++) {
    for (int x = 0; x < 8; x ++) {
        engine.setPixel(x,y);
     }
   }
  engine.drawToDisplay();
  engine.playSound(494, 640);
  delay(700);

  // Transition out
  for (int i = 0; i < 8; i ++) {
    for (int x = 0; x < 8; x ++) {
      for (int y = 0; y < 8; y ++) {
        if ((x+(8-y) <= i || 8-x+y <= i)) {
          engine.setPixelToValue(x, y, false);
        }
      }
    }
    engine.drawToDisplay();
    delay(35);
  }
  delay(30);
}
