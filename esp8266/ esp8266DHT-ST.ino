/* DHTServer - ESP8266 Webserver with a DHT sensor as an input
 
   Based on ESP8266Webserver, DHTexample, and BlinkWithoutDelay (thank you)
 
   Version 1.0  5/3/2014  Version 1.0   Mike Barela for Adafruit Industries
*/
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <DHT.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266HTTPClient.h>
#define DHTTYPE DHT11
#define DHTPIN  2

const char* ssid = "particle";
const char* password = "particle";
byte mac[6];                     // the MAC address of your Wifi shield

// Smartthings hub information
IPAddress hubIp(192,168,1,219); // smartthings hub ip
const unsigned int hubPort = 39500; // smartthings hub port

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266
 
float humidity, temp_f;  // Values read from sensor
String webString="";     // String to display
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor
float lastValue = 100;
const unsigned int serverPort = 8090; // port to run the arduino server on
String readString;

WiFiServer server(serverPort);

//WiFiClient espClient;

void setup(void)
{

  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
  dht.begin();           // initialize temperature sensor

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();

}

void gettemperature() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor 
    previousMillis = currentMillis;   
 
    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp_f = dht.readTemperature(true);     // Read temperature as Fahrenheit
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}

void sendJSONData(WiFiClient client) {
  Serial.println("sendJSONData");
  client.println(F("CONTENT-TYPE: application/json"));
  client.println(F("CONTENT-LENGTH: 15"));
  client.println();
  client.print("{\"temp\":");
  client.print(temp_f);
  client.println("}");
}


// send response to client for a request for status
void handleRequest(WiFiClient client)
{
  Serial.print("handleRequest");
  boolean currentLineIsBlank = true;
  while (client.connected()) {
    if (client == 1) {
      char c = client.read();
      //read char by char HTTP request
      if (readString.length() < 100) {
        //store characters to string
        readString += c;
      }
      if (c == '\n' && currentLineIsBlank) {
        //now output HTML data header
        if(readString.substring(readString.indexOf('/'), readString.indexOf('/')+10) == "/getstatus") {
          client.println("HTTP/1.1 200 OK"); //send new page
          sendJSONData(client);
        } else {
          client.println(F("HTTP/1.1 204 No Content"));
          client.println();
          client.println();
        }
        break;
      }
      if (c == '\n') {
        // you're starting a new line
        currentLineIsBlank = true;
      } else if (c != '\r') {
        // you've gotten a character on the current line
        currentLineIsBlank = false;
      }
    }
  }
  readString = "";

  delay(1);
  //stopping client
  client.stop();
}

// send data 
int sendNotify() //client function to send/receieve POST data.
{
  WiFiClient client;
  int returnStatus = 1;
  //if (client.connect(hubIp, hubPort)) {
    client.println(F("POST / HTTP/1.1"));
    client.print(F("HOST: "));
    client.print(hubIp);
    client.print(F(":"));
    client.println(hubPort);
    sendJSONData(client);
  //}
  //else {
    //connection failed");
  //  returnStatus = 0;
  //}

  // read any data returned from the POST
  //while(client.connected() && !client.available()) delay(1); //waits for data
  //while (client.connected() || client.available()) { //connected or data available
  //  char c = client.read();
  //}

  delay(1);
  //client.stop();
  return returnStatus;
}


void loop(void){
  gettemperature();

  if (temp_f != lastValue){
    Serial.print("Publish message: ");
    Serial.println(temp_f);
    if(sendNotify()) {
      Serial.println("sendNotify");
      //send another request just to be safe    
      //Added this hack because sometimes the request doesn’t show up at the smartthings hub 
      //TODO: figure out what is happening with the request on the network
      delay(10);
      sendNotify();
    }
  } 
  
  lastValue = temp_f;
  // Wait 100 milliseconds
  delay(1000);
  
  // Handle any incoming requests  
  WiFiClient client = server.available();
  if (client) {
    handleRequest(client);
  }   
} 
 

