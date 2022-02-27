#ifndef TICKER_H
#define TICKER_H

#include "secrets.h"
#include "TFT_eSPI.h"


class TickerUI {
    public:
        TFT_eSPI tft;
        void demo();
};
#endif