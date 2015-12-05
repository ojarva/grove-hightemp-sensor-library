/*
Demo code for Grove - High Temperature Sensor

Prints out temperature readings in celsius.

Thermocouple readings -> A5
Room temperature readings -> A4
*/

#include "high_temp_sensor.h"

HighTemp ht(A4, A5);

void setup() {
    Serial.begin(57600);
    Serial.println("grove - high temperature sensor demo");
    ht.begin();
}

void loop() {
    Serial.print("Room temperature: ");
    Serial.print(ht.getRoomTemperature());
    Serial.print("C; thermocouple reading: ");
    Serial.print(ht.getThermoCoupleTemperature());
    Serial.println("C");
    delay(100);
}
