#include "E:\Ruppin College\Subjects\Thinking Skills\Robot\Code V3\Code_V3.1\class_headers.h"
#define sensors 6

bool Values[sensors];
bool previousValues[sensors];
int counter = 0;

int weights[sensors] = {-250, -50, -50, 50, 50, 250};

const int PWM_LEFT = 11, PWM_RIGHT = 3;
const int DIR_RIGHT = 12, DIR_LEFT = 13;
const int left_brake = 8, right_brake = 9; 

Motor rightMotor(12, 3);
Motor leftMotor(DIR_LEFT, PWM_LEFT);

void getReadings() {
  Values[0] = digitalRead(2); // digital pin arduino
  Values[1] = digitalRead(4);
  Values[2] = digitalRead(5);
  Values[3] = digitalRead(6);
  Values[4] = digitalRead(7);
  Values[5] = digitalRead(10);
}
void setup() {
  Serial.begin(9600);
//  for (int i = 0; i < sensors; i++)
//      previousValues[i] = 0;
}

void loop() {
  getReadings();
//  delay(1000);
  int product = dot_product(Values, weights);
  int bias = 150;

  for (int i = 0; i < sensors; i++) {
    Serial.print(Values[i]);
  }
  Serial.println("    Product: " + String(product));
  Serial.println();
  Serial.println("-------------");

//  if () {
//    
//  }
  while (check0(Values) == 1) {
    int correction = 350;
    leftMotor.drive(bias + correction);
    rightMotor.drive(bias - correction);
    getReadings();
  }

  getReadings();
  product = dot_product(Values, weights);
  
  leftMotor.drive(bias + product);
  rightMotor.drive(bias - product);
  
  counter += 1;
  
  if (counter % 10 == 0) {
    for (int i = 0; i < sensors; i++)
      previousValues[i] = Values[i];
    counter = 0;
  }
}

int dot_product(bool* vector1, int* vector2) {
  int sum = 0;
  for (int i = 0; i < sensors; i++){
    sum += vector1[i] * vector2[i];
  }
  return sum;
}
bool check0 (bool* vector) {
  for (int i = 0; i < sensors; i++)
    if (vector[i] == 1) return 0;
  return 1;
}
