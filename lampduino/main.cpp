#include <Arduino.h>
#include <stdint.h>
#include "NeoPixelManager.h"
//#define COMM_PIN 5
//#define PREV_PIN 7
//#define NEXT_PIN 8
//#define DECR_PIN 9
//#define INCR_PIN 10
#define RING_PIN 4
#define RING_PIXELS 12

NeoPixelManager manager(RING_PIXELS, RING_PIN);


//volatile byte brlevel = manager.MAX_BRIGHTNESS;
//void commute() { if (manager.isActive()) manager.stop(); else manager.start(); }
//void next_effect() { manager.nextEffect(); }
//void prev_effect() { manager.prevEffect(); }
//void incr_bright() { if (brlevel < manager.MAX_BRIGHTNESS) manager.setBrightness(++brlevel); }
//void decr_bright() { if (brlevel > manager.MIN_BRIGHTNESS) manager.setBrightness(--brlevel); }

uint8_t rounds;
void setup() {
	Serial.begin(9600);
	manager.begin();
//	pinMode(COMM_PIN, INPUT_PULLUP);
//	pinMode(PREV_PIN, INPUT_PULLUP);
//	pinMode(NEXT_PIN, INPUT_PULLUP);
//	pinMode(DECR_PIN, INPUT_PULLUP);
//	pinMode(INCR_PIN, INPUT_PULLUP);
//	attachInterrupt(digitalPinToInterrupt(COMM_PIN), commute, CHANGE);
//	attachInterrupt(digitalPinToInterrupt(PREV_PIN), prev_effect, CHANGE);
//	attachInterrupt(digitalPinToInterrupt(NEXT_PIN), next_effect, CHANGE);
//	attachInterrupt(digitalPinToInterrupt(DECR_PIN), decr_bright, CHANGE);
//	attachInterrupt(digitalPinToInterrupt(INCR_PIN), incr_bright, CHANGE);
	rounds = 1;
	delay(1000);
}

void loop() {
	if (rounds % 16 == 0) manager.nextEffect();
	manager.run();
	rounds++;
}
