#include "DHT.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

// WiFi Credentials....
const char* ssid = "TP-Link_AOSR";
const char* password = "7979853506";
const char* mqtt_server = "192.168.0.107";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

#define STATE_S (10)



#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET -1       
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// LED PIN
#define LED 2
// Flame Sensor PIN
#define FLAME 34
// SWITCH PIN
#define SWITCH 15
// DHT PIN
#define DHTPIN 4
// DHT Type
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Variable to Store the Value of Sensors
float f;
float t;
float h;
float humidity;
uint16_t f_light;

// Variable to Check when buzzer should buzz...
uint8_t next = 10;
uint8_t prev = 10;
uint8_t d = 0;
#define STATE_S (10)

char sstate[STATE_S];
char Temp[STATE_S];

void setup_wifi();
void get_value_from_sensor();
void OLD_Display(float, float, float, int);
void callback(char* topic, byte* payload, unsigned int length);