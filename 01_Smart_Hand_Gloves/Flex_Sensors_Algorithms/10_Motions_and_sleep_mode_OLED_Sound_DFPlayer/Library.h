// Libraries for FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Task_Declarations.h"

// Library for Debug Message
#include "Debug_Macro.h"

// Libraries for DFPlayer
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 17; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 16; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
// Create the Player object
DFRobotDFPlayerMini player;

// Libraries for I2C OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Library for Track_Playback Number
#include "ENUM_TRACK_NO.h"

// Libraries for GPIO PINS
#include "GPIO_Pin_Declarations.h"

// Library for Function Declarations
#include "Function_Declarations.h"

// Library for Global Variables
#include"Global_variable.h"
