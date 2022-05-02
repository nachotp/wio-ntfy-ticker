#include "ntfyClient.h"
#include <vector>
#include <ArduinoJson.h>

using namespace std;

NtfyClient::NtfyClient(){
    url = String(NTFY_DOMAIN) + String(NTFY_TOPIC) + String("/json?poll=1");
    //Serial.println(url);
    http.setAuthorization(NTFY_USER, NTFY_PASS);
    http.begin(client, url);
};

vector<NtfyMessage> NtfyClient::check_server(){
    int result = http.GET();
    http.useHTTP10(true);
    Serial.print(url);
    Serial.printf(" Returned %d\n", result);
    
    vector<NtfyMessage> response_list;

    if (result == 200) {
        String raw_response = http.getStream().readString();
        String buffer = "";
        bool append_flag = false;

        for (char c : raw_response) {
            if (c == '\n' && append_flag) {
                append_flag = false;
                DynamicJsonDocument doc(512);

                DeserializationError error = deserializeJson(doc, buffer);
                if (error) {
                    Serial.print(F("deserialization failed: "));
                    Serial.println(error.f_str());
                    Serial.println(buffer);
                    break;
                } else {
                
                    buffer = "";

                    JsonArray tags_array = doc["tags"];
                    vector<String> tags;

                    for (JsonVariant tag : tags_array) {
                        tags.push_back(String((const char *)tag));
                    } 
                    
                    response_list.push_back(
                        NtfyMessage(
                            doc["id"],
                            doc["title"],
                            doc["message"],
                            tags,
                            doc["priority"]
                        )
                    );
                
                }
                // deserializeJson(doc, doc["message"]);
            }
            else if (c == '{') {
                append_flag = true;
            }

            if (append_flag) {
                buffer += c;
            }
        }
    }
    return response_list;
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
      delay(250);
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

NtfyMessage::NtfyMessage(String nid, String ntitle, String nmessage, vector<String> ntags, int npriority) {
    id = nid;
    title = ntitle;
    message = nmessage;
    tags = ntags;
    priority = npriority;    
};

NtfyMessage::NtfyMessage(String nid, String ntitle, String nmessage, int npriority) {
    id = nid;
    title = ntitle;
    message = nmessage;
    priority = npriority;    
};              