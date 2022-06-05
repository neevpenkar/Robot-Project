//#include "E:\Ruppin College\Subjects\Thinking Skills\Robot\Code V4\Code_V4.1\class_headers.h"
//
//#include <Arduino_APDS9960.h>
//#define sensors 4
//
//int bias = 170;
//int globalStatus;
//bool Values[sensors], sideRight, sideLeft;
//bool farRight, nearRight, nearLeft, farLeft;
//
//bool previousValues[sensors];
//int previous_prod;
//int errorcounter = 0;
//
//int weights[sensors] = {-300, -120, 120, 300};
//
//const int PWM_LEFT = 11, PWM_RIGHT = 3;
//const int DIR_RIGHT = 12, DIR_LEFT = 13;
//const int left_brake = 8, right_brake = 9; 
//
//Motor rightMotor(12, 3, 9);
//Motor leftMotor(DIR_LEFT, PWM_LEFT, 8);
//
//#include "E:\Ruppin College\Subjects\Thinking Skills\Robot\Code V4\Code_V4.1\Readings.ino"
//
//void setup() {
//  Serial.begin(9600);
//
//  while (!Serial);
//  if (!APDS.begin()) {
//    Serial.println("Error initializing APDS-9960 sensor.");
//  }
//  
//  pinMode(8, OUTPUT);
//  pinMode(9, OUTPUT);
//}
//
//int counter1 = 0, counter2 = 0;
//void loop() {
//  getReadings();
//  drive();
//  int product = dot_product(Values, weights);
//  checkProcedures();
//  Prox();
//  errorcounter += 1;
//  if (errorcounter % 10 == 0) {
//    for (int i = 0; i < sensors; i++)
//      previousValues[i] = Values[i];
//    errorcounter = 0;
//    previous_prod = product;
//  }
//}
//void drive() {
//  getReadings();
//  int product = dot_product(Values, weights);
//  leftMotor.drive(bias - product);
//  rightMotor.drive(bias + product);
//}
//void brake_routine(int val) {
//  analogWrite(9, val); // This is braking procedure FULL brake, val = 255;
//  analogWrite(8, val);
//  getReadings();
////  delay(60);
//  analogWrite(9, 0);
//  analogWrite(8, 0);
//}
//int dot_product(bool* vector1, int* vector2) {
//  int sum = 0;
//  for (int i = 0; i < sensors; i++){
//    sum += vector1[i] * vector2[i];
//  }
//  return sum;
//}
//bool check0 (bool* vector) {
//  for (int i = 0; i < sensors; i++)
//    if (vector[i] == 1) return 0;
//  return 1;
//}
//void getReadings() {
//
//  Values[0] = digitalRead(7);
//  Values[1] = digitalRead(6);
//  Values[2] = digitalRead(5);
//  Values[3] = digitalRead(4);
//
//  sideRight = digitalRead(10);
//  sideLeft = digitalRead(2);
//
//  farRight = digitalRead(7);
//  nearRight = digitalRead(6);
//  nearLeft = digitalRead(4);
//  farLeft = digitalRead(5);
//}
//void checkProcedures() {
//  if (sideRight && check0(Values) && !sideLeft) {
//    delay(50);
//    while (!check0(Values)) {
//      int correction = 300;
//      leftMotor.drive(bias + correction);
//      rightMotor.drive(bias - correction);
//    }
//  }
//  else if (sideLeft && check0(Values) && !sideRight) {
//    delay(50);
//    while (!check0(Values)) {
//      int correction = 300;
//      leftMotor.drive(bias - correction);
//      rightMotor.drive(bias + correction);
//    }
//  }
//  while (check0(Values) == 1 && previous_prod < 100) {
//    delay(5);
//    //if (topLeft && topRight) break;
//    //if (!topLeft && !topRight) break;
//    
//    counter1++;
//    if (counter1 == 20) {
//        counter1 = 0;
//        int correction = 300;
//        leftMotor.drive(bias + correction);
//        rightMotor.drive(bias - correction);
//        delay(200);
//    }
//    else drive();
//    getReadings();
//  }
//  while (check0(Values) == 1 && previous_prod > 100) {
//    delay(5);
//    counter2++;
//    if (counter2 == 20) {
//        counter2 = 0;
//        int correction = 300;
//        leftMotor.drive(bias - correction);
//        rightMotor.drive(bias + correction);
//        delay(200);
//    }
//    else drive();
//  }
//}
//
//int Prox() {
//   int proximity;
//   if (APDS.proximityAvailable()) {
//    proximity = APDS.readProximity();
//    Serial.println(proximity);
//  }
////  if (proximity < 200)
//  while (proximity < 200) {
//    analogWrite(9, 255); // This is braking procedure FULL brake, val = 255;
//    analogWrite(8, 255);
//    colorSense();
//    Serial.println("Helllooooooo");
//    
//    if (APDS.proximityAvailable()) 
//    proximity = APDS.readProximity();
//    if (proximity > 200) break;
//    delay(100);
//  }
////  else if (proximity > 200)
//    drive();
//  
////  analogWrite(9, 0); // This is braking procedure FULL brake, val = 255;
////  analogWrite(8, 0);
//}
//int colorSense() {
//  int r, g, b;
//
//  APDS.readColor(r, g, b);
//
//  Serial.print("r = ");
//  Serial.println(r);
//  Serial.print("g = ");
//  Serial.println(g);
//  Serial.print("b = ");
//  Serial.println(b);
//  Serial.println();
//  if (r > g && r > b)Serial.print("red color detected");
//    if (g > r && g > b)Serial.print("green color detected");
//    if (b > g && b > r)Serial.print("blue color detected");
//  Serial.println();
//   // wait a bit before reading again
//  delay(100);
//}
