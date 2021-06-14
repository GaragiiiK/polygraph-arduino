#define led 13      // LED pin
#define breath A0   // Breath detector pin
#define gsr A1      // GSR detector pin
#define hpg A2      // HPG detector pin
#define trm A3      // Tremor detector pin

bool transmit = false;        // ON/OFF data transmittion
unsigned long prevMillis = 0; // previous values of milliseconds

int breathValues[4];  // array of breath values
int gsrValues[4];     // array of gsr values
int hpgValues[4];     // array of hpg values
int trmValues[4];     // array of tremor values
int countOfReadValues = 0; // counter of read values

void setup() 
{
	Serial.begin(115200);     // serial port initialization
	pinMode(led,OUTPUT);      // pins initialization
	pinMode(breath, INPUT);
	pinMode(gsr, INPUT);
	pinMode(hpg, INPUT);
	pinMode(trm, INPUT);
}

void loop() 
{
  char data = Serial.read(); // read of data from USB port
  switch(data)
  {
    case '0':                 // OFF
      digitalWrite(led, LOW);
      transmit = false;
      break;      
    case '1':                 // ON
      digitalWrite(led, HIGH); 
      transmit = true;
      break;
  }

  unsigned long currentMillis = millis(); // current value of milliseconds
  if(currentMillis - prevMillis >= 25)    // data from detectors reads no rare than 25 ms
  {
    prevMillis = currentMillis;           // save current value of milliseconds
    if(countOfReadValues == 3)            // data forms only if we have 4 saved values
    {
      if(transmit)                        // if module works
      {                                   // form data as an average of 4 detections
        Serial.print("(");
        print_fmt(map((breathValues[0] + breathValues[1] + breathValues[2] + breathValues[3])/4, 0, 1000, 1000, 0));
        Serial.print(", ");
        print_fmt(map((gsrValues[0] + gsrValues[1] + gsrValues[2] + gsrValues[3])/4, 0, 400, 400, 0));
        Serial.print(", ");
        print_fmt(hpgValues[0] + hpgValues[1] + hpgValues[2] + hpgValues[3])/4);
        Serial.print(", ");
        print_fmt(map((trmValues[0] + trmValues[1] + trmValues[2] + trmValues[3])/4, 0, 1000, 1000, 0));
        Serial.println(")");
      }
      countOfReadValues = 0;  // reset of counter
    }
    else
    {
      countOfReadValues++; // increment of counter
    }

    breathValues[countOfReadValues] = analogRead(breath); // reading of new values 
    gsrValues[countOfReadValues] = analogRead(gsr);       //   for every detector
    hpgValues[countOfReadValues] = analogRead(hpg);
    trmValues[countOfReadValues] = analogRead(trm);
  }
}

void print_fmt(int num)
{
  if(num == 0)
    Serial.print("0000");
  else if(num<10)
  {
    Serial.print("000");
    Serial.print(num);
  }
  else if(num<100)
  {
    Serial.print("00");
    Serial.print(num);
  }
  else if(num<1000)
  {
    Serial.print("0");
    Serial.print(num);
  }
  else
    Serial.print(num);
}

  unsigned long currentMillis = millis(); // current value of milliseconds
  if(currentMillis - prevMillis >= 25)    // data from detectors reads no rare than 25 ms
  {
    prevMillis = currentMillis;           // save current value of milliseconds
    if(countOfReadValues == 3)            // data forms only if we have 4 saved values
    {
      ... // sending data to serial port
    }
    else countOfReadValues++; // increment of counter

    breathValues[countOfReadValues] = analogRead(breath); // reading of new values 
    gsrValues[countOfReadValues] = analogRead(gsr);       //   for every detector
    hpgValues[countOfReadValues] = analogRead(hpg);
    trmValues[countOfReadValues] = analogRead(trm);
  }
