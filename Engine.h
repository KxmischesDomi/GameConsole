#pragma once
#include <Arduino.h>
#include <LedControl.h>

#define NUM_HORIZONTAL_DISPLAYS 4
#define NUM_VERTICAL_DISPLAYS 1
#define WIDTH 8 * NUM_HORIZONTAL_DISPLAYS
#define HEIGHT 8 * NUM_VERTICAL_DISPLAYS

class Engine {
private:
	// Input pins:
	const int buttonPin = 2;
	const int xPin = 0;
	const int yPin = 1;

	// Audio pins:
	const int buzzerPin = A5;
	
	// Display pins:
	const int dinPin = 13;
	const int csPin = 12;
	const int clkPin = 11;

	const int numDisplays = NUM_HORIZONTAL_DISPLAYS * NUM_VERTICAL_DISPLAYS;

	LedControl ledController = LedControl(dinPin,clkPin,csPin, numDisplays); // (DIN, CLK, CS, num displays

	bool rowsDisplay[WIDTH][HEIGHT];
	int buttonState;

	float remap(float, float, float, float, float);

public:
	// Display properties:
	static const int width = WIDTH;
	static const int height = HEIGHT;

	// Timings:
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