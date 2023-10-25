#include "lemca.h"

#include "esp_timer.h"

#include "common/util.h"
#include "lib_cci/IsoVtcApi.h"
#include "AppIso/VIEngine.h"
#include "AppIso/App_VTClientLev2.h"
#include "AppIso/config.h"

#include "uart/my_uart.h"
#include "gpio.h"
#include "gpio.h"
#include "AppIso/config.h"

#include "driver/adc.h"

#define CAPTEUR_ANGLE_PIN ADC2_CHANNEL_7 //18
#define CAPTEUR_H_PIN ADC2_CHANNEL_7 //18

void initADC(){
    adc2_config_channel_atten( CAPTEUR_ANGLE_PIN, ADC_ATTEN_11db );
}

int desired_h = 50; //0-100
int desired_a = 0; //-50 50


void readAll2(int32_t * capteur_angle, int32_t * in_3p, int16_t * capteur_roue_count){
    int temp;
    adc2_get_raw(CAPTEUR_ANGLE_PIN, ADC_WIDTH_BIT_DEFAULT, &temp);//12
    *capteur_angle = temp;

    temp = gpio_get_level(CAPTEUR_ANGLE_PIN);
    *in_3p = temp;
}


double m_km_h = -1;
void setSpeedKmH(double km_h){
    m_km_h = km_h;
}
double getSpeedKmH(){
    return m_km_h;
}


void changeWorkState(){

}

int old_millis = 0;
void lemca_loop(){
    int millis = esp_timer_get_time()/1000;
    int i = millis/100;
    if(i != old_millis){
        update_gpio(millis);
        if(i%5 == 0){
            updateVTC();
        }
        //jd_loop(millis); 
    }
    old_millis = i;
}

