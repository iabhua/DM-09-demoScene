#ifndef Arduboy_h
#define Arduboy_h

#include <SPI.h>
#include <Print.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <limits.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

#define DEVKIT

#define AVAILABLE_TIMERS 2
#define TUNE_OP_PLAYNOTE  0x90  /* play a note: low nibble is generator #, note is next byte */
#define TUNE_OP_STOPNOTE  0x80  /* stop a note: low nibble is generator # */
#define TUNE_OP_RESTART 0xe0  /* restart the score from the beginning */
#define TUNE_OP_STOP  0xf0  /* stop playing */

// EEPROM settings

#define EEPROM_VERSION 0
#define EEPROM_BRIGHTNESS 1
#define EEPROM_AUDIO_ON_OFF 2
// we reserve the first 16 byte of EEPROM for system use
#define EEPROM_STORAGE_SPACE_START 16 // and onward

// eeprom settings above are needed for audio

#define PIXEL_SAFE_MODE
#define SAFE_MODE

#define CS 6
#define DC 4
#define RST 12

// compare Vcc to 1.1 bandgap
#define ADC_VOLTAGE _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1)
// compare temperature to 2.5 internal reference
// also _BV(MUX5)
#define ADC_TEMP _BV(REFS0) | _BV(REFS1) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0)

#define LEFT_BUTTON _BV(5)
#define RIGHT_BUTTON _BV(6)
#define UP_BUTTON _BV(7)
#define DOWN_BUTTON _BV(4)
#define A_BUTTON _BV(3)
#define B_BUTTON _BV(2)

#define PIN_LEFT_BUTTON A2
#define PIN_RIGHT_BUTTON A1
#define PIN_UP_BUTTON A0
#define PIN_DOWN_BUTTON A3
#define PIN_A_BUTTON 7
#define PIN_B_BUTTON 8

#define PIN_SPEAKER_1 5
#define PIN_SPEAKER_2 13

#define WIDTH 128
#define HEIGHT 64

#define WHITE 1
#define BLACK 0

#define COLUMN_ADDRESS_END (WIDTH - 1) & 0x7F
#define PAGE_ADDRESS_END ((HEIGHT/8)-1) & 0x07

#define SPRITE_MASKED 1
#define SPRITE_UNMASKED 2
#define SPRITE_OVERWRITE 2
// PLUS_MASK means that the mask data is included in the bitmap itself
// 1st byte image, 2nd byte mask, 3rd byte image, 4th byte mask, etc.
// The 2nd byte ask provides the masking data for the 1st byte of
// image data.
#define SPRITE_PLUS_MASK 3
#define SPRITE_IS_MASK 250
#define SPRITE_IS_MASK_ERASE 251
// will select SPRITE_MASKED or SPRITE_UNMASKED depending on the presence
// of mask (if one was passed to the draw function)
#define SPRITE_AUTO_MODE 255

class ArduboyAudio
{
public:
  void setup();
  void on();
  void off();
  void save_on_off();
  bool enabled();
  void tone(uint8_t channel, unsigned int frequency, unsigned long duration);

protected:
  bool audio_enabled = false;
};


class ArduboyTunes
{
public:
  // Playtune Functions
  void initChannel(byte pin);     // assign a timer to an output pin
  void playScore(const byte *score);  // start playing a polyphonic score
  void stopScore();     // stop playing the score
  void delay(unsigned msec);    // delay in milliseconds
  void closeChannels();     // stop all timers
  bool playing();

    void tone(unsigned int frequency, unsigned long duration);

  // called via interrupt
  void static step();
  void static soundOutput();


private:
  void static playNote (byte chan, byte note);
  void static stopNote (byte chan);
};


class Arduboy : public Print
{
public:
  Arduboy();
  void LCDDataMode();
  void LCDCommandMode();

