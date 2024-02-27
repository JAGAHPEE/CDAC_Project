#include "library.h"
BlynkTimer timer;
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#define CORE 1
#define DELAY 1000
#define
/* Semaphore Handle */
SemaphoreHandle_t my_sema;

TaskHandle_t update_to_cloud, fire_alarm;

void get_reading_from_sensor(void *Data) {
  while (1) {

    xSemaphoreTake(my_sema, portMAX_DELAY);
    // Get Sensor Value from the Sensor
    get_value_from_sensor();

    xSemaphoreGive(my_sema);

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
void fire_alarm_event(void *Data) {
  while (1) {

    // Get Sensor Value from the Sensor

    // Read the State of the Sensor
    state = digitalRead(SWITCH);
    // Serial.println("\nSwitch State:");
    // Serial.print(state);

    if (state == 1) {
      digitalWrite(LED, LOW);
      // Serial.println("LED OFF");
      prev = 0;
      d = 0;
    } else {
      // if ((next == 1) && (prev == 0) && (t > 32)) {
      if ((next == 1) && (prev == 0)) {
        digitalWrite(LED, HIGH);
        // Serial.println("LED ON");
        prev = next;
        d = 1;
      }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void setup() {

  // Initialize LED and Switch PIN as OUTPUT and INPUT Respectively
  pinMode(LED, OUTPUT);
  pinMode(SWITCH, INPUT);

  Serial.begin(9600);
  Serial.println("Serial Begin...");

  digitalWrite(LED, LOW);

  // DHT Sensor Begin
  dht.begin();

  // I2C Display Begin
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  vSemaphoreCreateBinary(my_sema);

  // Create Task for Sensor Data Read and Activate Alarm
  
  xTaskCreatePinnedToCore(get_reading_from_sensor, "My Task 1", 2048, NULL, 1, &update_to_cloud, CORE);
  xTaskCreatePinnedToCore(fire_alarm_event, "My Task 2", 2048, NULL, 1, &fire_alarm, CORE);
}

void loop() {

  // Start the Blynk
  Blynk.run();
  // Start Timer to update at 500ms interval
  timer.run();
}
