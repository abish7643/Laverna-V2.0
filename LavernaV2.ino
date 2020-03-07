#include <Button.h>
#include <QTRSensors.h>
#include <Wire.h>

Button button = Button(13, BUTTON_PULLUP_INTERNAL); // Pin 8 - Button

QTRSensors qtrrc;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

int pinButton = 13; // Button PIN
int inA1 = A0;     // Dual H-Bridge pins
int inA2 = A1;
int inB1 = A2;
int inB2 = A3;
int ENa = 11;       // Enable Pins
int ENb =10;
int Sty = 12;

int last_proportional; //(PID Variables)
int integral;

void setup(){
  qtrrc.setTypeRC(); //Call the fuction specifying the type of sensor, setTypeRC for QTR-xRC
  qtrrc.setSensorPins((const uint8_t[]){2, 3, 4, 5, 6, 7, 8, 9}, SensorCount); //the 5 sensor inputs 25, 27, 29, 31, 33
  qtrrc.setEmitterPin(12); //LEDON Pin - 22
  Serial.begin(9600);
  while(button.isPressed()){    
  }
  
  Serial.println("Calibrating");   
  unsigned int i;
  for(i=0; i<130; i++){
    qtrrc.calibrate();
    delay(10); 
  }
  set_motors(0,0);
  delay(500);
}

void loop(){
  while(button.isPressed()){
  }
  delay(500);
  
  while(1){
    unsigned int position = qtrrc.readLineBlack(sensorValues); //the sensorValues is given as argument to the function readLineBlack or readLineWhite
    int proportional = ((int)position) - 3500;
    int derivative = proportional - last_proportional;
    integral += proportional;
    last_proportional = proportional;
    int m_power_difference = proportional/10 + integral/10000 + derivative*3/2;
    int power_difference = (m_power_difference);
    
    const int max = 160;
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
  }
  if(right_speed >= 0 && left_speed < 0){
    left_speed = -left_speed;
    analogWrite(ENa, right_speed);
    analogWrite(ENb, left_speed);
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
  }
  if(right_speed < 0 && left_speed >= 0){
    right_speed = -right_speed;
    analogWrite(ENa, right_speed);
    analogWrite(ENb, left_speed);
    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, LOW);
    digitalWrite(inB2, HIGH);
  } 
}
void readWhiteorBlack(){
  
    if(((sensorValues[0] < 1500) || (sensorValues[1] < 1500 ) && ((sensorValues[6] <1500) || (sensorValues[7] < 1500)) && ((sensorValues[3] < 2200) || (sensorValues[4] > 2200)))){
    unsigned int position = qtrrc.readLineBlack(sensorValues); //the sensorValues is given as argument to the function readLineBlack or readLineWhite
    return position;
    Serial.println("Black Line");
  }
    else if(((sensorValues[0] > 2200) || (sensorValues[1] > 2200 ) && ((sensorValues[6] > 2200) || (sensorValues[7] > 2200)) && ((sensorValues[3] < 1500) || (sensorValues[4] < 1500)))){
    unsigned int position = qtrrc.readLineWhite(sensorValues); //the sensorValues is given as argument to the function readLineBlack or readLineWhite
    return position;
    Serial.println("White Line");
  }
 }
