// For use with 16-segment displays driven by a HT16K33.
//
// Expected connections for font:
//
//     2   0
//   +---+---+
//   |\  |  /|
// 5 | 4 3 1 | C
//   |  \|/  |
//   +-6-+-D-+
//   |  /|\  |
// 9 | 8 7 F | E
//   |/  |  \|
//   +---+---+
//     A   B
//
// Swap it with:
// https://gist.github.com/rileyjshaw/d4fb76d52141b1adaa5850931ce18df5
//
// Other libraries:
// https://github.com/adafruit/Adafruit_LED_Backpack
// https://github.com/jonpearse/ht16k33-arduino

#ifndef Seg16_h
#define Seg16_h

#include "Arduino.h"
#include <Wire.h>
#include <avr/pgmspace.h>

// Commands from datasheet.
#define HT16K33_OSCILLATOR_ON       0x21
#define HT16K33_OSCILLATOR_STANDBY  0x20
#define HT16K33_DISPLAY_ON          0x81
#define HT16K33_DISPLAY_OFF         0x80
#define HT16K33_BRIGHTNESS          0xE0

class Seg16 {
  public:
    Seg16(uint8_t nDisplays = 1, uint8_t address = 0x70);
    void init();
    void setOscillatorOn(bool on = true);
    void setDisplayOn(bool on = true);
    void setBrightness(uint8_t brightness);
    void setBlinkMode(uint8_t mode);
    static uint16_t getCharacter(uint8_t index);
    static uint16_t getDecimal(uint8_t index);
    static uint16_t getHex(uint8_t index);
    static uint16_t getUpper(uint8_t index);
    static uint16_t getLower(uint8_t index);
    void write(uint16_t character, uint8_t displayIndex = 0);
    uint8_t writeStream(uint16_t character, uint8_t startIndex = 0);
    uint8_t writeStream(uint16_t character, uint8_t startIndex, uint8_t endIndex);

  private:
    uint8_t _address;
    uint8_t _nDisplays = 8;
    uint8_t _streamIndex;
    void _writeCommand(uint8_t command);
};

#endif
