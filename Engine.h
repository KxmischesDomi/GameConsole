#pragma once
#include <Arduino.h>
#include <LedControl.h>


class Engine {
private:

	// Input pins:
	const int buttonPin = 3;
	const int xPin = 1;
	const int yPin = 0;

	// Audio pins:
	const int buzzerPin = 11;
	
	// Display pins:
	const int dinPin = 13;
	const int csPin = 12;
	const int clkPin = 11;

	LedControl ledController = LedControl(dinPin,clkPin,csPin, 1); // (DIN, CLK, CS, num displays

	unsigned char rowsDisplay[8];
	int buttonState;

	float remap(float, float, float, float, float);

public:
	float deltaTime;
	unsigned long time;

	// Player input info:
	float inputX;
	float inputY;
	bool buttonDown;
	bool buttonUpThisFrame;
	bool buttonDownThisFrame;
	float buttonDownDuration;


	Engine();

	void playSound(int frequency, int duration);

	void updateLoop(float);

	void clearScreen();

	void setPixel(int x, int y);

	void setPixelToValue(int x, int y, bool on);

	void drawToDisplay();

	void setDisplayBrightness(int);
	
};