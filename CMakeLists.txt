idf_component_register(
        SRCS SoilMoistureSensor.cpp
        INCLUDE_DIRS "."
        PRIV_REQUIRES esp_adc_cal
)
