# Seg16

**Seg16** is a simple Arduino library for driving 16-segment displays with a HT16K33.

## Usage

```.cpp
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
```

See the [examples directory](/examples) for full working code examples.

## Methods

```.cpp
// Seg16 class, use to instantiate a new HT16K33.
Seg16(uint8_t nDisplays = 1, uint8_t address = 0x70);

// Starts the HT16K33 with sensible defaults. Call once in setup().
void init();

// Low-level calls, might be useful for energy-saving / power-down.
void setOscillatorOn(bool on);
void setDisplayOn(bool on);

// Change the brightness. Expects an int from 0 to 15.
// Duty cycle = (brightness + 1) / 16, so brightness = 0 is still on.
// To shut the display off, use setDisplayOn(false).
void setBrightness(uint8_t brightness);

// 0: blink off.
// 1: blink at 2HZ.
// 2: blink at 1HZ.
// 3: blink at 0.5HZ.
void setBlinkMode(uint8_t mode);

// Static helper methods; return characters to use with write() or writeStream().
static uint16_t getCharacter(uint8_t index);  // Index range [0 - 61], returns characters in the order decimal, upper, lower.
static uint16_t getDecimal(uint8_t index);  // Index range [0 - 9], returns that number as a decimal character.
static uint16_t getHex(uint8_t index);  // Index range [0 - 15], returns that number as a hexidecimal character.
static uint16_t getUpper(uint8_t index);  // Index range [0 - 25], returns that number as an uppercase letter.
static uint16_t getLower(uint8_t index);  // Index range [0 - 25], returns that number as an lowercase letter.

// Write a character to a specific display 0-7.
void write(uint16_t character, uint8_t displayIndex = 0);

// Write to several displays in the same transmission. For instance, if three displays are hooked up, calling:
//     for (int i = 0; i < 3; ++i) writeStream(Seg16::getUpper(0));
// will write the letter “A” to each of them.
// startIndex and endIndex can be specified for partial updates.
uint8_t writeStream(uint16_t character, uint8_t startIndex = 0);
uint8_t writeStream(uint16_t character, uint8_t startIndex, uint8_t endIndex);
```

## Hardware

Note: for the font to render as expected, hook displays up like this:

```
     2   0
   +---+---+
   |\  |  /|
 5 | 4 3 1 | C
   |  \|/  |
   +-6-+-D-+
   |  /|\  |
 9 | 8 7 F | E
   |/  |  \|
   +---+---+
     A   B
```

## Similar libraries

- https://github.com/adafruit/Adafruit_LED_Backpack
- https://github.com/jonpearse/ht16k33-arduino

## License

[GNU GPLv3](LICENSE.md)
