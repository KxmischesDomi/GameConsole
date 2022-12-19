#include "PongGame.h"
#include "Arduino.h"
#include "../Engine.h"

PongGame::PongGame() {
    points = 0;

    player1Y = 3;
    player2Y = 3;

    ballVelX = 1;
    ballVelY = 0;
    ballX = 4;
    ballY = 3;
}

void PongGame::updateLoop(Engine& engine) {

    // Move player
	player1Y += engine.deltaTime * playerSpeed * engine.inputY;
	if (player1Y >= Engine::height - 1) {
		player1Y = Engine::height - 2;
	}
	else if (player1Y < 0) {
		player1Y = 0;
	}

    // Update player 2's position based on the ball's position
    if (ballY > player2Y + 1) {
        player2Y += engine.deltaTime * botSpeed;
    } else if (ballY < player2Y) {
        player2Y -= engine.deltaTime * botSpeed;
    }
    // Ensure that player 2 doesn't go out of bounds
    if (player2Y < 0) {
        player2Y = 0;
    } else if (player2Y > Engine::height - 2) {
        player2Y = Engine::height - 2;
    }

    // Move ball
    ballX += engine.deltaTime * ballSpeed * ballVelX;
    ballY += engine.deltaTime * ballSpeed * ballVelY;

    // Check for goals
    if (ballX >= Engine::width) {
        // Point for the player
        ballX = 4;
        ballY = 3;
        ballVelY = 0;
        ballVelX = 1;
        player2Y = 3;
        points++;
        engine.playSound(230,450);
        return;
    } else if (ballX <= 0) {
        // Game over
        engine.playSound(200,1000);
        gameOver = true;
        return;
    } else {
        // Check for top / bottom collissions
        if (ballY >= Engine::height - 1 || ballY <= 1) {
            ballVelY *= -1;
        }

        // Check player collissions
        if (ballX >= Engine::width - 1) {
            if ((int) ballY >= (int) player2Y && (int) ballY <= (int) player2Y + 1) {
                ballX = Engine::width - 2;
                ballVelY = (int) ballY == (int) player2Y ? ballVelY < 0 ? 0 : -1 : ballVelY > 0 ? 0 : 1;
                ballVelX *= -1;
                engine.playSound(360, 150);
            }
        } else if (ballX <= 1) {
            if ((int) ballY >= (int) player1Y && (int) ballY <= (int) player1Y + 1) {
                ballX = 1;
                ballVelY = (int) ballY == (int) player1Y ? ballVelY < 0 ? 0 : -1 : ballVelY > 0 ? 0 : 1;
                ballVelX *= -1;
                engine.playSound(349, 150);
            }
        }
    }
    
    // Draw players
    drawPlayer(engine, 0, player1Y);
    drawPlayer(engine, 7, player2Y);

    // Draw Ball
    engine.setPixel(ballX, ballY);
}

void PongGame::drawPlayer(Engine& engine, int x, int y) {
    engine.setPixel(x, y);
    engine.setPixel(x, y + 1);
}

int PongGame::getScore() {
    return points;
}