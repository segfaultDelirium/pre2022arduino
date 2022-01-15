#include <dht.h>
// https://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/
dht DHT;

#define SENSOR_SWITCH 2
#define SENSOR_SWITCH_LED 4

#define DHT11_PIN 7
#define DHT11_PIN_ALT 8

void setup(){
  Serial.begin(9600);
  pinMode(SENSOR_SWITCH, INPUT);
  pinMode(SENSOR_SWITCH_LED, OUTPUT);
}

void loop(){
  // when sensorNumber is HIGH this means that 3 pin humidity sensor is chosen
  int sensorNumber = digitalRead(SENSOR_SWITCH);
  digitalWrite(SENSOR_SWITCH_LED, sensorNumber);
  int humidityPin = ( sensorNumber == HIGH )? DHT11_PIN : DHT11_PIN_ALT;

  
  int chk = DHT.read11(humidityPin);
  Serial.print("sensor pin:");
  Serial.print(humidityPin);
  Serial.print("\tTemperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(2000); // reading should not occur more often than 2 seconds
}
