#include "Library.h"
RTC_DATA_ATTR int value = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);


  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  xTaskCreatePinnedToCore(client_task_callback,"Client.Loop",2048,NULL,5,&client_task,CORE);
  // delay(2000);

  softwareSerial.begin(9600);
  if (!player.begin(softwareSerial, /*isACK = */ false, /*doReset = */ false)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0);
    }
  }
  player.volume(15);
  delay(100);


  DEBUG_LN("Wake Up Successful...");
  DEBUG_LN("Serial Monitor Begin");
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);  //1 = High, 0 = Low


  OLED_init();
  OLED_commands_out();
  display.setCursor(0, 0);
  display.println(F("Smart Gloves Wake Up"));
  display.display();


  player.play(KEEP_FS);
  init_smart_gloves();
  display.setCursor(0, 16);
  display.println(F("Ready to Give Commands"));
  display.display();
  player.play(INIT_TRACK);
  get_values_for_motion();
  check_conditions_for_motions();


  snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("outTopic", msg);
  value++;


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
