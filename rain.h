#pragma once
//
//    FILE: rain.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-11-23
// PURPOSE: Arduino library for rain sensor (analog).
//     URL: https://github.com/RobTillaart/RAIN
//          https://www.tinytronics.nl/shop/nl/sensoren/vloeistof/regensensor


#include "Arduino.h"


#define RAIN_LIB_VERSION         (F("0.1.0"))


class RAIN
{
public:
  RAIN(uint8_t port);

  //  set the ADC parameters
  //  can be changed runtime, e.g if voltage fluctuates.
  bool  begin(float maxVoltage, uint16_t maxSteps);
  
  //  returns voltage
  float read(uint8_t times = 1);

  //  returns last read value as percentage.
  //  indicating wetness?
  float percentage();


private:
  uint8_t  _port;
  float    _maxVoltage;
  uint16_t _maxSteps;
  float    _mVstep;
  float    _value;
};


//  -- END OF FILE --

