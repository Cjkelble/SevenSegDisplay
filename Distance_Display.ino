//www.elegoo.com
//2016.12.12

#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11

int latch = 9; //74HC595  pin 9 STCP
int clock = 10; //74HC595  pin 10 SHCP
int data = 8; //74HC595  pin 8 DS

int dig1 = 4; // anode for 1s digit
int dig2 = 3; // anode for 10s digit
int dig3 = 2; // anode for 100s digit
int dig4 = 5; // anode for 1000s digit

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

long a;


byte table[] =
{ B00111111, B00000110, B01011011, B01001111, B01100110,
  B01101101, B01111101, B00000111, B01111111, B01101111, B01111111
};


void setup() {
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
  pinMode(dig4, OUTPUT);
  Serial.begin(9600);
}
void Display(int num)
{

  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, table[num]);
  digitalWrite(latch, HIGH);

}

void D1 (int num, int timer)
{
  Display(num);
  digitalWrite(dig1, LOW);
  delayMicroseconds(timer);
  digitalWrite(dig1, HIGH);
}

void D2 (int num, int timer)
{
  Display(num);
  digitalWrite(dig2, LOW);
  delayMicroseconds(timer);
  digitalWrite(dig2, HIGH);
}
void D3 (int num, int timer)
{
  Display(num);
  digitalWrite(dig3, LOW);
  delayMicroseconds(timer);
  digitalWrite(dig3, HIGH);
}
void D4 (int num, int timer)
{
  Display(num);
  digitalWrite(dig4, LOW);
  delayMicroseconds(timer);
  digitalWrite(dig4, HIGH);
}

void erase()
{
  digitalWrite(dig1, HIGH);
  digitalWrite(dig2, HIGH);
  digitalWrite(dig3, HIGH);
  digitalWrite(dig4, HIGH);
}


void loop() {
  int timer = 2700;
  int ones, tens, hunds, thsnds;

  a = sr04.Distance();

  Serial.print(a);
  Serial.println("cm");

  if ( a <= 1000)

  {
    ones = (a % 10);
    tens = ((a / 10) % 10);
    hunds = ((a / 100) % 10);
    thsnds = (a / 1000);

    erase();

    D1(ones, timer);
    if (a >= 10)
    {
      D2(tens, timer);
    }
    if (a >= 100) {
      D3(hunds, timer);
    }
    if (a >= 1000)
    {
      D4(thsnds, timer);
    }

  }
  else {

    erase();

    D1(10, timer);
    D2(10, timer);
    D3(10, timer);
    D4(10, timer);
  }
}

