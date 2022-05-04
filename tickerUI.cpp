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
    delay(350);
}


void TickerUI::setHeader() {
    tft.fillScreen(tft.color565(0,0,0));
    tft.setTextColor(TFT_WHITE);

    tft.fillRect(0, 0, TFT_HEIGHT, SPRITE_SIZE, TFT_DARKCYAN);
    tft.fillRect(0, TFT_HEIGHT, TFT_HEIGHT, TFT_WIDTH, TFT_BLACK);
    
    tft.drawRect(5, 0, SPRITE_SIZE, SPRITE_SIZE, TFT_GREENYELLOW);
    drawImage<uint16_t>("mail.bmp", 5, 0);
    tft.setTextSize(1);

}; 

void TickerUI::notificationBadge(int num) {
    tft.fillCircle(SPRITE_SIZE/2 + 5, SPRITE_SIZE/2 + 5, 16, TFT_BLACK);
    tft.fillCircle(SPRITE_SIZE/2 + 5, SPRITE_SIZE/2 + 5, 13, TFT_RED);
    tft.drawCentreString(String(num), SPRITE_SIZE/2 + 5, SPRITE_SIZE/2 - 5, 4);
};

void TickerUI::setMessageboard(NtfyMessage message){
    tft.fillRoundRect(0, SPRITE_SIZE + 2, TFT_HEIGHT - 2, TFT_WIDTH - 2 - SPRITE_SIZE, 10, TFT_WHITE);
    //tft.drawRoundRect(0, 20, 2*TFT_HEIGHT/3 - 20, TFT_WIDTH - 40, 10, TFT_BLACK);
    for (size_t i = message.tags.size(); i > 0; i--) {
        drawIcon(message.tags[i-1], TFT_HEIGHT - 5 - i*(ICON_SIZE), SPRITE_SIZE + 5);
    }
    
    tft.setCursor(5, SPRITE_SIZE  + 10);
    
    tft.setTextPadding(25);
    tft.setTextColor(TFT_BLACK);
    tft.setTextFont(4);
    tft.print(message.priority);
    tft.print(" ");
    tft.println(message.title);
    
    tft.setTextFont(2);
    tft.println(message.message);
    tft.setTextColor(TFT_WHITE);
}

void TickerUI::screenshotSerial() {
    Serial.println("=== BEGIN SCREENSHOT ARRAY ===");
    Serial.print("[");
    for (size_t x = 0; x < TFT_HEIGHT; x++) {
        Serial.print("[");
        for (size_t y = 0; y < TFT_WIDTH; y++) {
            Serial.print(tft.readPixel(x, y));
            if (y < TFT_WIDTH-1) {
                Serial.print(",");
            }
        }
        
        Serial.print("]");
        if (x < TFT_HEIGHT-1) {
            Serial.print(",\n");
        }
    }
    Serial.print("\n]\n");
    Serial.println("=== END SCREENSHOT ARRAY ===");
}

void TickerUI::drawIcon(String name, int x, int y) {
    String path = name + String(".bmp");
    drawImage<uint16_t>(path.c_str(), x, y);
}