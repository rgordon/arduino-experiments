#include <dht11.h>
#include <SoftwareSerial.h>

dht11 DHT11;
const int dht11Pin = 2;

const int TxPin = 6;
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);

void setup()
{
  DHT11.attach(dht11Pin);
  Serial.begin(9600);
  
  pinMode(TxPin, OUTPUT);
  digitalWrite(TxPin, HIGH);
  
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12);                 // Clear             
  mySerial.write(17);                 // Turn backlight on
  delay(5);                           // Required delay
  mySerial.print("Temp/Humidity");  // First line
  mySerial.write(13);                 // Form feed
  mySerial.print("initializing...");   // Second line
  mySerial.write(212);                // Quarter note
  mySerial.write(220);                // A tone
  delay(3000);                        // Wait 3 seconds
  mySerial.write(18);                 // Turn backlight off

}

void loop()
{
  int chk = DHT11.read();
  
  mySerial.write(12); // clear
  delay(5);
  
  mySerial.print(" ");  
  mySerial.print((float)DHT11.temperature, 1);
  mySerial.print("C  ");
  
  mySerial.print((float)DHT11.fahrenheit(), 1);
  mySerial.print("F");
  
  mySerial.write(13); // line 2
  
  mySerial.print("Hu:");
  mySerial.print((float)DHT11.humidity,1);
  mySerial.print("%");
  
  mySerial.print(" Dw:");
  mySerial.print((float)DHT11.dewPoint(), 1);
  mySerial.print("C");
  
  delay(5000);
}

