#include "E:\Ruppin College\Subjects\Thinking Skills\Robot\Code V4\Code_V4.1\class_headers.h"

#include <Arduino_APDS9960.h>
#define sensors 4

int bias = 150;
int globalStatus;
bool Values[sensors], sideRight, sideLeft;
bool farRight, nearRight, nearLeft, farLeft;

bool previousValues[sensors];
int previous_prod, counter1 = 0, counter2 = 0;
int errorcounter = 0, globalError = 0;

int weights[sensors] = {-300, -120, 120, 300};

const int PWM_LEFT = 11, PWM_RIGHT = 3;
const int DIR_RIGHT = 12, DIR_LEFT = 13;
const int left_brake = 8, right_brake = 9; 

Motor rightMotor(12, 3, 9);
Motor leftMotor(DIR_LEFT, PWM_LEFT, 8);

//#include "E:\Ruppin College\Subjects\Thinking Skills\Robot\Code V4\Code_V4.1\DriveTrain.ino"

void setup() {
  Serial.begin(9600);

  while (!Serial);
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }

  pinMode(left_brake, OUTPUT); // Brake OUTPUTS
  pinMode(right_brake, OUTPUT);
}

void loop() {
  // Get readings and make the dot product -> calculate the "error" from the black line
  getReadings();
  int product = dot_product(Values, weights);

  // Color Sensor - may be called every 10 rounds of procesor
  int proximity = prox();
  //Serial.println(proximity); //delay(90);
  
  if (proximity < 240) {
    // Color and Brake
    analogWrite(left_brake, 255);
    analogWrite(right_brake, 255);
    // ---------------------------------
    char color = getColor();
//    if (color == 'R')
    Serial.println(color);

  }
  else {
  drive();
  // 90 Degree Turns / Stripped Lines
  if (checkCurrentValuesForWhite())
    allWhiteProcedure();
  
  // Drive Normal PID Actions
    // No Braking while proximity is more than 120 
    analogWrite(left_brake, 0);
    analogWrite(right_brake, 0);
  
  pastDataI(product);
  int temp_product = I(product);
  }
}
void getReadings() {

  Values[0] = digitalRead(7);
  Values[1] = digitalRead(6);
  Values[2] = digitalRead(5);
  Values[3] = digitalRead(4);

  sideRight = digitalRead(10);
  sideLeft = digitalRead(2);

  farRight = digitalRead(7);
  nearRight = digitalRead(6);
  nearLeft = digitalRead(4);
  farLeft = digitalRead(5);
}
int dot_product(bool* vector1, int* vector2) {
  int sum = 0;
  for (int i = 0; i < sensors; i++){
    sum += vector1[i] * vector2[i];
  }
  return sum;
}
void drive() {
  getReadings();
  int product = dot_product(Values, weights);
  
  leftMotor.drive(bias - product);
  rightMotor.drive(bias + product);
}
void brake_routine(int val) {
  analogWrite(9, val); // This is braking procedure FULL brake, val = 255;
  analogWrite(8, val);
  getReadings();
//  delay(60);
  analogWrite(9, 0);
  analogWrite(8, 0);
}

bool checkAllWhite (bool* vector) {
  for (int i = 0; i < sensors; i++)
    if (vector[i] == 1) return 0;
  return 1;
}
bool checkCurrentValuesForWhite () {
  getReadings();
  return checkAllWhite(Values);
}

void pastDataI(int product) {
  globalError ++;

  if (globalError % 10 == 0){ // Every ten cycles shift values
    previous_prod = product;
    for (int i = 0; i < sensors; i++) {
      previousValues[i] = Values[i];
    }
    globalError = 0;
  }
}

int prox() {
  int proximity;
   if (APDS.proximityAvailable()) {
      proximity = APDS.readProximity();
      return proximity;
   }
}
void allWhiteProcedure () {
  delay(70);
  if (!checkCurrentValuesForWhite()) drive();

  // Side sensor checks
  else if (sideRight && !sideLeft) { //    else if (sideRight && checkCurrentValuesForWhite()) {
    while (checkCurrentValuesForWhite()) {
      analogWrite(right_brake, 255);
      leftMotor.drive(255);
    }
    analogWrite(right_brake, 0);
    drive();
  }
  
  else if (!sideRight && sideLeft) {
     while (checkCurrentValuesForWhite()) {
      analogWrite(left_brake, 255);
      rightMotor.drive(255);
     }
     analogWrite(left_brake, 0);
     drive();
  }
}
char getColor() {
  int r, g, b;
  while (! APDS.colorAvailable()) {
    //delay(5);
  }
  APDS.readColor(r, g, b);
  
       if (r > g && r > b) return 'R';
  else if (g > r && g > b) return 'G';
  else if (b > g && b > r) return 'B';
  
  else return 'E';
}

int I(int prod) {
  static int a = 0;
  long int error = 0;

  if (prod == 60000) {
    a = 0;
    error = 0;
  }
  
  error += prod;
  a ++;
  return error / a;
}
