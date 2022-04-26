#ifndef TICKER_H
#define TICKER_H

#include "secrets.h"
#include "TFT_eSPI.h"
#define SPRITE_WIDTH 80

extern TFT_eSPI tft;
class TickerUI {
    public:
        void setHeader();
        void notificationBadge(int num);
        void setMessageboard(String message);
        void loading_screen();
        void loading(int perc);

};
#endif