void get_test_value(void *data) {
  int sum = 0;
  for (int i = 0; i < test_count; i++) {
    // Get value from Sensor min and maximum
    sum = sum + get_value_from_sensor(sensor_Pin_1);
    // sum = sum + 4;
    vTaskDelay(100);
    // Serial.println(sum);
  }
  sum = sum / test_count;

  int *value = (int *)data;
  *value = sum;
  vTaskDelete(NULL);
}


// Task Functions to get values
// Task 1
void get_test_value_from_sensor_1(void *data) {
  int sum = 0;
  for (int i = 0; i < test_count; i++) {
    sum = sum + get_value_from_sensor_1();
    vTaskDelay(100);
    // Serial.println(sum);
  }
  sum = sum / test_count;

  int *value = (int *)data;
  *value = sum;
  vTaskDelete(NULL);
}

// Task 2
void get_test_value_from_sensor_2(void *data) {
  int sum = 0;
  for (int i = 0; i < test_count; i++) {
    sum = sum + get_value_from_sensor_2();
    vTaskDelay(100);
    // Serial.println(sum);
  }
  sum = sum / test_count;

  int *value = (int *)data;
  *value = sum;

  vTaskDelete(NULL);
}

// Task 3
void get_test_value_from_sensor_3(void *data) {
  int sum = 0;
  for (int i = 0; i < test_count; i++) {
    sum = sum + get_value_from_sensor_1();
    vTaskDelay(100);
    // Serial.println(sum);
  }
  sum = sum / test_count;

  int *value = (int *)data;
  *value = sum;
  vTaskDelete(NULL);
}
