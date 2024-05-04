#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define the pins for the sensors
const int MQ7_AOUTpin = A0; // the AOUT pin of the MQ7 sensor goes into analog pin A0 of the arduino
const int MQ7_DOUTpin = 8; // the DOUT pin of the MQ7 sensor goes into digital pin D8 of the arduino
const int MQ6_AOUTpin = A1; // the AOUT pin of the MQ6 sensor goes into analog pin A1 of the arduino
const int MQ6_DOUTpin = 9; // the DOUT pin of the MQ6 sensor goes into digital pin D9 of the arduino
const int MQ4_AOUTpin = A2; // the AOUT pin of the MQ4 sensor goes into analog pin A2 of the arduino
const int MQ4_DOUTpin = 10; // the DOUT pin of the MQ4 sensor goes into digital pin D10 of the arduino
const int ledPin = 13; // the anode of the LED connects to digital pin D13 of the arduino
const int BUZZER_PIN = 11; // Connect Buzzer to Digital Pin 11
const int DHT_PIN = 7; // Connect DHT11 Data pin to Digital Pin 7

int mq7Value;
int mq6Value;
int mq4Value;

DHT dht(DHT_PIN, DHT11);

void setup() {
  Serial.begin(9600); // sets the baud rate to 9600
  pinMode(MQ7_DOUTpin, INPUT); // sets the pin as an input to the arduino
  pinMode(MQ6_DOUTpin, INPUT); // sets the pin as an input to the arduino
  pinMode(MQ4_DOUTpin, INPUT); // sets the pin as an input to the arduino
  pinMode(ledPin, OUTPUT); // sets the pin as an output of the arduino
  pinMode(BUZZER_PIN, OUTPUT); // sets the pin as an output of the arduino

  dht.begin(); // Initialize DHT sensor
}

void loop() {
  mq7Value = analogRead(MQ7_AOUTpin); // reads the analog value from the MQ7 sensor's AOUT pin
  Serial.print("Carbon Monoxide Sensor MQ7 value: ");
  Serial.println(mq7Value); // prints the MQ7 value
  
  mq6Value = analogRead(MQ6_AOUTpin); // reads the analog value from the MQ6 sensor's AOUT pin
  Serial.print("Gas Sensor MQ6 value: ");
  Serial.println(mq6Value); // prints the MQ6 value
  
  mq4Value = analogRead(MQ4_AOUTpin); // reads the analog value from the MQ4 sensor's AOUT pin
  Serial.print("Methane Sensor MQ4 value: ");
  Serial.println(mq4Value); // prints the MQ4 value

  float temperature = dht.readTemperature(); // Read temperature from DHT11
  float humidity = dht.readHumidity(); // Read humidity from DHT11
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  if (mq7Value > 200 || mq6Value > 200 || mq4Value > 200) {
    // Activate the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(ledPin, HIGH); // Turn on the LED as well
  } else {
    // Deactivate the buzzer
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ledPin, LOW); // Turn off the LED
  }

  delay(2000);
}