#include <SPI.h>
#include <ILI9341_t3.h>

#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8

// Create display object
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ILI9341 Communication Test Starting...");

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  // Static text test
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("ILI9341 SPI TEST");

  tft.setTextSize(1);
  tft.setCursor(10, 40);
  tft.println("Teensy 4.1");
  tft.println("MC -> Display OK");

  delay(2000);
}

void loop() {
  // Color fill test
  tft.fillScreen(ILI9341_RED);
  delay(500);
  tft.fillScreen(ILI9341_GREEN);
  delay(500);
  tft.fillScreen(ILI9341_BLUE);
  delay(500);

  // Dynamic update test
  static int counter = 0;

  tft.fillRect(0, 100, 320, 40, ILI9341_BLACK);
  tft.setCursor(10, 110);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.print("Count: ");
  tft.print(counter++);

  delay(500);
}
