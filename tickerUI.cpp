#include "rawImage.h"
#include "tickerUI.h"
#include "ntfyClient.h"

void TickerUI::loading_screen(){
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(tft.color565(50,50,250));
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE);

    tft.drawString("Loading...", 75, 70);
    tft.drawRoundRect(50, 160, TFT_HEIGHT-100, 30, 5, TFT_WHITE);
    delay(100);

}

void TickerUI::loading(int perc){
  int max_width = TFT_HEIGHT-106;
  for (int i; i <= perc; i++)
    tft.fillRoundRect(53, 163, max_width * i / 100, 24, 5, TFT_WHITE);
    delay(250);
}


void TickerUI::setHeader() {
    tft.fillScreen(tft.color565(0,0,0));
    tft.setTextColor(TFT_WHITE);

    tft.fillRect(0, 0, TFT_HEIGHT, SPRITE_WIDTH, TFT_DARKCYAN);
    tft.fillRect(0, TFT_HEIGHT, TFT_HEIGHT, TFT_WIDTH, TFT_BLACK);
    
    tft.drawRect(5, 0, SPRITE_WIDTH, SPRITE_WIDTH, TFT_GREENYELLOW);
    drawImage<uint16_t>("mail.bmp", 5, 0);
    tft.setTextSize(1);

}; 

void TickerUI::notificationBadge(int num) {
    tft.fillCircle(SPRITE_WIDTH/2 + 5, SPRITE_WIDTH/2 + 5, 16, TFT_BLACK);
    tft.fillCircle(SPRITE_WIDTH/2 + 5, SPRITE_WIDTH/2 + 5, 13, TFT_RED);
    tft.drawCentreString(String(num), SPRITE_WIDTH/2 + 5, SPRITE_WIDTH/2 - 5, 4);
};

void TickerUI::setMessageboard(NtfyMessage message){
    tft.fillRoundRect(0, SPRITE_WIDTH + 2, TFT_HEIGHT - 2, TFT_WIDTH - 2 - SPRITE_WIDTH, 10, TFT_WHITE);
    //tft.drawRoundRect(0, 20, 2*TFT_HEIGHT/3 - 20, TFT_WIDTH - 40, 10, TFT_BLACK);
    tft.setCursor(5, SPRITE_WIDTH + 10);
    tft.setTextPadding(25);
    tft.setTextColor(TFT_BLACK);
    tft.setTextFont(2);
    tft.print(message.priority);
    tft.print(" ");
    tft.println(message.title);

    for (String tag : message.tags){
        tft.print(tag);
        tft.print(" ");
    }
    tft.println("");

    tft.setTextFont(2);
    tft.println(message.message);
    tft.setTextColor(TFT_WHITE);
}