void get_value_from_sensor() {
  delay(500);

  h = dht.readHumidity();

  // Read temperature as Celsius
  t = dht.readTemperature();

  // Read temperature as Fahrenheit
  f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Read Humidity
  // humidity = dht.computeHeatIndex(t, h, false);

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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED, HIGH);
    s = 1;
  } else {
    digitalWrite(LED, LOW);  // Turn the LED off by making the voltage HIGH
    s = 0;
  }
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    if (client.connect("CL_ID_1", "CDAC", "cdac@123")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");

      snprintf(sstate, 4, "LED: %d", s);
      client.publish("state", sstate);

      snprintf(Temp, STATE_S, "%f", t);
      client.publish("Temp", Temp);

      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}