#include "ClickButton.h"
#include <Adafruit_NeoPixel.h>

#define PIN_Strip_a 16              //Strip Vorne Links
#define PIN_Strip_b 17              //Strip Vorne Rechts
#define PIN_Strip_c 19              //Strip Hinten Links
#define PIN_Strip_d 18              //Strip Hinten Rechts
#define NUMPIXEL_a 7
#define NUMPIXEL_b 7
#define NUMPIXEL_c 7
#define NUMPIXEL_d 7

unsigned long previousMillis = 0;
const int buttonPin1 = 26;      //Lichthorn
const int buttonPin2 = 25;      //Blinker Links
const int buttonPin3 = 33;      //Blinker Rechts
const int buttonPin4 = 32;      //Warnblinklicht
const long intervalwbl = 80;    //Blinkzeit Warnblinklicht
const long intervalbli = 100;   //Blinkzeit Blinker
long TimeFL = 50;               //Blitzzeit Blaulicht
long TimeRB = 5;                //Timer Rainbow
int ledState = LOW;
int wblState = LOW;             //Warnblinklicht Zähler
int blState = LOW;              //Blaulicht Zähler
int rbState = LOW;              //Rainbow Zähler
unsigned long ZaehlerBL = 0;
unsigned long ZaehlerWBL = 0;


ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);  //Licht/Lichthupe
ClickButton button2(buttonPin2, LOW, CLICKBTN_PULLUP);  //Blinker Links
ClickButton button3(buttonPin3, LOW, CLICKBTN_PULLUP);  //Blinker Rechts
ClickButton button4(buttonPin4, LOW, CLICKBTN_PULLUP);  //Warnblinklicht

