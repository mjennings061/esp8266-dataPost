/* ESP8266-based data logger
 * Author: Michael Jennings
 * To-do
 * - Add get temperature and humidity functions
 * - Connect to Wi-Fi
 * - Post to Thingspeak
 * - Add moisture sensor
 * - Add low power mode
 * - Low power wakeup timer
 * 
 * Moisture levels
 * 0 to 1200 (0-31%) dry soil
 * 1201 to 2800 (32-73%) humid soil
 * 2801 to 3800 (74-100%) in water
*/

#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ThingSpeak.h>
#include <stdio.h>

<<<<<<< Updated upstream
#define LEDPIN 2        //inbuilt LED pin
#define DHTPIN 13       //DHT sensor pin
#define BUTTONPIN 14    //Button input pin
#define MPIN 32         //moisture sensor analog pin (GPIO4)
=======
#define LEDPIN D4        //inbuilt LED pin
#define DHTPIN D6       //DHT sensor pin
#define BUTTONPIN D0    //Button input pin
#define MPIN A0         //moisture sensor analog pin (GPIO4)
>>>>>>> Stashed changes
#define DHTTYPE    DHT11     // Type of sensor is a DHT11

// Sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview
DHT_Unified dht(DHTPIN, DHTTYPE); //declare DHT sensor object

/////// FUNCTION DECLARATIONS ///////
void initDHT(void);         //initialise the DHT11
float getMoisture(int pin); //get moisture value from capacitive sensor in percent
float getTemp(void);        //get temperature from the DHT11
float getHumid(void);       //get relative humidity from the DHT11
void connectWiFi(void);     //wait for wifi connection
void postData(float field1Data, float field2Data, float field3Data); //send data to Thingspeak

/////// GLOBAL VARIABLES ///////
// Network information
char ssid[] = "VM8029428";
char password[] = "b5knLvcwnnmq";
WiFiClient client;

// ThingSpeak settings
unsigned long myChannelNumber = 1081009;
const char * myWriteAPIKey = "D3OJ6EMLX6PP244E";
// Timer variables
<<<<<<< Updated upstream
uint32_t delayMS;
uint32_t ms,old_ms = 0;
uint32_t loopTime = 30000;
uint32_t lastConnectionTime;
//uint32_t loopTime = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTONPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, 0);
=======
unsigned long delayMS;
unsigned long old_ms = 0;
unsigned long loopTime = 30000;
unsigned long lastConnectionTime;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTONPIN, 0);
  pinMode(LEDPIN, 1);
  digitalWrite(LEDPIN, 1);
>>>>>>> Stashed changes
  initDHT();
  connectWiFi();
  ThingSpeak.begin(client);
  
}

void loop() {
  // In each loop, make sure there is an Internet connection.
  if (WiFi.status() != WL_CONNECTED) { 
    connectWiFi();
  }
    
  // Perform measurements every loopTime milliseconds unless button is pressed
  ms = esp_log_timestamp(); //log time since startup (millis)
  boolean buttonState = digitalRead(BUTTONPIN);
<<<<<<< Updated upstream
  if((ms - old_ms) > loopTime){
    old_ms = esp_log_timestamp(); //update the "last" timestamp
=======
  if((millis() - old_ms) > loopTime){
    old_ms = millis(); //update the "last" timestamp
>>>>>>> Stashed changes
    digitalWrite(LEDPIN, 1);
    Serial.print(F("\nButton value: ")); Serial.println(buttonState);
    float moisture = getMoisture(MPIN); //get the moisture in percent
    float tem = getTemp();  //get the temperature from the DHT11
    float hum = getHumid(); //get the relative humidity from the DHT11
<<<<<<< Updated upstream
    httpRequest(moisture, tem, hum);
=======
    postData(moisture, tem, hum); //transmit data to thingspeak
>>>>>>> Stashed changes
    digitalWrite(LEDPIN, 0);
    while(digitalRead(BUTTONPIN) == 0); //wait until button has been released (debounce)
  }
}
