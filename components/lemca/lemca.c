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

int m_alive = 0;

void setAlive(){
    m_alive = 5;
}

int isAlive(){
    return (m_alive > 1);
}
void decreaseAlive(){
    --m_alive;
}

double m_speed_kmh;
void setSpeedKmH(double speed_kmh){
    m_speed_kmh = speed_kmh;
    setAlive();
    //updateVTC();
}
double getSpeedKmH(){
    return m_speed_kmh;
}


int m_workstate = 0;


int m_section1 = 1;
int m_section2 = 1;
int m_section3 = 1;
int m_section4 = 1;
int m_section5 = 1;
int m_section6 = 1;
int m_section7 = 1;
int m_section8 = 1;
int m_section9 = 1;
int m_section10 = 1;
int m_section11 = 1;
int m_section12 = 1;
int m_section13 = 1;
int m_section14 = 1;
int m_section15 = 1;
int m_section16 = 1;

int getWorkState(){
    return m_workstate;
}

void setWorkState(int workstate){
    m_workstate = workstate;
    if(m_workstate){
        m_section1 = 1;
        m_section2 = 1;
        m_section3 = 1;
        m_section4 = 1;
        m_section5 = 1;
        m_section6 = 1;
        m_section7 = 1;
        m_section8 = 1;
        m_section9 = 1;
        m_section10 = 1;
        m_section11 = 1;
        m_section12 = 1;
        m_section13 = 1;
        m_section14 = 1;
        m_section15 = 1;
        m_section16 = 1;
    } else {
        m_section1 = 0;
        m_section2 = 0;
        m_section3 = 0;
        m_section4 = 0;
        m_section5 = 0;
        m_section6 = 0;
        m_section7 = 0;
        m_section8 = 0;
        m_section9 = 0;
        m_section10 = 0;
        m_section11 = 0;
        m_section12 = 0;
        m_section13 = 0;
        m_section14 = 0;
        m_section15 = 0;
        m_section16 = 0;
    }
}

void changeWorkState(){
    setWorkState(!m_workstate);
}


int m_inwork = 0;
void setRearWork(int inwork){
    m_inwork = inwork;
    setAlive();
    //setWorkState(inwork);
}
int getRearWork(){
    return m_inwork;
}

int getSectionAndNbr(int no){
    if(no <= m_nbr_elements){
        return getSection(no);
    } else {
        return false;
    }
}

int getNotectionAndNbr(int no){
    if(no <= m_nbr_elements){
        return !getSection(no);
    } else {
        return false;
    }
}

int checkSection1toN(int no){
    for(int i = 1; i <= no; ++i){
        if(!getSectionAndNbr(i)){
            return false;
        }
    }
    return true;
}

int checkSectionNto13(int no){
    if(no > m_nbr_elements){
        return false;
    }
    for(int i = no; i <= m_nbr_elements; ++i){
        if(i <= m_nbr_elements){
            if(!getSection(i)){
                return false;
            }
        }
    }
    return true;
}

void startManualSectionLeft(){
    lc_DebugPrint("la_left");
    if(checkSection1toN(13)){
        m_section13 = 0;
    } else if(checkSection1toN(12)){
        m_section12 = 0;
    } else if(checkSection1toN(11)){
        m_section11 = 0;
    } else if(checkSection1toN(10)){
        m_section10 = 0;
    } else if(checkSection1toN(9)){
        m_section9 = 0;
    } else if(checkSection1toN(8)){
        m_section8 = 0;
    } else if(checkSection1toN(7)){
        m_section7 = 0;
    } else if(checkSection1toN(6)){
        m_section6 = 0;
    } else if(checkSection1toN(5)){
        m_section5 = 0;
    } else if(checkSection1toN(4)){
        m_section4 = 0;
    } else if(checkSection1toN(3)){
        m_section3 = 0;
    } else if(checkSection1toN(2)){
        m_section2 = 0;
    } else if(checkSection1toN(1)){
        m_section1 = 0;
    } else if(getNotectionAndNbr(13)){
        m_section13 = 1;
    } else if(getNotectionAndNbr(12)){
        m_section12 = 1;
    } else if(getNotectionAndNbr(11)){
        m_section11 = 1;
    } else if(getNotectionAndNbr(10)){
        m_section10 = 1;
    } else if(getNotectionAndNbr(9)){
        m_section9 = 1;
    } else if(getNotectionAndNbr(8)){
        m_section8 = 1;
    } else if(getNotectionAndNbr(7)){
        m_section7 = 1;
    } else if(getNotectionAndNbr(6)){
        m_section6 = 1;
    } else if(getNotectionAndNbr(5)){
        m_section5 = 1;
    } else if(getNotectionAndNbr(4)){
        m_section4 = 1;
    } else if(getNotectionAndNbr(3)){
        m_section3 = 1;
    } else if(getNotectionAndNbr(2)){
        m_section2 = 1;
    } else if(getNotectionAndNbr(1)){
        m_section1 = 1;
    }
}



