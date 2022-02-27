#include "ntfyClient.h"

NtfyClient::NtfyClient(){
    url = String("https://ntfy.sh/healthcheck/json?poll=1&since=1m");// String(NTFY_DOMAIN) + String(NTFY_TOPIC) + String("/json?poll=1");
    //Serial.println(url);
    http.begin(client, url);
};

bool NtfyClient::check_server(){
    int result = http.GET();
    http.useHTTP10(true);
    Serial.printf("%s Returned %d\n", url, result);
    Serial.println(http.getStream().readString());
}

bool NtfyClient::connect_wifi(bool debug_boot){
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(500);

    if (debug_boot){
        Serial.printf("Connecting to WiFi: %s", WIFI_SSID);
        Serial.println("");
    }

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 5) {
      if (debug_boot)
          Serial.println("\tRetrying...");
      delay(500);
      // beep(2);
      WiFi.begin(WIFI_SSID, WIFI_PASS);
      attempts += 1;
    }

    if (WiFi.status() == WL_CONNECTED){
        WiFi.setAutoConnect(true);
        if (debug_boot)
            Serial.println("Connected to WiFi");
        return true;
    } else {
        if (debug_boot)
            Serial.println("Not connected to WiFi");
        return false;
    }
  
};