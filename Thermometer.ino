/*


CONNECTION:

0.96 inch OLED:
VCC > +5
GND > GND
SCL > A5
SDA > A4

DTH11:
S > 2
MID > +5
- > GND


You must include the following libraries:
https://github.com/adafruit/DHT-sensor-library
https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/Adafruit_SSD1306


*/


//DISPLAY
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


//DHT11
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);



void DispayMessage(String text, int delayMs = 1000, byte size = 2)
{
	display.clearDisplay();

	display.setCursor(0, 0);
	display.setTextSize(size);
	display.setTextColor(WHITE);
	display.println(text);

	display.display();

	Serial.println(text);

	delay(delayMs);
}

void DispayTemperature(float temperature, float humidity, float heatindex)
{
	display.clearDisplay();

	display.setCursor(0, 0);
	display.setTextColor(WHITE);

	display.setTextSize(2);
	display.print("H:");
	display.print((int)humidity);
	display.println(" %");

	display.setTextSize(1);
	display.println("");

	display.setTextSize(3);
	display.print("T:");
	display.print((int)temperature);
	display.println(" C");

	display.setTextSize(1);
	display.println("");

	display.print("HI:");
	display.print((int)heatindex);
	display.println(" C");

	display.display();


	Serial.print("Temperature: ");
	Serial.print(temperature);
	Serial.print(" C ");

	Serial.print("Humidity: ");
	Serial.print(humidity);
	Serial.print(" %\t");

	Serial.print("Heat index: ");
	Serial.print(heatindex);
	Serial.print(" C ");

}


void setup() {
	Serial.begin(9600);

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	dht.begin();

	DispayMessage("Starting..");
}


void loop() {
	delay(2000);

	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t)) {
		DispayMessage("Failed to read from DHT sensor!", 2000, 1);
		return;
	}

	// Compute heat index in Celsius (isFahreheit = false)
	float hic = dht.computeHeatIndex(t, h, false);

	char buffer[10];
	DispayTemperature(t, h, hic);
}


