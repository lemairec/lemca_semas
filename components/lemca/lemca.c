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

typedef enum  {
    TimeAction_Off = 0,
    TimeAction_Left = 1,
    TimeAction_Right = 2,
    TimeAction_Up = 3,
    TimeAction_Down = 4,
} TimeAction;


const double max_value = 3200.0;

int m_agress_hydr = 0;

int m_last_millis = 0;

//alive
int m_last_millis_alive = 0;

//time fonction
enum State m_state = 0; //0 off, 1 time, 2 up, 3 time
int64_t m_last_millis_time = 0;
TimeAction m_time_action = TimeAction_Off;

double m_vitesse_max_ang = 100.0;
double m_vitesse_max_h = 100.0;

double m_last_corr_angl_100 = 0;
double m_last_corr_h_100 = 0;

int m_last_machine_a = 0;
int m_last_machine_h = 0;
int m_last_machine_l = 0;
int m_last_machine_r = 0;


double m_last_machine_a_100 = 0;
double m_last_machine_h_100 = 0;
double m_last_machine_l_100 = 0;
double m_last_machine_r_100 = 0;

int m_work_h = 0;
int m_last_millis_up = 0;


double m_vitesse_simu = 0;
double m_km_h = -1;

const double sum_erreur_max = 10;
double sum_error_ang = 0;
double sum_error_h = 0;

void verify_config(){
    if(m_work_h > 100){
        m_work_h = 100;
    }
    if(m_work_h < 0){
        m_work_h = 0;
    }
}

void print_config(){
    hw_DebugPrint("***- AGRESS_HYD %d\n",m_agress_hydr);
    hw_DebugPrint("***- WORK_H %d\n",m_work_h);
    hw_DebugPrint("***- V_MAX_H %d\n",m_vitesse_max_h);
    hw_DebugPrint("***- V_MAX_ANG %d\n",m_vitesse_max_ang);
}

void lemca_init(){
    hw_DebugPrint("*** lemca_init\n");
	hw_DebugPrint("*** \n");

    m_agress_hydr = getS32("LEMCA", "AGRESS_HYD", 100);
    m_work_h = getS32("LEMCA", "WORK_H", 50);
    m_vitesse_max_h = getS32("LEMCA", "V_MAX_H", 100);
    m_vitesse_max_ang = getS32("LEMCA", "V_MAX_ANG", 100);
    verify_config();
}

void save_config(){
    hw_DebugPrint("*** save_config\n");
    hw_DebugPrint("*** \n");
    
    verify_config();
    setS32("LEMCA", "AGRESS_HYD", m_agress_hydr);
    setS32("LEMCA", "WORK_H", m_work_h);
    setS32("LEMCA", "V_MAX_H", m_vitesse_max_h);
    setS32("LEMCA", "V_MAX_ANG", m_vitesse_max_ang);
}

