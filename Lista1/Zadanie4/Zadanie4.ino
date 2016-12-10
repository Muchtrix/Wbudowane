#define BUZZER 13
#define LED 4
#define SENSOR 0
#define BUTTON 2

int magnet;
bool victory;

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  reset();
}

void loop() {
  int value = analogRead(SENSOR);
  victory = abs(value-magnet) <= 20;
  if (abs(value-magnet) <= 20) {
    digitalWrite(LED,HIGH);
    tone(BUZZER, 6000, 1000);
  }
  else {
    delay(abs(value-magnet)*3);
    tone(BUZZER, 6000, 100);
    delay(1000);
  }

  if(digitalRead(BUTTON) == HIGH) reset();

}

void reset(){
  victory = false;
  digitalWrite(LED,LOW);
  magnet = random(0,1024);
}
