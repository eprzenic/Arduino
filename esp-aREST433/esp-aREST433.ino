#include <RCSwitch.h>
#include <ESP8266WiFi.h>
#include <aREST.h>


// Create aREST instance
aREST rest = aREST();

// Create RCSwitch
RCSwitch mySwitch = RCSwitch();

// WiFi parameters
const char* ssid = "particle";
const char* password = "particle";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           8000

// Create an instance of the server
WiFiServer server(LISTEN_PORT);


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

// Declare functions to be exposed to the API
int socketControl(String command);

void setup(void)
{
  //Setup receiver/transmiter
  mySwitch.enableTransmit(2);
  mySwitch.setPulseLength(218);
  mySwitch.setRepeatTransmit(10);
  mySwitch.enableReceive(0);
  delay(1000);
  Serial.begin(115200);

   // Function to be exposed
  rest.function("socket",socketControl);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("Socket8266");

    // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
  /*
  //433 recieve
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
          Serial.println( mySwitch.getReceivedProtocol() );  }
   if (mySwitch.getReceivedValue()){
       process();
       }
   mySwitch.resetAvailable();
   }*/    
}

int socketControl(String command) {

  // Get state from command
  Serial.print(command);
  if(command == "1on"){
      Serial.println("");
      Serial.print("Socket 1 On");    
      mySwitch.sendTriState(socket1On);
      delay(1000);
      return 1;
  }
  else if (command == "1off"){
      Serial.println("");
      Serial.print("Socket 1 Off");    
      mySwitch.sendTriState(socket1Off);
      delay(1000); 
      return 1;
      }
  if(command == "2on"){
      Serial.println("");
      Serial.print("Socket 2 On");    
      mySwitch.sendTriState(socket2On);
      delay(1000);
      return 1;
  }
  else if (command == "2off"){
      Serial.println("");
      Serial.print("Socket 2 Off");    
      mySwitch.sendTriState(socket2Off);
      delay(1000); 
      return 1;
      }
  if(command == "3on"){
      Serial.println("");
      Serial.print("Socket 3 On");    
      mySwitch.sendTriState(socket3On);
      delay(1000);
      return 1;
  }
  else if (command == "3off"){
      Serial.println("");
      Serial.print("Socket 3 Off");    
      mySwitch.sendTriState(socket3Off);
      delay(1000); 
      return 1;
      }
  if(command == "4on"){
      Serial.println("");
      Serial.print("Socket 4 On");    
      mySwitch.sendTriState(socket4On);
      delay(1000);
      return 1;
  }
  else if (command == "4off"){
      Serial.println("");
      Serial.print("Socket 4 Off");    
      mySwitch.sendTriState(socket4Off);
      delay(1000); 
      return 1;
      }
  if(command == "5on"){
      Serial.println("");
      Serial.print("Socket 5 On");    
      mySwitch.sendTriState(socket5On);
      delay(1000);
      return 1;
  }
  else if (command == "5off"){
      Serial.println("");
      Serial.print("Socket 5 Off");    
      mySwitch.sendTriState(socket5Off);
      delay(1000); 
      return 1;
      }      
  if(command == "6on"){
      Serial.println("");
      Serial.print("Socket 6 On");    
      mySwitch.sendTriState(socket6On);
      delay(1000);
      return 1;
  }
  else if (command == "6off"){
      Serial.println("");
      Serial.print("Socket 6 Off");    
      mySwitch.sendTriState(socket6Off);
      delay(1000); 
      return 1;
      }  
  if(command == "7on"){
      Serial.println("");
      Serial.print("Socket 7 On");    
      mySwitch.sendTriState(socket7On);
      delay(1000);
      return 1;
  }
  else if (command == "7off"){
      Serial.println("");
      Serial.print("Socket 7 Off");    
      mySwitch.sendTriState(socket7Off);
      delay(1000); 
      return 1;
      }              
}
/*
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
}*/


