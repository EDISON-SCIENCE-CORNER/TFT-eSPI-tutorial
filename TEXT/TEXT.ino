#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void setup() {
  tft.init();
  tft.fillScreen(TFT_CYAN);
  tft.setSwapBytes(true);
  tft.setRotation(1);
  sprite.createSprite(320,170);
  sprite.setTextColor(TFT_BLACK,TFT_CYAN);
  sprite.setTextDatum(4);


}

void draw()
  {
    sprite.fillSprite(TFT_CYAN);
    
    sprite.setFreeFont(&Orbitron_Light_24);
 sprite.drawString("EDISON",160,40);
 sprite.drawString("SCIENCE",160,80);
 sprite.drawString("CORNER",160,120);
 sprite.pushSprite(0,0);

 
  }

void loop() {
  draw();
}