  uint8_t getInput();
  boolean pressed(uint8_t buttons);
  boolean not_pressed(uint8_t buttons);
  void start();
  void saveMuchPower();
  void idle();
  void blank();
  void clearDisplay();
  void display();
  void drawScreen(const unsigned char *image);
  void drawScreen(unsigned char image[]);
  void drawPixel(int x, int y, uint8_t color);
  uint8_t getPixel(uint8_t x, uint8_t y);
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
  void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t color);
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
  void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint8_t color);
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
  void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
  void fillScreen(uint8_t color);
  void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint8_t color);
  void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint8_t color);
  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);
  void fillTriangle (int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);
  void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint8_t color);
  void drawCompressed(int16_t sx, int16_t sy, const uint8_t *bitmap, uint8_t color);
  void drawSprite(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint8_t frame, uint8_t color);
  void drawMaskedSprite(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, const uint8_t *mask, uint8_t frame, uint8_t color);
  void drawSlowXYBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint8_t color);
  void drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size);
  void setCursor(int16_t x, int16_t y);
  void setTextSize(uint8_t s);
  void setTextWrap(boolean w);
  unsigned char* getBuffer();
  uint8_t width();
  uint8_t height();
  virtual size_t write(uint8_t);
  void initRandomSeed();
  void swap(int16_t& a, int16_t& b);

  ArduboyTunes tunes;
  ArduboyAudio audio;

  void setFrameRate(uint8_t rate);
  bool nextFrame();
  bool everyXFrames(uint8_t frames);
  int cpuLoad();
  uint8_t frameRate = 60;
  uint16_t frameCount = 0;
  uint8_t eachFrameMillis = 1000/60;
  long lastFrameStart = 0;
  long nextFrameStart = 0;
  bool post_render = false;
  uint8_t lastFrameDurationMs = 0;

private:
  unsigned char sBuffer[(HEIGHT*WIDTH)/8];

  void bootLCD() __attribute__((always_inline));
  void safeMode() __attribute__((always_inline));
  void slowCPU() __attribute__((always_inline));
  uint8_t readCapacitivePin(int pinToMeasure);
  uint8_t readCapXtal(int pinToMeasure);
  uint16_t rawADC(byte adc_bits);
  volatile uint8_t *mosiport, *clkport, *csport, *dcport;
  uint8_t mosipinmask, clkpinmask, cspinmask, dcpinmask;

// Adafruit stuff
protected:
  int16_t cursor_x = 0;
  int16_t cursor_y = 0;
  uint8_t textsize = 1;
  boolean wrap; // If set, 'wrap' text at right edge of display
};


class SimpleButtons
{
public:
  SimpleButtons(Arduboy &arduboy);

  /// Poll the hardware buttons and tracks state over time
  /**
  This must be called before any of the other button member functions.  It should be called either in your main `loop()` or as part of the frame system (called pre-frame).
  */
  void poll();
  boolean pressed(uint8_t buttons);
  boolean notPressed(uint8_t buttons);
  boolean justPressed(uint8_t button);

private:
  uint8_t currentButtonState = 0;
  uint8_t previousButtonState = 0;

  Arduboy *arduboy;
};

/// base struct other Sprites inherit from
struct SimpleSprite
{
  SimpleSprite(int x, int y, const uint8_t *bitmap);
  int x, y;
  const uint8_t *bitmap;
  uint8_t frame = 0;
  uint8_t drawMode = SPRITE_AUTO_MODE;
};

struct Sprite : public SimpleSprite
{
  Sprite(int x, int y, const uint8_t *bitmap);
  Sprite(int x, int y, const uint8_t *bitmap, const uint8_t *mask);
  const uint8_t *mask;
  uint8_t maskFrame = 0;
};

class Sprites
{
public:
  Sprites(Arduboy &arduboy);

  void draw(Sprite sprite);
  void draw(SimpleSprite sprite);
  void draw(int16_t x, int16_t y, const uint8_t *bitmap);
  void draw(int16_t x, int16_t y, const uint8_t *bitmap, const uint8_t *mask);
  void draw(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);

