#include <Button.h>
#include <QTRSensors.h>
#include <Wire.h>

Button button = Button(13, BUTTON_PULLUP_INTERNAL);

QTRSensors qtrrc;
QTRSensors qtrEnd;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
const uint8_t EndSensorCount = 2;
uint16_t endsensorValues[EndSensorCount];

//#define LeftMostSensor 2
//#define RightMostSensor 9

int pinButton = 13; 
int inA1 = A0;
int inA2 = A1;
int inB1  = A2;
int inB2 = A3;
int ENa = 10;
int ENb =11;

int last_proportional = 0;
int integral;
int readPIDConstants = 0;

int blackLine = 1;
//int whiteLine = 0;

//Black Line
float Kp = 0.1;
float Kd = 0.5;
float Ki = 1/10000;

unsigned int position;

/*
//White Line
float Kp = 5.50;
float Kd = 9.45;
float Ki = 1/10000;
*/
//#define Kp 7
//#define Kd 3
//#define Ki 1/10000
#define analogKp A7
#define analogKd A6
#define statusLED 12
#define invertionstatusLED A5

void setup(){
  //Serial.begin(9600);
  qtrrc.setTypeRC();
  qtrrc.setSensorPins((const uint8_t[]){3, 4, 5, 6, 7, 8}, SensorCount);
  qtrEnd.setTypeRC();
  qtrEnd.setSensorPins((const uint8_t[]){2, 9}, EndSensorCount);
  //qtrrc.setEmitterPin(12); //LEDON Pin - 22

  while(button.isPressed()){
    digitalWrite(statusLED, HIGH);
  }
  digitalWrite(statusLED, LOW);
  //Serial.println("Calibrating");   
  
  unsigned int i;
  for(i=0; i<150; i++){
    qtrrc.calibrate();
    delay(10); 
  }
  set_motors(0,0);
  //Serial.println("Calibrated");
  delay(500);
  
}


void loop(){
  while(button.isPressed()){
    digitalWrite(statusLED, HIGH);
  }
    delay(500);
    //checkPIDValues(readPIDConstants);
    
  while(1){
    digitalWrite(statusLED, LOW);
    qtrEnd.read(endsensorValues);
    /*
    for (int i=0; i<6; i++){
      Serial.print(sensorValues[i]);
      Serial.print(' ');
      }
    Serial.println(' ');
    */
    /*unsigned int positionSharp = qtrEnd.readLineBlack(endsensorValues);
    for (int i=0; i<2; i++){
      Serial.print(endsensorValues[i]);
      Serial.print(' ');
      }
    Serial.println(' ');
    */
    //checkInversion(endsensorValues, sensorValues);
    putLineState(blackLine);
    turnHandlerWithoutPID(endsensorValues, sensorValues, position);
    //turnHandlerWithoutPIDWhiteLine(endsensorValues, sensorValues, position);
    /*
    if (blackLine == 1){
      //checkAcuteBlackLine(position, endsensorValues);
      if (position == 0){
      set_motors(-70, 70);
      delay(20);
      }
      if (position == 5000){
      set_motors(70, -70);
      delay(20);
      }
    }
    if (blackLine == 0){
      //checkAcuteWhiteLine(position, endsensorValues);
      if (position == 0){
        set_motors(-80, 80);
        delay(20);
        }
  
      if (position == 5000){
        set_motors(80, -80);
        delay(20);
        }
    }
    */
      
    int proportional = (int(position)) - 2500;
    //Serial.println(position);
    int derivative = proportional - last_proportional;
    integral += proportional;
    int power_difference = Kp * (proportional) + Kd * (derivative) + Ki * (integral);
    last_proportional = proportional;
    
    //Black Line
    //int power_difference = proportional*1.4 + derivative*3 + integral/10000; // + derivative*200;    
    //White Line
    //int power_difference = proportional*7 + derivative*8 + integral/10000;
    
    
    
    //fastNinety(position);
    //checkAcuteWithCount(position);
    //checkAcuteWithEndSensors(position, endsensorValues);
    //Serial.println(power_difference);  
    const int max = 100;
    if(power_difference > max)
      power_difference = max;
    if(power_difference < -max)
      power_difference = -max;
    if(power_difference < 0)
      set_motors(max+power_difference, max);
    else
      set_motors(max, max-power_difference);
  }
}

