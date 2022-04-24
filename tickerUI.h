#ifndef TICKER_H
#define TICKER_H

#include "secrets.h"
#include "TFT_eSPI.h"
#define SPRITE_WIDTH 80

extern TFT_eSPI tft;
class TickerUI {
    public:
        void demo();
};
#endif