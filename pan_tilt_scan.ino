#include <Servo.h>
int samples[] = {0,0,0};
int analogPin = 12;
int value = 0;
int pan_min = 0;
int pan_max = 90;
int tilt_min = 0;
int tilt_max = 90;

int panPin = ;
int tiltPin = ;
Servo pan_servo;
Servo tilt_servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pan_servo.attach(panPin);
  tilt_servo.attach(tiltPin);
}

void loop() {
  pan_servo.write(pan_min);
  tilt_servo.write(tilt_min);
  for (pan = pan_min; pan <= pan_max; pan +=2) {
    pan_servo.write(pan);
    delay(10);
    for (tilt = tilt_min; tilt <= tilt_max; tilt ++) {
      tilt_servo.write(tilt);
      delay(10);
      scan(pan, tilt);
    }
    pan_servo.write(pan + 1);
    delay(10);
    for (tilt = tilt_max; tilt >= tilt_min; tilt -= 1) {
      tilt_servo.write(tilt);
      delay(10);
      scan(pan, tilt);
    }
  }
  Serial.println("DONE");
}

void scan(int p, int t) {
  // put your main code here, to run repeatedly:
  samples[0] = analogRead(analogPin);
  samples[1] = analogRead(analogPin);
  delay(1);
  samples[2] = analogRead(analogPin);
  samples[3] = analogRead(analogPin);
  value = min(samples[0],samples[1]);
  value = min(value, samples[2]);
  value = min(value, samples[3]);
  Serial.print(p);
  Serial.print(" ");
  Serial.print(t);
  Serial.print(" ");
  Serial.println(value);
}
