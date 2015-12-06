/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "particle";
const char* password = "particle";

ESP8266WebServer server(80);

// Replace with your remote TriState values
char* socket1On = "00F0FFFF0101";
char* socket1Off = "00F0FFFF0110";
char* socket2On = "00F0FFFF1001";
char* socket2Off = "00F0FFFF1010";
char* socket3On = "00F0FFF10001";
char* socket3Off = "00F0FFF10010";
char* socket4On = "00F0FF1F0001";
char* socket4Off = "00F0FF1F0010";
char* socket5On = "FF00FFFF0101";
char* socket5Off = "FF00FFFF0110";
char* socket6On = "FF00FFFF1001";
char* socket6Off = "FF00FFFF1010";
char* socket7On = "FF00FFF10001";
char* socket7Off = "FF00FFF10010";

String webPage = "";
 
void setup(void){
  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #3 <a href=\"socket3On\"><button>ON</button></a>&nbsp;<a href=\"socket3Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #4 <a href=\"socket4On\"><button>ON</button></a>&nbsp;<a href=\"socket4Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #5 <a href=\"socket5On\"><button>ON</button></a>&nbsp;<a href=\"socket5Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #6 <a href=\"socket6On\"><button>ON</button></a>&nbsp;<a href=\"socket6Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #7 <a href=\"socket7On\"><button>ON</button></a>&nbsp;<a href=\"socket7Off\"><button>OFF</button></a></p>";
  mySwitch.enableTransmit(2);
  mySwitch.setPulseLength(218);
  mySwitch.setRepeatTransmit(10);
  mySwitch.enableReceive(0);
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    Serial.println("");
    Serial.print("Socket 1 On");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket1On);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    Serial.println("");
    Serial.print("Socket 1 Off");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket1Off);
    delay(1000); 
  });  
  server.on("/socket2On", [](){
    Serial.println("");
    Serial.print("Socket 2 On");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket2On);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    Serial.println("");
    Serial.print("Socket 2 Off");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket2Off);
    delay(1000); 
  });  
  server.on("/socket3On", [](){
    Serial.println("");
    Serial.print("Socket 3 On");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket3On);
    delay(1000);
  });
  server.on("/socket3Off", [](){
    Serial.println("");
    Serial.print("Socket 3 Off");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket3Off);
    delay(1000); 
  });
  server.on("/socket4On", [](){
    Serial.println("");
    Serial.print("Socket 4 On");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket4On);
    delay(1000);
  });
  server.on("/socket4Off", [](){
    Serial.println("");
    Serial.print("Socket 4 Off");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket4Off);
    delay(1000); 
  });
  server.on("/socket5On", [](){
    Serial.println("");
    Serial.print("Socket 5 On");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket5On);
    delay(1000);
  });
  server.on("/socket5Off", [](){
    Serial.println("");
    Serial.print("Socket 5 Off");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket5Off);
    delay(1000); 
  });
  server.on("/socket6On", [](){
    Serial.println("");
    Serial.print("Socket 6 On");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket6On);
    delay(1000);
  });
  server.on("/socket6Off", [](){
    Serial.println("");
    Serial.print("Socket 6 Off");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket6Off);
    delay(1000); 
  });
  server.on("/socket7On", [](){
    Serial.println("");
    Serial.print("Socket 7 On");
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket7On);
    delay(1000);
  });
  server.on("/socket7Off", [](){
    Serial.println("");
    Serial.print("Socket 7 Off");    
    server.send(200, "text/html", webPage);
    mySwitch.sendTriState(socket7Off);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
  if (mySwitch.available()) {  
  int value = mySwitch.getReceivedValue();
    /*
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      //  used for checking received data      
         Serial.print("Received ");       
          Serial.print( mySwitch.getReceivedValue() );      
          Serial.print(" / ");     
          Serial.print( mySwitch.getReceivedBitlength() );      
          Serial.print("bit ");      
          Serial.print("Protocol: ");     
          Serial.println( mySwitch.getReceivedProtocol() );  }*/
   if (mySwitch.getReceivedValue()){
       process();
       }
   mySwitch.resetAvailable();
   }
   
}
void process()
{
  unsigned long res = mySwitch.getReceivedValue();
  
  switch (res){
     case 5266700:
     Serial.println("Button A");
     break;
     case 5272835:
     Serial.println("Button B");
     break;
     case 292108:
     Serial.println("Button C");
     break;
     case 292099:
     Serial.println("Button D");
     break;    
  }
}

