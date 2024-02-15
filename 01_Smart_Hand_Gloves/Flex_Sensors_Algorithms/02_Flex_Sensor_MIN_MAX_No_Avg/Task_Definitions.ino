void get_test_value(void *data) {
  int next = 0;
  int prev = 3000;
  for (int i = 0; i < test_count; i++) {
    // Get value from Sensor min and maximum
    next = get_value_from_sensor(sensor_Pin_1);
    if (flag_for_min_max == 0) {
      if (next < prev) {
        prev = next;
      }
    } else {
      if (next > prev) {
        prev = next;
      }
    }
    Serial.println(prev);
    vTaskDelay(100);
  }
  int *value = (int *)data;
  *value = prev;
  vTaskDelete(NULL);
}


// Task Functions to get values
// Task 1
void get_test_value_from_sensor_1(void *data) {
  int next = 0;
  int prev = 3000;
  for (int i = 0; i < test_count; i++) {

    // Get value from Sensor min and maximum
    next = get_value_from_sensor_1();
    if (flag_for_min_max == 0) {
      if (next < prev) {
        prev = next;
      }
    } else {
      if (next > prev) {
        prev = next;
      }
    }
    Serial.println(prev);
    vTaskDelay(100);
  }
  int *value = (int *)data;
  *value = prev;
  vTaskDelete(NULL);
}

// Task 2
void get_test_value_from_sensor_2(void *data) {
  int next = 0;
  int prev = 3000;
  for (int i = 0; i < test_count; i++) {

    // Get value from Sensor min and maximum
    next = get_value_from_sensor_2();
    if (flag_for_min_max == 0) {
      if (next < prev) {
        prev = next;
      }
    } else {
      if (next > prev) {
        prev = next;
      }
    }
    Serial.println(prev);
    vTaskDelay(100);
  }
  int *value = (int *)data;
  *value = prev;
  vTaskDelete(NULL);
}

// Task 3
void get_test_value_from_sensor_3(void *data) {
  int next = 0;
  int prev = 3000;
  for (int i = 0; i < test_count; i++) {

    // Get value from Sensor min and maximum
    next = get_value_from_sensor_3();
    if (flag_for_min_max == 0) {
      if (next < prev) {
        prev = next;
      }
    } else {
      if (next > prev) {
        prev = next;
      }
    }
    Serial.println(prev);
    vTaskDelay(100);
  }
  int *value = (int *)data;
  *value = prev;
  vTaskDelete(NULL);
}
