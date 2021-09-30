#include <Servo.h>
int samples[] = {0,0,0};
int analogPin = A1;
int value = 0;
int pan_min = 0;
int pan_max = 40;
int tilt_min = 13;
int tilt_max = 45;
int pan;
int tilt;
int tbs = 30;

int panPin = 9;
int tiltPin = 10;
Servo pan_servo;
Servo tilt_servo;
float temp = 0;
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


void scan(int p, int t) {
  temp = 0;
  // put your main code here, to run repeatedly:
  for(int i = 0; i <20; i++){
    temp += analogRead(analogPin);
    temp = temp/2;
    }
  Serial.print(p);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(temp);
  Serial.print("L");
}
