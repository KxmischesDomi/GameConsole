#include "PongGame.h"
#include "Arduino.h"
#include "../Engine.h"

PongGame::PongGame() {
    points = 0;

    player1Y = Engine::height / 2 - 1;
    player2Y = Engine::height / 2 - 1;

    ballVelX = 1;
    ballVelY = 0;
    ballX = Engine::width / 2;
    ballY = Engine::height / 2 - 1;
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
        ballX = Engine::width / 2;
        ballY = Engine::height / 2 - 1;
        ballVelY = 0;
        ballVelX = 1;
        points++;
        engine.playSound(230,450);
        return;
    } else if (ballX <= 0) {
        // Game over
        engine.playSound(200,1000);
        gameOver = true;
        return;
    } else {
        bool onGround = false;
        // Check for top / bottom collissions
        if (ballY >= Engine::height - 1 || ballY <= 1) {
            ballVelY = -ballVelY;
            onGround = true;
        }

        // Check player collissions
        if (ballX >= Engine::width - 1 && ballVelX > 0) {
            if ((int) ballY >= (int) player2Y && (int) ballY <= (int) player2Y + 1) {
                ballX = Engine::width - 2;
                ballVelY = (int) player1Y == (int) ballY ? -ballYVelocity : ballYVelocity;
                if ((int) ballY == 0 || (int) ballY == Engine::height - 1) ballVelY = -ballVelY;
                ballVelX *= -1;
                engine.playSound(360, 150);
            }
        } else if (ballX <= 1 && ballVelX < 0) {
            if ((int) ballY >= (int) player1Y && (int) ballY <= (int) player1Y + 1) {
                ballX = 1;
                ballVelY = (int) player1Y == (int) ballY ? -ballYVelocity : ballYVelocity;
                if ((int) ballY == 0 || (int) ballY == Engine::height - 1) ballVelY = -ballVelY;
                ballVelX *= -1;
                engine.playSound(349, 150);
            }
        }
    }
    
    // Draw players
    drawPlayer(engine, 0, player1Y);
    drawPlayer(engine, Engine::width - 1, player2Y);

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