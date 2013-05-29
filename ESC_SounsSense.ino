// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

#define LED1 9
#define LED2 10
#define LED3 11

#define SOUND_SENSOR A0
#define THRESHOLD_VALUE1 10
#define THRESHOLD_VALUE2 500
#define THRESHOLD_VALUE3 1023

void setup()
{
  // initialize the digital pin as an output.
  pins_init();    
}

void loop()
{

//  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);               // wait for a second
//  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);               // wait for a second
int sensorValue = 0;
for (int i = 0; i < 500; i++) {
  int sv = analogRead(SOUND_SENSOR);//use A0 to read the electrical signal
  if (sensorValue < sv ) {
    sensorValue = sv;
  }
  delay(1);
}
if(sensorValue > THRESHOLD_VALUE1)
{
    turnOnLED(LED1);//if the value read from A0 is larger than 400,then light the LED
  }
  if(sensorValue > THRESHOLD_VALUE2)
  {
     turnOnLED(LED2);//if the value read from A0 is larger than 400,then light the LED
  }
  if(sensorValue > THRESHOLD_VALUE3)
 {
   turnOnLED(LED3);//if the value read from A0 is larger than 400,then light the LED
}

   delay(500);
   turnOffLED(LED1);
   turnOffLED(LED2);
   turnOffLED(LED3);
}

void pins_init()
{
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(SOUND_SENSOR, INPUT); 
}

void turnOnLED(int led)
{
	digitalWrite(led,HIGH);
}

void turnOffLED(int led)
{
	digitalWrite(led,LOW);
}
