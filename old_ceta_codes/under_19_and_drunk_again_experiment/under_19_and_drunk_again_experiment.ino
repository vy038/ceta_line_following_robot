/* Line Following Test - Written by Victor Yu
Created: 2024-01-10
Modified: 2024-04-12
Purpose: To create the fastest line following robot with 4 QTI sensors, turning when they detect black
*/

// declare constants for motor pins, QTI pins, and LED pins
const int Rightsensor = 2, Leftsensor = 3;
const int LMotor_pin1 = 6, LMotor_pin2 = 5;
const int RMotor_pin1 = 9, RMotor_pin2 = 10;
const int FarLeftsensor = 11, FarRightsensor = 12;
const int FFLeftsensor = 8, FFRightsensor = 7;
const int forwardSpeed = 250;

void setup(){
  // set motor pins as OUTPUTS
  pinMode(LMotor_pin1, OUTPUT);
  pinMode(LMotor_pin2, OUTPUT);
  pinMode(RMotor_pin1, OUTPUT);
  pinMode(RMotor_pin2, OUTPUT);
  
  // set the QTI sensor pins as INPUTS:
  pinMode(Leftsensor, INPUT);
  pinMode(Rightsensor, INPUT);
  pinMode(FarRightsensor, INPUT);
  pinMode(FarLeftsensor, INPUT);
  pinMode(FFRightsensor, INPUT);
  pinMode(FFLeftsensor, INPUT);
}

void loop(){
  // read all sensor values and create boolean value for each
  bool Left_sensorValue = digitalRead(Leftsensor);
  bool Right_sensorValue = digitalRead(Rightsensor);
  bool FarLeft_sensorValue = digitalRead(FarRightsensor);
  bool FarRight_sensorValue = digitalRead(FarLeftsensor);
  bool FFLeft_sensorValue = digitalRead(FFLeftsensor);
  bool FFRight_sensorValue = digitalRead(FFRightsensor);

  // if inner left sensor is black and right is white, make a minor left turn
  if ((Left_sensorValue == 1) && (Right_sensorValue == 0)){
    TURN(0);
  }
  // if both sensors detect white move forward
  else if ((Left_sensorValue == 0) && (Right_sensorValue == 0)){
    FORWARD(1);
  }
  // if left sensor is white and right is black, make a minor right turn
  else if ((Left_sensorValue == 0) && (Right_sensorValue == 1)){
    TURN(1);
  }
  // if both sensors are black, then stop
  else if ((Left_sensorValue == 1) && (Right_sensorValue == 1) && (FarLeft_sensorValue == 1) && (FarRight_sensorValue == 1)) {
   FORWARD(0);
  }

  if ((FarLeft_sensorValue == 1) && (FarRight_sensorValue == 0)){ //if far sensor right detects black
    MIDTURN(0); //make fast right turn
  } 
  
  if ((FarLeft_sensorValue == 0) && (FarRight_sensorValue == 1)){ //if far left sensor detects black
    MIDTURN(1); //make fast left turn
  }

  if ((FFLeft_sensorValue == 1) && (FFRight_sensorValue == 0)){ //if far sensor right detects black
    FARTURN(1); //make fast right turn
  } 
  
  if ((FFLeft_sensorValue == 0) && (FFRight_sensorValue == 1)){ //if far left sensor detects black
    FARTURN(0); //make fast left turn
  }
  delay(5); //small delay to save resources
}

void FORWARD(int boolean) { //forward function

  //Left motor turn forward if boolean int is 1
    analogWrite(LMotor_pin1, boolean*(forwardSpeed+5));  
    analogWrite(LMotor_pin2, 0); 

  //Right motor turn forward if boolean int is 1
    analogWrite(RMotor_pin1, boolean*forwardSpeed);  
    analogWrite(RMotor_pin2, 0);
}

void TURN(int dir) { //minor turn function
    if (dir == 1) { //if int is 1, make minor right turn

      //Left motor turn slightly backwards
      analogWrite(LMotor_pin1, 70);  
      analogWrite(LMotor_pin2, 0); 
  
      //Right motor forward full speed
      analogWrite(RMotor_pin1, 255);
      analogWrite(RMotor_pin2, 0);

    } else { //if int is 0, make minor left turn
      
      //left motor forward full speed
      analogWrite(LMotor_pin1, 255);  
      analogWrite(LMotor_pin2, 0);  

      //right motor backwards slow
      analogWrite(RMotor_pin1, 70);
      analogWrite(RMotor_pin2, 0);
    }
    
}

void MIDTURN(int dir) { //very fast turn function
    if (dir == 1) { //if int is 1, make fast right turn
      //left motor backwards full speed
      analogWrite(LMotor_pin1, 255);  
      analogWrite(LMotor_pin2, 0); 

      //Right motor forward full speed
      analogWrite(RMotor_pin1, 0);
      analogWrite(RMotor_pin2, 0);
    } else { //if int is 0, make fast left turn
      //left motor full speed forward
      analogWrite(LMotor_pin1, 0);  
      analogWrite(LMotor_pin2, 0); 

      //Right motor full speed backwards
      analogWrite(RMotor_pin1, 255);
      analogWrite(RMotor_pin2, 0);

    }
    
}

void FARTURN(int dir) { //very fast turn function
    if (dir == 1) { //if int is 1, make fast right turn
      //left motor backwards full speed
      analogWrite(LMotor_pin1, 255);  
      analogWrite(LMotor_pin2, 0); 

      //Right motor forward full speed
      analogWrite(RMotor_pin1, 0);
      analogWrite(RMotor_pin2, 255);
    } else { //if int is 0, make fast left turn
      //left motor full speed forward
      analogWrite(LMotor_pin1, 0);  
      analogWrite(LMotor_pin2, 255); 

      //Right motor full speed backwards
      analogWrite(RMotor_pin1, 255);
      analogWrite(RMotor_pin2, 0);

    }
    
}