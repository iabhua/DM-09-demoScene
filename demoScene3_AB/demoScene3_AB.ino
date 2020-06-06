/*
 DEMO: demoScene

 TEAM a.r.g.: http://www.team-arg.com

 2015 - JO3RI

 Game License: MIT : https://opensource.org/licenses/MIT

 */

//determine the game

#include <SPI.h>
#include "Arglib.h"
#include "menu_bitmaps.h"
#include "font.h"
#include "ATMlib.h"

SQUAWK_CONSTRUCT_ISR(SQUAWK_PWM_PIN5)

extern Melody TEAMargSong[];

byte rotatingFrame[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

byte stillStar[11][2] = {{84, 9}, {67, 14}, {109, 19}, {27, 24}, {9, 29}, {96, 34}, {31, 39}, {45, 44}, {82, 49}, {19, 54}, {57, 59}};
byte movingStar[11][2] = {{16, 5}, {125, 10}, {62, 15}, {79, 20}, {115, 25}, {104, 30}, {16, 35}, {117, 40}, {65, 45}, {98, 50}, {23, 55}};
byte fastMovingStar[11][2] = {{84, 7}, {67, 12}, {109, 17}, {27, 22}, {9, 27}, {96, 32}, {31, 37}, {45, 42}, {82, 47}, {19, 52}, {57, 57}};
const unsigned char PROGMEM demoText[] = "Once again, this is TEAM a.r.g.         for this demo we bring you a Zelda tune ! Only greetings too Finefin for this demo :)        and to all you people listening !           ";
int scrolling = 128;
int timeDemo;



Arduboy arduboy;

extern Melody TEAMargSong[];

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(60);
  arduboy.drawCompressed(0, 0, TEAMarg, WHITE);
  arduboy.display();
  delay(3000);
  Squawk.begin(32000);
  // Begin playback of melody.
  Squawk.play(TEAMargSong);
  // Tune the song to something more suitable for a piezo
  Squawk.tune(2.0);
  // Lower the tempo ever so slightly
  Squawk.tempo(50);
  timeDemo = sizeof(demoText);
}

void loop() {
  
  while (scrolling > -(timeDemo*13))
  {
    if (!(arduboy.nextFrame())) return;
    arduboy.clearDisplay();
    drawStarField();
    drawSwirl();
    drawScrollingText();
    arduboy.display();
  }
  
  if (!(arduboy.nextFrame())) return;
  arduboy.clearDisplay();
  drawGoPlay();
  arduboy.display();
}

void drawSwirl()
{
  if (arduboy.everyXFrames(3)) {
    for (byte x; x < 16; x++)
    {
      rotatingFrame[x]++;
    }
  }
  for (byte x; x < 16; x++)
  {
    if (rotatingFrame[x] > 20) rotatingFrame[x] = 0;
    arduboy.drawSprite(8 * x, 48, reverseRotating_bitmaps, 8, 16, rotatingFrame[x], WHITE);
  }
}

void drawStarField()
{
  for (byte i = 0; i < 11; i++)
  {
    if (arduboy.everyXFrames(2))
    {
      fastMovingStar[i][0]--;
      if (fastMovingStar[i][0] < 1) fastMovingStar[i][0] = 127;

    }

    if (arduboy.everyXFrames(3))
    {
      movingStar[i][0]--;
      if (movingStar[i][0] < 1) movingStar[i][0] = 127;

    }
    if (arduboy.everyXFrames(4))
    {
      stillStar[i][0]--;
      if (stillStar[i][0] < 1) stillStar[i][0] = 127;

    }
    arduboy.drawPixel(movingStar[i][0], movingStar[i][1], WHITE);
    arduboy.drawPixel(fastMovingStar[i][0], fastMovingStar[i][1], WHITE);
    arduboy.drawPixel(stillStar[i][0], stillStar[i][1], WHITE);
  }
}

void drawScrollingText()
{
  if (arduboy.everyXFrames(1)) scrolling--;
  for (int textX = 0; textX < sizeof(demoText) - 1; textX++)
  {
    if ((scrolling + 13 * textX < 128) && (scrolling + 13 * textX > -32))
    {
      arduboy.drawSprite(scrolling + 13 * textX, 20, font_bitmaps, 22, 24, pgm_read_byte(&demoText[textX]) - 32, WHITE);
    }
  }
}

void drawGoPlay()
{
  arduboy.drawCompressed(0, 0, TEAMarg2, WHITE);
}

