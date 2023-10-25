#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "soc/uart_struct.h"
#include "driver/uart.h"
#include "AppCommon/AppHW.h"

#include <string.h>
#include "my_uart.h"
#include "../lemca.h"

#define BUF_SIZE (1024)

const int uart_imu_num = UART_NUM_1;
const int uart_mnea_num = UART_NUM_2;
    
char* data_mnea;
char* data_imu;

void uart_init(void){ 
    uart_config_t uart_mnea_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,    
        .rx_flow_ctrl_thresh = 122,
    };
    uart_param_config(uart_mnea_num, &uart_mnea_config);
    uart_set_pin(uart_mnea_num, 15, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    
    uart_driver_install(uart_mnea_num, BUF_SIZE*2, 0, 0, NULL, 0);
    
    //hw_DebugPrint("Setup imu !\n");
    uart_config_t uart_imu_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,    
        .rx_flow_ctrl_thresh = 122,
    };
    uart_param_config(uart_imu_num, &uart_imu_config);
    uart_set_pin(uart_imu_num, 17, 18, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    
    uart_driver_install(uart_imu_num, BUF_SIZE * 2, 0, 0, NULL, 0);
    
    data_mnea = (char*) malloc(BUF_SIZE);
    data_imu = (char*) malloc(BUF_SIZE);
}

void uart_loop(void){
    int millis = esp_timer_get_time()/1000;
    uart_send_loop_message(millis);

    int len_mnea = uart_read_bytes(uart_mnea_num, data_mnea, BUF_SIZE, 10 / portTICK_RATE_MS);
    if(len_mnea > 0){
        for(int i = 0; i < len_mnea; ++i){
            //mneaReadChar(data_mnea[i]);
        }
        //hw_DebugPrint(" mnea (%i) => %.*s\n", millis, len_mnea, data_mnea);
    }
    
    
    int len_imu = uart_read_bytes(uart_imu_num, data_imu, BUF_SIZE, 10 / portTICK_RATE_MS);
    if(len_imu > 0){
        for(int i = 0; i < len_imu; ++i){
            //imuReadChar(data_imu[i]);
        }
        //hw_DebugPrint(" imu (%i) => %.*s\n", millis, len_imu, data_imu);
    }

    
}

int old_time = 0;
void uart_send_loop_message(int millis){
}

void uart_send_message_aux(int touch){
}

void uart_send_message(char * c){
    uart_write_bytes(uart_mnea_num, (const char*)c, strlen(c));
}