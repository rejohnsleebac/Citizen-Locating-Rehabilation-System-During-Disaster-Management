#include <SoftwareSerial.h>
 
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2
String textMessage="";
String str="",loc="";
int i=0,f=0;

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  
mySerial.println("AT+CNMI=2,2,0,0,0\r\n");
  delay(1000);


}


void loop()
{
  if(mySerial.available()>0){
    f=1;
    textMessage = mySerial.readString();
    Serial.print(textMessage);    
    delay(10);
  }
  
  if(f==1)
  {  
  for(i=51;textMessage[i]!=',';i++)
  {
      str=str+textMessage[i]; 
  }
 for(i=i+1;textMessage[i]!='\0';i++)
  {
    loc=loc+textMessage[i];
  }

  
  Serial.print("ID :");
  Serial.println(str);
  Serial.print("Location coordinates :");
  Serial.println(loc);
  Serial.print("url :");
  Serial.print("http://maps.google.com/maps?q=");
  Serial.print(loc);
  }
  
  delay(10);
  i=0;
  f=0;
  textMessage = "";
 str=""; 
 loc="";
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