enum State getState(){
    return m_state;
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

void setAlive(){
    m_last_millis_alive = m_last_millis;
}

int isAlive(){
    if((m_last_millis_alive - m_last_millis) < 3000){
        return 1;
    }
    return 0;
}





void setSpeedKmH(double km_h){
    m_km_h = km_h;
}
double getSpeedKmH(){
    return m_km_h;
}

double getCorrAng(){
    return m_last_corr_angl_100;
}


double getCorrH(){
    return m_last_corr_h_100;
}

void setState(enum State state){
    m_state = state;
    m_last_millis_up = m_last_millis;
    sum_error_ang = 0;
    sum_error_h = 0;
}

void setWorkStateWork(){
    setState(State_work);
}

void setWorkStateUp(){
    setState(State_up);
}

void changeWorkState(){
    if(m_state == State_work){
        setState(State_up);
    } else {
        setState(State_work);
    }
}

int getWorkState(){
    return m_state == State_work;
}

void setTranslateur(double corr_ang, double corr_h){
    m_last_corr_angl_100 = corr_ang;
    m_last_corr_h_100 = corr_h;
    if(m_last_corr_angl_100 > m_vitesse_max_ang){
        m_last_corr_angl_100 = m_vitesse_max_ang;
    }
    if(m_last_corr_angl_100 < -m_vitesse_max_ang){
        m_last_corr_angl_100 = -m_vitesse_max_ang;
    }
    if(m_last_corr_h_100 > m_vitesse_max_h){
        m_last_corr_h_100 = m_vitesse_max_h;
    }
    if(m_last_corr_h_100 < -m_vitesse_max_h){
        m_last_corr_h_100 = -m_vitesse_max_h;
    }
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;
    if(m_last_corr_angl_100 > 0){
        left = m_last_corr_angl_100;
    } else {
        right = -m_last_corr_angl_100;
    }
    if(m_last_corr_h_100 > 0){
        up = m_last_corr_h_100;
    } else {
        down = -m_last_corr_h_100;
    }
    setElectrovanne(left*81.91, right*81.91, up*81.91, down*81.91);
}

void updateUp(){
    if((m_last_millis - m_last_millis_up) < 3000){
        hw_DebugPrint("*** update up %i %i\n", m_last_millis_up, m_last_millis);
       // double a = (double)m_last_machine_a_100 - 50.0;
       // double res = a*m_agress_hydr;
        setTranslateur(0, 100);
    } else {
        m_state = State_off;
        setElectrovanne(0, 0, 0, 0);
    }
}

void updateWorkstate(){
    double agress_hyd = m_agress_hydr/20.0;
    double time = 0.02;
    
    
    double error_ang = (m_last_machine_l_100-m_last_machine_r_100);

    sum_error_ang+=error_ang*time;
    if(sum_error_ang > sum_erreur_max){
        sum_error_ang = sum_erreur_max;
    }
    if(sum_error_ang < -sum_erreur_max){
        sum_error_ang = -sum_erreur_max;
    }
   
    double corr_ang = agress_hyd*error_ang + agress_hyd*0.2*sum_error_ang;


    double error_h = (m_work_h-(m_last_machine_l_100+m_last_machine_r_100)*0.5);
    sum_error_h+=error_h*time;
    if(sum_error_h > sum_erreur_max){
        sum_error_h = sum_erreur_max;
    }
    if(sum_error_h < -sum_erreur_max){
        sum_error_h = -sum_erreur_max;
    }
    double corr_h =  agress_hyd*error_h+ agress_hyd*0.2*sum_error_h;
    
    setTranslateur(corr_ang, corr_h);
}

void updateTime(){
    if((m_last_millis - m_last_millis_time) < 500){
        //hw_DebugPrint("*** update time %i %i\n", m_last_millis, m_last_millis_time);
        if(m_time_action == TimeAction_Left){
            //left
            setTranslateur(-100, 0);
        } else if(m_time_action == TimeAction_Right){
            setTranslateur(100, 0);
            //right
        } else if(m_time_action == TimeAction_Up){
            //up
            setTranslateur(0, 100);
        } else if(m_time_action == TimeAction_Down){
            //down
            setTranslateur(0, -100);
        } else {
            setTranslateur(0, 0);
        }
    } else {
        m_state = State_off;
        m_last_millis_time = 0;
        m_time_action = TimeAction_Off;
        setTranslateur(0, 0);
    }
}

void update50Hz(int millis){
    //int capteur_angle = 0;
    //int capteur_h = 0;
    readAll2(&m_last_machine_a, &m_last_machine_h, &m_last_machine_l, &m_last_machine_r);
    m_last_machine_a_100 = (double)m_last_machine_a*100.0/max_value;
    m_last_machine_h_100 = (double)m_last_machine_h*100.0/max_value;
    m_last_machine_l_100 = 100.0-(double)m_last_machine_l*100.0/max_value;
    m_last_machine_r_100 = (double)m_last_machine_r*100.0/max_value;

    if(!isAlive()){
        return;
    }
    
    if(m_state == State_time){
        updateTime();
    } else if(m_state == State_work){
        updateWorkstate();
    } else if(m_state == State_up){
        updateUp();
    } else {
        setElectrovanne(0, 0, 0, 0);
    }
}

int old_millis_50HZ = 0;
int old_millis_5HZ = 0;
void lemca_loop(){
    int millis = esp_timer_get_time()/1000;
    m_last_millis = millis;
    int i_50HZ = millis/20;
    if(i_50HZ != old_millis_50HZ){
        update50Hz(m_last_millis);
        old_millis_50HZ = i_50HZ;
    }

    int i_5HZ = millis/500;
    if(i_5HZ != old_millis_5HZ){
        //hw_DebugPrint("*** update time %i\n", m_last_millis);
        updateVTC();
        old_millis_5HZ = i_5HZ;
    }
    
}


void onButtonUp(){
    m_state = State_time;
    m_time_action = TimeAction_Up;
    setAlive();
    m_last_millis_time = m_last_millis;
    hw_DebugPrint("*** onButtonUp\n");
};
void onButtonDown(){
    m_state = State_time;
    m_time_action = TimeAction_Down;
    setAlive();
    m_last_millis_time = m_last_millis;
    hw_DebugPrint("*** onButtonDown\n");
};
void onButtonUpLeft(){
    m_state = State_time;
    m_time_action = TimeAction_Left;
    setAlive();
    m_last_millis_time = m_last_millis;
    hw_DebugPrint("*** onButtonLeft\n");
};
void onButtonUpRight(){
    m_state = State_time;
    m_time_action = TimeAction_Right;
    setAlive();
    m_last_millis_time = m_last_millis;
    hw_DebugPrint("*** onButtonRight\n");
};

void onButtonUpWork(){
    m_work_h += 5;
    setAlive();
    verify_config();
    save_config();
};
void onButtonDownWork(){
    m_work_h -= 5;
    setAlive();
    verify_config();
    save_config();
};


//setter accesseur
void setWorkHeight(int work_height){
    m_work_h = work_height;
    setAlive();
    verify_config();
    save_config();
};
int getWorkHeight(){
    return m_work_h;
};


void setVitesseMaxH(int vitesse_max_h){
    m_vitesse_max_h = vitesse_max_h;
    setAlive();
    verify_config();
    save_config();
}
int getVitesseMaxH(){
    return m_vitesse_max_h;
};

void setVitesseMaxAng(int vitesse_max_ang){
    m_vitesse_max_ang = vitesse_max_ang;
    setAlive();
    verify_config();
    save_config();
}
int getVitesseMaxAng(){
    return m_vitesse_max_ang;
};
