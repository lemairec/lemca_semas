#include "gpio.h"

#include "driver/gpio.h"
#include "common/util.h"
#include "lemca.h"
#include "AppIso/config.h"


/*#include "driver/ledc.h"
#include "driver/pcnt.h"
#include "common/util.h"

#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "esp_system.h"
#include "esp_timer.h"*/



/*#define SC_ENABLE GPIO_NUM_10 Hadrien

#define SC_PIN_1 GPIO_NUM_6
#define SC_PIN_2 GPIO_NUM_8
#define SC_PIN_3 GPIO_NUM_9 
#define SC_PIN_4 GPIO_NUM_7 */

#define SC_ENABLE GPIO_NUM_15

#define SC1_PIN GPIO_NUM_16
#define SC2_PIN GPIO_NUM_17
#define SC3_PIN GPIO_NUM_18 
#define SC4_PIN GPIO_NUM_8
#define SC5_PIN GPIO_NUM_19
#define SC6_PIN GPIO_NUM_20 
#define SC7_PIN GPIO_NUM_3 
#define SC8_PIN GPIO_NUM_46 
#define SC9_PIN GPIO_NUM_9 
#define SC10_PIN GPIO_NUM_10 
#define SC11_PIN GPIO_NUM_11 
#define SC12_PIN GPIO_NUM_12 
#define SC13_PIN GPIO_NUM_13 

#define TIME_UPDATE_SC_MS 4000

void gpio_set_direction_out(int gpio){
    lc_DebugPrint("  --> %i\n", gpio);
    gpio_reset_pin(gpio);
    int i = gpio_set_direction (gpio, GPIO_MODE_OUTPUT);
    if(i != ESP_OK){
        lc_DebugPrint("problem\n");
    }
}


void setup_gpio(){
    lc_DebugPrint("$INIT,*\n");

    gpio_set_direction_out(SC_ENABLE);
    gpio_set_direction_out(SC1_PIN);
	gpio_set_direction_out(SC2_PIN);
	gpio_set_direction_out(SC3_PIN);
	gpio_set_direction_out(SC4_PIN);
    gpio_set_direction_out(SC5_PIN);
    gpio_set_direction_out(SC6_PIN);
	gpio_set_direction_out(SC7_PIN);
	gpio_set_direction_out(SC8_PIN);
	gpio_set_direction_out(SC9_PIN);
    gpio_set_direction_out(SC10_PIN);
	gpio_set_direction_out(SC11_PIN);
	gpio_set_direction_out(SC12_PIN);
	gpio_set_direction_out(SC13_PIN);

    lc_DebugPrint("$INIT,END,*\n");
}


int m_sc1_old_value = 0;
int m_sc1_time_counter = 0;
int m_sc2_old_value = 0;
int m_sc2_time_counter = 0;
int m_sc3_old_value = 0;
int m_sc3_time_counter = 0;
int m_sc4_old_value = 0;
int m_sc4_time_counter = 0;
int m_sc5_old_value = 0;
int m_sc5_time_counter = 0;
int m_sc6_old_value = 0;
int m_sc6_time_counter = 0;
int m_sc7_old_value = 0;
int m_sc7_time_counter = 0;
int m_sc8_old_value = 0;
int m_sc8_time_counter = 0;
int m_sc9_old_value = 0;
int m_sc9_time_counter = 0;
int m_sc10_old_value = 0;
int m_sc10_time_counter = 0;
int m_sc11_old_value = 0;
int m_sc11_time_counter = 0;
int m_sc12_old_value = 0;
int m_sc12_time_counter = 0;
int m_sc13_old_value = 0;
int m_sc13_time_counter = 0;

int m_time_counter_enable = 0;


void update_one_gpio(int no_sc, int *old_value, int * time_sc){
    if(no_sc <= m_nbr_elements){
        int value_tc1 = getSection(no_sc);
        //lc_DebugPrint(" %i => %i - %i => %i \n", no_sc, value_tc1, *old_value, *time_sc);
        if(value_tc1 != (*old_value)){
            *time_sc = TIME_UPDATE_SC_MS/100;
            if(!value_tc1){
                m_time_counter_enable = TIME_UPDATE_SC_MS/100;
            }
            *old_value = value_tc1;
        }
    }

    if((*time_sc) > 0){
        (*time_sc)--;
    }
    //lc_DebugPrint(" %i => %i - %i \n", no_sc, m_time_counter_enable);
}

void update_one_gpio2(int time_sci, int old_value_i, int *i_tc){
    if(m_time_counter_enable){
        if(time_sci){
            *i_tc = 1;
        } else {
            *i_tc = 0;
        }
        
    } else {
        *i_tc = old_value_i;
    }
    
    //lc_DebugPrint(" %i => %i - %i \n", no_sc, m_time_counter_enable);
}

char getChar(int no, int i_tc){
    if(no <= m_nbr_elements){
        if(i_tc){
            return '1';
        } else {
            return '0';
        }
    } else {
        if(i_tc){
            return '-';
        } else {
            return '|';
        }
    }
}

int getItci(int no_sc, int *enable){
    if(no_sc <= m_nbr_elements){
        int res = !getSection(no_sc);
        if(res){
            *enable = 1;
        }
        return res;
    }
    return 0;
}


