#include "tickerUI.h"
#include "ntfyClient.h"

TickerUI ui;
NtfyClient ntfy;

void setup() {
	Serial.begin(115200);

	ui.demo();
	if (ntfy.connect_wifi(true)) {
		ui.tft.drawCircle(TFT_HEIGHT/2, TFT_WIDTH/2, 5, TFT_GREEN);
		ui.tft.print(ntfy.url);
		ntfy.check_server();
	} else {
		ui.tft.drawCircle(TFT_HEIGHT/2, TFT_WIDTH/2, 5, TFT_RED);
	}

}

void loop() {
	
}
