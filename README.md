# SoilMoistureSensor for the ESP32 IDF

Inspiration from
- https://how2electronics.com/interface-capacitive-soil-moisture-sensor-arduino/
- https://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another for the conversion

## Sample Code

```c++
#include <esp_log.h>
#include <SoilMoistureSensor.h>
#include <esp_event.h>

#ifdef __cplusplus
extern "C" {
#endif

[[noreturn]] void app_main()
{
    ESP_LOGI("SoilMoistureSensor", "Test...");

    SoilMoistureSensor sensor;

    do {
        ESP_LOGI("SoilMoistureSensor", "Value: %d, %.2f%%", sensor.readRawValue(), sensor.getPercentValue());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    } while (true);
}

#ifdef __cplusplus
} // extern "C"
#endif
```
