#include "Library.h"
RTC_DATA_ATTR int value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);  //1 = High, 0 = Low

  delay(1000);
  DEBUG_LN("Wake Up Successful...");
  DEBUG_LN("Serial Monitor Begin");
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  Serial.print("Wake-up reason: ");
  Serial.println(wakeup_reason);
  pinMode(LED, OUTPUT);


  toggle_led();
  delay(100);
  toggle_led();


  setup_wifi();

  espClient.setCACert(root_ca);
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

// Task for Fast Call back Response
  // xTaskCreatePinnedToCore(client_task_callback, "Client_Loop", 1024, NULL, 5, &client_task, CORE);


  softwareSerial.begin(9600);
  if (!player.begin(softwareSerial, /*isACK = */ false, /*doReset = */ false)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0);
    }
  }

  player.volume(30);
  delay(100);

  OLED_init();
  OLED_commands_out();
  display.setCursor(0, 0);
  display.println(F("Smart Gloves Wake Up"));
  display.display();

}
void loop() {

  if (null_condition_check > 1) {
    display.setCursor(0, 56);
    display.println(F("Going to Sleep Mode"));
    display.display();
    DEBUG_LN("Going to Sleep Mode");
    delay(3000);
    display.clearDisplay();
    display.display();
    delay(1000);
    esp_deep_sleep_start();
  }
  player.play(KEEP_FS);
  init_smart_gloves();
  display.setCursor(0, 16);
  display.println(F("Ready to Give Commands"));
  display.display();
  player.play(INIT_TRACK);
  get_values_for_motion();
  check_conditions_for_motions();
  delay(2000);
}
