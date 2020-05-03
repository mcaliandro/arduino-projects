#include "NeoPixelManager.h"

const NeoPixelManager::Interval NeoPixelManager::BRIGHTNESS[] = { {16,32}, {32,64}, {48,96}, {64,128}, {80,160}, {96,192}, {112,224}, {127,255} };

const uint16_t NeoPixelManager::COLORS[] = { 10922, 21845, 32768, 43689, 54612, 65535 };


NeoPixelManager::NeoPixelManager(uint8_t pixels, uint8_t pin) {
	neopixel = new Adafruit_NeoPixel(pixels, pin, NEO_GRB+NEO_KHZ800);
	numPixels = pixels;
	brightness = MAX_BRIGHTNESS-1;
	currentEffect = 0;
	active = true;
}

bool NeoPixelManager::isActive() {
	return active;
}

void NeoPixelManager::begin() {
	neopixel->begin();
	neopixel->show();
}

void NeoPixelManager::clear() {
	neopixel->fill();
	neopixel->show();
}

void NeoPixelManager::goEffect(uint8_t effect) {
	if (effect>0 && effect<=N_EFFECTS) {
		currentEffect = effect-1;
		clear();
	}
}

void NeoPixelManager::nextEffect() {
	currentEffect = (currentEffect+1) % N_EFFECTS;
	clear();
}

void NeoPixelManager::prevEffect() {
	currentEffect = (currentEffect-1) % N_EFFECTS;
	clear();
}

void NeoPixelManager::run() {
	if (active) {
		switch (currentEffect) {
		case 0: effect1(); break;
		case 1: effect2(); break;
		case 2: effect3(); break;
		case 3: effect4(); break;
		case 4: effect5(); break;
		case 5: effect6(); break;
		case 6: effect7(); break;
		case 7: effect8(); break;
		default: break;
		}
	}
}

void NeoPixelManager::start() {
	if (!active) active = true;
}

void NeoPixelManager::stop() {
	if (active) {
		active = false;
		clear();
	}
}

void NeoPixelManager::setBrightness(uint8_t level) {
	if (level >= MIN_BRIGHTNESS && level <= MAX_BRIGHTNESS)
		brightness = level-1;
}

uint16_t NeoPixelManager::randomColor() {
	randomSeed(analogRead(RANDOM_SEED_PIN));
	return COLORS[random(N_COLORS)];
}


void NeoPixelManager::effect1() {
	const uint8_t PAUSE = 50;  // pause 50ms
	uint16_t color = randomColor();
	delay(PAUSE);
	for (uint8_t fade=BRIGHTNESS[brightness].min; fade<BRIGHTNESS[brightness].max; fade+=brightness+1) {
		neopixel->fill(neopixel->gamma32(neopixel->ColorHSV(color, MAX_SATURATION, fade)));
		neopixel->show();
		delay(PAUSE);
	}
	for (uint8_t fade=BRIGHTNESS[brightness].max; fade>BRIGHTNESS[brightness].min; fade-=brightness+1) {
		neopixel->fill(neopixel->gamma32(neopixel->ColorHSV(color, MAX_SATURATION, fade)));
		neopixel->show();
		delay(PAUSE);
	}
}

void NeoPixelManager::effect2() {
	const uint8_t PAUSE = 100;  // pause 100ms
	uint16_t color = neopixel->gamma32(neopixel->ColorHSV(randomColor(), MAX_SATURATION, BRIGHTNESS[brightness].max));
	for (uint8_t led=0; led<numPixels; led++) {
		neopixel->setPixelColor(led, color);
		neopixel->show();
		delay(PAUSE);
	}
	color = neopixel->gamma32(neopixel->ColorHSV(randomColor(), MAX_SATURATION, BRIGHTNESS[brightness].max));
	for (uint8_t led=numPixels-1; led>0; led--) {
		neopixel->setPixelColor(led, color);
		neopixel->show();
		delay(PAUSE);
	}
}

