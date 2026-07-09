// Use the ESP32-WROOM-DA Module from espressif
// Reference this schematic: https://www.amazon.com/DIYmall-ESP32-2432S028R-Dual-core-240X320-Display/dp/B0BVFXR313
// Add this link to your board manager URLs in Preferences: https://espressif.github.io/arduino-esp32/package_esp32_index.json, and search for "esp32" in your board manager after adding it

#include <Adafruit_ILI9341.h>

// RGB LED
#define LEDR  4 // Active LOW
#define LEDG 16 // Active LOW
#define LEDB 17 // Active LOW

// Photoresistor and piezo
#define PHOTO_RES 34 // Does not seem to work with analogRead(), more testing required
#define PIEZO 26

// ILI9341 Display
#define BKLT     21 // Active HIGH
#define TFT_SCK  14
#define TFT_MOSI 13
#define TFT_MISO 12
#define TFT_DC    2
#define TFT_CS   15

// XPT2046 Chip
#define TP_SCK 25
#define TP_DIN 32
#define TP_OUT 39
#define TP_IRQ 36
#define TP_CS  33

void setup() {
  // Define LED pins as outputs
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Turn LED off (active low signal)
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

void loop() {
  // Turn the green LED on
  digitalWrite(LEDG, LOW);
  delay(1000);

  // Turn the green LED off
  digitalWrite(LEDG, HIGH);
  delay(1000);
}
