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


#include "Settings/settings.h"
#include "AppCommon/AppHW.h"

int m_agress_hydr = 0;
void lemca_init(){
    hw_DebugPrint("*** lemca_init\n");
	hw_DebugPrint("*** \n");

    m_agress_hydr = getS32("LEMCA", "AGRESS_HYD", 100);
    
    hw_DebugPrint("*** AGRESS_HYD %d\n",m_agress_hydr);
}

void save_config(){
    hw_DebugPrint("*** save_config\n");
    hw_DebugPrint("*** \n");
    
    setS32("LEMCA", "AGRESS_HYD", m_agress_hydr);

    hw_DebugPrint("*** AGRESS_HYD %d\n",m_agress_hydr);
}


void setAgressHyd(int agress_hydr){
    m_agress_hydr = agress_hydr;
    save_config();
}

int getAgressHyd(){
    return m_agress_hydr;
}






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

void update20Hz(int millis){

}

int old_millis = 0;
void lemca_loop(){
    int millis = esp_timer_get_time()/1000;
    int i = millis/50;
    if(i != old_millis){
        update20Hz(i);
        if(i%10 == 0){
            updateVTC();
        }
        //jd_loop(millis); 
    }
    old_millis = i;
}

