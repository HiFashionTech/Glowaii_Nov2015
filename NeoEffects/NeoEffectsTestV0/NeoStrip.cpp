// NeoStrip.cpp
// a wrapper/dervied class of Adafruit_NeoPixel to add some functionality
// most everything passes on to the parent class

#include <Adafruit_NeoPixel.h>
#include "NeoStrip.h"


int NeoStrip::s_nIDGenerator = 1;
// wrapper on Adafruit_NeoPixel constructor
NeoStrip::NeoStrip(uint16_t n, uint8_t p, uint8_t t) 
 : Adafruit_NeoPixel(n, p, t)
{
  stripChanged = false;
  myId = s_nIDGenerator++;
}

void NeoStrip::printId(void)
{
  Serial.print("Strip  "); 
  Serial.print(myId); Serial.print(" ");
}


// overload the base class show to check if stripChanged
void NeoStrip::show(void)
{
    if (!stripChanged) {
//      printId(); Serial.println(" Strip did not Changed");
      return;
    }
//    printId(); Serial.println("Strip Changed, show it");
    
    Adafruit_NeoPixel::show();
    
    stripChanged = false;
}

 void NeoStrip::setStripChanged()
 {
//  printId();Serial.println("  Setting changed ");
    stripChanged = true;
 }
 
 void NeoStrip::clearStripChanged()
 {
//  printId();Serial.println("  Setting cleared ");
    stripChanged = false;
 }
 
 boolean NeoStrip::getStripChanged()
 {
    return stripChanged;
 }

 void NeoStrip::clearStrip()
 {
   for (int i=0;i < numPixels();i++)
    setPixelColor(i, 0);

    setStripChanged();
 }
 
void NeoStrip::fillStrip(uint32_t c)
{
  for (int i=0;i < numPixels();i++)
    setPixelColor(i, c);
    setStripChanged();
}


