void setup() {
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
// if(Serial.available() > 0){ // Checks whether data is comming from the serial port
//    state = Serial.read(); // Reads the data from the serial port
//    Serial.println(String(state));
// }
 Serial.println("ok");
}
