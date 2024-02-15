#include "Library.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Wake Up Successfull...");
  Serial.println("Serial Monitor Begin");
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  init_smart_gloves();
  get_values_for_motion();
  check_conditions_for_motions();
  Serial.println("Going to sleep now");
  delay(1000);
  esp_deep_sleep_start();
}
void loop() {
}
