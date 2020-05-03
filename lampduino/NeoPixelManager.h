#ifndef NEOPIXELMANAGER_H_
#define NEOPIXELMANAGER_H_

#include <Arduino.h>
#include <stdint.h>
#include "Adafruit_NeoPixel.h"

#define RANDOM_SEED_PIN A5

class NeoPixelManager {
public:
	const static uint8_t MIN_BRIGHTNESS = 1;
	const static uint8_t MAX_BRIGHTNESS = 8;
	const static uint8_t N_EFFECTS = 8;

	NeoPixelManager(uint8_t, uint8_t);
	bool isActive();
	void begin();
	void clear();
	void colorTest();
	void goEffect(uint8_t);
	void nextEffect();
	void prevEffect();
	void run();
	void start();
	void stop();
	void setBrightness(uint8_t);

private:
	struct Interval { uint8_t min, max; };
	const static uint8_t MAX_SATURATION = 255;
	const static uint16_t MAX_COLOR = 65535;
	const static uint8_t N_COLORS = 6;

	const static Interval BRIGHTNESS[MAX_BRIGHTNESS];
	const static uint16_t COLORS[N_COLORS];

	Adafruit_NeoPixel* neopixel;
	bool active;
	uint8_t brightness;
	uint8_t currentEffect;
	uint8_t numPixels;

	uint16_t randomColor();
	void effect1();
	void effect2();
	void effect3();
	void effect4();
	void effect5();
	void effect6();
	void effect7();
	void effect8();
};

#endif
