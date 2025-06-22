//NAME: malak fathy abdelaal 
//ID: 20237014

//Right Motor
#define Rightmotorsp 10 // Enable1 L289 pin enA (pin connected to the right motor) (controls the speed of the motors by connecting it to a PWM Arduino pin)//
#define RightmotorDirecB 9  // Motor 1 L289 pin in1 (right motor) (controls the direction of the wheel) (anticlockwise/ BACKWARD)//
#define RightmotorDirecF 8  // Motor 1 L289 pin in2 (right motor) (controls the direction of the wheel) (clockwise/ FORWARD)//
//Left Motor
#define LeftmotorDirecB 7  // Motor 2 L289 pin in3 (left motor) (controls the direction of the wheel) (anticlockwise)//
#define LeftmotorDirecF 6  // Motor 2 L289 pin in4 (left motor) (controls the direction of the wheel) (clockwise)//
#define Leftmotorsp 5  // Enable2 L289 pin enB (pin connected to the left motor) (controls the speed of the motors by connecting it to a PWM Arduino pin)//
//Ir Sensors
#define RSensors A0 // Ir left sensor
#define LSensors A4 // Ir right sensor
#define CSensors1 A2 // Ir center sensors
#define CSensors2 A3 // Ir center sensors
//Utrasonic
#define Echo 11 // Ultrasonic echo pin//
#define Trig 3 // Ultrasonic trigger pin//

void setup() {
  pinMode(LSensors, INPUT); //declare Ir left sensor as a digital input signal for Arduino// 
  pinMode(RSensors, INPUT); //declare Ir right sensor as a digital input signal for Arduino//
  pinMode(CSensors1, INPUT); //declare Ir center sensor1 as a digital input signal for Arduino// 
  pinMode(CSensors2, INPUT); //declare Ir center sensor2 as a digital input signal for Arduino// 

  pinMode(10, OUTPUT); //declare as an output for L289 pin enA//
  pinMode(9, OUTPUT); //declare as an output for L289 pin IN1//
  pinMode(8, OUTPUT); //declare as an output for L289 pin IN2//
  pinMode(5, OUTPUT); //declare as an output for L289 pin enB//
  pinMode(7, OUTPUT); //declare as an output for L289 pin IN3//
  pinMode(6, OUTPUT); //declare as an output for L289 pin IN4//

  pinMode(11, INPUT); // Ultrasonic echo pin//
  pinMode(3, OUTPUT); // Ultrasonic trigger pin//

  Serial.begin(9600);
}

void moveForward() {
  digitalWrite(9, LOW); // Right motor backward direction
  digitalWrite(8, HIGH);// Right motor forward direction
  analogWrite(10,50); // Right motor speed

digitalWrite(7, LOW); // Left motor backward direction
digitalWrite(6, HIGH);// Left motor forward direction
analogWrite(5,50);// left motor speed
}

void turnLeft() {
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  analogWrite(10,50);

digitalWrite(7, HIGH);
digitalWrite(6, LOW);
analogWrite(5,40); // slowed the left motor and increased the right motor speed to make it turn left
}

void turnRight() {
digitalWrite(9, HIGH);
digitalWrite(8, LOW);
analogWrite(10,40);

digitalWrite(7, LOW);
digitalWrite(6, HIGH);
analogWrite(5,50); // slowed the right motor and increased the right motor speed to make it turn right
}

void stopMotors() {
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
analogWrite(10,50);
analogWrite(5,50);
}

void loop() {
  int rightIRSensorValue = digitalRead(RSensors);
  int centerIRSensorValue1 = digitalRead(CSensors1);
  int centerIRSensorValue2 = digitalRead(CSensors2);
  int leftIRSensorValue = digitalRead(LSensors);

  // obstacle avoidance by ultrasonic
  double duration = 0.0;
  double distance = 0.0;

  digitalWrite(Trig, LOW); //set trigger pin to low to make sure that the pin doesn't have noise
  delayMicroseconds(2); //enable module

  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo, HIGH); //return duration in microseconds
  distance = duration * 0.034 / 2.0;

  if (distance < 20) {  //if obstacle is near the car by less than 20cm, the car will stop//
    stopMotors();
    delay(1000); // Wait for one second
  }

   else
{
  
if (leftIRSensorValue ==HIGH && centerIRSensorValue1 == LOW && centerIRSensorValue2 == LOW &&
    rightIRSensorValue == HIGH) {
    moveForward();
  }

  // left case (the left sensor sees black and the right sensor see black and the center see white)//
  else if (leftIRSensorValue == HIGH && centerIRSensorValue1 == LOW && centerIRSensorValue2 == LOW &&
   rightIRSensorValue== HIGH) {
    turnLeft();
  }

 // right case (the left sensor sees black and the right sensor sees white and the center sees white)//
  else if (leftIRSensorValue == HIGH && centerIRSensorValue1 == LOW && centerIRSensorValue2 == LOW &&
   rightIRSensorValue == LOW) {
    turnRight();
  }
  else if (leftIRSensorValue == HIGH && centerIRSensorValue1 == HIGH && centerIRSensorValue2 == HIGH &&
rightIRSensorValue == HIGH)
{
stopMotors();
}
  else if (leftIRSensorValue == LOW && centerIRSensorValue1 == LOW && centerIRSensorValue2 == LOW &&
rightIRSensorValue == LOW){
stopMotors(); 
}
}
}
