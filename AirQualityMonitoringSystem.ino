//Developed and tested using Wokwi simulation environment


#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define MQ2_PIN 34   // Analog pin for MQ-2 sensor

// WiFi settings
const char* ssid = "Wokwi-GUEST"; // Wokwi default
const char* password = "";         // No password

// ThingSpeak settings
const char* server = "http://api.thingspeak.com/update";
String apiKey = "C77E94JIBKFS1993"; //  ThingSpeak API key

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
    dht.begin();

      // Connect to WiFi
        WiFi.begin(ssid, password);
          Serial.print("Connecting to WiFi");
            while(WiFi.status() != WL_CONNECTED){
                delay(500);
                    Serial.print(".");
                      }
                        Serial.println("\nWiFi Connected!");
                        }

                        void loop() {
                          // Read sensors
                            float temperature = dht.readTemperature();      // Celsius
                              float humidity = dht.readHumidity();            // %
                                int gasValue = analogRead(MQ2_PIN);            // 0-4095
                                  int aqi = map(gasValue, 0, 4095, 0, 500);     // Convert gas to AQI scale

                                    // Send data to ThingSpeak
                                      if(WiFi.status() == WL_CONNECTED){
                                          HTTPClient http;
                                              String url = String(server) + "?api_key=" + apiKey +
                                                               "&field1=" + String(temperature) +
                                                                                "&field2=" + String(humidity) +
                                                                                                 "&field3=" + String(gasValue) +
                                                                                                                  "&field4=" + String(aqi);
                                                                                                                      http.begin(url);
                                                                                                                          int responseCode = http.GET();
                                                                                                                              if(responseCode > 0){
                                                                                                                                    Serial.println("Data sent to ThingSpeak");
                                                                                                                                        } else {
                                                                                                                                              Serial.println("Error sending data");
                                                                                                                                                  }
                                                                                                                                                      http.end();
                                                                                                                                                        }

                                                                                                                                                          delay(15000); // ThingSpeak minimum interval
                                                                                                                                                          }
