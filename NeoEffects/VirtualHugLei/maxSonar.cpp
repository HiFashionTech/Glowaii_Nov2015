/*
 * MaxSonar class implementation
 */
#include "maxSonar.h"

//variables needed to store values
#define MODE_ARRAY_SIZE 9
const int sonar_arraysize = MODE_ARRAY_SIZE; //quantity of values to find the median (sample size). Needs to be an odd number

//declare an array to store the samples. not necessary to zero the array values here, it just makes the code clearer
static int sonar_rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Mode function, returning the mode or median.
static int sonar_mode(int *x, int n) {

  int i = 0;
  int count = 0;
  int maxCount = 0;
  int mode = 0;
  int bimodal;
  int prevCount = 0;
  while (i < (n - 1)) {
    prevCount = count;
    count = 0;
    while (x[i] == x[i + 1]) {
      count++;
      i++;
    }
    if (count > prevCount && count > maxCount) {
      mode = x[i];
      maxCount = count;
      bimodal = 0;
    }
    if (count == 0) {
      i++;
    }
    if (count == maxCount) { //If the dataset has 2 or more modes.
      bimodal = 1;
    }
    if (mode == 0 || bimodal == 1) { //Return the median if there is no mode.
      mode = x[(n / 2)];
    }
  }
  return mode;
}


MaxSonar::MaxSonar(int pin)
{
  myAnalogPin = pin ;
}

int MaxSonar::readCM(void)
{
  int range;
  for (int i = 0; i < sonar_arraysize; i++)
  {
    range = analogRead(myAnalogPin);  // vcc/1024 is range in 5mm steps
    sonar_rangevalue[i] = (range * 5) / 10 ; // range in cm
    delay(10);
  }
  return sonar_mode(sonar_rangevalue, sonar_arraysize);
}



