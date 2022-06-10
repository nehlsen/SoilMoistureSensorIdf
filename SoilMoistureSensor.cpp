#include "SoilMoistureSensor.h"
#include <driver/adc.h>
#include <esp_log.h>

#define DEFAULT_VREF 3300
#define AIR_VALUE 2275
#define WET_VALUE 280

SoilMoistureSensor::SoilMoistureSensor(adc1_channel_t adcChannel):
    m_adcChannel(adcChannel)
{
    auto err = adc1_config_width(ADC_WIDTH_BIT_12);
    if (err != ESP_OK) {
        ESP_LOGE("SoilMoistureSensor", "adc1_config_width FAILED: %s", esp_err_to_name(err));
    }

    err = adc1_config_channel_atten(m_adcChannel, ADC_ATTEN_DB_11);
    if (err != ESP_OK) {
        ESP_LOGE("SoilMoistureSensor", "adc1_config_channel_atten FAILED: %s", esp_err_to_name(err));
    }

    m_adcCalCharacteristics = (esp_adc_cal_characteristics_t*)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, m_adcCalCharacteristics);
}

bool SoilMoistureSensor::readRawData()
{
    const int numberOfSamples = 64;
    int reading = 0;
    for (int i = 0; i< numberOfSamples; ++i) {
        const int raw = adc1_get_raw(m_adcChannel);
        if (raw < 0) {
            ESP_LOGE("SoilMoistureSensor", "read ERROR");
        }
        reading += raw;
    }

    m_adcRawValue = reading / numberOfSamples;

    return m_adcRawValue != -1;
}

int SoilMoistureSensor::getRawValue()
{
    return m_adcRawValue;
}

int SoilMoistureSensor::readRawValue()
{
    readRawData();
    return getRawValue();
}

double SoilMoistureSensor::getPercentValue()
{
    const auto output_end = 0.0;
    const auto output_start = 100.0;
    const auto input_end = AIR_VALUE;
    const auto input_start = WET_VALUE;
    auto input = readRawValue();

    auto slope = (output_end - output_start) / (input_end - input_start);
    return output_start + slope * (input - input_start);
}

double SoilMoistureSensor::readPercentValue()
{
    readRawData();
    return getPercentValue();
}