void startManualSectionRight(){
    if(checkSectionNto13(1)){
        m_section1 = 0;
    } else if(checkSectionNto13(2)){
        m_section2 = 0;
    } else if(checkSectionNto13(3)){
        m_section3 = 0;
    } else if(checkSectionNto13(4)){
        m_section4 = 0;
    } else if(checkSectionNto13(5)){
        m_section5 = 0;
    } else if(checkSectionNto13(6)){
        m_section6 = 0;
    } else if(checkSectionNto13(7)){
        m_section7 = 0;
    } else if(checkSectionNto13(8)){
        m_section8 = 0;
    } else if(checkSectionNto13(9)){
        m_section9 = 0;
    } else if(checkSectionNto13(10)){
        m_section10 = 0;
    } else if(checkSectionNto13(11)){
        m_section11 = 0;
    } else if(checkSectionNto13(12)){
        m_section12 = 0;
    } else if(checkSectionNto13(13)){
        m_section13 = 0;
    } else if(getNotectionAndNbr(1)){
        m_section1 = 1;
    } else if(getNotectionAndNbr(2)){
        m_section2 = 1;
    } else if(getNotectionAndNbr(3)){
        m_section3 = 1;
    } else if(getNotectionAndNbr(4)){
        m_section4 = 1;
    } else if(getNotectionAndNbr(5)){
        m_section5 = 1;
    } else if(getNotectionAndNbr(6)){
        m_section6 = 1;
    } else if(getNotectionAndNbr(7)){
        m_section7 = 1;
    } else if(getNotectionAndNbr(8)){
        m_section8 = 1;
    } else if(getNotectionAndNbr(9)){
        m_section9 = 1;
    } else if(getNotectionAndNbr(10)){
        m_section10 = 1;
    } else if(getNotectionAndNbr(11)){
        m_section11 = 1;
    } else if(getNotectionAndNbr(12)){
        m_section12 = 1;
    } else if(getNotectionAndNbr(13)){
        m_section13 = 1;
    }
}

int getSection(int i){
    if(i == 1){
        return m_section1;
    } else if(i == 2){
        return m_section2;
    } else if(i == 3){
        return m_section3;
    } else if(i == 4){
        return m_section4;
    } else if(i == 5){
        return m_section5;
    } else if(i == 6){
        return m_section6;
    } else if(i == 7){
        return m_section7;
    } else if(i == 8){
        return m_section8;
    } else if(i == 9){
        return m_section9;
    } else if(i == 10){
        return m_section10;
    } else if(i == 11){
        return m_section11;
    } else if(i == 12){
        return m_section12;
    } else if(i == 13){
        return m_section13;
    } else if(i == 14){
        return m_section14;
    } else if(i == 15){
        return m_section15;
    } else if(i == 16){
        return m_section16;
    }
    return 0;
}


int getTCSection(){
    int res = 0;
    res += m_section1*0x00000001;
    res += m_section2*0x00000004;
    res += m_section3*0x00000010;
    res += m_section4*0x00000040;
    res += m_section5*0x00000100;
    res += m_section6*0x00000400;
    res += m_section7*0x00001000;
    res += m_section8*0x00004000;
    res += m_section9*0x00010000;
    res += m_section10*0x00040000;
    res += m_section11*0x00100000;
    res += m_section12*0x00400000;
    res += m_section13*0x01000000;
    res += m_section14*0x04000000;
    res += m_section15*0x10000000;
    res += m_section16*0x40000000;
    return res;
}
void setTCSection(int value){
    if(m_workstate){
        if(m_speed_kmh > m_vitesse_min_kmh){
            m_section1 = (value & 0x00000001);
            m_section2 = (value & 0x00000004) >> 2;
            m_section3 = (value & 0x00000010) >> 4;
            m_section4 = (value & 0x00000040) >> 6;
            m_section5 = (value & 0x00000100) >> 8;
            m_section6 = (value & 0x00000400) >> 10;
            m_section7 = (value & 0x00001000) >> 12;
            m_section8 = (value & 0x00004000) >> 14;
            m_section9 = (value & 0x00010000) >> 16;
            m_section10 = (value & 0x00040000) >> 18;
            m_section11 = (value & 0x00100000) >> 20;
            m_section12 = (value & 0x00400000) >> 22;
            m_section13 = (value & 0x01000000) >> 24;
            m_section14 = (value & 0x04000000) >> 26;
            m_section15 = (value & 0x10000000) >> 28;
            m_section16 = (value & 0x40000000) >> 30;
        }
    }
}

void send_message_aux(int touch){
    uart_send_message_aux(touch);
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

