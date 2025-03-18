//  TESTING THE CLOUD SYSTEM OF THEAMPLITUHEDRON.COM 
//
//-TheAmplituhedron.com
//-Cloud System
//-Sending data to TheAmplituhedron.com
//-Getting data from TheAmplituhedron.com
//
//-By Kutluhan Aktar

//
// * For more information, please go to https://www.theamplituhedron.com/dashboard/cloud/
// * This is an example code file for Arduino Ethernet Shield 2 or ENC28J60.
//  * Do not forget to use percent-encoding reserved characters for the header. 
//  * Circuit:
//  * Ethernet shield attached to pins 10, 11, 12, 13
//
// CONNECTIONS:
//
// DHT11 Module
// Pin 2   -------------------------
//
// 2 Way Relay (1)
// Pin 3   -------------------------
// Pin 4   -------------------------
//
// 2 Way Relay (2)
// Pin 5   -------------------------
// Pin 6   -------------------------
//
// 2 Way Relay (3)
// Pin 7   -------------------------
// Pin 8   -------------------------
//
// Arduno Ethernet Shield
// Pin 10  --------------------------
// Pin 11  --------------------------
// Pin 12  --------------------------
// Pin 13  --------------------------
//
// LDR
// AO      -------------------------- 
//                             
// Flame Sensor 
// A1      --------------------------
//
// MQ4   Sensor
// A2      --------------------------
//
// Hygrometer Module
// A3      -------------------------- 
 
#include <SPI.h>
#include <Ethernet.h>
//Initial DHT11 library and create an object named dht to communicate with the sensor.
#include "DHT.h"
DHT dht;

byte mac[] = {
    0xDE,0xAD,0xBE,0xEF,0xFE,0xED  // Your MAC address has to be here.
};
IPAddress ip(192,168,1,21); // A valid IP address to make an HTTP request.

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

// Define the sensors variables and types.
float Sensor_1;
float Sensor_2;
int   Sensor_3;
int   Sensor_4;
int   Sensor_5;
int   Sensor_6;

/////////////////////////////////////////////////////////////
// Define the relays variables.
int Device_1 = 3;
int Device_2 = 4;
int Device_3 = 5;
int Device_4 = 6;
int Device_5 = 7;
int Device_6 = 8;
////////////////////////////////////////////////////////////

// Determine a string to collect the commands came from TheAmplituhedron.com.
String readString ;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // Start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

/////////////////////////////////////////////////////////////
// Determine the relay module's pins.
pinMode(Device_1,OUTPUT);
pinMode(Device_2,OUTPUT);
pinMode(Device_3,OUTPUT);
pinMode(Device_4,OUTPUT);
pinMode(Device_5,OUTPUT);
pinMode(Device_6,OUTPUT);
// Give HIGH value for the default.
digitalWrite(Device_1,HIGH);
digitalWrite(Device_2,HIGH);
digitalWrite(Device_3,HIGH);
digitalWrite(Device_4,HIGH);
digitalWrite(Device_5,HIGH);
digitalWrite(Device_6,HIGH);
//Connect Dht11 to data pin 2.
   dht.setup(2); 
////////////////////////////////////////////////////////////
}