void update_gpio(int millis){
/*
   
    update_one_gpio(1, &m_sc1_old_value, &m_sc1_time_counter);
    update_one_gpio(2, &m_sc2_old_value, &m_sc2_time_counter);
    update_one_gpio(3, &m_sc3_old_value, &m_sc3_time_counter);
    update_one_gpio(4, &m_sc4_old_value, &m_sc4_time_counter);
    update_one_gpio(5, &m_sc5_old_value, &m_sc5_time_counter);
    update_one_gpio(6, &m_sc6_old_value, &m_sc6_time_counter);
    update_one_gpio(7, &m_sc7_old_value, &m_sc7_time_counter);
    update_one_gpio(8, &m_sc8_old_value, &m_sc8_time_counter);
    update_one_gpio(9, &m_sc9_old_value, &m_sc9_time_counter);
    update_one_gpio(10, &m_sc10_old_value, &m_sc10_time_counter);
    update_one_gpio(11, &m_sc11_old_value, &m_sc11_time_counter);
    update_one_gpio(12, &m_sc12_old_value, &m_sc12_time_counter);
    update_one_gpio(13, &m_sc13_old_value, &m_sc13_time_counter);

    int i_enable = 0;
    int i_tc1 = 0;
    int i_tc2 = 0;
    int i_tc3 = 0;
    int i_tc4 = 0;
    int i_tc5 = 0;
    int i_tc6 = 0;
    int i_tc7 = 0;
    int i_tc8 = 0;
    int i_tc9 = 0;
    int i_tc10 = 0;
    int i_tc11 = 0;
    int i_tc12 = 0;
    int i_tc13 = 0;
    
    if(m_time_counter_enable > 0){
        i_enable = 1;
        m_time_counter_enable--;
    } else {
        i_enable = 0;
        
    }

    update_one_gpio2(m_sc1_time_counter, m_sc1_old_value, &i_tc1);
    update_one_gpio2(m_sc2_time_counter, m_sc2_old_value, &i_tc2);
    update_one_gpio2(m_sc3_time_counter, m_sc3_old_value, &i_tc3);
    update_one_gpio2(m_sc4_time_counter, m_sc4_old_value, &i_tc4);
    update_one_gpio2(m_sc5_time_counter, m_sc5_old_value, &i_tc5);
    update_one_gpio2(m_sc6_time_counter, m_sc6_old_value, &i_tc6);
    update_one_gpio2(m_sc7_time_counter, m_sc7_old_value, &i_tc7);
    update_one_gpio2(m_sc8_time_counter, m_sc8_old_value, &i_tc8);
    update_one_gpio2(m_sc9_time_counter, m_sc9_old_value, &i_tc9);
    update_one_gpio2(m_sc10_time_counter, m_sc10_old_value, &i_tc10);
    update_one_gpio2(m_sc11_time_counter, m_sc11_old_value, &i_tc11);
    update_one_gpio2(m_sc12_time_counter, m_sc12_old_value, &i_tc12);
    update_one_gpio2(m_sc13_time_counter, m_sc13_old_value, &i_tc13);

    */ 

    int i_enable = 0;
    int i_tc1 = getItci(1, &i_enable);
    int i_tc2 = getItci(2, &i_enable);
    int i_tc3 = getItci(3, &i_enable);
    int i_tc4 = getItci(4, &i_enable);
    int i_tc5 = getItci(5, &i_enable);
    int i_tc6 = getItci(6, &i_enable);
    int i_tc7 = getItci(7, &i_enable);
    int i_tc8 = getItci(8, &i_enable);
    int i_tc9 = getItci(9, &i_enable);
    int i_tc10 = getItci(10, &i_enable);
    int i_tc11 = getItci(11, &i_enable);
    int i_tc12 = getItci(12, &i_enable);
    int i_tc13 = getItci(13, &i_enable);

    gpio_set_level(SC_ENABLE, i_enable);
    gpio_set_level(SC1_PIN, i_tc1);
    gpio_set_level(SC2_PIN, i_tc2);
    gpio_set_level(SC3_PIN, i_tc3);
    gpio_set_level(SC4_PIN, i_tc4);
    gpio_set_level(SC5_PIN, i_tc5);
    gpio_set_level(SC6_PIN, i_tc6);
    gpio_set_level(SC7_PIN, i_tc7);
    gpio_set_level(SC8_PIN, i_tc8);
    gpio_set_level(SC9_PIN, i_tc9);
    gpio_set_level(SC10_PIN, i_tc10);
    gpio_set_level(SC11_PIN, i_tc11);
    gpio_set_level(SC12_PIN, i_tc12);
    gpio_set_level(SC13_PIN, i_tc13);
    

   /** char c1 = getChar(1, i_tc1);
    char c2 = getChar(2, i_tc2);
    char c3 = getChar(3, i_tc3);
    char c4 = getChar(4, i_tc4);
    char c5 = getChar(5, i_tc5);
    char c6 = getChar(6, i_tc6);
    char c7 = getChar(7, i_tc7);
    char c8 = getChar(8, i_tc8);
    char c9 = getChar(9, i_tc9);
    char c10 = getChar(10, i_tc10);
    char c11 = getChar(11, i_tc11);
    char c12 = getChar(12, i_tc12);
    char c13 = getChar(13, i_tc13);
    lc_DebugPrint("(%i) %i => %c - %c - %c - %c - %c - %c - %c - %c - %c - %c - %c - %c - %c\n", millis, i_enable, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13);*/
}
