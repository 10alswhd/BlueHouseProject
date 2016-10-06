int soundPin = 8;
int ledPin = 6;
int min1 = 0;
int max1 = 500;

int min2 = 100;
int max2 = 1000;
int zzz = 2;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}


void loop() {
 long b = random(0,2);
 int factor = 1;
 if (b == 0) {
   factor = 1;
 } else {
  factor = -1; 
 }
 long start = random(min1, max1);
 long ende = random(min2, max2);

 if (factor == 1) {
    for (long i=start; i<=ende; i++) {
    tone(soundPin, i);
    updateLed(i);
    delay(zzz);
  }
 } else {
    for (long i=ende; i>=start; i--) {
    tone(soundPin, i);
    updateLed(i);
    delay(zzz);
  }
 }
}


void updateLed(float value) {
  float n = max2;
  float result = value / n;
  float analogValue =  result * 256;
  int iValue = analogValue;
  analogWrite(ledPin, analogValue);
}
