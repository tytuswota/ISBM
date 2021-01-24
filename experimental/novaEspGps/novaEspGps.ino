#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266HTTPClient.h>

//#include <SPI.h>
const char* ssid     = "A";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "***";


float lattitude,longitude; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(5,4);//rx,tx
TinyGPSPlus gps;// create gps object

//gps for esp 

void setup(){
    Serial.begin(9600); // connect serial
    gpsSerial.begin(9600); // connect gps sensor
    delay(1000);

    delay(10);
    Serial.println('\n');
    
    WiFi.begin(ssid, password);             // Connect to the network
    Serial.print("Connecting to ");
    Serial.print(ssid); Serial.println(" ...");
  
    int i = 0;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
      delay(1000);
      Serial.print(++i); Serial.print(' ');
    }
  
    Serial.println('\n');
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

String string_bin(String msg)
{
    String byte_msg;
    for(int i=0; i<msg.length(); i++){
      
      char myChar = msg.charAt(i);
      String byte_string;
      for(int i=5; i>=0; i--){
        byte bytes = bitRead(myChar,i);
        
        byte_string += String(bytes, BIN);
        
        //Serial.print(bytes, BIN);
      }

      byte_msg += byte_string + " ";
      
    }
    return byte_msg;
}

void loop(){

  while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
       break;
      }

 }
   String lat_a;
   String long_a;
   String bin_message;
   String url;
   lat_a = String(lattitude, 6);
   long_a = String(longitude, 6);

   bin_message = string_bin("1") + string_bin(";") + string_bin(lat_a) + string_bin(";") + string_bin(long_a); 
   url = "http://145.24.222.137/iridium_sim/index.php?incoming_message=" + bin_message;
   
   Serial.println(bin_message);
   HTTPClient http;
   http.begin(url);
   int http_code = http.GET();

   Serial.print("LATTITUDE="); Serial.println(lat_a);
   Serial.print("LONGITUDE="); Serial.println(long_a);
   
   if(http_code > 0)
   {
      Serial.println(http.getString()); 
   }

   http.end();
   
   delay(1000);


}
