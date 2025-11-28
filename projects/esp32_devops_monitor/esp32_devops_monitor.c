#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// I2C pins for ESP32
#define I2C_SDA 21
#define I2C_SCL 22

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1      // We don't use reset pin
#define OLED_ADDR    0x3C    // Most 0.96" OLEDs use 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// AHT10 sensor
Adafruit_AHTX0 aht;

// LDR analog pin
const int LDR_PIN = 34;

// State variables
float lastTempC = 0.0;
float lastHum = 0.0;
int   lastLightPercent = 0;

// Timing
unsigned long lastSensorUpdate = 0;
const unsigned long sensorInterval = 1000;  // 1 second

unsigned long lastLogTime = 0;
const unsigned long logInterval = 5000;     // 5 seconds

void setup() {
  // Serial for logging
  Serial.begin(115200);
  delay(200);

  // I2C init
  Wire.begin(I2C_SDA, I2C_SCL);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 allocation failed");
    while (true) {
      delay(1000);
    }
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Embedded Systems Lab");
  display.println("ESP32 DevOps Monitor");
  display.display();
  delay(1500);

  // AHT10 init
  if (!aht.begin()) {
    Serial.println("Could not find AHT10/AHT20 sensor");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("AHT10 not found!");
    display.display();
    while (true) {
      delay(1000);
    }
  }

  // LDR pin
  pinMode(LDR_PIN, INPUT);

  Serial.println("Setup done.");
}

void loop() {
  unsigned long now = millis();

  // ---- Task 1: Read sensors every 1 second ----
  if (now - lastSensorUpdate >= sensorInterval) {
    lastSensorUpdate = now;
    readSensorsAndUpdateState();
    updateOLED();
  }

  // ---- Task 2: Log every 5 seconds ----
  if (now - lastLogTime >= logInterval) {
    lastLogTime = now;
    logStatus();
  }

  // No delay() -> non-blocking loop
}

void readSensorsAndUpdateState() {
  // Read AHT10 (temperature & humidity)
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // populate temp and humidity objects

  lastTempC = temp.temperature;
  lastHum   = humidity.relative_humidity;

  // Read LDR (0-4095 on ESP32)
  int raw = analogRead(LDR_PIN);

  // Map to 0-100% (you may invert this if it's reversed)
  int lightPercent = map(raw, 0, 4095, 100, 0);
  // If you see inverse behavior (dark -> high %), use:
  // int lightPercent = map(raw, 0, 4095, 100, 0);

  lastLightPercent = constrain(lightPercent, 0, 100);
}

void updateOLED() {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.println("ESP32 DevOps Monitor");
  display.println("--------------------");

  display.print("Temp: ");
  display.print(lastTempC, 1);
  display.println(" C");

  display.print("Hum : ");
  display.print(lastHum, 1);
  display.println(" %");

  display.print("Light: ");
  display.print(lastLightPercent);
  display.println(" %");

  display.display();
}

void logStatus() {
  unsigned long uptime = millis();
  Serial.print("[Log] Temp=");
  Serial.print(lastTempC, 1);
  Serial.print("C  Hum=");
  Serial.print(lastHum, 1);
  Serial.print("%  Light=");
  Serial.print(lastLightPercent);
  Serial.print("%  Uptime=");
  Serial.print(uptime);
  Serial.println("ms");
}
