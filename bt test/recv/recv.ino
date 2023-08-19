void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");

  delay(2000);
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (Serial.available())
    Serial.write(Serial.read());
}
