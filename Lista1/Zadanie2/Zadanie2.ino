const int led_pin = 5;
const int ldr_pin = 0;
const int left_pin = 2;
const int right_pin = 13;

#define LDR A0
#define LED 5
#define LEFT 2
#define RIGHT 13

int ldr_min = 0;
int ldr_max = 1023;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
}
 
void loop()
{
  int ldr = analogRead(LDR);

  if(digitalRead(LEFT) == HIGH) ldr_min = ldr;
  if(digitalRead(RIGHT)  == HIGH) ldr_max = ldr;

  analogWrite(LED, map(constrain(ldr, ldr_min, ldr_max), ldr_min, ldr_max, 255, 0));
  delay(10);
}