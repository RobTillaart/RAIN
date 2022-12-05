//
//    FILE: rain_setLevel_guard_low.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo how to control a pump with the sensor.
//     URL: https://github.com/RobTillaart/RAIN


#include "rain.h"

RAIN  RS(A0);

uint32_t lastTime = 0;

const int PUMP_PIN = 6;   //  UNO PWM pin.
uint8_t prevLevel = -1;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("RAIN_LIB_VERSION: ");
  Serial.println(RAIN_LIB_VERSION);

  RS.begin(5.000, 1023);  //  adjust if needed

  //  set the levels
  //  very low levels need to start the pump quite fast.
  //  adapt to your needs.
  RS.setLevel(1, 0.05);
  RS.setLevel(2, 0.10);
  RS.setLevel(3, 0.20);
  RS.setLevel(4, 0.50);

}


void loop()
{
  uint32_t now = millis();
  if (now - lastTime > 1000)
  {
    lastTime = now;
    RS.read();
    int level = RS.getLevel();
    switch (level)
    {
      case 4:
        if (prevLevel != level)
        {
          Serial.println("Pump speed 100%");
        }
        analogWrite(PUMP_PIN, 255);
        break;
      case 3:
        if (prevLevel != level)
        {
          Serial.println("Pump speed 90%");
        }
        analogWrite(PUMP_PIN, 230);
        break;
      case 2:
        if (prevLevel != level)
        {
          Serial.println("Pump speed 75%");
        }
        analogWrite(PUMP_PIN, 195);  //  ~75%
        break;
      case 1:
        if (prevLevel != level)
        {
          Serial.println("Start pumping");
        }
        analogWrite(PUMP_PIN, 130);  //  ~50%
        break;
      case 0:
      default:
        if (prevLevel != level)
        {
          Serial.println("Stop pumping");
        }
        analogWrite(PUMP_PIN, 0);
        break;
    }
    prevLevel = level;
  }
}


// -- END OF FILE --