void NeoPixelManager::effect3() {
	const uint8_t PAUSE = 100;  // pause 100ms
	uint16_t maxcolor = randomColor();
	uint16_t mincolor = neopixel->gamma32(neopixel->ColorHSV(maxcolor, MAX_SATURATION, BRIGHTNESS[brightness].min));
	maxcolor = neopixel->gamma32(neopixel->ColorHSV(maxcolor, MAX_SATURATION, BRIGHTNESS[brightness].max));
	neopixel->setPixelColor(0, maxcolor);
	neopixel->show();
	delay(PAUSE);
	for (uint8_t led=1; led<numPixels; led++) {
		neopixel->setPixelColor(led-1, mincolor);
		neopixel->setPixelColor(led, maxcolor);
		neopixel->show();
		delay(PAUSE);
	}
	neopixel->setPixelColor(numPixels-1, mincolor);
	neopixel->show();
	delay(PAUSE);
}

void NeoPixelManager::effect4() {
	const uint8_t PAUSE = 100;  // pause 100ms
	uint16_t nocolor = randomColor();
	uint16_t maxcolor = neopixel->gamma32(neopixel->ColorHSV(nocolor, MAX_SATURATION, BRIGHTNESS[brightness].max));
	uint16_t avgcolor = neopixel->gamma32(neopixel->ColorHSV(nocolor, MAX_SATURATION, BRIGHTNESS[brightness].min));
	uint16_t mincolor = neopixel->gamma32(neopixel->ColorHSV(nocolor, MAX_SATURATION, (uint8_t) BRIGHTNESS[brightness].min/2));
	nocolor = neopixel->gamma32(neopixel->ColorHSV(0, 0, 0));
	neopixel->setPixelColor(0, maxcolor); neopixel->show();
	delay(PAUSE);
	neopixel->setPixelColor(0, avgcolor); neopixel->setPixelColor(1, maxcolor); neopixel->show();
	delay(PAUSE);
	neopixel->setPixelColor(0, mincolor); neopixel->setPixelColor(1, avgcolor); neopixel->setPixelColor(2, maxcolor); neopixel->show();
	delay(PAUSE);
	for (uint8_t led=3; led<numPixels; led++) {
		neopixel->setPixelColor(led-3, nocolor);
		neopixel->setPixelColor(led-2, mincolor);
		neopixel->setPixelColor(led-1, avgcolor);
		neopixel->setPixelColor(led, maxcolor);
		neopixel->show();
		delay(PAUSE);
	}
	neopixel->setPixelColor(numPixels-3, nocolor); neopixel->setPixelColor(numPixels-2, mincolor); neopixel->setPixelColor(numPixels-1, avgcolor); neopixel->show();
	delay(PAUSE);
	neopixel->setPixelColor(numPixels-2, nocolor); neopixel->setPixelColor(numPixels-1, mincolor); neopixel->show();
	delay(PAUSE);
	neopixel->setPixelColor(numPixels-1, nocolor); neopixel->show();
	delay(PAUSE);
}

void NeoPixelManager::effect5() {
	const uint8_t PAUSE = 100;  // pause 100ms
	const uint8_t N_LEDS = 4;
	const uint8_t N_GROUPS = (uint8_t) numPixels / N_LEDS;
	uint16_t colors[N_GROUPS];
	for (uint8_t g=0; g<N_GROUPS; g++)
		colors[g] = randomColor();

	for (uint8_t fade=BRIGHTNESS[brightness].min; fade<BRIGHTNESS[brightness].max; fade+=brightness+1) {
		for (uint8_t led=0; led<N_LEDS; led++)
			for (uint8_t group=0; group<N_GROUPS; group++)
				neopixel->setPixelColor(led + (group * N_LEDS), neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, fade)));
		neopixel->show();
		delay(PAUSE);
	}
	for (uint8_t fade=BRIGHTNESS[brightness].max; fade>BRIGHTNESS[brightness].min; fade-=brightness+1) {
		for (uint8_t led=0; led<N_LEDS; led++) {
			for (uint8_t group=0; group<N_GROUPS; group++) {
				neopixel->setPixelColor(led+(group*N_LEDS), neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, fade)));
			}
		}
		neopixel->show();
		delay(PAUSE);
	}
}

