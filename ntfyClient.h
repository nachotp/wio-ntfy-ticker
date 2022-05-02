#ifndef NTFYCLIENT_H
#define NTFYCLIENT_H

#include "secrets.h"
#include <rpcWiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <vector>

using namespace std;

typedef vector<DynamicJsonDocument> JsonVector;


class NtfyMessage {
    public:
        String id;
        String message;
        String title;
        vector<String> tags;
        int priority;


        NtfyMessage(String nid, String ntitle, String nmessage, vector<String> ntags, int npriority);
        NtfyMessage(String nid, String ntitle, String nmessage, int npriority);
        String str();
};

class NtfyClient {
    public:
        WiFiClientSecure client;
        HTTPClient http;
        String url;
        
        NtfyClient();
        bool connect_wifi(bool debug_boot);
        vector<NtfyMessage> poll_notifications();
};

#endif