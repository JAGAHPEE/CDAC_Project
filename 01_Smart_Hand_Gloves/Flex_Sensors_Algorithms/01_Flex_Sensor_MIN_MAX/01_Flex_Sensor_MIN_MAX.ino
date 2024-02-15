#include "Library.h"

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("Serial Monitor Begin");

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  init_smart_gloves();  

}

void loop() {
  // put your main code here, to run repeatedly:
}
