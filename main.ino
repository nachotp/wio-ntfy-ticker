
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
	pinMode(LED_BUILTIN, OUTPUT);
	ui.demo();
	if (ntfy.connect_wifi(true)) {
		tft.println("Connected to Wifi");

	} else {
		tft.drawCircle(TFT_HEIGHT/2, TFT_WIDTH/2, 5, TFT_RED);
	}

}

void loop() {
	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(100);                       // wait for a second
	digitalWrite(LED_BUILTIN, LOW);
	vector<String> response_list = ntfy.check_server();
	ui.notificationBadge(response_list.size());
	tft.setTextPadding(TFT_HEIGHT/3);
	for (String response : response_list) {
		ui.setMessageboard(response);
		delay(10000);    
	}
	//tft.setCursor(0,0);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(100);   // turn the LED on (HIGH is the voltage level)                   // wait for a second
	digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
	delay(100);
	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(100);                       // wait for a second
	digitalWrite(LED_BUILTIN, LOW);
}
