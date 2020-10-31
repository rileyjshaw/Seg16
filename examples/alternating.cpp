// Alternating display updates.
//
// This sketch alternates updating the first display with uppercase letters A-Z,
// and the second display with digits 0-9.
//
// Hardware setup: attach two 16-segment displays to a HT16K33 at address 0x70.
#include "Seg16.h"

Seg16 segments(2, 0x70);

enum Letters {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
enum Displays {LEFT, RIGHT};

void setup() {
	segments.init();
	segments.setBrightness(15);  // Max brightness.
	segments.writeStream(Seg16::getUpper(H));
	segments.writeStream(Seg16::getLower(I));
	delay(2000);
}

uint16_t i = 0;
void loop() {
	uint8_t display = i % 2;
	if (display == 0) {
		// Update the first display on even numbers.
		segments.write(Seg16::getUpper((i / 2) % 26), display);
	} else {
		// Update the second display on odd numbers.
		segments.write(Seg16::getDecimal((i / 2) % 10), display);
	}
	++i;
	delay(1000);
}
