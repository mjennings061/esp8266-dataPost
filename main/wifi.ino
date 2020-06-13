void connectWiFi(){
  while (WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    delay(3000);
  }
  // Display a notification that the connection is successful. 
  Serial.println("Connected");
}

void httpRequest(float field1Data, float field2Data, float field3Data) {
  WiFiClient client;
  if (!client.connect(server, 80)){
    Serial.println("Connection failed");
    client.stop();
    return;     
  }else{
    // Create data string to send to ThingSpeak.
    String data = "field1=" + String(field1Data) + "&field2=" + String(field2Data) + "&field3=" + String(field3Data); //shows how to include additional field data in http post
    // POST data to ThingSpeak.
    if (client.connect(server, 80)) {
      client.println("POST /update HTTP/1.1");
      client.println("Host: api.thingspeak.com");
      client.println("Connection: close");
      client.println("User-Agent: ESP32WiFi/1.1");
      client.println("X-THINGSPEAKAPIKEY: "+writeAPIKey);
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.print(data.length());
      client.print("\n\n");
      client.print(data);
      delay(250);
    }
  }
  client.stop();
}
