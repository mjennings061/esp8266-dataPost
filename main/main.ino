/* ESP32-based data logger
 * Author: Michael Jennings
 * To-do
 * - Add get temperature and humidity functions
 * - Connect to Wi-Fi
 * - Post to Thingspeak
 * - Add moisture sensor
 * - Add low power mode
 * - Low power wakeup timer
*/

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13       //DHT sensor pin
#define BUTTONPIN 14    //Button input pin
#define DHTTYPE    DHT11     // Type of sensor is a DHT11

// Sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview
DHT_Unified dht(DHTPIN, DHTTYPE); //declare DHT sensor object

/////// FUNCTION DECLARATIONS ///////
void initDHT(void);         //initialise the DHT11
float getTemp(void);        //get temperature from the DHT11
float getHumid(void);       //get relative humidity from the DHT11

/////// GLOBAL VARIABLES ///////
uint32_t delayMS;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTONPIN,INPUT);
  initDHT();
}

void loop() {
  // Delay between measurements.
  delay(delayMS); //set by the sensor's max sample rate
  boolean buttonState = digitalRead(BUTTONPIN);
  Serial.print(F("Button value: ")); Serial.println(buttonState);
  float tem = getTemp();  //get the temperature from the DHT11
  float hum = getHumid(); //get the relative humidity from the DHT11
}
