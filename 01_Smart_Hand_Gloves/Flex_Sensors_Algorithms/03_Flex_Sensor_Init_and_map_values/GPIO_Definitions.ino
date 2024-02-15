// LED Function Definition
void toggle_gpio(const int PIN) {
  digitalWrite(PIN, !digitalRead(PIN));
  delay(100);
}
void toggle_led() {
  digitalWrite(LED, !digitalRead(LED));
  // delay(100);
}

//  Read Value from sensor
int get_value_from_sensor(const int GPIO_PIN)
{
  int value = analogRead(GPIO_PIN);
  delay(50);
  return value;
}

int get_value_from_sensor_1()
{
  int value = analogRead(sensor_Pin_1);
  // delay(50);
  return value;
}
int get_value_from_sensor_2()
{
  int value = analogRead(sensor_Pin_2);
  // delay(50);
  return value;
}
int get_value_from_sensor_3()
{
  int value = analogRead(sensor_Pin_3);
  // delay(50);
  return value;
}

// Initialize Smart Gloves with MAX MIN Values
void init_smart_gloves()
{
  // Creating Task to Get Values for Initialization
  Serial.println("Initialize Minimum Value for Sensor");
  Serial.println("Put Flex Straight");
  flag_for_min_max = 0;
  delay(2000);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_1,"Get Sensor 1 Min Value",2048,&MIN_1,5,&task_1,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_2,"Get Sensor 2 Min Value",2048,&MIN_2,5,&task_2,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_3,"Get Sensor 3 Min Value",2048,&MIN_3,5,&task_3,CORE);
  delay(3000);

  Serial.println("Minimum Values : ");
  Serial.println(MIN_1);
  Serial.println(MIN_2);
  Serial.println(MIN_3);

}

// Get Sensor Values for Motion Detect
void get_values_for_motion()
{
  flag_for_min_max = 1;
  delay(3000);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_1,"Get Sensor 1 Values",2048,&value_1,5,&task_1,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_2,"Get Sensor 2 Values",2048,&value_2,5,&task_2,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_3,"Get Sensor 3 Values",2048,&value_3,5,&task_2,CORE);
  delay(1000);
  map_all_values();
  Serial.println("Mapped Values:");
  Serial.println(value_1);
  Serial.println(value_2);
  Serial.println(value_3);
}
void map_all_values()
{
  value_1 = map(value_1, MIN_1, MAX, 0, 100);
  value_2 = map(value_2, MIN_2, MAX, 0, 100);
  value_3 = map(value_3, MIN_3, MAX, 0, 100);
}