void set_motors(int left_speed, int right_speed){
  if(right_speed >= 0 && left_speed >= 0){
    analogWrite(ENa, right_speed);
    analogWrite(ENb, left_speed);
    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
    //Serial.println("Straight");    
  }
  if(right_speed >= 0 && left_speed < 0){
    left_speed = -left_speed;
    analogWrite(ENa, right_speed);
    analogWrite(ENb, left_speed);
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
    //Serial.println("Left");
  }
  if(right_speed < 0 && left_speed >= 0){
    right_speed = -right_speed;
    analogWrite(ENa, right_speed);
    analogWrite(ENb, left_speed);
    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, LOW);
    digitalWrite(inB2, HIGH);
    //Serial.println("Right");
  } 
}


void checkAcute(int positionLine){
  int turnOppositeA = 0;
  if (positionLine == 0) {
      if (turnOppositeA == 0){
        set_motors(-70, 70);
        delay(500);
        if (positionLine == 0){
          turnOppositeA = 1;
          if (positionLine == 0 && turnOppositeA == 1){
            set_motors(70, -70);
            delay(800);
            turnOppositeA == 0;
          }
        }
      }
      //Serial.println("postion 0");
  }
}

void checkAcuteWithCount(int positionLine){
  //int turnOppositeA = 0;
  if (positionLine == 0) {
    int count = 0;
    for (count=0; positionLine = 0; count++){
      set_motors(-70, 70);
      delay(20);
      if (count == 5 && positionLine == 0){
        for (int countOpposite=0; positionLine = 0; countOpposite++){
          set_motors(70, -70);
          delay(20);
          if (countOpposite == 8) {
            break;
            }
          }
        }
      }
    }
  }

void checkAcuteBlackLine(int positionLine, int ValueofEndSensors[2]){
    if (ValueofEndSensors[1] >= 2000 && ValueofEndSensors[0] <= 1000){
      if (positionLine > 2000 && positionLine < 3000) {
          //Serial.println("Acute Right Triggered");
          set_motors(90, -100);
          delay(110);
        }
      }

    if (ValueofEndSensors[0] >= 2000 && ValueofEndSensors[1] <= 1000){
      if (positionLine > 2000 && positionLine < 3000) {
          //Serial.println("Acute Left Triggered");
          set_motors(-100, 90);
          delay(110);   
        }
      }
  }

  
void checkAcuteWhiteLine(int positionLine, int ValueofEndSensors[2]){
    if (ValueofEndSensors[0] >= 2000 && ValueofEndSensors[1] <= 1000){
      if (positionLine > 2000 && positionLine < 3000) {
          //Serial.println("Acute Right Triggered");
          set_motors(90, -90);
          delay(100);
        }
      }

    if (ValueofEndSensors[1] >= 2000 && ValueofEndSensors[0] <= 1000){
      if (positionLine > 2000 && positionLine < 3000) {
          //Serial.println("Acute Left Triggered");
          set_motors(-90, 90);
          delay(100);   
        }
      }
  }

void checkInversion(int endSensors[2], int otherSensors[6]){
  if (endSensors[0] < 1000 && endSensors[1] < 1000){
      if (otherSensors[2] > 500 && otherSensors[3] > 500) {
        blackLine = 1;
        }
    }
    if (endSensors[0] > 1000 && endSensors[1] > 1000){
      if (otherSensors[2] < 500 && otherSensors[3] < 500) {
        blackLine = 0;
        }
    }}

