// LED Function Definition
void toggle_gpio(const int PIN) {
  digitalWrite(PIN, !digitalRead(PIN));
  delay(100);
}
void toggle_led() {
  digitalWrite(LED, !digitalRead(LED));
  // delay(100);
}

// OLED_Display Init...
void OLED_init()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    DEBUG_LN(F("SSD1306 allocation failed"));
  }
}

void OLED_commands_out()
{
  display.clearDisplay();
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
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
  DEBUG_LN("Initialize Minimum Value for Sensor");
  DEBUG_LN("Put Flex Straight");
  flag_for_min_max = 0;
  delay(2000);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_1,"Get Sensor 1 Min Value",2048,&MIN_1,5,&task_1,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_2,"Get Sensor 2 Min Value",2048,&MIN_2,5,&task_2,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_3,"Get Sensor 3 Min Value",2048,&MIN_3,5,&task_3,CORE);
  delay(1000);

  DEBUG_LN("Minimum Values : ");
  DEBUG_LN(MIN_1);
  DEBUG_LN(MIN_2);
  DEBUG_LN(MIN_3);
  
  track_number = INIT_TRACK;
  xTaskCreatePinnedToCore(command_via_speaker,"Play Track via Speaker",2048,&track_number,5,&sound_task,CORE);
}

// Get Sensor Values for Motion Detect
void get_values_for_motion()
{

  DEBUG_LN("Ready to Detect Motion");
  flag_for_min_max = 1;
  delay(3000);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_1,"Get Sensor 1 Values",2048,&value_1,5,&task_1,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_2,"Get Sensor 2 Values",2048,&value_2,5,&task_2,CORE);
  xTaskCreatePinnedToCore(get_test_value_from_sensor_3,"Get Sensor 3 Values",2048,&value_3,5,&task_2,CORE);
  delay(1000);
  map_all_values();
  DEBUG_LN("Mapped Values:");
  DEBUG_LN(value_1);
  DEBUG_LN(value_2);
  DEBUG_LN(value_3);
}
void map_all_values()
{
  value_1 = map(value_1, MIN_1, Sense_MAX, 0, MAX_MAPPED);
  value_2 = map(value_2, MIN_2, Sense_MAX, 0, MAX_MAPPED);
  value_3 = map(value_3, MIN_3, Sense_MAX, 0, MAX_MAPPED);
}


// Checking conditions and playing track via DFPlayer
void check_conditions_for_motions()
{
  display.setCursor(0, 40);
  if (value_1 > THRESHOLD) 
  {
    if (value_2 > THRESHOLD) 
    {
      if (value_3 > THRESHOLD) 
      {
        // Case 1  (1 1 1)
        track_number = MEDICINE;
        display.println(F("Medicine Required"));
        DEBUG_LN("Medicine Required");
      } 
      else 
      {
        // Case 2 (0 1 1)
        track_number = FOOD_RES;
        display.println(F("Thanks For Food")); 
        DEBUG_LN("Thanks For Food");
      }
    } 
    else 
    {
      if (value_3 > THRESHOLD) 
      {
        // Case NA (1 0 1)
        // track_number = 4;
        display.println(F("Not Applicable"));
        DEBUG_LN("Not Applicable");
      } 
      else 
      {
        // Case 4 (0 0 1)
        track_number = WATER_RES;
        display.println(F("Thanks For Water"));
        DEBUG_LN("Thanks For Water");
      }
    }
  } 
  else 
  {
    if (value_2 > THRESHOLD) 
    {
      if (value_3 > THRESHOLD) 
      {
        // Case 5 (1 1 0)
        track_number = FOOD_REQ;
        display.println(F("Food Request"));
        DEBUG_LN("Food Request");
      } 
      else
      {
        // Case 6 (0 1 0)
        track_number = ENERGY_DRINK;
        display.println(F("Energy Drink Required"));
        DEBUG_LN("Energy Drink Required");
      }
    } 
    else
    {
      if (value_3 > THRESHOLD) 
      {
        // Case 7 (1 0 0)
        track_number = WATER_REQ;
        display.println(F("Water Required"));
        DEBUG_LN("Water Required");
      } 
      else 
      {
        // Case 8 (0 0 0)
        track_number = DEFAULT_TRACK;
        display.println(F("Normal Mode No Request/Response"));
        DEBUG_LN("Normal Mode No Request/Response");
      }
    }
  }
  xTaskCreatePinnedToCore(command_via_speaker,"Play Track via Speaker",2048,&track_number,5,&sound_task,CORE);
  display.display();
  delay(1000);
}