Melody TEAMargSong[] = {
    0x41, 0x03, 0x00, 0x01, 0x02, 0xEA, 0x04, 0x01, 0x0F, 0x06, 0x00, 0x9F, 0x7F, 0xA6, 0x0A, 0x04,
  0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xA6, 0x7F,
  0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0x7F, 0x9F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00,
  0x00, 0xAB, 0x9F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00,
  0x0A, 0x05, 0x00, 0x9F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA,
  0x04, 0x05, 0x00, 0x00, 0x00, 0xAB, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F,
  0x9F, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0x9F, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00,
  0x7F, 0x9F, 0xA1, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xAB, 0x9F, 0xA2, 0xAA, 0x04, 0x05, 0x0A,
  0x05, 0x00, 0x7F, 0xA1, 0xA4, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x9D, 0xA2, 0xA6, 0xAA, 0x04,
  0x05, 0x00, 0x00, 0x00, 0x7F, 0xA4, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0xA9, 0xAB, 0x7F,
  0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F,
  0xAB, 0x7F, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0x7F, 0xAD, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00,
  0x00, 0xA9, 0xAE, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xB0, 0x7F, 0x0A, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x9D, 0xB2, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA,
  0x04, 0x05, 0x00, 0x00, 0x00, 0xA9, 0x7F, 0xA6, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F,
  0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xA6, 0xA6, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00,
  0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0xA9, 0xA6, 0xA7, 0xAA, 0x04, 0x05, 0x0A,
  0x05, 0x00, 0x7F, 0x7F, 0xA9, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x9B, 0xA7, 0xAB, 0xAA, 0x04,
  0x05, 0x00, 0x00, 0x00, 0x7F, 0xA9, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA7, 0xAB, 0x7F,
  0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F,
  0xAB, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xAE, 0x7F, 0xAA, 0x04, 0x05, 0x0A, 0x05,
  0x00, 0xA7, 0xB0, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xB3, 0x7F, 0x0A, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x9B, 0xB7, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA,
  0x04, 0x05, 0x00, 0x00, 0x00, 0xA7, 0x7F, 0xAB, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F,
  0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xAB, 0xAB, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00,
  0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0xA7, 0xAB, 0xA9, 0xAA, 0x04, 0x05, 0x0A,
  0x05, 0x00, 0x7F, 0x7F, 0xA7, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0xA2, 0xA9, 0xA9, 0xAA, 0x04,
  0x05, 0x00, 0x00, 0x00, 0x7F, 0xA7, 0x7F, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0xAE, 0xA9, 0x7F,
  0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0xA7, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F,
  0x7F, 0xA6, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA7, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00,
  0x00, 0xAE, 0xAE, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xB0, 0x7F, 0x0A, 0x04, 0x00,
  0x00, 0x00, 0x00, 0xA2, 0xB2, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x0A,
  0x04, 0x00, 0x0A, 0x05, 0x00, 0xAE, 0xAE, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F,
  0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xA9, 0xA6, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00,
  0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xAE, 0xA6, 0x7F, 0x0A, 0x04, 0x00, 0x0A,
  0x05, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x7F, 0xA4, 0xAA, 0x04,
  0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0xAC, 0xA4, 0x7F,
  0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0xA6, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F,
  0x7F, 0xA7, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA6, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00,
  0x00, 0xAC, 0xA4, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA6, 0x7F, 0x0A, 0x04, 0x00,
  0x00, 0x00, 0x00, 0xA0, 0xA7, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA,
  0x04, 0x05, 0x0A, 0x05, 0x00, 0xAC, 0xA4, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA6,
  0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xA7, 0xA6, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00,
  0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xAC, 0xA6, 0xA4, 0xAA, 0x04, 0x05, 0x0A,
  0x05, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x9F, 0xA4, 0xA2, 0xAA, 0x04,
  0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0xAB, 0xA2, 0x7F,
  0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0xA4, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F,
  0x7F, 0xA6, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA4, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00,
  0x00, 0xAB, 0xA2, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA4, 0x7F, 0x0A, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x9F, 0xA6, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA,
  0x04, 0x05, 0x0A, 0x05, 0x00, 0xAB, 0xA2, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA4,
  0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xA6, 0xA4, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00,
  0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xA4, 0xA2, 0xAA, 0x04, 0x05, 0x0A,
  0x05, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA1, 0xA2, 0xA1, 0xAA, 0x04,
  0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0xAD, 0xA1, 0x7F,
  0x0A, 0x04, 0x00, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0xA4, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F,
  0x7F, 0xA5, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA4, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00,
  0x00, 0xAD, 0xA2, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA4, 0x7F, 0x0A, 0x04, 0x00,
  0x00, 0x00, 0x00, 0xA1, 0xA5, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA,
  0x04, 0x05, 0x0A, 0x05, 0x00, 0xAD, 0xA1, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0x7F, 0xA3,
  0x7F, 0xAC, 0x14, 0x05, 0x00, 0x00, 0x00, 0xB7, 0xA4, 0xA8, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00,
  0x7F, 0xA5, 0x7F, 0xAA, 0x04, 0x05, 0x00, 0x00, 0x00, 0xAD, 0xA6, 0x7F, 0xAA, 0x04, 0x05, 0x0A,
  0x05, 0x00, 0x7F, 0xA8, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xAD, 0xA6, 0xA6, 0xAA, 0x04,
  0x05, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0x7F, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xB0, 0xAB, 0xA4,
  0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xB0, 0xAB, 0xA4, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xB0,
  0xAB, 0xA4, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA, 0x04, 0x05, 0x0A, 0x05,
  0x00, 0xB0, 0xAB, 0xA4, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xB0, 0xAB, 0xA4, 0x0A, 0x04, 0x00,
  0x00, 0x00, 0x00, 0xB0, 0xAB, 0xA4, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0x7F, 0x0A,
  0x04, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x7F,
  0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00,
  0x00, 0x00, 0xA1, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA6, 0x7F, 0x7F, 0x0A, 0x04,
  0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xB0, 0xAA, 0xA4,
  0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xB0, 0xAA, 0xA4, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xB0,
  0xAA, 0xA4, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0xAA, 0x04, 0x05, 0x0A, 0x05,
  0x00, 0xB0, 0xAA, 0xA4, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0xB0, 0xAA, 0xA4, 0x0A, 0x04, 0x00,
  0x00, 0x00, 0x00, 0xB0, 0xAA, 0xA4, 0xAA, 0x04, 0x05, 0x0A, 0x05, 0x00, 0x7F, 0x7F, 0x7F, 0x0A,
  0x04, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x7F,
  0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00,
  0xA2, 0x7F, 0x7F, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0xA3, 0x7F, 0x7F, 0xDA, 0x04, 0x00, 0x00,
  0x00, 0x00, 0xA4, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
  0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x7F, 0x7F,
};
