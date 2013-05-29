/*
HC-SR04 Ping distance sensor]
coucou
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPinA 13
#define echoPinA 12
#define trigPinB 7

#include <Ethernet.h>
#include <SPI.h>

////////////////////////////////////////////////////////////////////////
//CONFIGURE ETH
////////////////////////////////////////////////////////////////////////
byte server[] = {213, 251, 166, 71};

//The location to go to on the server
//make sure to keep HTTP/1.0 at the end, this is telling it what type of file it i
String location = "/open HTTP/1.0";

// if need to change the MAC address (Very Rare)
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
////////////////////////////////////////////////////////////////////////
EthernetClient client;

char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?



void setup() 
{
  Serial.begin (9600);
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  //Ethernet.begin(mac);
}

void loop() 
{
  //Ecriture CapteurA
  long duration, distance;
  
  //Constante pin7 Capteur B ~PWM~
  const int pwPin = 7; 
  
  //Ecritures CapteurB
  long pulse, cm;
  
  
  ///////////// CAPTEUR A ////////////
  
  digitalWrite(trigPinA, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinA, HIGH);
  //delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinA, LOW);
  duration = pulseIn(echoPinA, HIGH);
  distance = (duration/2) / 29.1; 
  //Serial.println (distance);
  delay(200);

/*
  ///////////// CAPTEUR B ////////////

  pinMode(pwPin, INPUT);
    //Used to read in the pulse that is being sent by the MaxSonar device.
  //Pulse Width representation with a scale factor of 147 uS per Inch.

  pulse = pulseIn(pwPin, HIGH);
  //147uS per inch
  cm = pulse/147;      //Attention a changer le 147uS (valeur pour inches) en cm
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(200);
*/

  ///////////// CALCUL DE PRIORITE AB-BA ////////////
  if (distance < 20 )
  {
  
    Serial.println (distance);
    pushStatus();
  }
  
/*
  else (cm < ??);
  {
    
  }
  else
  
*/

}
  
  
String pushStatus()
{
  //connect to the server

  Serial.println("connecting...");

  //port 80 is typical of a www page
  if (client.connect(server, 80)) 
  {
    client.println("GET /api_cantine/?do=up HTTP/1.1" );
    client.println("Host: mathemagie.net");
    client.println("Content-Type: application/x-www-form-urlencoded" );
    client.println("User-Agent: Arduino/1.1");
    //client.println("Connection: close");
   // client.print("Content-Length: ");
  //  client.println(data.length());
    client.println();
  //  client.println(data);
    client.stop();
    client.flush();
    Serial.println("Connected");
 
 }
 else
 {
  return "connection failed";
 }
}
