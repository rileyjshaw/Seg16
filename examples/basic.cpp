// Basic hello world.
//
// This sketch displays the word "Hi" across two 16-segment displays.
//
// Hardware setup: attach two 16-segment displays to a HT16K33 at address 0x70.
#include "Seg16.h"

Seg16 segments(2, 0x70);

enum Letters {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};

void setup() {
	segments.init();
	segments.writeStream(Seg16::getUpper(H));
	segments.writeStream(Seg16::getLower(I));
}

void loop() {
}
