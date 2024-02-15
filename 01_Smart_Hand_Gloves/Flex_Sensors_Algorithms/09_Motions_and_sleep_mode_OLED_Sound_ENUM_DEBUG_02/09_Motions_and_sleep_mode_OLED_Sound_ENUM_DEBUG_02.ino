#include "Library.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  DEBUG_LN("Wake Up Successful...");
  DEBUG_LN("Serial Monitor Begin");
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  OLED_init();
  OLED_commands_out();
  display.setCursor(0, 0);
  display.println(F("Smart Gloves Wake Up"));
  display.display();


  init_smart_gloves();
  display.setCursor(0, 16);
  display.println(F("Ready to Give Commands"));
  display.display();
  get_values_for_motion();
  check_conditions_for_motions();


  display.setCursor(0, 56);
  display.println(F("Going to Sleep Mode"));
  display.display();
  DEBUG_LN("Going to Sleep Mode");

  delay(3000);
  display.clearDisplay();
  display.display();

  esp_deep_sleep_start();
}
void loop() {
}
