// 🔔 Doorbell Controller - ESP1
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define BUTTON_PIN D2

const char* ssid = "BAJPAI_2.4Ghz";       // Change this
const char* password = "44444422";    // Change this

// IPs of the 5 receiver nodes (ESP2 to ESP6)
String receiverIPs[5] = {
  "192.168.1.101",
  "192.168.1.102",
  "192.168.1.103",
  "192.168.1.104",
  "192.168.1.105"
};

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWiFi failed. Starting AP...");
    WiFi.softAP("ESP_Doorbell_AP", "12345678");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("🔔 Doorbell Pressed! Sending ring signals...");

    for (int i = 0; i < 5; i++) {
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "http://" + receiverIPs[i] + "/ring";
        http.begin(url);
        int httpCode = http.GET();
        if (httpCode > 0) {
          Serial.println("Notified " + receiverIPs[i]);
        } else {
          Serial.println("❌ Failed: " + receiverIPs[i]);
        }
        http.end();
      }
    }

    delay(1000); // debounce
  }
}
