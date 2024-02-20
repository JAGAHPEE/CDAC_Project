// Task Functions to get values
// Task 1
void get_test_value_from_sensor_1(void *data) {
  int next = 0;
  int prev = 3000;
  for (int i = 0; i < test_count; i++) {
    toggle_led();
    // Get value from Sensor min and maximum
    next = get_value_from_sensor_1();
    if (flag_for_min_max == 0) {
      if (next < prev) {
        prev = next;
      }
    } else {
      if (next > MIN_1) {
        prev = next;
      }
    }
    // DEBUG_LN(prev);
    vTaskDelay(50);
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
    toggle_led();

    // Get value from Sensor min and maximum
    next = get_value_from_sensor_2();
    if (flag_for_min_max == 0) {
      if (next < prev) {
        prev = next;
      }
    } else {
      if (next > MIN_2) {
        prev = next;
      }
    }
    // DEBUG_LN(prev);
    vTaskDelay(50);
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
    toggle_led();

    // Get value from Sensor min and maximum
    next = get_value_from_sensor_3();
    if (flag_for_min_max == 0) {
      if (next < prev) {
        prev = next;
      }
    } else {
      if (next > MIN_3) {
        prev = next;
      }
    }
    // DEBUG_LN(prev);
    vTaskDelay(50);
  }
  int *value = (int *)data;
  *value = prev;
  vTaskDelete(NULL);
}

// Task 4 Sound Task
// xTaskCreatePinnedToCore(command_via_speaker,"Play Track via Speaker",2048,&track_number,5,&sound_task,CORE);
void command_via_speaker(void *data) {
  if (player.begin(softwareSerial)) {
    // DEBUG_LN("OK");
    delay(100);
    player.volume(MAX_VOLUME);
    delay(100);
    int track_number = *(int *)data;
    player.play(track_number);
    DEBUG_LN("Track Going to Play");
    DEBUG_LN(track_number);
  } else {
    DEBUG_LN("Connecting to DFPlayer Mini failed!");
  }
  vTaskDelete(NULL);
}

void client_task_callback(void *data) {
  while (1) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    vTaskDelay(50);
  }
}