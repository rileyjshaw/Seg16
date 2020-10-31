#include "Arduino.h"
#include "Seg16.h"

static const uint16_t characters[] PROGMEM = {
  0b0101111100100111, // 0
  0b0101000000000010, // 1
  0b0011111001000101, // 2
  0b0111110000000101, // 3
  0b0111000001100000, // 4
  0b0110110001100101, // 5
  0b0110111001100101, // 6
  0b0101000000000101, // 7
  0b0111111001100101, // 8
  0b0111110001100101, // 9
  0b0111001001100101, // A
  0b0111110010001101, // B
  0b0000111000100101, // C
  0b0101110010001101, // D
  0b0000111001100101, // E
  0b0000001001100101, // F
  0b0110111000100101, // G
  0b0111001001100000, // H
  0b0000110010001101, // I
  0b0101111000000000, // J
  0b1000001001100010, // K
  0b0000111000100000, // L
  0b0101001000110010, // M
  0b1101001000110000, // N
  0b0101111000100101, // O
  0b0011001001100101, // P
  0b1101111000100101, // Q
  0b1011001001100101, // R
  0b1000110001100101, // S
  0b0000000010001101, // T
  0b0101111000100000, // U
  0b0000001100100010, // V
  0b1101001100100000, // W
  0b1000000100010010, // X
  0b0111110001100000, // Y
  0b0000110100000111, // Z
  0b0000111011000000, // a
  0b0000011011100000, // b
  0b0000011001000000, // c
  0b0111100010000000, // d
  0b0000011101000000, // e
  0b0010000011001001, // f
  0b0000010011101100, // g
  0b0000001011100000, // h
  0b0000000010000000, // i
  0b0000011010001000, // j
  0b1000000010001010, // k
  0b0000001000100000, // l
  0b0110001011000000, // m
  0b0000001011000000, // n
  0b0000011011000000, // o
  0b0000001001101100, // p
  0b0000000011101100, // q
  0b0000001001000000, // r
  0b0000010011100100, // s
  0b0000011001100000, // t
  0b0000011010000000, // u
  0b0000001100000000, // v
  0b1100001100000000, // w
  0b1000000100010010, // x
  0b0111100000001000, // y
  0b0000010101000000, // z
};


void Seg16::_writeCommand(uint8_t command) {
  Wire.beginTransmission(_address);
  Wire.write(command);
  Wire.endTransmission();
}

static uint16_t Seg16::getCharacter(uint8_t index) {
  return pgm_read_word(characters + min(index, 61));
}

static uint16_t Seg16::getDecimal(uint8_t index) {
  return pgm_read_word(characters + min(index, 9));
}

static uint16_t Seg16::getHex(uint8_t index) {
  return pgm_read_word(characters + min(index, 15));
}

static uint16_t Seg16::getUpper(uint8_t index) {
  return pgm_read_word(characters + min(10 + index, 35));
}

static uint16_t Seg16::getLower(uint8_t index) {
  return pgm_read_word(characters + min(36 + index, 61));
}

void Seg16::setOscillatorOn(bool on) {
  _writeCommand(on ? HT16K33_OSCILLATOR_ON : HT16K33_OSCILLATOR_STANDBY);
}

void Seg16::setDisplayOn(bool on) {
  _writeCommand(on ? HT16K33_DISPLAY_ON : HT16K33_DISPLAY_OFF);
}

// Duty cycle = (brightness + 1) / 16, so brightness = 0 is still on.
void Seg16::setBrightness(uint8_t brightness) {
  _writeCommand(HT16K33_BRIGHTNESS | (brightness & 0xF));
}

// [OFF, 2HZ, 1HZ, 0.5HZ]
void Seg16::setBlinkMode(uint8_t mode) {
  _writeCommand(HT16K33_DISPLAY_ON | (min(mode, 3) << 1));
}

// Write a character to a specific display 0-7.
void Seg16::write(uint16_t character, uint8_t displayIndex) {
  writeStream(character, displayIndex, displayIndex);
}

// Write to several displays in the same transmission.
uint8_t Seg16::writeStream(uint16_t character, uint8_t startIndex) {
  return writeStream(character, startIndex, _nDisplays);
}
uint8_t Seg16::writeStream(uint16_t character, uint8_t startIndex, uint8_t endIndex) {
  if (_streamIndex == 0) {
    _streamIndex = startIndex;
    Wire.beginTransmission(_address);
    Wire.write(startIndex * 2);
  }
  Wire.write(character & 0xFF);
  Wire.write(character >> 8);
  if (++_streamIndex >= endIndex) {
    Wire.endTransmission();
    _streamIndex = 0;
  }
  return _streamIndex;
}

Seg16::Seg16(uint8_t nDisplays, uint8_t address) {
  _address = address;
  _nDisplays = nDisplays;
  _streamIndex = 0;
}

void Seg16::init() {
  Wire.begin();
  setOscillatorOn();
  while(writeStream(0x0000)) {};
  setBlinkMode(0);
  setBrightness(0);
  setDisplayOn();
}
