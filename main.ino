#include <vector>
#include "Seeed_FS.h"
#include "rawImage.h"

#include "tickerUI.h"
#include "ntfyClient.h"
//#include "utils.h"

using namespace std;

TFT_eSPI tft;
TickerUI ui;
NtfyClient ntfy;

void blink(int times);
void blink(int times, int delay_val);

vector<NtfyMessage> response_list;
int response_size;
bool screenshoting = false;

void setup() {
	ui.loading_screen();
	Serial.begin(115200);
	pinMode(WIO_KEY_C, INPUT_PULLUP);
	
	if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
        while (1);
    }
	ui.loading(33);
	pinMode(LED_BUILTIN, OUTPUT);
	
	if (ntfy.connect_wifi(true)) {
		tft.println("Connected to Wifi");

	} else {
		tft.drawCircle(TFT_HEIGHT/2, TFT_WIDTH/2, 5, TFT_RED);
	}
	ui.loading(66);
	response_list = ntfy.poll_notifications();
	response_size = response_list.size();
	ui.loading(100);
	tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, TFT_DARKCYAN);
	ui.setHeader();
}

void loop() {

	

	if (response_size > 0){
		ui.notificationBadge(response_size);
	}
	
	for (NtfyMessage response : response_list) {
		if (digitalRead(WIO_KEY_C) == LOW && !screenshoting){
			beep(2);
			ui.screenshotSerial();
		}
		ui.setMessageboard(response);
		delay(1000);    
	}
	
	blink(3);
	
	response_list = ntfy.poll_notifications();
	response_size = response_list.size();
}

void blink(int times) {
    blink(times, 100);
}

void blink(int times, int delay_val){
    for (int i = 0; i < times; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(delay_val);  
        digitalWrite(LED_BUILTIN, LOW); 
        delay(delay_val);
    }
}

void beep(int n){
  for (int i = 0; i < n; i++){
    analogWrite(WIO_BUZZER, 64);
    delay(125);  
    analogWrite(WIO_BUZZER, 0);
    delay(75);
  }
}