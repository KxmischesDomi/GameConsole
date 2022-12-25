#include "Engine.h"
#include "Arduino.h"
#include <LedControl.h>
#include "src/Game.h"

Engine :: Engine() {
	for (int i = 0; i < numDisplays; i++) {
		ledController.shutdown(i, false);
	}

  	pinMode(buzzerPin, INPUT);
  	pinMode(buzzerPin, OUTPUT);

	pinMode(buttonPin, INPUT);
	digitalWrite(buttonPin, HIGH);

  	clearScreen();
  	time = 0;
}

void Engine :: updateLoop(float deltaTime) {
	this->deltaTime = deltaTime;
	time += deltaTime;

	// Button input:
	int buttonStateOld = buttonState;
	buttonState = !digitalRead(buttonPin);
	buttonDown = buttonState == 1;
  	buttonDownThisFrame = buttonDown && buttonState != buttonStateOld;
  	buttonUpThisFrame = buttonState == 0 && buttonStateOld == 1;

  	if (buttonDownThisFrame) {
  		buttonDownDuration = 0;
  	}
  	if (buttonDown) {
  		buttonDownDuration += deltaTime;
  	}

	// Get analog stick input:
	const float inputThreshold = 0.1;
	inputX = remap(analogRead(xPin), 0, 1023, 1, -1);
	inputY = -remap(analogRead(yPin), 0, 1023, -1, 1);

/* 	Serial.print("X: ");
	Serial.print(inputX);
	Serial.print(" Y: ");
	Serial.print(inputY);
	Serial.print("\n"); */

	if (abs(inputX) < inputThreshold) {
		inputX = 0;
	}
	if (abs(inputY) < inputThreshold) {
		inputY = 0;
	}
}

void Engine :: playSound(int frequency, int duration) {
	tone(buzzerPin, frequency, duration);
}

void Engine :: clearScreen() {
 	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			rowsDisplay[x][y] = 0;
		}
 	}
}

void Engine :: drawToDisplay() {
	for (int h = 0; h < NUM_HORIZONTAL_DISPLAYS; h++) { // 1
		for (int v = 0; v < NUM_VERTICAL_DISPLAYS; v++) { // 0
			int index = (h + 1) * (v + 1) - 1; // 1
			for (int row = 0; row < 8; row++) { // 7
				byte rowData = 0;
				for (int col = 0; col < 8; col++) { // 7
					rowData |= rowsDisplay[col + h * 8][row + v * 8] << col; // 7 :: 15
				}
				ledController.setRow(index, 7 - row, rowData);
			}
		}
	}
}

// set display brightness [0,15]
void Engine :: setDisplayBrightness(int brightness) {
	for (int i = 0; i < numDisplays; i++) {
		ledController.setIntensity(i, brightness);
	}
}

void Engine :: setPixel(int x, int y) {
	setPixelToValue(x, y, true);
}

void Engine :: setPixelToValue(int x, int y, bool on) {
	if (x >= width || x < 0 || y >= height || y < 0) {
		return;
	}
		if (on) {
			rowsDisplay[x][y] = true;
		}
		else {
			rowsDisplay[x][y] = false;
		}
}

float Engine :: remap(float value, float minOld, float maxOld, float minNew, float maxNew) {
  return minNew + (value - minOld)/(maxOld-minOld) * (maxNew-minNew);
}
