void connectWiFi(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(F("."));
    digitalWrite(LEDPIN, 0);
    delay(250);
    digitalWrite(LEDPIN, 1);
    delay(250);
  }
  // Display a notification that the connection is successful. 
  Serial.println("Connected");
  digitalWrite(LEDPIN, 1);
}

void postData(float field1Data, float field2Data, float field3Data) {
  // Write to ThingSpeak
  Serial.println(F("Sending data..."));
  ThingSpeak.setField(1,field1Data);
  ThingSpeak.setField(2,field2Data);
  ThingSpeak.setField(3,field3Data);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  Serial.println(F("... sent!"));
  delay(1000);
  client.stop();
}
