// pico index url: https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
// use Raspberry Pi Pico package by Earle Philhower
// in board/port selection, search for "raspberry pi pico" and select it (rp2040)
// libraries to install: "ESP8266Audio" (earle philhower), "Adafruit GFX Library" (Adafruit), "Adafruit ST7735 and ST7789 Library" (Adafruit)
// if it asks to install dependencies, click yes (obviously.. pfft i knew that)

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#include <SD.h>

#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include <AudioFileSourceSD.h>

// display pins
#define TFT_SCLK 22
#define TFT_MOSI 24
#define TFT_CS   25
#define TFT_DC   26
#define TFT_RST  30
#define TFT_BL   29

// SD shares CS with display
#define SD_CS TFT_CS

// MAX98357A I2S pins
#define I2S_BCLK 0
#define I2S_DOUT 1
#define I2S_LRC  2

// audio variables
AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;

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
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // turn on display
  Serial.begin(115200);

  // backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // begin SPI
  SPI.setSCK(TFT_SCLK);
  SPI.setTX(TFT_MOSI);
  SPI.begin();

  // using the display now
  tft.init(240, 320);
  tft.setRotation(1); 

  // aesthetic loading function that does literally nothing 
  loading();

  // display actual birthday animation
  drawBirthday();






 

}

void drawBirthday(){
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
  tft.fillScreen(WHITE);
  delay(10); 
  tft.fillScreen(BLACK);





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