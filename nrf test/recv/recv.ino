/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
  == Example 01 - Servo Control / Node 01 - Servo motor ==
*/
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)

void setup() {
  SPI.begin();
  radio.begin();
  Serial.begin(9600);
  network.begin(90, this_node); //(channel, node address)
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(7, LOW);
}

void loop() {
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    unsigned long incomingData;
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    digitalWrite(7, HIGH);
    delay(100);
    Serial.println(incomingData);
  }
  digitalWrite(7, LOW);
}
