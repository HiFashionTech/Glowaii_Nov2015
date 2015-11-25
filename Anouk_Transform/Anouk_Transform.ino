#include <Adafruit_NeoPixel.h>

#define PIN1 2
#define PIN2 14
#define PIN3 7
#define PIN4 8
#define PIN5 6
#define PIN6 20
#define PIN7 21
#define PIN8 5

Adafruit_NeoPixel strip[8] = {
   Adafruit_NeoPixel(12, PIN1, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(12, PIN2, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(12, PIN3, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(12, PIN4, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(12, PIN5, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(12, PIN6, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(12, PIN7, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(12, PIN8, NEO_GRB + NEO_KHZ800)
};

void setup() {
  for(int i=0;i<8;i++) {
    strip[i].begin();
    strip[i].show(); // Initialize all pixels to 'off'
  }
}

void loop() {
  
  // FADE to PURPLE
  
  colorFade(0,0,0,        128, 0, 128,  20); // From off to purple fade
  colorFade(128, 0, 128,   0,0,0,      20); // from purple to off fade
  
  // FADE to WHITE
  
  colorFade(0,0,0,       128,128,128,  20); // From off to white fade
  colorFade(128,128,128,       0,0,0,  20); // From white to off fade
  
   // FADE to PURPLE
  
  colorFade(0,0,0,        128, 0, 128,  20); // From off to purple fade
  colorFade(128, 0, 128,   0,0,0,      20); // from purple to off fade
  
  // FADE to WHITE
  
  colorFade(0,0,0,       128,128,128,  20); // From off to white fade
  colorFade(128,128,128,       0,0,0,  20); // From white to off fade
 
  // CIRCLES

  colorWipe(strip[0].Color(128, 0, 128), 150); // Purple
  colorWipe(strip[0].Color(128, 128, 128), 150); // White
  colorWipe(strip[0].Color(0, 0, 0), 150); // Off
  
  // FADE to PURPLE
  
  colorFade(0,0,0,        128, 0, 128,  20); // From off to purple fade
  colorFade(128, 0, 128,   0,0,0,      20); // from purple to off fade
  
  // FADE to WHITE
  
  colorFade(0,0,0,       128,128,128,  20); // From off to white fade
  colorFade(128,128,128,       0,0,0,  20); // From white to off fade
  
  // FADE to PURPLE
  
  colorFade(0,0,0,        128, 0, 128,  20); // From off to purple fade
  colorFade(128, 0, 128,   0,0,0,      20); // from purple to off fade
  
  // FADE to WHITE
  
  colorFade(0,0,0,       128,128,128,  20); // From off to white fade
  colorFade(128,128,128,       0,0,0,  20); // From white to off fade
  
    // FADE to PURPLE
  
  colorFade(0,0,0,        128, 0, 128,  20); // From off to purple fade
  colorFade(128, 0, 128,   0,0,0,      20); // from purple to off fade
  
  // FADE to WHITE
  
  colorFade(0,0,0,       128,128,128,  20); // From off to white fade
  colorFade(128,128,128,       0,0,0,  20); // From white to off fade
  
  
    // PURPLE-WHITE-PURPLE
  
  colorFade(128, 0, 50,       128,128,128,  20); // From purple to white
  colorFade(128,128,128,      128, 0, 50,   20); // from white to purple
  
  // PURPLE-WHITE-PURPLE
  
  colorFade(128, 0, 50,       128,128,128,  10); // From purple to white
  colorFade(128,128,128,      128, 0, 50,   10); // from white to purple
  colorFade(128, 0, 50,       128,128,128,  10); // From purple to white
  colorFade(128,128,128,      128, 0, 50,   10); // from white to purple
  colorFade(128, 0, 50,       128,128,128,  10); // From purple to white
  colorFade(128,128,128,      128, 0, 50,   10); // from white to purple
  colorFade(128, 0, 50,       128,128,128,  10); // From purple to white
  colorFade(128,128,128,      128, 0, 50,   10); // from white to purple

  
    // CHASE PURPLE
    
  colorWipe(strip[0].Color(128, 0, 50), 5); // Purple
  colorWipe(strip[0].Color(0, 0, 0), 5); // Off
  colorWipe(strip[0].Color(128, 0, 50), 5); // Purple
  colorWipe(strip[0].Color(0, 0, 0), 5); // Off
  
    // FADE to PURPLE
  
  colorFade(0,0,0,        128, 0, 128,  20); // From off to purple fade
  colorFade(128, 0, 128,   0,0,0,      20); // from purple to off fade
  
   // CHASE WHITE
   
  colorWipe(strip[0].Color(128, 128, 128), 5); // White
  colorWipe(strip[0].Color(0, 0, 0), 5); // Off
  colorWipe(strip[0].Color(128, 128, 128), 5); // White
  colorWipe(strip[0].Color(0, 0, 0), 5); // Off
  
    // FADE to WHITE
  
  colorFade(0,0,0,       128,128,128,  20); // From off to white fade
  colorFade(128,128,128,       0,0,0,  20); // From white to off fade
  
      // CHASE PURPLE-WHITE

  colorWipe(strip[0].Color(128, 0, 50), 250); // Purple
  colorWipe(strip[0].Color(128, 128, 128), 250); // White
  colorWipe(strip[0].Color(0, 0, 0),250); // Off
  
}

void colorFade(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t wait)
{
  while(r1 != r2 || g1 != g2 || b1 != b2) { // terinary operation
    r1 = r2 > r1 ? r1+1 : r2 != r1 ? r1-1 : r1;
    g1 = g2 > g1 ? g1+1 : g2 != g1 ? g1-1 : g1;
    b1 = b2 > b1 ? b1+1 : b2 != b1 ? b1-1 : b1;
    colorFill(strip[0].Color(r1, g1, b1));
    delay(wait);
  }
}

void colorFill(uint32_t c) {
  for(uint8_t s=0;s<8;s++) {
    for(uint16_t i=0; i<strip[0].numPixels(); i++) {
      strip[s].setPixelColor(i, c);
    }
    strip[s].show();
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip[0].numPixels(); i++) {
      for(uint8_t s=0;s<8;s++) {
        strip[s].setPixelColor(i, c);
        strip[s].show();
      }
      delay(wait);
  }
}


// not in use -

void hsv2rgb(float h, float s, float v, unsigned char *r,  unsigned char *g,  unsigned char *b) {
    
    v = v > 1 ? 1 : v < 0 ? 0 : v;
    s = s > 1 ? 1 : s < 0 ? 0 : s;
    if(v == 0) {
        *(r) = 0;
        *(g) = 0;
        *(b) = 0;
        return;
    }

    int i = int(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch(i % 6){
        case 0: *(r) = v*255, *(g) = t*255, *(b) = p*255; return;
        case 1: *(r) = q*255, *(g) = v*255, *(b) = p*255; return;
        case 2: *(r) = p*255, *(g) = v*255, *(b) = t*255; return;
        case 3: *(r) = p*255, *(g) = q*255, *(b) = v*255; return;
        case 4: *(r) = t*255, *(g) = p*255, *(b) = v*255; return;
        case 5: *(r) = v*255, *(g) = p*255, *(b) = q*255; return;
    }
    return;
}
