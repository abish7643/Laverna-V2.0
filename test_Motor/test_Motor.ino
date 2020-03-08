int inA1 = A0;
int inA2 = A1;
int inB1  = A2;
int inB2 = A3;
int ENa = 10;
int ENb =11;
//int Sty = 12;


void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:
//   digitalWrite(Sty, HIGH);
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
    analogWrite(ENa, 255);
    analogWrite(ENb, 255);
  
}
