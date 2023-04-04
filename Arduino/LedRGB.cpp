#include "LedRGB.h"

LedRGB::LedRGB(const int pin_r, const int pin_g, const int pin_b)
	: pin_r_(pin_r), pin_g_(pin_g), pin_b_(pin_b) {
	pinMode(pin_r_, OUTPUT);
	pinMode(pin_g_, OUTPUT);
	pinMode(pin_g_, OUTPUT);
}

void LedRGB::PaintRed() {
	Update(HIGH, LOW, LOW);
}

void LedRGB::PaintGreen() {
	Update(LOW, HIGH, LOW);
}

void LedRGB::PaintBlue() {
	Update(LOW, LOW, HIGH);
}

void LedRGB::NoColor() {
	Update(LOW, LOW, LOW);
}

void LedRGB::Update(const uint8_t red, const uint8_t green, const uint8_t blue) {
	digitalWrite(pin_r_, red);
	digitalWrite(pin_g_, green);
	digitalWrite(pin_b_, blue);
}
