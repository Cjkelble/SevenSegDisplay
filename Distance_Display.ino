// Created by Chris Kelble
// Loyola University Maryland Class of 2018
// Computer Engineering

// Shift register pins

int latch = 9; //74HC595  pin 9 STCP
int clock = 10; //74HC595  pin 10 SHCP
int data = 8; //74HC595  pin 8 DS

// Each annode pin (for those that don't know think of it as an on switch when it's assigned HIGH)
int dig1 = 4; // anode for 1s digit
int dig2 = 3; // anode for 10s digit
int dig3 = 2; // anode for 100s digit
int dig4 = 5; // anode for 1000s digit

// pin to get signal from echo sensor
int pingPin = 12;


// just some variables
long duration, inches, cm;
int  cycle, results;

// these are bits to make the 8 bit byte accepted by the segment display the 9th is the demical point
// 0-9 then invald numbers
byte table[] =
{ B00111111, B00000110, B01011011, B01001111, B01100110,
  B01101101, B01111101, B00000111, B01111111, B01101111, B01111111
};

//sets everything up

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

//this sends the data to the digit
void Display(int num)
{

  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, table[num]);
  digitalWrite(latch, HIGH);

}

//function for ones place
void D1 (int num, int timer)
{
  Display(num);
  digitalWrite(dig1, LOW);
  delay(timer);
  digitalWrite(dig1, HIGH);

}
// function for tens place
void D2 (int num, int timer)
{
  Display(num);
  digitalWrite(dig2, LOW);
  delay(timer);
  digitalWrite(dig2, HIGH);

}

//hundred place
void D3 (int num, int timer)
{
  Display(num);
  digitalWrite(dig3, LOW);
  delay(timer);
  digitalWrite(dig3, HIGH);

}

// thounsands
void D4 (int num, int timer)
{
  Display(num);
  digitalWrite(dig4, LOW);
  delay(timer);
  digitalWrite(dig4, HIGH);

}

//clears the display
void erase()
{
  digitalWrite(dig1, HIGH);
  digitalWrite(dig2, HIGH);
  digitalWrite(dig3, HIGH);
  digitalWrite(dig4, HIGH);
}

// calculates the distance
long GetDist()
{

  int duration, inches, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5); //5 micro second pulse width to start the ping sensor to read
  digitalWrite(pingPin, LOW);

  
  pinMode(pingPin, INPUT);
  
  delayMicroseconds(300); //holdoff delay
 
  duration = pulseIn(pingPin, HIGH);

  if(duration > 1500)
  {
    duration = 1500;
  }

  cm = microsecondsToCentimeters(duration);

  if(cm > 100)
  {
    cm = 0;
  }

  return cm;
}

//does as the function says
int microsecondsToCentimeters(int microseconds) {
  return microseconds / 29 / 2;
}


//main program
void loop() {
  int timer = 3; //was set at 5
  int ones, tens, hunds, thsnds;
  int cycmax = 1;



  if (cycle >= cycmax)
  {
    cycle = 0;

    results = GetDist();

    Serial.println(results);
  }
  else {
    cycle = cycle + 1;
  }


  if ( results < 100) 

  {
    ones = (results % 10);
    tens = ((results / 10) % 10);
    hunds = ((results / 100) % 10);
    thsnds = (results / 1000);



    erase();

    D1(ones, timer);
    if (results >= 10)
    {
    D2(tens, timer);
    }
   if (results >= 100) {
    D3(hunds, timer);
    }
    if (results >= 1000)
    {
      D4(thsnds, timer);
    }

  }
  else {


    D1(0, timer); 
    D2(0, timer); 
    D3(0, timer); 
    D4(0, timer); 
  }

}
