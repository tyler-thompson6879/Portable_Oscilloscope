#include <SPI.h>
#include <ILI9341_t3n.h>
#include <math.h>

// pins
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8

#define ILI9341_DARKGREY 0x7BEF

ILI9341_t3n tft(TFT_CS, TFT_DC, TFT_RST);

// display
#define SCREEN_W 320
#define SCREEN_H 240
#define DISPLAY_POINTS 320
#define GRID_X_DIVS 10
#define GRID_Y_DIVS 8

// waveform buffers
uint16_t waveBuffer[DISPLAY_POINTS];
uint16_t lastY[DISPLAY_POINTS];

// setup
void setup() {
  tft.begin();
  tft.setRotation(1);
  drawGrid();

  // initialize buffers to center line
  for (int i = 0; i < DISPLAY_POINTS; i++) {
    waveBuffer[i] = SCREEN_H / 2;
    lastY[i] = SCREEN_H / 2;
  }
}

// main loop
void loop() {
  generateTestWave();
  drawWaveformWithGrid();
  delay(16);
}

// grid
void drawGrid() {
  tft.fillScreen(ILI9341_BLACK);

  // vertical divisions
  for (int i = 0; i <= GRID_X_DIVS; i++) {
    int x = i * (SCREEN_W / GRID_X_DIVS);
    tft.drawLine(x, 0, x, SCREEN_H, ILI9341_DARKGREY);
  }

  // horizontal divisions
  for (int i = 0; i <= GRID_Y_DIVS; i++) {
    int y = i * (SCREEN_H / GRID_Y_DIVS);
    tft.drawLine(0, y, SCREEN_W, y, ILI9341_DARKGREY);
  }

  // center reference line
  tft.drawLine(0, SCREEN_H / 2, SCREEN_W, SCREEN_H / 2, ILI9341_BLUE);
}

// test wave
void generateTestWave() {
  static float phase = 0.0f;

  for (int i = 0; i < DISPLAY_POINTS; i++) {
    float s = sinf(phase + i * 0.05f);
    waveBuffer[i] = (SCREEN_H / 2) - (s * (SCREEN_H / 3));
  }

  phase += 0.08f;
}

// reduce flicker
void drawWaveformWithGrid() {
  for (int i = 1; i < DISPLAY_POINTS; i++) {
    int x0 = i - 1;
    int x1 = i;
    int y0 = lastY[x0];
    int y1 = lastY[x1];

    // erase old waveform by redrawing grid lines over old waveform range
    tft.drawLine(x0, y0, x1, y1, ILI9341_BLACK);

    // redraw vertical grid lines if waveform passed through them
    for (int g = 0; g <= GRID_X_DIVS; g++) {
      int gx = g * (SCREEN_W / GRID_X_DIVS);
      if ((x0 <= gx && gx <= x1) || (x1 <= gx && gx <= x0)) {
        tft.drawLine(gx, 0, gx, SCREEN_H, ILI9341_DARKGREY);
      }
    }

    // redraw horizontal grid lines if waveform passed through them
    for (int g = 0; g <= GRID_Y_DIVS; g++) {
      int gy = g * (SCREEN_H / GRID_Y_DIVS);
      if ((y0 <= gy && gy <= y1) || (y1 <= gy && gy <= y0)) {
        tft.drawLine(0, gy, SCREEN_W, gy, ILI9341_DARKGREY);
      }
    }

    // redraw center line if waveform passed through it
    int cy = SCREEN_H / 2;
    if ((y0 <= cy && cy <= y1) || (y1 <= cy && cy <= y0)) {
      tft.drawLine(0, cy, SCREEN_W, cy, ILI9341_BLUE);
    }
  }

  // draw new waveform
  for (int i = 1; i < DISPLAY_POINTS; i++) {
    int y = waveBuffer[i];
    tft.drawLine(i - 1, lastY[i - 1], i, y, ILI9341_GREEN);
    lastY[i] = y;
  }
}
