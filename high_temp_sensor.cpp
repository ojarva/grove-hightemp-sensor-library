/*
  2014 Copyright (c) Seeed Technology Inc.,
  2015 Olli Jarva <olli@jarva.fi>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <Arduino.h>
#include "high_temp_sensor.h"


const float VOL_OFFSET = 350; // Offset voltage in millivolts
const float AMP_AV = 54.16; // Av of amplifier
const float VOLTAGE = 3.3;

const float Var_VtoT_K[3][10] = {
    {0, 2.5173462e1, -1.1662878, -1.0833638, -8.9773540/1e1, -3.7342377/1e1,
    -8.6632643/1e2, -1.0450598/1e2, -5.1920577/1e4},
    {0, 2.508355e1, 7.860106/1e2, -2.503131/1e1, 8.315270/1e2,
    -1.228034/1e2, 9.804036/1e4, -4.413030/1e5, 1.057734/1e6, -1.052755/1e8},
    {-1.318058e2, 4.830222e1, -1.646031, 5.464731/1e2, -9.650715/1e4,
    8.802193/1e6, -3.110810/1e8}
};


HighTemp::HighTemp(int _pinTmp, int _pinForThermocouple) {
    pinForRoomTemperature = _pinTmp;
    pinForThermocouple = _pinForThermocouple;
}

void HighTemp::begin() {
    roomTemperature = getRoomTemperature();
    delay(20);
}

float HighTemp::getThermoCoupleTemperature() {
    float vol  = getThermocoupleVoltage();
    thermoCoupleTemperature = convertKVoltageToCelsius(vol) + roomTemperature;
    return thermoCoupleTemperature;
}

int HighTemp::getAveragedAnalog(int pin) {
    long sum = 0;
    for (int i=0; i<32; i++) {
        sum += analogRead(pin);
    }
    return ((sum>>5));
}


float HighTemp::getRoomTemperature()
{
    int a = getAveragedAnalog(pinForRoomTemperature) * (VOLTAGE * 10) / 33;
    float resistance = (float) (1023 - a) * 10000 / a;

    float temperature = 1 / (log(resistance / 10000) / 3975 + 1 / 298.15) - 273.15;

    roomTemperature = temperature;
    return temperature;
}


float HighTemp::getThermocoupleVoltage() {
    float analogValue = (float) getAveragedAnalog(pinForThermocouple);
    float vout = analogValue / 1023.0 * VOLTAGE * 1000;
    float vin = (vout - VOL_OFFSET) / AMP_AV;
    return (vin);
}


float HighTemp::convertKVoltageToCelsius(float mV) {
    int i = 0;
    float value = 0;

    if (mV >= -6.478 && mV < 0) {
        value = Var_VtoT_K[0][8];
        for (i = 8; i >0; i--) {
          value = mV * value + Var_VtoT_K[0][i-1];
        }
    } else if (mV >= 0 && mV < 20.644) {
        value = Var_VtoT_K[1][9];
        for (i = 9; i >0; i--) {
            value = mV * value + Var_VtoT_K[1][i-1];
        }
    }
    else if (mV >= 20.644 && mV <= 54.900) {
        value = Var_VtoT_K[2][6];
        for (i = 6; i >0; i--) {
          value = mV * value + Var_VtoT_K[2][i-1];
        }
    }

    return value;
}
