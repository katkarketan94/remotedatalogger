/*Note: this code is a demo for how to using gprs shield to send sms message, dial a voice call and 
  send a http request to the website, upload data to pachube.com by TCP connection,
 
  The microcontrollers Digital Pin 7 and hence allow unhindered
  communication with GPRS Shield using SoftSerial Library. 
  IDE: Arduino 1.0 or later
  Replace the following items in the code:
  1.Phone number, don't forget add the country code
  2.Replace the Access Point Name
  3. Replace the Pachube API Key with your personal ones assigned
  to your account at cosm.com
  */
#include <glcd.h>
#include <SoftwareSerial.h>
#include <String.h>
#include <fonts/allFonts.h>


  
SoftwareSerial mySerial(11, 12); //pin23,pin7  on 2560
int sensorPin = A14; //pin97 on 2560

char buffer[16];
#define buffer_size sizeof(buffer)/sizeof(buffer[0])
int8_t buffer_pos = 0;


 
void setup()
{ 
   // Initialize the GLCD 
 GLCD.Init();

 // Select the font for the default text area
  GLCD.SelectFont(System5x7);

  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  delay(500);
  
  buffer_pos = 0;
}
 
void loop()

{
  mySerial.println("AT+CREG?");
  Serial.println("AT+CREG?");
  GLCD.println("Reg Status");
  delay(1000);
    
  ShowSerialData();
    
  mySerial.println("AT+CGATT?");
  Serial.println("AT+CGATT?");
  
  //lcd.setCursor(0,0);
  GLCD.println("GPRS status");
 // lcd.setCursor(0,1);
 // lcd.print(mySerial.read());
  delay(500);
 
  ShowSerialData();
  
///send2Pachube()///
///this function is to send the sensor data to the pachube, you can see the new value in the pachube after execute this function///

  /*mySerial.println("AT+CGATT?");
  Serial.println("AT+CGATT?");
  lcd.setCursor(0,0);
  lcd.print("GPRS status");
  lcd.setCursor(0,1);
  lcd.print(mySerial.read());
  delay(1000); 
 
  ShowSerialData(); */
 
 mySerial.println("AT+CIPSHUT");//bring up wireless connection
  Serial.println("AT+CIPSHUT");
  //lcd.setCursor(0,0);
  GLCD.println("Begin Wireless");
  // lcd.setCursor(0,1);
  //lcd.print(mySerial.read());
  delay(3000);
  //lcd.clear();
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  Serial.println("AT+CSTT=\"airtelgprs.com\"");
  //lcd.setCursor(0,0);
  GLCD.println("APN");
  //lcd.setCursor(0,1);
  //lcd.print(mySerial.read());
  delay(1000);
  //lcd.clear();
 
  ShowSerialData();
   
  mySerial.println("AT+CIICR");//bring up wireless connection
  Serial.println("AT+CIICR");
  //lcd.setCursor(0,0);
  GLCD.println("Bring up wireless");
  //lcd.setCursor(0,1);
  //lcd.print(mySerial.read());
  delay(3000);
  //lcd.clear();
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  Serial.println("AT+CIFSR");
  //lcd.setCursor(0,0);
  //lcd.print("IP");
  //lcd.setCursor(0,1);
  //lcd.print(mySerial.read());
  delay(2000);
  //lcd.clear();
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSPRT=0");
  Serial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();

  mySerial.println("AT+CIPSTART=\"tcp\",\"api.xively.com\",\"8081\"");//start up the connection
  Serial.println("AT+CIPSTART=\"tcp\",\"api.xively.com\",\"8081\"");
  delay(2000);
 
  ShowSerialData();
  
  while(1){ 
  
  int sensorValue = analogRead(sensorPin);  
    
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  Serial.println("AT+CIPSEND");
  delay(4000);
  ShowSerialData();
  if ( ShowSerialData() == false ) break;
 
  
  mySerial.print("{\"method\": \"put\",\"resource\": \"/feeds/1198901478.json/\",\"params\"");//here is the feed you apply from pachube
  delay(500);
  ShowSerialData();
  mySerial.print(": {},\"headers\": {\"X-ApiKey\":");//in here, you should replace your pachubeapikey
  delay(500);
  ShowSerialData();
  mySerial.print("\"RxDtavgd84MKtJIMK1R4xZ4jwANT6z25XA0DYV3GYOeOaYsR\"");//pachubeapikey
  delay(500);
  ShowSerialData();
 
  mySerial.print("},\"body\":");
  delay(500);
  ShowSerialData();
  
  mySerial.print(" {\"version\": \"1.0.0\",\"datastreams\":");
  delay(500);
  ShowSerialData();
  mySerial.print("[{\"id\": \"Pot\",\"current_value\" : \"");mySerial.print(sensorValue);mySerial.println("\"}]}}");

 
  delay(500);
  ShowSerialData();
 
  mySerial.println((char)26);//sending
  delay(6000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
}
  mySerial.println("AT+CIPCLOSE");//close the connection
  delay(100);
  ShowSerialData();
}
 
boolean ShowSerialData()
{  char inByte;
  /* String content = "";
  char character;
  for(int i=0; i<40; i++){
    character = mySerial.read();
    content.concat(character);
    delay(50);
  }
  if (content != ""){
  GLCD.println(content);
  //Serial.println(content);
  }
  //while(mySerial.available()!=0)
  //Serial.write(mySerial.read());
    //c = mySerial.read();
    //GLCD.println(c);
    //temp=Serial.read();
    //delay(10);
    //lcd.clear();
    //lcd.setCursor(0,0);
    //GLCD.write((char) Serial.read()); 
    //delay(2000);
 */
  para = false;
 while (mySerial.available()) {
    inByte = mySerial.read();
    while (buffer_pos >= buffer_size) {
      for (int8_t i = 0; i < buffer_size - 1; i++) { // if shift buff left if at end of buff
        buffer[i] = buffer[i + 1];
      }
      buffer_pos--;
    }
    buffer[buffer_pos++] = inByte;
    if (strcasestr(buffer, "track")) {
      buffer_pos = 0;
      Serial.println("ERROR");
      para = true;
    } 
    else {
      Serial.write(inByte);
    }
    return para;
  }
}
