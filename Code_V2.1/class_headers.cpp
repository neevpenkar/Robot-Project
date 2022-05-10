#include "Arduino.h"
#include "class_headers.h"

Motor::Motor (byte direction_pin, byte signal_pin) {
  pinMode(direction_pin, OUTPUT);
  pinMode(signal_pin, OUTPUT);
  
  dir_pin = direction_pin;
  sig_pin = signal_pin;
}

void Motor::drive(int val) {
  // Negative value = Go back
  if (val < 0)
    digitalWrite(dir_pin, 0);
    
  // Positive value = Go forward
  else if (val > 0)
    digitalWrite(dir_pin, 1);

  if (abs(val) > 255) val = 255;
  analogWrite(sig_pin, abs(val));
}

//----------------
InfraRed::InfraRed(int sensor_pin, String _type) {
  type = _type;
  pin = sensor_pin;
}

int InfraRed::reading() {
  return analogRead(pin);
}

int InfraRed::TimedaverageFunction() {
  int sum = 0; const int rounds = 5;
  
  for (int i = 0; i < rounds; i++) {
    delay(5);
    sum += reading();
  }
  return sum / rounds;
}
void InfraRed::setBias(int bias){
  Cbias = bias;
}
