// 🔔 Receiver Node - ESP2 to ESP6
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "BAJPAI_2.4Ghz";       // Change this
const char* password = "44444422";    // Change this

ESP8266WebServer server(80);
#define BUZZER_PIN D1

void handleRing() {
  Serial.println("🔔 Ring signal received!");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
  server.send(200, "text/plain", "Buzzed!");
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWiFi failed. Trying fallback AP...");
    WiFi.begin("ESP_Doorbell_AP", "12345678");
    delay(5000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    server.on("/ring", handleRing);
    server.begin();
  } else {
    Serial.println("❌ Unable to connect to any WiFi.");
  }
}

void loop() {
  server.handleClient();
}