void putLineState(int lineState){
  if (lineState == 1){
      position = qtrrc.readLineBlack(sensorValues);
      digitalWrite(invertionstatusLED, LOW);
      //Serial.println("BlackLine");
    } else {
      position = qtrrc.readLineWhite(sensorValues);
      digitalWrite(invertionstatusLED, HIGH);
      //Serial.println("WhiteLine");
      }
  }

void checkPIDValues(int ReadState){
  if (ReadState == 0){
      const int p = analogRead(analogKp);
      const int d = analogRead(analogKd);
      const float KP = map(p, 0, 1023, 1, 200);
      const float KD = map(d, 0, 1023, 1, 200);
      Kp = KP/20;
      Kd = KD/20;
      //Serial.print("  Kp : ");
      //Serial.print(Kp);
      //Serial.print("  Kd : ");
      //Serial.print(Kd);
      //Serial.println(" ");
      readPIDConstants = 1;
  }
}
int turn; //Left = 1 & Right = 2
int numberWhiteSensors = 0;
int highestValue;
int LeftendSensor;
int RightendSensor;
void turnHandlerWithoutPID(int endSensors[2], int otherSensors[6], int linePosition){
  LeftendSensor = endSensors[0];
  RightendSensor = endSensors[1];
  if (blackLine == 1){
    if (LeftendSensor >= 800 && RightendSensor <= 800) {
      turn = 1;
      //Serial.println("ReadytoTurnLeft");
      //Serial.print(LeftendSensor);
    }
    if (RightendSensor >= 800 && LeftendSensor <= 800) {
      turn = 2;
      //Serial.println("ReadytoTurnRight");
      //Serial.print(RightendSensor);
    }
    for (int i = 0; i <= 6; i++){
      if (otherSensors[i] < 500){
       numberWhiteSensors++;
      }else{
       numberWhiteSensors = 0;
      }
    }
    if (numberWhiteSensors >= 6){
      numberWhiteSensors = 6;
      }
    //Serial.println(numberWhiteSensors);
    if (numberWhiteSensors == 6){
      if (turn==1){
        set_motors(-70, 70);
        digitalWrite(statusLED, HIGH);
        delay(40);
        if (endSensors[0] > 800 || otherSensors[0] > 350){
          turn = 0;
          digitalWrite(statusLED, LOW);
        }
        //Serial.println("LeftTurnWithoutPID");
        }
      if (turn==2){
        set_motors(70, -70);
        digitalWrite(statusLED, HIGH);
        delay(40);
        if (endSensors[1] > 800 || otherSensors[5] > 350){
          turn = 0;
          digitalWrite(statusLED, LOW);
        }
        //Serial.println("RightTurnWithoutPID");
        }
      }
    }
  }
void turnHandlerWithoutPIDWhiteLine(int endSensors[2], int otherSensors[6], int linePosition){
  if (blackLine == 0){
    if (LeftendSensor <= 1000 && RightendSensor >= 1000) {
      turn = 1;
      //Serial.println("ReadytoTurnLeft");
      //Serial.print(LeftendSensor);
    }
    if (RightendSensor <= 1000 && LeftendSensor >= 1000) {
      turn = 2;
      //Serial.println("ReadytoTurnRight");
      //Serial.print(RightendSensor);
    }
    for (int i = 0; i <= 6; i++){
      if (otherSensors[i] > 500){
       numberWhiteSensors++;
      }else{
       numberWhiteSensors = 0;
      }
    }
    if (numberWhiteSensors >= 6){
      numberWhiteSensors = 6;
      }
    //Serial.println(numberWhiteSensors);
    if (numberWhiteSensors == 6){
      if (turn==1){
        set_motors(-100, 100);
        delay(20);
        if (endSensors[0] < 1200 || otherSensors[0] < 500){
          turn = 0;
        }
        //Serial.println("LeftTurnWithoutPID");
        }
      if (turn==2){
        set_motors(100, -100);
        delay(20);
        if (endSensors[0] < 1200 || otherSensors[0] < 500){
          turn = 0;
        }
        //Serial.println("RightTurnWithoutPID");
        }
      }
    }
  }
