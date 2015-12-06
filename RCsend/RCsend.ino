/*
  Example for different sending methods
  
  http://code.google.com/p/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
   mySwitch.enableTransmit(10);
   mySwitch.setPulseLength(192);
   mySwitch.enableReceive(0);
  // Optional set protocol (default is 1, will work for most outlets)
   //mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  
}

void loop() {
  /* Same switch as above, but using decimal code */
  Serial.print("On ");
  mySwitch.send("010100000101110100000011");
  delay(1000);  
  Serial.print("Off ");
  mySwitch.send("010100000101110100001100");
  //delay(1000);  
  delay(20000);
  Serial.print("Received ");
  Serial.print( mySwitch.getReceivedValue() );
  Serial.print(" / ");
  Serial.print( mySwitch.getReceivedBitlength() );
  Serial.print("bit ");
  Serial.print("Protocol: ");
  Serial.println( mySwitch.getReceivedProtocol() );
}

