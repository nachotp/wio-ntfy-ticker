#ifndef NTFYCLIENT_H
#define NTFYCLIENT_H

#include "secrets.h"
#include <rpcWiFi.h>
#include <HTTPClient.h>
#include <vector>

using namespace std;

class NtfyClient {
    public:
        WiFiClientSecure client;
        HTTPClient http;
        String url;
        
        NtfyClient();
        bool connect_wifi(bool debug_boot);
        vector<String> check_server();
};

#endif