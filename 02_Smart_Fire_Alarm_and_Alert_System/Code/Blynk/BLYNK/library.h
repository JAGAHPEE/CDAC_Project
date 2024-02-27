#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3usWQkCit"
#define BLYNK_TEMPLATE_NAME "CDAC"
#define BLYNK_AUTH_TOKEN "Ju3IUmzw52GIXlbs151sVfZWaIBM4oS6"

#include "DHT.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi Credentials....
char ssid[] = "TP-Link_AOSR";
char pass[] = "7979853506";


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

unsigned int state = 0;
// Variable to Check when buzzer should buzz...
uint8_t next = 10;
uint8_t prev = 10;
uint8_t d = 0;

void myTimerEvent();
void get_value_from_sensor();
void OLD_Display(float, float, float, int);
