#include <EEPROM.h>

int address = 0; // starting address of the EEPROM
int value = 42; // value to be written to the EEPROM

void setup() {
  Serial.begin(9600); // initialize serial communication
  EEPROM.begin(1);
  EEPROM.write(0, 1); // write the value to the EEPROM
  EEPROM.commit();
  Serial.println("Value written to EEPROM");
}

void loop() {
  int readValue = EEPROM.read(0); // read the value from the EEPROM
  Serial.print("Value read from EEPROM: ");
  Serial.println(readValue);
  delay(1000);
}
