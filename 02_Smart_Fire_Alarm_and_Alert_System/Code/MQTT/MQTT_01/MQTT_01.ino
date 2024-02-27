
#include "library.h"

int value = 0;
int s = 0;

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
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Get Sensor Value from the Sensor
  get_value_from_sensor();
  // Read the State of the Sensor
  unsigned int state = digitalRead(SWITCH);
  Serial.println("Switch State:");
  Serial.print(state);

  if (state == 1) {
    digitalWrite(LED, LOW);
    prev = 0;
    d = 0;
  } else {
    if ((next == 1) && (prev == 0) && (t > 32)) {
      digitalWrite(LED, HIGH);
      prev = next;
      d = 1;
    }
  }
    unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
  }

   snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);

    Serial.print("Publish message: ");

    Serial.println(msg);
    client.publish("outTopic", msg);

    snprintf(sstate, 10, "LED: %d", s);
    client.publish("state", sstate);

    Serial.printf("Temperature: %3.2f\n", t);
    snprintf(Temp, STATE_S, "%f", t);
    client.publish("Temp", Temp);
    delay(1000);
}
