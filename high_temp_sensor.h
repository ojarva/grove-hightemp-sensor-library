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
#ifndef __HIGH_TEMP_SENSOR_H__
#define __HIGH_TEMP_SENSOR_H__

class HighTemp {

public:

    HighTemp(int _pinTmp, int _pinForThermocouple);

    float getRoomTemperature();
    float getThermoCoupleTemperature();

    void begin();


private:

    int pinForRoomTemperature;                // analog pin for board temperature sensor, used for calibrating the results.
    int pinForThermocouple;                   // analog pin for thermocouple amplifier

    float roomTemperature;         // Room temperature in C. Stored for converting thermocouple readings properly.
    float thermoCoupleTemperature; // Thermocouple temperature in C.
    int getAveragedAnalog(int pin); // Reads analog input multiple times and takes an average of the reading.
    float getThermocoupleVoltage();                       // get voltage of thmc in mV
    float convertKVoltageToCelsius(float mV); // Convert type K thermocouple mV reading to convertKVoltageToCelsius
};


#endif