void loop() {
 // It makes Arduino wait until the temperature and the humidity values are accurate.
 delay(dht.getMinimumSamplingPeriod());
 
  // Attach whatever data you want to send TheAmplituhedron.com
  Sensor_1 =  dht.getHumidity();
  Sensor_2 =  dht.getTemperature();
  Sensor_3 =  analogRead(A0); 
  Sensor_4 =  analogRead(A1);
  Sensor_5 =  analogRead(A2);
  Sensor_6 =  analogRead(A3);
   
  // Listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // An http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        // Add each data came from TheAmplituhedron.com to a string named readString.
        if (readString.length() < 110) {
          readString += c;
          //Serial.print(c);
         }
        Serial.println(readString);
            // If the line ends, initial a HTTP Request.
        if (c ==  '\n') {
      
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");;
          client.println("Content-Type:text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html style=""background-color:#002699;"">");
          client.println("<head>");
          client.println("<title>DeviceSide</title>"); // Header for the web page.
          client.println("<link rel=""icon"" href=""https://www.theamplituhedron.com/images/favicon.ico""></link>"); // Describe the name and icon of DeviceSide.
          client.println("</head>");
          client.println("<body>");
          // The hedron must be send with the get method.
                    client.println("<form action=""  https://www.theamplituhedron.com/dashboard/cloud/test.php?hedron=The hedron is here"" method=""post"" target=""_parent"">"); // Enter your cloud page address. *Hedron here when the post method is active.
           
                  client.println("<button type=""submit"" style=""position:absolute;top:5px;width:100%;height:200px;background-color:#eb2e00;color:white;"">DeviceSide</button>"); // When the DeviceSide button is clicked, the information is sent to TheAmplituhedron.com by the valid IP address. 
                    client.println("<input type=""hidden""  name=""Sensor-1"" value="" ");
                    client.println(Sensor_1);
                    client.println(" ""><br> ");
                    client.println("<input type=""hidden""  name=""Sensor-2"" value="" ");
                    client.println(Sensor_2);
                    client.println(" ""><br> ");
                    client.println("<input type=""hidden""  name=""Sensor-3"" value="" ");
                    client.println(Sensor_3);
                    client.println(" ""><br> ");
                    client.println("<input type=""hidden""  name=""Sensor-4"" value="" ");
                    client.println(Sensor_4);
                    client.println(" ""><br> ");
                    client.println("<input type=""hidden""  name=""Sensor-5"" value="" ");
                    client.println(Sensor_5);
                    client.println(" ""><br> ");
                    client.println("<input type=""hidden""  name=""Sensor-6"" value="" ");
                    client.println(Sensor_6);
                    client.println(" ""><br> ");
          client.println("</form>");
          client.println("</body>");
          client.println("</html>");
          
          break;
        }

      }
    }
    delay(1);
    // Close the connection:
    client.stop();

    // Define conditions for your system.
      //  Device-1, Device-2, Device-3, Device-4, Device-5 are the constant on or off type.
        if (readString.indexOf("?Device-1=ON") >0){ 
          // Condition here;
          digitalWrite(Device_1,LOW);
          }
        else if (readString.indexOf("?Device-1=OFF") >0){ 
          // Condition here;
          digitalWrite(Device_1,HIGH);
          }
        if (readString.indexOf("&Device-2=ON") >0){ 
          //  Condition here;
          digitalWrite(Device_2,LOW);
          }
        else if (readString.indexOf("&Device-2=OFF") >0){
          // Condition here;
          digitalWrite(Device_2,HIGH);
          }
        
        if (readString.indexOf("&Device-3=ON") >0){ 
          // Condition here;
          digitalWrite(Device_3,LOW);
          }
        else if (readString.indexOf("&Device-3=OFF") >0){  
          // Condition here;
          digitalWrite(Device_3,HIGH);
          }  
        if (readString.indexOf("&Device-4=ON") >0){
         // Condition here;
         digitalWrite(Device_4,LOW);
          }
        else if (readString.indexOf("&Device-4=OFF") >0){ 
          // Condition here;
          digitalWrite(Device_4,HIGH);
          }
        if (readString.indexOf("&Device-5=ON") >0){ 
          // Condition here;
          digitalWrite(Device_5,LOW);
          }
        else if (readString.indexOf("&Device-5=OFF") >0){
          // Condition here;
          digitalWrite(Device_5,HIGH);
          }
        
      //  Device-6 is the limitless text type.
        if (readString.indexOf("&Device-6=Hello") >0){ 
          // Condition here;
          digitalWrite(Device_6,LOW);
          }
        else if (readString.indexOf("&Device-6=By") >0){ 
          // Condition here;
          digitalWrite(Device_6,HIGH);
          }

        readString=""; // Start a new string.
  }
}