void NeoPixelManager::effect6() {
	const uint8_t PAUSE = 100;  // pause 100ms
	const uint8_t N_LEDS = 4;
	const uint8_t N_GROUPS = (uint8_t) numPixels / N_LEDS;
	uint16_t colors[N_GROUPS];
	for (uint8_t g=0; g<N_GROUPS; g++)
		colors[g] = randomColor();

	for (uint8_t group=0; group<N_GROUPS; group++)
		neopixel->setPixelColor(group * N_LEDS, neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, BRIGHTNESS[brightness].max)));
	neopixel->show();
	delay(PAUSE);
	for (uint8_t led=1; led<N_LEDS; led++) {
		for (uint8_t group=0; group<N_GROUPS; group++) {
			neopixel->setPixelColor(led + (group * N_LEDS) - 1, neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, BRIGHTNESS[brightness].min)));
			neopixel->setPixelColor(led + (group * N_LEDS), neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, BRIGHTNESS[brightness].max)));
		}
		neopixel->show();
		delay(PAUSE);
	}
	for (uint8_t group=0; group<N_GROUPS; group++)
		neopixel->setPixelColor(N_LEDS + (group * N_LEDS) - 1, neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, BRIGHTNESS[brightness].min)));
}

void NeoPixelManager::effect7() {
	const uint8_t PAUSE = 100; // pause 100ms
	const uint8_t N_LEDS = 4;
	const uint8_t N_GROUPS = (uint8_t) numPixels / N_LEDS;
	uint16_t colors[N_GROUPS];
	for (uint8_t g=0; g<N_GROUPS; g++)
		colors[g] = randomColor();

	for (uint8_t group=0; group<N_GROUPS; group++) {
		neopixel->setPixelColor(group * N_LEDS, neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, BRIGHTNESS[brightness].max)));
	}
	neopixel->show();
	delay(PAUSE);
	for (uint8_t led=1; led<N_LEDS; led++) {
		for (uint8_t group=0; group<N_GROUPS; group++) {
			neopixel->setPixelColor(led + (group * N_LEDS) - 1, neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, BRIGHTNESS[brightness].min)));
			neopixel->setPixelColor(led + (group * N_LEDS), neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, BRIGHTNESS[brightness].max)));
		}
		neopixel->show();
		delay(PAUSE);
	}
	for (uint8_t led=N_LEDS-1; led>0; led--) {
		for (uint8_t group=0; group<N_GROUPS; group++) {
			neopixel->setPixelColor(led + (group * N_LEDS), neopixel->gamma32(neopixel->ColorHSV(0, 0, 0)));
			neopixel->setPixelColor(led + (group * N_LEDS) - 1, neopixel->gamma32(neopixel->ColorHSV(colors[group], MAX_SATURATION, BRIGHTNESS[brightness].max)));
		}
		neopixel->show();
		delay(PAUSE);
	}
}

void NeoPixelManager::effect8() {
	const uint8_t PAUSE = 100; // pause 100ms
	const uint8_t MID_LED = (uint8_t) numPixels / 2;
	uint16_t maincolor = neopixel->gamma32(neopixel->ColorHSV(randomColor(), MAX_SATURATION, BRIGHTNESS[brightness].max));
	uint16_t altcolor = neopixel->gamma32(neopixel->ColorHSV(randomColor(), MAX_SATURATION, BRIGHTNESS[brightness].max));

	neopixel->fill(maincolor);
	neopixel->show();
	delay(PAUSE);
	neopixel->setPixelColor(0, altcolor);
	neopixel->show();
	delay(PAUSE);
	for (uint8_t incr=1, decr=numPixels-1; incr<MID_LED && decr>MID_LED; incr++, decr--) {
		neopixel->setPixelColor(incr, altcolor);
		neopixel->setPixelColor(decr, altcolor);
		neopixel->show();
		delay(PAUSE);
	}
	neopixel->setPixelColor(MID_LED, altcolor);
	neopixel->show();
	delay(PAUSE);
	neopixel->setPixelColor(MID_LED, maincolor);
	neopixel->show();
	delay(PAUSE);
	for (uint8_t incr=MID_LED+1, decr=MID_LED-1; incr<numPixels && decr>=0; incr++, decr--) {
		neopixel->setPixelColor(incr, maincolor);
		neopixel->setPixelColor(decr, maincolor);
		neopixel->show();
		delay(PAUSE);
	}
	neopixel->setPixelColor(0, maincolor);
	neopixel->show();
	delay(PAUSE);
}

void NeoPixelManager::colorTest() {
	const uint16_t PAUSE = 2000;
	for (uint8_t index=0; index<N_COLORS; index++) {
		neopixel->fill(neopixel->gamma32(neopixel->ColorHSV(COLORS[index], MAX_SATURATION, BRIGHTNESS[brightness].max)));
		neopixel->show();
		delay(PAUSE);
		clear();
	}
}
