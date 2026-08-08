#include <ESP8266WiFi.h> 

#include <SinricPro.h> 
#include <SinricProSwitch.h> 

#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"

#define APP_KEY "YOUR_SINRIC_APP_KEY"
#define APP_SECRET "YOUR_SINRIC_APP_SECRET"

#define SWITCH_ID "YOUR_SWITCH_ID"

#define RELAY_PIN  D1 // Relay control pin 
bool onPowerState(const String &deviceId, bool &state) { digitalWrite(RELAY_PIN, state ? LOW : HIGH); // active LOW relay Serial.println(state ? "Relay ON" : "Relay OFF"); return true; } 
void setupWiFi() {
 Serial.print("Connecting to WiFi"); 
WiFi.begin(WIFI_SSID, WIFI_PASS); 
while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); 
}
 Serial.println(); 
Serial.print("Connected! IP: "); 
Serial.println(WiFi.localIP()); 
} 
void setup() {
 Serial.begin(115200);  
pinMode(RELAY_PIN, OUTPUT); 
digitalWrite(RELAY_PIN, HIGH); // Relay OFF at start 
setupWiFi(); SinricProSwitch &mySwitch = SinricPro[SWITCH_ID]; mySwitch.onPowerState(onPowerState);  
SinricPro.begin(APP_KEY, APP_SECRET);
 }
void loop() {
 SinricPro.handle(); 
}
