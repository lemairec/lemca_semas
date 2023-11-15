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

const double max_value = 3200.0;

int m_agress_hydr = 0;

int m_last_millis = 0;

//time fonction
int m_time = 0;
int m_time_off = 0;
int m_electrovanne = 0;

int m_last_machine_l = 0;
int m_last_machine_r = 0;

double m_last_machine_l_100 = 0;
double m_last_machine_r_100 = 0;
    
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

int getLastRight(){
    return m_last_machine_r_100;
}

int getLastLeft(){
    return m_last_machine_l_100;
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

bool m_workstate_on = false;
void changeWorkState(){

}

void updateTranslator(int left_right, int up_down){
    int left_right2 = left_right;
    int up_down2 = up_down;

    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;

    if(left_right2 < 0){
        left_right2 = -left_right2;
        if(left_right2 > 8191){
            left_right2 = 8191;
        }
        left = left_right2;
    } else {
        if(left_right2 > 8191){
            left_right2 = 8191;
        }
        right = left_right2;
    }

    if(up_down2 < 0){
        up_down2 = -up_down2;
        if(up_down2 > 8191){
            up_down2 = 8191;
        }
        up = up_down2;
    } else {
        if(up_down2 > 8191){
            up_down2 = 8191;
        }
        down = up_down2;
    }
    setElectrovanne(left, right, up, down);
}

void updateTime(){
    if(m_last_millis < m_time_off){
        hw_DebugPrint("*** update time %i %i\n", m_last_millis, m_time_off);
        if(m_electrovanne == 1){
            setElectrovanne(8191, 0, 0, 0);
        } else if(m_electrovanne == 2){
            setElectrovanne(0, 8191, 0, 0);
        } else if(m_electrovanne == 3){
            setElectrovanne(0, 0, 8191, 0);
        } else if(m_electrovanne == 4){
            setElectrovanne(0, 0, 0, 8191);
        }
    } else {
        m_time = 0;
        m_time_off = 0;
        m_electrovanne = 0;
        setElectrovanne(0, 0, 0, 0);
    }
}

void update20Hz(int millis){
    int capteur_angle = 0;
    int capteur_h = 0;
    readAll2(&capteur_angle, &capteur_h, &m_last_machine_l, &m_last_machine_r);
    m_last_machine_l_100 = (double)m_last_machine_l*100.0/max_value;
    m_last_machine_r_100 = (double)m_last_machine_r*100.0/max_value;

    //hw_DebugPrint("*** update20Hz %d %d %d %d\n",capteur_angle, capteur_h, m_last_machine_l, m_last_machine_r);
    
    double h = (double)capteur_h/max_value - 0.5;
    double a = (double)capteur_angle/max_value - 0.5;

    //hw_DebugPrint("*** update20Hz %.1f %.1f %d %d\n",a, h, 0, 0);

    int left_right = a*500;

    
    if(m_time){
        updateTime();
    }
}

int old_millis = 0;
void lemca_loop(){
    int millis = esp_timer_get_time()/1000;
    m_last_millis = millis;
    int i = millis/50;
    if(i != old_millis){
        update20Hz(m_last_millis);
        if(i%10 == 0){
            updateVTC();
        }
        //jd_loop(millis); 
    }
    old_millis = i;
}


void onButtonUp(){
    m_time = 1;
    m_electrovanne = 3;
    m_time_off = m_last_millis + 500;
    hw_DebugPrint("*** onButtonUp\n");
};
void onButtonDown(){
    m_time = 1;
    m_electrovanne = 4;
    m_time_off = m_last_millis + 500;
    hw_DebugPrint("*** onButtonDown\n");
};
void onButtonLeft(){
    m_time = 1;
    m_electrovanne = 1;
    m_time_off = m_last_millis + 500;
    hw_DebugPrint("*** onButtonLeft\n");
};
void onButtonRight(){
    m_time = 1;
    m_electrovanne = 2;
    m_time_off = m_last_millis + 500;
    hw_DebugPrint("*** onButtonRight\n");
};