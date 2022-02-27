#include <ArduinoJson.h>
#include "tickerUI.h"
#include "ntfyClient.h"
#include <vector>

using namespace std;

TickerUI ui;
NtfyClient ntfy;

void setup() {
	Serial.begin(115200);

	ui.demo();
	if (ntfy.connect_wifi(true)) {
		ui.tft.println("Connected to Wifi");
		ui.tft.println(ntfy.url);

		vector<String> response_list = ntfy.check_server();
		for (String response : response_list) {
			ui.tft.println(response);
		}

	} else {
		ui.tft.drawCircle(TFT_HEIGHT/2, TFT_WIDTH/2, 5, TFT_RED);
	}

}

void loop() {
	
}
