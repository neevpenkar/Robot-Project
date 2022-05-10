#include <E:\Ruppin College\Subjects\Thinking Skills\Robot\Code V2\Code_V2.1\class_headers.h>

int Xright, Xleft, delta;
const float e = 2.71828, pi = 3.14159, d = 1;

const int PWM_LEFT = 11, PWM_RIGHT = 3;
const int DIR_RIGHT = 12, DIR_LEFT = 13;
const int left_brake = 8, right_brake = 9;
#define derivativeDepth 8

Motor rightMotor(12, 3);
Motor leftMotor(DIR_LEFT, PWM_LEFT);

InfraRed rightSensor(A2, "Right");
InfraRed leftSensor(A3, "Left");

int f = 0, df = 0, ddf = 0;
int reading, prev_reading, prev_prev_reading;
 
void setup() {
  Serial.begin(9600);
  TCCR1B &= ~(1 << CS12);
  TCCR1B |= (1 << CS11);
  TCCR1B &= ~(1 << CS10);
  pinMode(8, OUTPUT);
  calibration();
  
  // One time use
  int rightReading = rightSensor.TimedaverageFunction() - Xright;
  int leftReading = leftSensor.TimedaverageFunction() - Xleft;
  reading = rightReading - leftReading;
}

void loop() {
  next_values();

  f = derivative(reading);
  df = function(reading / 2);
  ddf = second_derivative(reading / 2);

  int bias = 90;
  int avg_function = f + df + ddf;
  avg_function = abs(avg_function);
  
  Serial.print(reading);
  Serial.print(" ");
  Serial.println(avg_function);

  if (reading > 20) { // Going Left
    leftMotor.drive(bias + avg_function);
    rightMotor.drive(bias - avg_function);  
  }
  else if (reading < -20) { // Going Right
    leftMotor.drive(bias - avg_function);
    rightMotor.drive(bias + avg_function);
  }
  else {
    leftMotor.drive(bias);
    rightMotor.drive(bias);
  }
//  delay(300);
}
int function(int x) {
  x = abs(x);
  int y;

  y = (x * d) / 10.0;
  return y;
}
int derivative (int x) {
  x = abs(x);
  int y;

  y = 4 * d * sqrt(x);
  return y;
}
int second_derivative (int x) {
  x = abs(x);
  int y;

  y = pow(x, 2)/1000.0;
  return y;
}
int tikun (int x) {
  x = abs(x);
  return cos(x);
}
void next_values (){
  prev_prev_reading = prev_reading;
  prev_reading = reading;
  
  // F(x):
  int rightReading = rightSensor.TimedaverageFunction() - Xright;
  int leftReading = leftSensor.TimedaverageFunction() - Xleft;
  reading = rightReading - leftReading;
  // Value of "reading" is positive as the robot goes left, negative as it goes right
}
void calibration() {
  Xright = rightSensor.TimedaverageFunction();
  Xleft = leftSensor.TimedaverageFunction();
}
