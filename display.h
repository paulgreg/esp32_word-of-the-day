#include "Fonts/Cantarell_Regular_euro8pt8b.h"
#include "Fonts/FreeMonoBold_euro12pt8b.h"
#include "Fonts/FreeMonoBold_euro14pt8b.h"

#define FONT_SMALL Cantarell_Regular_euro8pt8b
#define FONT_NORMAL FreeMonoBold_euro12pt8b
#define FONT_BIG FreeMonoBold_euro14pt8b

// Screen resolution is 264 × 176

void drawSmallText(int x, int y, char* text, int color) {
  display.setFont(&FONT_SMALL);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.println(text);
}

void drawSmallTextRightAlign(int x, int y, char* text, int color) {
  display.setFont(&FONT_SMALL);
  display.setTextColor(color);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  display.setCursor(x - tbw, y);
  display.println(text);
}

void drawText(int x, int y, char* text, int color) {
  display.setFont(&FONT_NORMAL);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.println(text);
}

void drawTextRightAlign(int x, int y, char* text, int color) {
  display.setFont(&FONT_NORMAL);
  display.setTextColor(color);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  display.setCursor(x - tbw, y);
  display.println(text);
}

void drawBoldText(int x, int y, char* text, int color) {
  display.setFont(&FONT_BIG);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.println(text);
}

void drawBoldTextRightAlign(int x, int y, char* text, int color) {
  display.setFont(&FONT_BIG);
  display.setTextColor(color);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  display.setCursor(x - tbw, y);
  display.println(text);
}

void displayCenteredText(char* text) {
  display.setFont(&FONT_NORMAL);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(text);
  }
  while (display.nextPage());
}

void displayData(Words* words) {
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  int xLang = 2;
  int xWord = 40;
  int yGap = 32;
  do {
    for (int i = 0; i < NB; i++) {
      int y = (1 + i) * yGap;
      drawBoldText(xLang, y, words->languages[i], GxEPD_RED);
      drawText(xWord, y, words->translations[i], GxEPD_BLACK);
      display.drawLine(0, y + 5, display.width(), y + 5, GxEPD_BLACK);
    }

  } while (display.nextPage());
}