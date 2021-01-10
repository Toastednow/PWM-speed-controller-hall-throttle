#include <Adafruit_MCP4725.h>
#include <Wire.h>

Adafruit_MCP4725 dac;

int throttle = 0;
float tvoltage = 5;
int tvalue = tvoltage * 819;

void setup() {
  Serial.begin(9600);
  Serial.println("Running startup sequence");
  Serial.println("Throttle percentage should be 0");
  Serial.println(throttle);
  Serial.println("Establishing i2c connection");
  dac.begin(0x60);
  Serial.println("Throttle voltage should be 5v");
  Serial.println(tvoltage);
  Serial.println("Setting throttle voltage to 5v");
  dac.setVoltage(tvalue, false);
  Serial.println("Throttle value should be 4095");
  Serial.println(tvalue);
}

void loop() {
int sensorValue = analogRead(A7);
float voltage = sensorValue * (5.0 / 1023.0);
if (voltage > 1.25) {
  throttle = (voltage - 1.25) * 32.7868852;
  if (throttle > 100) throttle = 100;
  Serial.println(throttle);
  tvoltage = -0.05 * throttle + 5;
  tvalue = tvoltage * 819;
  dac.setVoltage(tvalue, false);
}
if (voltage < 1.25) {
  tvalue = 4095;
  dac.setVoltage(tvalue, false);
}
}
