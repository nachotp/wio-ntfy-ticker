#ifndef TICKER_H
#define TICKER_H

#include "secrets.h"
#include "TFT_eSPI.h"
#include "ntfyClient.h"

#define SPRITE_SIZE 80
#define ICON_SIZE 32

extern TFT_eSPI tft;
class TickerUI {
    public:
        void setHeader();
        void notificationBadge(int num);
        void setMessageboard(NtfyMessage message);
        void loading_screen();
        void loading(int perc);
        void drawIcon(String name, int x, int y);
        void screenshotSerial();

};
#endif