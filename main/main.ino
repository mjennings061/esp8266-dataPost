/* ESP32-based data logger
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
 * 0 to 340 (0-31%) dry soil
 * 341 to 700 (32-73%) humid soil
 * 701 to 1023 (74-100%) in water
*/

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>

#define LEDPIN 4        //inbuilt LED pin
#define DHTPIN 7       //DHT sensor pin
#define BUTTONPIN 8    //Button input pin
#define MPIN A0         //moisture sensor analog pin (GPIO4)
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
void httpRequest(float field1Data, float field2Data, float field3Data); //send data to Thingspeak

/////// GLOBAL VARIABLES ///////
// Network information
char* ssid = "VM8029428";
const char* password = "b5knLvcwnnmq";
// ThingSpeak settings
char server[] = "api.thingspeak.com";
String writeAPIKey = "D3OJ6EMLX6PP244E";
// Timer variables
uint32_t delayMS;
uint32_t old_ms = 0;
uint32_t loopTime = 30000;
uint32_t lastConnectionTime;
//uint32_t loopTime = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTONPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, 1);
  initDHT();
  connectWiFi();
}

void loop() {
  // In each loop, make sure there is an Internet connection.
  if (WiFi.status() != WL_CONNECTED) { 
    connectWiFi();
  }
    
  // Perform measurements every loopTime milliseconds unless button is pressed
  boolean buttonState = digitalRead(BUTTONPIN);
  if((millis() - old_ms) > loopTime){
    old_ms = millis(); //update the "last" timestamp
    digitalWrite(LEDPIN, 0);
    Serial.print(F("\nButton value: ")); Serial.println(buttonState);
    float moisture = getMoisture(MPIN); //get the moisture in percent
    float tem = getTemp();  //get the temperature from the DHT11
    float hum = getHumid(); //get the relative humidity from the DHT11
    httpRequest(moisture, tem, hum);
    digitalWrite(LEDPIN, 1);
    while(digitalRead(BUTTONPIN) == 0); //wait until button has been released (debounce)
  }
}

//get moisture value from capacitive sensor in percent
float getMoisture(int pin){ 
  int sensValue = analogRead(pin);
  float sensFloat = float(sensValue);
  float percent = (sensFloat/3800)*100;
  if(percent > 100.0){
    percent = 100.0;
  }
  Serial.print(F("Sensor Value: ")); Serial.println(sensValue);
  Serial.print(F("Moisture: ")); Serial.print(percent); Serial.println(F("%"));
  return percent;
}
