
#include "tickerUI.h"
#include "Seeed_FS.h"
#include "ntfyClient.h"
#include <vector>
#include "rawImage.h"

using namespace std;

TFT_eSPI tft;
TickerUI ui;
NtfyClient ntfy;

void setup() {
	Serial.begin(115200);
	if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
        while (1);
    }
	ui.demo();
	if (ntfy.connect_wifi(true)) {
		tft.println("Connected to Wifi");
		tft.println(ntfy.url);

		vector<String> response_list = ntfy.check_server();
		for (String response : response_list) {
			tft.println(response);
		}

	} else {
		tft.drawCircle(TFT_HEIGHT/2, TFT_WIDTH/2, 5, TFT_RED);
	}

}

void loop() {
	
}
