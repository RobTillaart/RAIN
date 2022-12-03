//
//    FILE: rain.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-12-03
// PURPOSE: Arduino library for a rain sensor
//     URL: https://github.com/RobTillaart/RAIN
//          https://www.tinytronics.nl/shop/nl/sensoren/vloeistof/regensensor


#include "rain.h"

RAIN::RAIN(uint8_t port)
{
  _port       = port;
  _maxVoltage = 5;
  _maxSteps   = 1023;
}


bool RAIN::begin(float maxVoltage, uint16_t maxSteps)
{
  _maxVoltage = maxVoltage;
  _maxSteps   = maxSteps;
  _mVstep = _maxVoltage / _maxSteps;
  read();
  return true;
}


float RAIN::read(uint8_t times)
{
  if (times == 0) times = 1;
  float sum = 0;
  for (int i = 0; i < times; i++)
  {
    sum += analogRead(_port);
  }
  if (times > 1) sum /= times;
  _value = sum * _mVstep;
  return _value;
}


float RAIN::percentage()
{
  return _value * 100.0 / _maxVoltage;
}


//  -- END OF FILE --

