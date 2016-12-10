
#define BUTTON 2
#define LED 3

unsigned int buffer = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  unsigned int inp = digitalRead(BUTTON);
  digitalWrite(LED, buffer & 1 ? HIGH : LOW);
  buffer >>= 1;
  buffer |= inp << 15;
  delay(63);
}