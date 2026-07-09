// Use the ESP32-WROOM-DA Module from espressif
// Reference this schematic: https://www.amazon.com/DIYmall-ESP32-2432S028R-Dual-core-240X320-Display/dp/B0BVFXR313
// Add this link to your board manager URLs in Preferences: https://espressif.github.io/arduino-esp32/package_esp32_index.json, and search for "esp32" in your board manager after adding it

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// ESP32 display pins
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4
#define TFT_BL   21

// colors !!
#define PINK 0xFA74
#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREEN 0x27E4
#define DARKGREEN 0x0200
#define YELLOWGREEN 0xAFE5
#define YELLOW 0xFD20
#define ORANGE 0xF800
#define BROWN  0xA145

// initialize global stuff for display
SPIClass hspi = SPIClass(HSPI);
Adafruit_ILI9341 tft = Adafruit_ILI9341(&hspi, TFT_DC, TFT_CS, TFT_RST);

void setup() {
  // turn on display
  Serial.begin(115200);
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  hspi.begin(TFT_SCLK, TFT_MISO, TFT_MOSI, TFT_CS);
  tft.begin();
  tft.setRotation(1); 
  tft.fillScreen(WHITE);
  delay(10); 
  tft.fillScreen(BLACK); 
  loading(); // loading function (for aesthetics, not actually loading anything lol)

  // text
  tft.setCursor(35, 20);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.println("happy birthday");
  tft.setCursor(tft.width()/2-30, 50);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.println("unc!");
  
  // cake
  tft.drawEllipse(tft.width()/2, tft.height()/2+20, 60, 30, GREEN);
  drawHalfEllipse(tft.width()/2, tft.height()/2+35, 60, 30, GREEN);
  drawHalfEllipse(tft.width()/2, tft.height()/2+50, 60, 30, GREEN);
  tft.drawLine(tft.width()/2-60, tft.height()/2+20, tft.width()/2-60, tft.height()/2+50, GREEN);
  tft.drawLine(tft.width()/2+60, tft.height()/2+20, tft.width()/2+60, tft.height()/2+50, GREEN);
  
  // number
  tft.setCursor(tft.width()/2-12, tft.height()/2+20);
  tft.setTextColor(DARKGREEN);
  tft.setTextSize(2);
  tft.println("23");

  // candles
  drawCandle(tft.width()/2 - 35, tft.height()/2 + 15);
  drawCandle(tft.width()/2 - 15, tft.height()/2 + 10);
  drawCandle(tft.width()/2 + 5,  tft.height()/2 + 10);
  drawCandle(tft.width()/2 + 25, tft.height()/2 + 15);
}




void drawCandle(int16_t x, int16_t y) {
  // candle dimensions
  const int candleWidth = 8;
  const int candleHeight = 22;

  // candle body
  tft.fillRect(x, y - candleHeight, candleWidth, candleHeight, YELLOWGREEN);
  tft.drawRect(x, y - candleHeight, candleWidth, candleHeight, GREEN);

  // wick
  int wickX = x + candleWidth / 2;
  tft.drawLine(wickX, y - candleHeight, wickX, y - candleHeight - 4, BROWN);

  // flame (outer)
  tft.fillTriangle(
    wickX,     y - candleHeight - 14,
    wickX - 4, y - candleHeight - 4,
    wickX + 4, y - candleHeight - 4,
    ORANGE
  );

  // flame (inner)
  tft.fillTriangle(
    wickX,     y - candleHeight - 11,
    wickX - 2, y - candleHeight - 5,
    wickX + 2, y - candleHeight - 5,
    YELLOW
  );
}

void drawHalfEllipse(int16_t centerX, int16_t centerY, int16_t radiusX, int16_t radiusY, uint16_t color) {
  // calculate the starting pixel at 0 degrees (right side edge)
  int16_t lastX = centerX + radiusX;
  int16_t lastY = centerY;

  // loop from 0 to 180 degrees to draw the bottom bowl curve
  for (int angle = 0; angle <= 180; angle += 2) {
    float rad = angle * DEG_TO_RAD; // converts degrees to radians
    int16_t x = centerX + (cos(rad) * radiusX);
    int16_t y = centerY + (sin(rad) * radiusY); // sin is positive, moving it downward

    // connect the dots (ha ha ha)
    tft.drawLine(lastX, lastY, x, y, color);
    
    lastX = x;
    lastY = y;
  }
}


void loading(){
  // will make this better later
  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading");

  delay(2000);

  tft.fillScreen(BLACK); 

  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading.");

  delay(500);

  tft.fillScreen(BLACK); 

  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading..");

  delay(500);

  tft.fillScreen(BLACK); 

  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading...");

  delay(2000);

  tft.fillScreen(BLACK); 

  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading");

  delay(500);

  tft.fillScreen(BLACK); 

  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading.");

  delay(500);

  tft.fillScreen(BLACK); 

  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading..");

  delay(500);

  tft.fillScreen(BLACK); 

  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading...");

  delay(2000);

  tft.fillScreen(BLACK); 

  tft.setCursor(50, 100);
  tft.setTextColor(PINK);
  tft.setTextSize(4);
  tft.println("Loading :)");

  delay(500);

  tft.fillScreen(BLACK);
}

void loop() {
  // not looping anything as of now
}