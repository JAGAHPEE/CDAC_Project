void get_value_from_sensor() {
  delay(200);

  h = dht.readHumidity();

  // Read temperature as Celsius
  t = dht.readTemperature();

  // Read temperature as Fahrenheit
  f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.printf("\nTemperature: %3.2f\n", t);
  Serial.printf("\nHumidity: %3.0f\n", h);

  int f_light = analogRead(FLAME);
  if (f_light < 250) {
    next = 1;
  } else {
    next = 0;
    prev = 0;
  }
  Serial.println("\nFlame: ");
  Serial.print(f_light);
  Serial.println("");
  OLD_Display(f, t, h, f_light);
}

// Display Data on OLED
void OLD_Display(float f, float t, float humidity, int f_light) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println(F("Flame:"));
  display.print(f_light);

  display.println(F("\nTemperature:"));
  display.print(t);

  display.println(F("\nHumidity:"));
  display.print(humidity);
  if (d == 1) {
    display.println(F("\n<--Alarm ON-->"));
  } else {
    display.println(F("\n<--Alarm OFF-->"));
  }
  display.display();
  delay(50);
}

// Write To Blynk Cloud
void myTimerEvent() {
  int f_light = analogRead(FLAME);
  Blynk.virtualWrite(V1, f_light);
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V4, d);
}