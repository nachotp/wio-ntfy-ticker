#include "tickerUI.h"

void TickerUI::demo() {
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(tft.color565(0,0,0));
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE);

    tft.fillRect(0, 0, TFT_HEIGHT/3, TFT_WIDTH, TFT_DARKCYAN);
    tft.fillRect(TFT_HEIGHT/3, 0, 2*TFT_HEIGHT/3, TFT_WIDTH, TFT_BLACK);

};