#include <SoftwareSerial.h>
#include "TinyGPS++.h"

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2
SoftwareSerial serial_connection(10, 12); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data

void setup()
{
  //pinMode(INPUT,8);
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();

}

void loop()
{
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"");
    updateSerial();
    mySerial.print("xxxxx");
    mySerial.print(gps.location.lat(), 6);
    mySerial.print(",");
    mySerial.print(gps.location.lng(), 6);
    updateSerial();
    mySerial.write(26);
     
  }
    //delay(5000);
}

void updateSerial()
{
  delay(500);
  while(Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