Adafruit_NeoPixel strip_a = Adafruit_NeoPixel(NUMPIXEL_a, PIN_Strip_a, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip_b = Adafruit_NeoPixel(NUMPIXEL_b, PIN_Strip_b, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip_c = Adafruit_NeoPixel(NUMPIXEL_c, PIN_Strip_c, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_d = Adafruit_NeoPixel(NUMPIXEL_d, PIN_Strip_d, NEO_GRB + NEO_KHZ800);


//Farben Strips Vorne
uint32_t blue_a = strip_a.Color(0, 0, 255, 0 );
uint32_t orange_a = strip_a.Color(255, 120, 0, 0);
uint32_t white_a = strip_a.Color(0, 0, 0, 255);
uint32_t off_a = strip_a.Color(0, 0, 0, 0);

uint32_t blue_b = strip_b.Color(0, 0, 255, 0 );
uint32_t orange_b = strip_b.Color(255, 120, 0, 0);
uint32_t white_b = strip_b.Color(0, 0, 0, 255);
uint32_t off_b = strip_b.Color(0, 0, 0, 0);

//Farben Strip Hinten
uint32_t blue_c = strip_c.Color(0, 0, 255);
uint32_t red_c = strip_c.Color(255, 0, 0);
uint32_t orange_c = strip_c.Color(255, 120, 0);
uint32_t off_c = strip_c.Color(0, 0, 0);

uint32_t blue_d = strip_d.Color(0, 0, 255);
uint32_t red_d = strip_d.Color(255, 0, 0);
uint32_t orange_d = strip_d.Color(255, 120, 0);
uint32_t off_d = strip_d.Color(0, 0, 0);

void setup()
{

  Serial.begin(9600);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  WiFi.mode(WIFI_OFF);
  btStop();
  strip_a.begin();
  strip_b.begin();
  strip_c.begin();
  strip_d.begin();
  strip_a.show();
  strip_b.show();
  strip_c.show();
  strip_d.show();
  button1.debounceTime   = 100;  // Debounce timer in ms
  button1.multiclickTime = 250;  // Time limit for multi clicks
  button1.longClickTime  = 2000; // time until "held-down clicks" register
  button2.debounceTime   = 100;  // Debounce timer in ms
  button2.multiclickTime = 250;  // Time limit for multi clicks
  button2.longClickTime  = 2000; // time until "held-down clicks" register
  button3.debounceTime   = 100;  // Debounce timer in ms
  button3.multiclickTime = 250;  // Time limit for multi clicks
  button3.longClickTime  = 2000; // time until "held-down clicks" register
  button4.debounceTime   = 100;  // Debounce timer in ms
  button4.multiclickTime = 250;  // Time limit for multi clicks
  button4.longClickTime  = 2000; // time until "held-down clicks" register
  Licht();
}


void loop() {
  unsigned long currentMillis = millis();

  button1.Update();
  if (button1.clicks == 1) {
    Serial.println("Taster 1 - 1 mal gedrückt");
    Lichthupe();
  }
  else if (button1.clicks == 2 ) {
    Serial.println("Taster 1 - 2 mal gedrückt");
    Licht();
  }
  else if (button1.clicks == 3 ) {
    Serial.println("Taster 1 - 3 mal gedrückt");
    if (rbState == LOW) {
      blState = LOW;
      wblState = LOW;
      rbState = HIGH;
    }
    else {
      rbState = LOW;
      Licht();
    }
  }

  button2.Update();
  if (button2.clicks == 1) {
    Serial.println("Taster 2 - 1 mal gedrückt");
    Licht();
    delay(50);
    Blinker_Links();
    Blinker_Links();
    Blinker_Links();
    Licht();
  }
  else if (button2.clicks == 2 ) {
    Serial.println("Taster 2 - 2 mal gedrückt");
    Licht();
  }

  button3.Update();
  if (button3.clicks == 1) {
    Serial.println("Taster 3 - 1 mal gedrückt");
    Licht();
    delay(50);
    Blinker_Rechts();
    Blinker_Rechts();
    Blinker_Rechts();
    Licht();
  }
  else if (button3.clicks == 2 ) {
    Serial.println("Taster 3 - 2 mal gedrückt");
    Licht();
  }

  button4.Update();
  if (button4.clicks == 1) {
    Serial.println("Taster 4 - 1 mal gedrückt");
    if (wblState == LOW) {
      blState = LOW;
      wblState = HIGH;
    }
    else {
      wblState = LOW;
      Licht();
    }
  }


  else if (button4.clicks == 2 ) {
    Serial.println("Taster 4 - 2 mal gedrückt");
    if (blState == LOW) {
      wblState = LOW;
      blState = HIGH;
    }
    else {
      blState = LOW;
      ZaehlerBL = 0;
      Licht();
    }

  }

  //WARNBLINKLICHT
  if ((currentMillis - previousMillis >= intervalwbl) && (wblState == HIGH)) {
    previousMillis = currentMillis;
    strip_a.setBrightness(180);
    strip_b.setBrightness(180);
    strip_c.setBrightness(180);
    strip_d.setBrightness(180);
    
    if (ZaehlerWBL == 0)     //Oben AN
    {
      strip_a.fill(orange_a, 0, 3);
      strip_a.fill(orange_a, 6, 1);
      strip_b.fill(orange_b, 0, 3);
      strip_b.fill(orange_b, 6, 1);
      strip_c.fill(orange_c, 0, 3);
      strip_c.fill(orange_c, 6, 1);
      strip_d.fill(orange_d, 0, 3);
      strip_d.fill(orange_d, 6, 1);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 1)    //Oben AUS
    {
      strip_a.fill(off_a, 0, 7);
      strip_b.fill(off_b, 0, 7);
      strip_c.fill(off_c, 0, 7);
      strip_d.fill(off_d, 0, 7);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 2) //Oben AN
    {
      strip_a.fill(orange_a, 0, 3);
      strip_a.fill(orange_a, 6, 1);
      strip_b.fill(orange_b, 0, 3);
      strip_b.fill(orange_b, 6, 1);
      strip_c.fill(orange_c, 0, 3);
      strip_c.fill(orange_c, 6, 1);
      strip_d.fill(orange_d, 0, 3);
      strip_d.fill(orange_d, 6, 1);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 3) //Oben AUS
    {
      strip_a.fill(off_a, 0, 7);
      strip_b.fill(off_b, 0, 7);
      strip_c.fill(off_c, 0, 7);
      strip_d.fill(off_d, 0, 7);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 4) //Oben AN
    {
      strip_a.fill(orange_a, 0, 3);
      strip_a.fill(orange_a, 6, 1);
      strip_b.fill(orange_b, 0, 3);
      strip_b.fill(orange_b, 6, 1);
      strip_c.fill(orange_c, 0, 3);
      strip_c.fill(orange_c, 6, 1);
      strip_d.fill(orange_d, 0, 3);
      strip_d.fill(orange_d, 6, 1);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 5) //Oben AUS
    {
      strip_a.fill(off_a, 0, 7);
      strip_b.fill(off_b, 0, 7);
      strip_c.fill(off_c, 0, 7);
      strip_d.fill(off_d, 0, 7);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 6)    //Unten AN
    {
      strip_a.fill(orange_a, 3, 3);
      strip_b.fill(orange_b, 3, 3);
      strip_c.fill(orange_c, 3, 3);
      strip_d.fill(orange_d, 3, 3);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 7)  //Unten AUS
    {
      strip_a.fill(off_a, 0, 7);
      strip_b.fill(off_b, 0, 7);
      strip_c.fill(off_c, 0, 7);
      strip_d.fill(off_d, 0, 7);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 8)    //Unten AN
    {
      strip_a.fill(orange_a, 3, 3);
      strip_b.fill(orange_b, 3, 3);
      strip_c.fill(orange_c, 3, 3);
      strip_d.fill(orange_d, 3, 3);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 9)  //Unten AUS
    {
      strip_a.fill(off_a, 0, 7);
      strip_b.fill(off_b, 0, 7);
      strip_c.fill(off_c, 0, 7);
      strip_d.fill(off_d, 0, 7);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 10)    //Unten AN
    {
      strip_a.fill(orange_a, 3, 3);
      strip_b.fill(orange_b, 3, 3);
      strip_c.fill(orange_c, 3, 3);
      strip_d.fill(orange_d, 3, 3);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL++;
    }
    else if (ZaehlerWBL == 11)  //Unten AUS
    {
      strip_a.fill(off_a, 0, 7);
      strip_b.fill(off_b, 0, 7);
      strip_c.fill(off_c, 0, 7);
      strip_d.fill(off_d, 0, 7);
      strip_a.show();
      strip_b.show();
      strip_c.show();
      strip_d.show();
      ZaehlerWBL = 0;
    }
  }

    //Blaulicht
    if ((currentMillis - previousMillis >= TimeFL) && (blState == HIGH)) {
      previousMillis = currentMillis;
      strip_a.setBrightness(180);
      strip_b.setBrightness(180);
      strip_c.setBrightness(180);
      strip_d.setBrightness(180);
      if (ZaehlerBL == 0)     
      {
        strip_a.fill(blue_a, 0, 3); //A oben
        strip_a.fill(blue_a, 6, 1); //A oben
        strip_d.fill(blue_d, 0, 3); //D oben
        strip_d.fill(blue_d, 6, 1); //D oben
        strip_b.fill(blue_b, 3, 3); //B unten
        strip_c.fill(blue_c, 3, 3); //B unten
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 1)    
      {
        strip_a.fill(off_a, 0, 7);
        strip_b.fill(off_b, 0, 7);
        strip_c.fill(off_c, 0, 7);
        strip_d.fill(off_d, 0, 7);
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 2) 
      {
        strip_a.fill(blue_a, 0, 3); //A oben
        strip_a.fill(blue_a, 6, 1); //A oben
        strip_d.fill(blue_d, 0, 3); //D oben
        strip_d.fill(blue_d, 6, 1); //D oben
        strip_b.fill(blue_b, 3, 3); //B unten
        strip_c.fill(blue_c, 3, 3); //B unten
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 3) 
      {
        strip_a.fill(off_a, 0, 7);
        strip_b.fill(off_b, 0, 7);
        strip_c.fill(off_c, 0, 7);
        strip_d.fill(off_d, 0, 7);
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 4)
      {
        strip_a.fill(blue_a, 0, 3); //A oben
        strip_a.fill(blue_a, 6, 1); //A oben
        strip_d.fill(blue_d, 0, 3); //D oben
        strip_d.fill(blue_d, 6, 1); //D oben
        strip_b.fill(blue_b, 3, 3); //B unten
        strip_c.fill(blue_c, 3, 3); //B unten
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 5) 
      {
        strip_a.fill(off_a, 0, 7);
        strip_b.fill(off_b, 0, 7);
        strip_c.fill(off_c, 0, 7);
        strip_d.fill(off_d, 0, 7);
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 6)    
      {
        strip_a.fill(blue_a, 3, 3);   //A unten
        strip_d.fill(blue_d, 3, 3);   //D unten
        strip_b.fill(blue_b, 0, 3);   //B Oben
        strip_b.fill(blue_d, 6, 1);   //B Oben
        strip_c.fill(blue_c, 0, 3);   //D Oben
        strip_c.fill(blue_c, 6, 1);   //D Oben
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 7)  
      {
        strip_a.fill(off_a, 0, 7);
        strip_b.fill(off_b, 0, 7);
        strip_c.fill(off_c, 0, 7);
        strip_d.fill(off_d, 0, 7);
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 8)    //Unten AN
      {
        strip_a.fill(blue_a, 3, 3);   //A unten
        strip_d.fill(blue_d, 3, 3);   //D unten
        strip_b.fill(blue_b, 0, 3);   //B Oben
        strip_b.fill(blue_d, 6, 1);   //B Oben
        strip_c.fill(blue_c, 0, 3);   //D Oben
        strip_c.fill(blue_c, 6, 1);   //D Oben
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 9)  //Unten AUS
      {
        strip_a.fill(off_a, 0, 7);
        strip_b.fill(off_b, 0, 7);
        strip_c.fill(off_c, 0, 7);
        strip_d.fill(off_d, 0, 7);
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 10)    //Unten AN
      {
        strip_a.fill(blue_a, 3, 3);   //A unten
        strip_d.fill(blue_d, 3, 3);   //D unten
        strip_b.fill(blue_b, 0, 3);   //B Oben
        strip_b.fill(blue_d, 6, 1);   //B Oben
        strip_c.fill(blue_c, 0, 3);   //D Oben
        strip_c.fill(blue_c, 6, 1);   //D Oben
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL++;
      }
      else if (ZaehlerBL == 11)  //Unten AUS
      {
        strip_a.fill(off_a, 0, 7);
        strip_b.fill(off_b, 0, 7);
        strip_c.fill(off_c, 0, 7);
        strip_d.fill(off_d, 0, 7);
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        ZaehlerBL = 0;
      }
    }

    //Rainbow
    if ((currentMillis - previousMillis >= TimeRB) && (rbState == HIGH)) {
      previousMillis = currentMillis;
      strip_a.setBrightness(180);
      strip_b.setBrightness(180);
      strip_c.setBrightness(180);
      strip_d.setBrightness(180);


      for (long firstPixelHue = 0; firstPixelHue < 50 * 65536; firstPixelHue += 256) {
        for (int i = 0; i < strip_a.numPixels(); i++) { // For each pixel in strip...
          // Offset pixel hue by an amount to make one full revolution of the
          // color wheel (range of 65536) along the length of the strip
          // (strip.numPixels() steps):

          int pixelHue = firstPixelHue + (i * 65536L / strip_a.numPixels());
          strip_a.setPixelColor(i, strip_a.gamma32(strip_a.ColorHSV(pixelHue)));
          strip_b.setPixelColor(i, strip_b.gamma32(strip_b.ColorHSV(pixelHue)));
          strip_c.setPixelColor(i, strip_c.gamma32(strip_c.ColorHSV(pixelHue)));
          strip_d.setPixelColor(i, strip_d.gamma32(strip_d.ColorHSV(pixelHue)));

        }
        strip_a.show();
        strip_b.show();
        strip_c.show();
        strip_d.show();
        delay(10);
      }
    }
    // --- ENDE ---
  }


  //-----------Funktionen-----------

  void Blinker_Rechts() {
    strip_b.fill(off_a, 0, 7);
    strip_d.fill(off_c, 0, 7);
    strip_b.show();
    strip_d.show();
    delay(intervalbli);
    strip_b.setBrightness(100);
    strip_d.setBrightness(100);
    strip_b.fill(orange_b, 0, 1);
    strip_d.fill(orange_d, 0, 1);
    strip_b.show();
    strip_d.show();
    delay(intervalbli);
    strip_b.fill(orange_b, 1, 1);
    strip_d.fill(orange_d, 1, 1);
    strip_b.show();
    strip_d.show();
    delay(intervalbli);
    strip_b.fill(orange_b, 6, 1);
    strip_d.fill(orange_d, 2, 1);
    strip_b.show();
    strip_d.show();
    delay(intervalbli);
    strip_b.fill(orange_b, 5, 1);
    strip_d.fill(orange_d, 3, 1);
    strip_b.show();
    strip_d.show();
    delay(intervalbli);
    strip_b.fill(orange_b, 4, 1);
    strip_d.fill(orange_d, 4, 1);
    strip_b.show();
    strip_d.show();
    delay(intervalbli);
    strip_b.fill(orange_b, 3, 1);
    strip_d.fill(orange_d, 5, 1);
    strip_b.show();
    strip_d.show();
    delay(intervalbli);
    strip_b.fill(orange_b, 2, 1);
    strip_d.fill(orange_d, 6, 1);
    strip_b.show();
    strip_d.show();
    delay(intervalbli);
  }


  void Blinker_Links() {
    strip_a.fill(off_a, 0, 7);
    strip_c.fill(off_c, 0, 7);
    strip_a.show();
    strip_c.show();
    strip_a.setBrightness(100);
    strip_c.setBrightness(100);
    delay(intervalbli);
    strip_a.fill(orange_a, 0, 1);
    strip_c.fill(orange_c, 0, 1);
    strip_a.show();
    strip_c.show();
    delay(intervalbli);
    strip_a.fill(orange_a, 1, 1);
    strip_c.fill(orange_c, 1, 1);
    strip_a.show();
    strip_c.show();
    delay(intervalbli);
    strip_a.fill(orange_a, 2, 1);
    strip_c.fill(orange_c, 6, 1);
    strip_a.show();
    strip_c.show();
    delay(intervalbli);
    strip_a.fill(orange_a, 3, 1);
    strip_c.fill(orange_c, 5, 1);
    strip_a.show();
    strip_c.show();
    delay(intervalbli);
    strip_a.fill(orange_a, 4, 1);
    strip_c.fill(orange_c, 4, 1);
    strip_a.show();
    strip_c.show();
    delay(intervalbli);
    strip_a.fill(orange_a, 5, 1);
    strip_c.fill(orange_c, 3, 1);
    strip_a.show();
    strip_c.show();
    delay(intervalbli);
    strip_a.fill(orange_a, 6, 1);
    strip_c.fill(orange_c, 2, 1);
    strip_a.show();
    strip_c.show();
    delay(intervalbli);
  }

  void Licht() {
    strip_a.fill(white_a, 0, 7);
    strip_a.setBrightness(20);
    strip_b.fill(white_b, 0, 7);
    strip_b.setBrightness(20);
    strip_c.fill(red_c, 0, 7);
    strip_c.setBrightness(20);
    strip_d.fill(red_d, 0, 7);
    strip_d.setBrightness(20);
    strip_a.show();
    strip_b.show();
    strip_c.show();
    strip_d.show();

  }


  void Lichthupe() {
    strip_a.fill(white_a, 0, 7);
    strip_a.setBrightness(255);
    strip_b.fill(white_b, 0, 7);
    strip_b.setBrightness(255);
    strip_c.fill(red_c, 0, 7);
    strip_c.setBrightness(20);
    strip_d.fill(red_d, 0, 7);
    strip_d.setBrightness(20);
    strip_a.show();
    strip_b.show();
    strip_c.show();
    strip_d.show();
    delay(150);
    strip_a.setBrightness(20);
    strip_b.setBrightness(20);
    strip_a.show();
    strip_b.show();
    delay(150);
    strip_a.setBrightness(255);
    strip_b.setBrightness(255);
    strip_a.show();
    strip_b.show();
    delay(450);
    Licht();
  }
