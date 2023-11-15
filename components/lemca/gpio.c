#include "gpio.h"

#include "driver/gpio.h"
#include "driver/ledc.h"

#include "common/util.h"
#include "lemca.h"
#include "AppIso/config.h"
#include "AppCommon/AppHW.h"

#include "driver/adc.h"

#define CAPTEUR_ANGLE_PIN ADC2_CHANNEL_0
#define CAPTEUR_H_PIN ADC2_CHANNEL_3

#define CAPTEUR_MACHINE_L ADC2_CHANNEL_1
#define CAPTEUR_MACHINE_R ADC2_CHANNEL_2

#define MOTOR_L_PWM GPIO_NUM_15 //pwm
#define MOTOR_R_PWM GPIO_NUM_16 //pwm
#define MOTOR_U_PWM GPIO_NUM_17 //pwm
#define MOTOR_D_PWM GPIO_NUM_18 //pwm

void initADC(){
    adc2_config_channel_atten( CAPTEUR_ANGLE_PIN, ADC_ATTEN_11db );
    adc2_config_channel_atten( CAPTEUR_H_PIN, ADC_ATTEN_11db );
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc2_config_channel_atten( CAPTEUR_MACHINE_L, ADC_ATTEN_11db );
    adc2_config_channel_atten( CAPTEUR_MACHINE_R, ADC_ATTEN_11db );
}

ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .timer_num  = LEDC_TIMER_0,
    .duty_resolution = LEDC_TIMER_13_BIT,
    .freq_hz = 1000,
    .clk_cfg = LEDC_AUTO_CLK
};
ledc_channel_config_t ledc_channel[4];

static void initPwm(void)
{
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
    ledc_channel[0].channel = LEDC_CHANNEL_0;
    ledc_channel[0].gpio_num = MOTOR_L_PWM;

    ledc_channel[1].channel = LEDC_CHANNEL_1;
    ledc_channel[1].gpio_num = MOTOR_R_PWM;

    ledc_channel[2].channel = LEDC_CHANNEL_2;
    ledc_channel[2].gpio_num = MOTOR_U_PWM;

    ledc_channel[3].channel = LEDC_CHANNEL_3;
    ledc_channel[3].gpio_num = MOTOR_D_PWM;
    for (int i = 0; i < 4; i++)
    {   
        ledc_channel[i].speed_mode = LEDC_LOW_SPEED_MODE;
        ledc_channel[i].timer_sel = LEDC_TIMER_0;
        ledc_channel[i].intr_type = LEDC_INTR_DISABLE;
        ledc_channel[i].duty = 0;
        ledc_channel[i].hpoint = 0;
        
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel[i]));
    }

    /*gpio_set_direction_out(MOTOR_L_PWM);
    gpio_set_direction_out(MOTOR_R_PWM);
	gpio_set_direction_out(MOTOR_U_PWM);
    gpio_set_direction_out(MOTOR_D_PWM);*/
	
}


void setup_gpio(){
    initADC();
    initPwm();
}

void update_gpio(int millis){
}

void readAll2(int * capteur_angle, int * capteur_h, int * machine_l, int * machine_r){
    adc2_get_raw(CAPTEUR_ANGLE_PIN, ADC_WIDTH_BIT_DEFAULT, capteur_angle);
    adc2_get_raw(CAPTEUR_H_PIN, ADC_WIDTH_BIT_DEFAULT, capteur_h);
    adc2_get_raw(CAPTEUR_MACHINE_L, ADC_WIDTH_BIT_DEFAULT, machine_l);
    adc2_get_raw(CAPTEUR_MACHINE_R, ADC_WIDTH_BIT_DEFAULT, machine_r);
}

void setElectrovanne(int left, int right, int up, int down){
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, left));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, right));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1));

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, up));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2));

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, down));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3));
        
}