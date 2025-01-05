#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
#include "DFRobot_EnvironmentalSensor.h"
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
#include <SoftwareSerial.h>
#endif

#define MODESWITCH        /*UART:*/1 /*I2C: 0*/

#if MODESWITCH
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
  SoftwareSerial mySerial(/*rx =*/11, /*tx =*/12);
  DFRobot_EnvironmentalSensor environment(/*addr =*/SEN050X_DEFAULT_DEVICE_ADDRESS, /*s =*/&mySerial);
#else
  DFRobot_EnvironmentalSensor environment(/*addr =*/SEN050X_DEFAULT_DEVICE_ADDRESS, /*s =*/&Serial1); 
#endif
#else
DFRobot_EnvironmentalSensor environment(/*addr = */SEN050X_DEFAULT_DEVICE_ADDRESS, /*pWire = */&Wire);
#endif
String temperature;
String humidity;
String uv;
String light;
String elevation;
String pressure;

int x=42;
int y=65;
int r1=40;
int r2=30;
int a1=0;
int a2;

int x1=42;
int y3=160;
int r3=40;
int r4=30;
int a3=0;
int a4; 

int x2=42;
int y4=255;
int r5=40;
int r6=30;
int a5=0;
int a6; 
 
int x3=126;
int y5=65;
int r7=40;
int r8=30;
int a7=0;
int a8; 
 
int x4=126;
int y6=160;
int r9=40;
int r10=30;
int a9=0;
int a10; 
 
int x5=126;
int y7=255;
int r11=40;
int r12=30;
int a11=0;
int a12;  

void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  sprite.createSprite(170,320);
  sprite.setTextColor(TFT_WHITE,TFT_BLACK);
  sprite.setTextDatum(4);

     //brightness
     ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, 160);
     #if MODESWITCH

#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
  mySerial.begin(9600);
#elif defined(ESP32)
  Serial1.begin(9600, SERIAL_8N1, /*rx =*/11, /*tx =*/12);
#else
  Serial1.begin(9600);
#endif
#endif
  Serial.begin(115200);

  while(environment.begin() != 0){
    Serial.println(" Sensor initialize failed!!");
    delay(1000);
  }
  Serial.println(" Sensor  initialize success!!");
}

void draw()
  {
    sprite.fillSprite(TFT_BLACK);
    sprite.drawSmoothArc(42, 65, 40, 30, 0, 360, TFT_SILVER, TFT_BLACK); 
     sprite.drawSmoothArc(42, 160, 40, 30, 0, 360, TFT_SILVER, TFT_BLACK);
      sprite.drawSmoothArc(42, 255, 40, 30, 0, 360, TFT_SILVER, TFT_BLACK);
       sprite.drawSmoothArc(126, 65, 40, 30, 0, 360, TFT_SILVER, TFT_BLACK);
        sprite.drawSmoothArc(126, 160, 40, 30, 0, 360, TFT_SILVER, TFT_BLACK);
         sprite.drawSmoothArc(126, 255, 40, 30, 0, 360, TFT_SILVER, TFT_BLACK);
    sprite.drawSmoothArc(x, y, r1, r2, a1, a2, TFT_BLUE, TFT_BLACK); 
    sprite.drawSmoothArc(x1, y3, r3, r4, a3, a4, TFT_YELLOW, TFT_BLACK);
    sprite.drawSmoothArc(x2, y4, r5, r6, a5, a6, TFT_CYAN, TFT_BLACK); 
    sprite.drawSmoothArc(x3, y5, r7, r8, a7, a8, TFT_MAGENTA, TFT_BLACK); 
    sprite.drawSmoothArc(x4, y6, r9, r10, a9, a10, TFT_RED, TFT_BLACK); 
    sprite.drawSmoothArc(x5, y7, r11, r12, a11, a12, TFT_GREEN, TFT_BLACK);   
    sprite.setFreeFont(&Orbitron_Light_24);

 sprite.drawString( temperature.substring(0,4),42,65,4);
  temperature=String(environment.getTemperature(TEMP_C));
  
 sprite.drawString( humidity.substring(0,4),42,160,4);
  humidity=String(environment.getHumidity());
 sprite.drawString( uv.substring(0,4),42,255,4);
  uv=String(environment.getUltravioletIntensity());
 sprite.drawString( light.substring(0,3),126,65,4);
  light=String(environment.getLuminousIntensity());
 sprite.drawString( pressure.substring(0,4),126,160,2);
  pressure=String(environment.getAtmospherePressure(HPA));
 sprite.drawString( elevation.substring(0,4),126,255,2);
 elevation=String(environment.getElevation());
 sprite.setFreeFont(&Orbitron_Light_24);
 sprite.setTextFont(0);
 sprite.drawString("Temp(C)",42,80);
 sprite.drawString("Hum%",42,177);
 sprite.drawString("UV",42,270);
 sprite.drawString("LX",126,80);
 sprite.drawString("HPA",126,177);
 sprite.drawString("(M)",126,270);
 sprite.setTextFont(1);
 sprite.drawString("WEATHER STATION",100,310);
 sprite.pushSprite(0,0);

 
  }

void loop() {
  a2 =map(environment.getTemperature(TEMP_C),1,100,1,360);
  a4=map(environment.getHumidity(),1,100,1,360);
  a6=map(environment.getUltravioletIntensity(),0,10,2,360);
  a8=map(environment.getLuminousIntensity(),1,1000,1,360);
  a10=map(environment.getAtmospherePressure(HPA),1,1500,1,360);
  a12=map(environment.getElevation(),800,2000,1,360);
  draw();
  Serial.println("-------------------------------");
  Serial.print("Temp: ");
  Serial.print(environment.getTemperature(TEMP_C));
  Serial.println(" ℃");
  Serial.print("Temp: ");
  Serial.print(environment.getTemperature(TEMP_F));
  Serial.println(" ℉");
  Serial.print("Humidity: ");
  Serial.print(environment.getHumidity());
  Serial.println(" %");
  Serial.print("Ultraviolet intensity: ");
  Serial.print(environment.getUltravioletIntensity());
  Serial.println(" mw/cm2");
  Serial.print("LuminousIntensity: ");
  Serial.print(environment.getLuminousIntensity());
  Serial.println(" lx");
  Serial.print("Atmospheric pressure: ");
  Serial.print(environment.getAtmospherePressure(HPA));
  Serial.println(" hpa");
  Serial.print("Elevation: ");
  Serial.print(environment.getElevation());
  Serial.println(" m");
  Serial.println("-------------------------------");
  delay(500);
}
