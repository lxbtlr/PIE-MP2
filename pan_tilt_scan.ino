#include <Servo.h>
#include <stdio.h>
#include <stdlib.h>
int samples[] = {0,0,0};
int analogPin = A1;
int value = 0;
int pan_min = 0;
int pan_max = 40;
int tilt_min = 20;
int tilt_max = 20;
int pan;  
int tilt;
int tbs = 250;

int panPin = 9;
int tiltPin = 10;
Servo pan_servo;
Servo tilt_servo;
double temp[20] = {};
float avg = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(analogPin, INPUT);
  pan_servo.attach(panPin);
  tilt_servo.attach(tiltPin);
  
}

void loop() {
  pan_servo.write(pan_min);
  tilt_servo.write(tilt_min);
  for (pan = pan_min; pan <= pan_max; pan +=1) {
    pan_servo.write(pan);
    delay(tbs);
    for (tilt = tilt_min; tilt <= tilt_max; tilt +=1) {
      tilt_servo.write(tilt);
      delay(tbs);
      scan(pan, tilt);
    }
    pan+= 1;
    pan_servo.write(pan);
    delay(tbs);
    for (tilt = tilt_max; tilt >= tilt_min; tilt -= 1) {
      tilt_servo.write(tilt);
      delay(tbs);
      scan(pan, tilt);
    }
  }
  delay(1000);
  Serial.println();
  Serial.println("DONE");
  delay(6000);
}

int compfunc (const void * a, const void * b) {
  return ( *(int*) a - *(int*) b );
}

void scan(int p, int t) {
  avg = 0;
  // put your main code here, to run repeatedly:
  for(int i = 0; i <20; i++){
    temp[i] = analogRead(analogPin);
    delay(20);
    }
  qsort(temp, 20, sizeof(int), compfunc);
  for(int i = 0; i < 10; i++) {
    avg += temp[i+5]; 
  }
  avg = avg / 10;
  Serial.print(p);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(avg);
  Serial.print("L");
  delay(5);
}
