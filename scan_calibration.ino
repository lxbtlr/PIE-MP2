int samples[] = {0,0,0,0};
#define analogPin A1
int value = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int scan() {
  samples[0] = analogRead(analogPin);
  samples[1] = analogRead(analogPin);
  samples[2] = analogRead(analogPin);
  samples[3] = analogRead(analogPin);
  value = min(samples[0],samples[1]);
  value = min(value, samples[2]);
  value = min(value, samples[3]);
  return value;
}

void loop() {
  int i = 0;
  float scans = 0;
  while (i < 25) {
    scans += scan();
    i++;
//    Serial.println(scan());
  }
  Serial.println(scans / 25);
//  delay(5000);
}
