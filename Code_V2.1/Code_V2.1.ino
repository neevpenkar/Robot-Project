//#include <E:\Ruppin College\Subjects\Thinking Skills\Robot\Code V2\Code_V2.1\class_headers.h>
//int Xright, Xleft;
//const float e = 2.71828;
//const int PWM_LEFT = 11, PWM_RIGHT = 3;
//const int DIR_RIGHT = 12, DIR_LEFT = 13;
//const int left_brake = 8, right_brake = 9; 
//
//Motor rightMotor(12, 3);
//Motor leftMotor(DIR_LEFT, PWM_LEFT);
//
//InfraRed rightSensor(A2, "Right");
//InfraRed leftSensor(A3, "Left");
//
//int f[8];
//int df[4];
//int ddf[2];
//void setup() {
//  Serial.begin(9600);
//  TCCR1B &= ~(1 << CS12);
//  TCCR1B |= (1 << CS11);
//  TCCR1B &= ~(1 << CS10);
//  pinMode(8, OUTPUT);
//  calibration();
//}
//
//void loop() {
//  int rightReading = rightSensor.TimedaverageFunction() - Xright;
//  int leftReading = leftSensor.TimedaverageFunction() - Xleft;
//
//  int delta = rightReading - leftReading;// Value of Delta is positive as the robot goes left, negative as it goes right
////  printValue("Delta", delta);
//
//  int bias = 90;
//
//  if (delta > 0) { // Going Left
//    leftMotor.drive(bias + reduction_function(delta));
//    rightMotor.drive(bias - reduction_function(delta));  
//  }
//  else if (delta < 0) { // Going Right
//    leftMotor.drive(bias - reduction_function(delta));
//    rightMotor.drive(bias + reduction_function(delta));
//  }
//  else {
//    leftMotor.drive(bias);
//    rightMotor.drive(bias);
//  }
////  delay(300);
//}
//void calibration() {
//  Xright = rightSensor.TimedaverageFunction();
//  Xleft = leftSensor.TimedaverageFunction();
//}
//void printValue(String name1, int val) {
//  Serial.print(name1 + " | ");
//  Serial.println(val);
//  Serial.println("----------------------------------");
//}
//int reduction_function(int x) {
//  x = abs(x);
//  int y;
//  
//  if (x >= 0 && x < 200) {
//    y = 100 * pow(-1 * pow(x - 100, 2), 3000);
//  }
//  else if (x >= 200 && x <= 350) {
//    y = 200 * pow(-1 * pow(x - 300, 2), 3000);
//  }
//  else if (x > 350) {
//    y = 12 * log(x - 350) + 135;
//  }
//  return y;
// }
//void bin () {
//  //  int y = (x + 1) / 8 + pow(2.7183, 0.0124 * x);
//  //  int y = 12 * sqrt(x);
//  //int y = 0.05*x*sqrt(x); 
//  //int y = log(pow(x, pow(2.72,3))); 
//  //int y = 30 * pow(x + 2, 0.33333);
//  //int y = 4.5 * pow(x + 2, 0.33333) * log(x);
//
//  //  Serial.print("Delta: ");
////  Serial.print(log(abs(delta) + 1));
////  Serial.print("    ");
////  Serial.print("Motor Value: ");
////  Serial.println(reduction_function(delta));
//////  delay(200);
//}
