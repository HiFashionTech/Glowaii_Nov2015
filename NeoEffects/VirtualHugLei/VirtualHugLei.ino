/* 
 *  Virtual Hug Lei:  uses Maxbotix sonar to control 8 NeoPixel rings in a Lei-like wreath
 *  depending on how close someone comes, the effects displayed change
 *  Sonar actions derived from Jason Lessel's example from the arduino.cc pages on MaxSonar
 *  
*/

#include <Adafruit_NeoPixel.h>
#include "NeoStrip.h"
#include "NeoWindow.h"
#include "maxSonar.h"

//////////////////////////////////////////
//Set the pin to recieve the signal.
// although with class the const is not really needed
const int analogPin = 0;
MaxSonar sonar = MaxSonar(analogPin);
//////////////////////////////////////////
#define SMALL_NEORING_SIZE 12
// pin number changes far too often.
// Lei using teensy3.0 on sheild board uses pin2
// Lei is on pin 3, shoulders on pin1 
#define STRIP_1_PIN 2
//#define STRIP_1_PIN 3
//#define STRIP_1_PIN 1

const int RING_1_START = 0;
const int RING_2_START = (RING_1_START + SMALL_NEORING_SIZE);
const int RING_3_START = (RING_2_START + SMALL_NEORING_SIZE);
const int RING_4_START = (RING_3_START + SMALL_NEORING_SIZE);
const int RING_5_START = (RING_4_START + SMALL_NEORING_SIZE);
const int RING_6_START = (RING_5_START + SMALL_NEORING_SIZE);
const int RING_7_START = (RING_6_START + SMALL_NEORING_SIZE);
const int RING_8_START = (RING_7_START + SMALL_NEORING_SIZE);
const int numRings = 8;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

NeoStrip strip1 = NeoStrip(SMALL_NEORING_SIZE * numRings, STRIP_1_PIN, NEO_GRB + NEO_KHZ800);

NeoWindow ring1 = NeoWindow(&strip1, RING_1_START, SMALL_NEORING_SIZE);
NeoWindow ring2 = NeoWindow(&strip1, RING_2_START, SMALL_NEORING_SIZE);
NeoWindow ring3 = NeoWindow(&strip1, RING_3_START, SMALL_NEORING_SIZE);
NeoWindow ring4 = NeoWindow(&strip1, RING_4_START, SMALL_NEORING_SIZE);
NeoWindow ring5 = NeoWindow(&strip1, RING_5_START, SMALL_NEORING_SIZE);
NeoWindow ring6 = NeoWindow(&strip1, RING_6_START, SMALL_NEORING_SIZE);
NeoWindow ring7 = NeoWindow(&strip1, RING_7_START, SMALL_NEORING_SIZE);
NeoWindow ring8 = NeoWindow(&strip1, RING_8_START, SMALL_NEORING_SIZE);
NeoWindow allPixels = NeoWindow(&strip1, RING_1_START, strip1.numPixels());

NeoWindow *rings[] = {&ring1, &ring2, &ring3, &ring4, &ring5, &ring6, &ring7, &ring8,  };

int numPixelsInSocial = strip1.numPixels()/20; // social initially set to 20% of pixels

//////////////////////////////////////////
const int anoukRed = 128;
const int anoukGreen = 0;
const int anoukBlue = 50;

const uint32_t anoukPurple = strip1.Color(anoukRed, anoukGreen, anoukBlue);

uint32_t randomAnouk() 
{
  return Adafruit_NeoPixel::Color(random(10,200),0,random(10,100));
}

//////////////////////////////////////////

void blinkWholeStrip(void)
{
  strip1.clearStrip();
  strip1.show();
  delay(1000);    
  strip1.fillStrip(anoukPurple);
  strip1.show();
  delay(1000);
  strip1.clearStrip();
  strip1.show();
  delay(1000);
}

