typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv;

rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

#define MAXLIGHT 1
#define MINLIGHT 255

#define RED 9
#define GREEN 10
#define BLUE 11

short colors;
unsigned short value;
bool rise = true;

hsv target;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT); 

  analogWrite(GREEN, MINLIGHT);
  analogWrite(BLUE, MINLIGHT);
  analogWrite(RED, MINLIGHT);

  randomSeed(analogRead(0));

  target.h = 0.0;
  target.s = 1.0;
  target.v = 0.6;
}

void display(rgb col){
    analogWrite(RED, MINLIGHT - col.r * 255);
    analogWrite(GREEN, MINLIGHT - col.g * 255);
    analogWrite(BLUE, MINLIGHT - col.b * 255);
}
 
void loop()
{
  target.h += 0.1;

  if (target.h >= 360) target.h -= 360;

  display(hsv2rgb(target));

  delay(1);
}


