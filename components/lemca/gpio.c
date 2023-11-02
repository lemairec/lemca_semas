#include "gpio.h"

#include "driver/gpio.h"
#include "common/util.h"
#include "lemca.h"
#include "AppIso/config.h"


#include "driver/adc.h"

#define CAPTEUR_ANGLE_PIN ADC2_CHANNEL_7 //18
#define CAPTEUR_H_PIN ADC2_CHANNEL_7 //18

void initADC(){
    adc2_config_channel_atten( CAPTEUR_ANGLE_PIN, ADC_ATTEN_11db );
}

void setup_gpio(){
    initADC();
}

void update_gpio(int millis){
}

void readAll2(int32_t * capteur_angle, int32_t * in_3p, int16_t * capteur_roue_count){
    int temp;
    adc2_get_raw(CAPTEUR_ANGLE_PIN, ADC_WIDTH_BIT_DEFAULT, &temp);//12
    *capteur_angle = temp;

    temp = gpio_get_level(CAPTEUR_ANGLE_PIN);
    *in_3p = temp;
}