void setup() {

  //Open up a serial connection
  Serial.begin(115200);
  //Wait for the serial connection
  delay(500);

Serial.println("Virtual Hug Lei App");

  strip1.begin();
  strip1.setBrightness(100);

  blinkWholeStrip();

  setSocialEffect();

//  ring1.setWipeEfx(randomAnouk(),100 );

//  strip1.show();

Serial.println("Virtual Hug Lei App start loop");
  allPixels.printData();
    int range = sonar.readCM();
  int zone = findZone(range);
  Serial.print("Range CM is: "); Serial.print(range);
  Serial.print(" Zone is: "); Serial.print(zone);
  Serial.println();
Serial.println("Virtual Hug Lei App wait long time");
  delay(2000);
  Serial.println("OK GO");

}

// define the max centimeters in each zone
const int maxcmZO = 50;
const int maxcmZ1 = 121;// 4ft
const int maxcmZ2 = 243;
const int maxcmZ3 = 365;
const int maxcmZ4 = 10000;
#define IntimateZone 0
#define PersonalZone 1
#define SocialZone 2
//#define PublicZone 3

int findZone(long range)
{
  if (range <= maxcmZO)
    return IntimateZone;
  if (range <= maxcmZ1)
    return PersonalZone;
  if (range <= maxcmZ2)
    return SocialZone;
//  if (range <= maxcmZ3)
//    return 3;
//  return 4;

  return SocialZone;
}

//Main loop where the action takes place
int lastZone = SocialZone;

void loop() {
  // grab the current time in class method
  NeoWindow::updateTime();

  int range = sonar.readCM();
  int zone = findZone(range);
//  Serial.print("Range CM is: "); Serial.print(range);
//  Serial.print(" Zone is: "); Serial.print(zone);
//  Serial.println();

  if (zone != lastZone) {
    Serial.print(" Change Zone from ");Serial.print(lastZone);Serial.print(" toZone:");Serial.println(zone);
    lastZone = zone;
    switch (zone) {
      case IntimateZone:
        setIntimateEffect();
        break;
      case PersonalZone:
        setPersonalEffect();
        break;
      default:
        setSocialEffect();
        break;
    }
  }
  
  // now update each Window
  for (int i=0; i < numRings;i++)
  {
      rings[i]->updateWindow();
      if (rings[i]->effectDone()) {
        if (zone == PersonalZone)
          resetPersonalEfx();
      }
  }

  allPixels.updateWindow();

  strip1.show();
}

//
void setSocialEffect()
{
  Serial.println("Set Social Effect");
  // twinkle 20% of pixels
  allPixels.fillBlack();
  allPixels.setMultiSparkleEfx(anoukPurple, 500, 200, numPixelsInSocial);
  for (int i=0; i < numRings;i++)
  {
      rings[i]->setNoEfx();
  }

}

void resetPersonalEfx()
{
    allPixels.setNoEfx();
//    allPixels.fillBlack();
  for (int i=0; i < numRings;i++)
  {
      rings[i]->setCircleEfx(NeoStrip::randomColor(0, Adafruit_NeoPixel::Color(255,20,255)), 1 );
      
//      rings[i]->setRandomWipeEfx(0, strip1.randomColor(), 10 );
//      rings[i]->setRandomWipeEfx(0, randomAnouk(), 10 );
  }  

}

void setPersonalEffect()
{
    Serial.println("Set Personal Effect");

  resetPersonalEfx();
  
  // set spirals
//  allPixels.setNoEfx();
////  allPixels.fillBlack();
//  for (int i=0; i < numRings;i++)
//  {
//      rings[i]->setCircleEfx(Adafruit_NeoPixel::Color(255,20,255), 2 );
////      rings[i]->setRandomWipeEfx(0, Adafruit_NeoPixel::Color(255,20,255), 2 );
////      rings[i]->setRandomWipeEfx(0, strip1.randomColor(), 10 );
////      rings[i]->setRandomWipeEfx(0, randomAnouk(), 10 );
//  }  
}

void setIntimateEffect()
{
  Serial.println("Set Intimate Effect");
  allPixels.fillBlack();
  allPixels.setNoEfx();
  // slowFadeInOut
  for (int i=0; i < numRings;i++)
  {
      rings[i]->setFadeEfx(0, anoukPurple, 10, NeoWindow::fadeTypeCycle, 0);

  }
}

