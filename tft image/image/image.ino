#include <TFT_eSPI.h>
#include "image.h"
TFT_eSPI tft = TFT_eSPI();

void setup()
{
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.pushImage(10,100,150,150,image);
}

void loop()
{
  
}