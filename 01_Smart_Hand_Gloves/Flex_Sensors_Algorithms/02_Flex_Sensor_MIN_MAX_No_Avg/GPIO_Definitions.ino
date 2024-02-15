// LED Function Definition
void toggle_gpio(const int PIN) {
  digitalWrite(PIN, !digitalRead(PIN));
  delay(100);
}
void toggle_led() {
  digitalWrite(LED, !digitalRead(LED));
  delay(100);
}

//  Read Value from sensor
int get_value_from_sensor(const int GPIO_PIN)
{
  int value = analogRead(GPIO_PIN);
  return value;
}

int get_value_from_sensor_1()
{
  int value = analogRead(sensor_Pin_1);
  return value;
}
int get_value_from_sensor_2()
{
  int value = analogRead(sensor_Pin_2);
  return value;
}
int get_value_from_sensor_3()
{
  int value = analogRead(sensor_Pin_3);
  return value;
}

// Initialize Smart Gloves with MAX MIN Values
void init_smart_gloves()
{

  // Creating Task to Get Values for Initialization

  // xTaskCreatePinnedToCore(get_test_value,"Sensor Min Value Get",2048,&MIN_1,5,&task_1,CORE);

  Serial.println("Initialize Minimum Value for Sensor");
  Serial.println("Put Flex Straight");
  delay(2000);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_1,"Get Sensor 1 Min Value",2048,&MIN_1,5,&task_1,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_2,"Get Sensor 2 Min Value",2048,&MIN_2,5,&task_2,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_3,"Get Sensor 3 Min Value",2048,&MIN_3,5,&task_3,CORE);

  delay(3000);
  Serial.println("Minimum Values : ");
  Serial.println(MIN_1);
  Serial.println(MIN_2);
  Serial.println(MIN_3);


  Serial.println("Initialize Maximum Value for Sensor");
  Serial.println("Put Flex Bend");
  delay(2000);
  flag_for_min_max = 1;
  // xTaskCreatePinnedToCore(get_test_value,"Sensor Max Value Get",2048,&MAX,5,&task_2,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_1,"Get Sensor 1 Min Value",2048,&MAX_1,5,&task_1,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_2,"Get Sensor 2 Min Value",2048,&MAX_2,5,&task_2,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_3,"Get Sensor 3 Min Value",2048,&MAX_3,5,&task_3,CORE);
  delay(3000);
  Serial.println("Maximum Values : ");
  Serial.println(MAX_1);
  Serial.println(MAX_2);
  Serial.println(MAX_3);
}