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




int desired_h = 50; //0-100
int desired_a = 0; //-50 50



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

