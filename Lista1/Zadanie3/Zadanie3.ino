// We're using a Common Anode RGB LED, thus colour values are reversed (255 is no light, 0 is full light)
#define MAXLIGHT 1
#define MINLIGHT 255

#define RED 9
#define GREEN 10
#define BLUE 11

short colors;
unsigned short value;
bool rise = false;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT); 

  analogWrite(GREEN, MINLIGHT);
  analogWrite(BLUE, MINLIGHT);
  analogWrite(RED, MINLIGHT);

  randomSeed(analogRead(0));
  colors = random(1, 8);
  value = 255;
}

void decode(short colors, unsigned short value){
    if(colors & 1) analogWrite(RED, value);
    if(colors & 2) analogWrite(GREEN, value);
    if(colors & 4) analogWrite(BLUE, value);
}
 
void loop()
{
  value = rise ? value << 1 | 1 : value >> 1;

  if(value == MAXLIGHT || value == MINLIGHT) rise = !rise;

  decode(colors, MINLIGHT - value);

  // Rerolling the colour after each cycle, remember that colour values are reversed
  if (value == MAXLIGHT) {
    colors = random(1, 8);
  }
    
    delay(100);
}