  // drawExternalMask() uses a separate mask to mask image (MASKED)
  //
  // image  mask   before  after
  //  
  // .....  .OOO.  .....   ..... 
  // ..O..  OOOOO  .....   ..O..
  // OO.OO  OO.OO  .....   OO.OO
  // ..O..  OOOOO  .....   ..O..
  // .....  .OOO.  .....   .....
  //  
  // image  mask   before  after
  //   
  // .....  .OOO.  OOOOO   O...O
  // ..O..  OOOOO  OOOOO   ..O..
  // OO.OO  OOOOO  OOOOO   OO.OO
  // ..O..  OOOOO  OOOOO   ..O..
  // .....  .OOO.  OOOOO   O...O
  //
  void drawExternalMask(int16_t x, int16_t y, const uint8_t *bitmap, 
    const uint8_t *mask, uint8_t frame, uint8_t mask_frame); 

  // drawPlusMask has the same behavior as drawExternalMask except the
  // data is arranged in byte tuples interposing the mask right along
  // with the image data (SPRITE_PLUS_MASK)
  //
  // typical image data (8 bytes): 
  // [I][I][I][I][I][I][I][I]
  //
  // interposed image/mask data (8 byes):
  // [I][M][I][M][I][M][I][M]
  //
  // The byte order does not change, just for every image byte you mix
  // in it's matching mask byte.  Softare tools make easy work of this.
  // 
  // See: https://github.com/yyyc514/img2ard
  void drawPlusMask(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);

  // drawOverwrite() replaces the existing content completely (UNMASKED)
  //
  // image  before  after
  //
  // .....  .....   ..... 
  // ..O..  .....   ..O..
  // OO.OO  .....   OO.OO
  // ..O..  .....   ..O..
  // .....  .....   .....
  //
  // image  before  after
  //
  // .....  OOOOO   ..... 
  // ..O..  OOOOO   ..O..
  // OO.OO  OOOOO   OO.OO
  // ..O..  OOOOO   ..O..
  // .....  OOOOO   .....
  //
  void drawOverwrite(int16_t x, int16_t y, 
    const uint8_t *bitmap, uint8_t frame); 

  // drawErase() removes the lit pixels in the image from the display
  // (SPRITE_IS_MASK_ERASE)
  //
  // image  before  after
  //
  // .....  .....   ..... 
  // ..O..  .....   .....
  // OO.OO  .....   .....
  // ..O..  .....   .....
  // .....  .....   .....
  //
  // image  before  after
  //
  // .....  OOOOO   OOOOO 
  // ..O..  OOOOO   OO.OO
  // OO.OO  OOOOO   ..O..
  // ..O..  OOOOO   OO.OO
  // .....  OOOOO   OOOOO
  //

  void drawErase(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame); 

  // drawSelfMasked() only draws lit pixels, black pixels in
  // your image are treated as "transparent" (SPRITE_IS_MASK)
  //
  // image  before  after
  //
  // .....  .....   ..... 
  // ..O..  .....   ..O..
  // OO.OO  .....   OO.OO
  // ..O..  .....   ..O..
  // .....  .....   .....
  //
  // image  before  after
  //
  // .....  OOOOO   OOOOO  (no change because all pixels were
  // ..O..  OOOOO   OOOOO  already white)
  // OO.OO  OOOOO   OOOOO
  // ..O..  OOOOO   OOOOO
  // .....  OOOOO   OOOOO
  //
  void drawSelfMasked(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame); 

  // master function, needs to be abstracted into sep function for 
  // every render type
  void draw(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame,
    const uint8_t *mask, uint8_t sprite_frame, uint8_t drawMode);
  
  void drawBitmap(int16_t x, int16_t y,
    const uint8_t *bitmap, const uint8_t *mask,
    int8_t w, int8_t h, uint8_t draw_mode);

private:

  Arduboy *arduboy;
  unsigned char *sBuffer;
};


#endif
