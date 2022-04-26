#include "rawImage.h"
#include "tickerUI.h"


void TickerUI::demo() {
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(tft.color565(0,0,0));
    tft.setTextColor(TFT_WHITE);

    tft.fillRect(0, 0, TFT_HEIGHT, SPRITE_WIDTH, TFT_DARKCYAN);
    tft.fillRect(0, TFT_HEIGHT, TFT_HEIGHT, TFT_WIDTH, TFT_BLACK);
    
    tft.drawRect(5, 0, SPRITE_WIDTH, SPRITE_WIDTH, TFT_GREENYELLOW);
    drawImage<uint16_t>("mail.bmp", 5, 0);
    tft.setTextSize(1);

}; 

void TickerUI::notificationBadge(int num) {
    tft.fillCircle(SPRITE_WIDTH/2 + 5, SPRITE_WIDTH/2 + 5, 13, TFT_RED);
    tft.drawCircle(SPRITE_WIDTH/2 + 5, SPRITE_WIDTH/2 + 5, 13, TFT_BLACK);
    tft.drawCentreString(String(num), SPRITE_WIDTH/2 + 5, SPRITE_WIDTH/2 - 5, 4);
};

void TickerUI::setMessageboard(String message){
    tft.fillRoundRect(0, SPRITE_WIDTH + 2, TFT_HEIGHT - 2, TFT_WIDTH - 2 - SPRITE_WIDTH, 10, TFT_WHITE);
    //tft.drawRoundRect(0, 20, 2*TFT_HEIGHT/3 - 20, TFT_WIDTH - 40, 10, TFT_BLACK);
    tft.setCursor(5, SPRITE_WIDTH + 5);
    tft.setTextPadding(5);
    tft.setTextColor(TFT_BLACK);
    tft.setTextFont(2);
    tft.println(message);
    tft.setTextColor(TFT_WHITE);
}