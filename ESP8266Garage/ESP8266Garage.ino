#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "************"
#define DEVICE_ID "************"
#define DEVICE_CREDENTIAL "************"

#define SSID "**********"
#define SSID_PASSWORD "*************"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT);
  //digitalWrite(4, LOW);
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["garageTrigger"] << digitalPin(4);

}

void loop() {
  thing.handle();
}
