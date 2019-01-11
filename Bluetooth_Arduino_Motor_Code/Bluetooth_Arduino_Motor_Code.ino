#include <Servo.h>

Servo myservo1;

char unChar;
int angle = 90;
int change = 2;
String readString;

int Motor_A_Enable = 9;
int Motor_A_Reverse = 2;
int Motor_A_Forward = 3;

int Motor_B_Enable = 10;
int Motor_B_Reverse = 5;
int Motor_B_Forward = 4;

void setup() {
 
 myservo1.attach(13);
 myservo1.write(90);
 
  Serial.begin(9600);
  
  pinMode(Motor_A_Enable, OUTPUT);
  pinMode(Motor_A_Forward, OUTPUT);
  pinMode(Motor_A_Reverse, OUTPUT);

  pinMode(Motor_B_Enable, OUTPUT);
  pinMode(Motor_B_Forward,  OUTPUT);
  pinMode(Motor_B_Reverse, OUTPUT);
}

void loop() {

  int speed=150;
  
  if(Serial.available() > 0){
    char data;
    data = Serial.read();
    Serial.write(Serial.read());

    switch (data){

      case '0': //dur
        analogWrite(Motor_A_Enable, 0);
        analogWrite(Motor_B_Enable, 0);
        analogWrite(Motor_A_Forward, 0);
        analogWrite(Motor_B_Forward, 0);
        analogWrite(Motor_A_Reverse, 0);
        analogWrite(Motor_B_Reverse, 0);
      break;
      
      case '1': //ileri
        analogWrite(Motor_A_Enable, 100);
        analogWrite(Motor_B_Enable, 100);
        analogWrite(Motor_A_Forward, speed);
        analogWrite(Motor_B_Forward, speed);
        analogWrite(Motor_A_Reverse, 0);
        analogWrite(Motor_B_Reverse, 0);
      break;
        
      case '2': //geri
        analogWrite(Motor_A_Enable, 100);
        analogWrite(Motor_B_Enable, 100);
        analogWrite(Motor_A_Forward, 0);
        analogWrite(Motor_B_Forward, 0);
        analogWrite(Motor_A_Reverse, speed);
        analogWrite(Motor_B_Reverse, speed);
      break;
        
      case '3': //sol
        analogWrite(Motor_A_Enable, 100);
        analogWrite(Motor_B_Enable, 100);
        analogWrite(Motor_A_Forward, 0);
        analogWrite(Motor_B_Forward, speed);
        analogWrite(Motor_A_Reverse, speed);
        analogWrite(Motor_B_Reverse, 0);
      break;
        
      case '4': //sağ
        analogWrite(Motor_A_Enable, 100);
        analogWrite(Motor_B_Enable, 100);
        analogWrite(Motor_A_Forward, speed);
        analogWrite(Motor_B_Forward, 0);
        analogWrite(Motor_A_Reverse, 0);
        analogWrite(Motor_B_Reverse, speed);
      break;

      case '5': //kıskacı aç
      readString += data; 
        if (readString.length() > 0) {
          Serial.println(0);
          myservo1.write(180);
          readString = "";
        }
      break;

      case '6': //kıskacı kapat
      readString += data; 
        if (readString.length() > 0) {
          Serial.println(0);
          myservo1.write(87);
          readString = "";
        }
      break;
        
    }
  }
  
}
