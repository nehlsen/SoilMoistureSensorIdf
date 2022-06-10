#ifndef SOILMOISTURESENSOR_H
#define SOILMOISTURESENSOR_H

#include <esp_adc_cal.h>

class SoilMoistureSensor
{
public:
    explicit SoilMoistureSensor(adc1_channel_t adcChannel = ADC1_CHANNEL_0);

    /**
     * read value from ADC
     * @return bool whether read was successful
     */
    bool readRawData();
    /**
     * get last read value, does not trigger read from ADC
     * @return int last read value (12bit, 0-4096)
     */
    int getRawValue();
    /**
     * convenience function to read and return the value
     * @return int last read value
     */
    int readRawValue();

    /**
     * get last read value converted to percent
     * @return double percent moisture
     */
    double getPercentValue();
    /**
     * convenience function to read and return last value converted to percent
     * @return double percent moisture
     */
    double readPercentValue();

private:
    adc1_channel_t m_adcChannel;
    esp_adc_cal_characteristics_t *m_adcCalCharacteristics;
    int m_adcRawValue = 0;
};

#endif //SOILMOISTURESENSOR_H
