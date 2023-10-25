#include "isobus_message.h"

#include "AppIso/VIEngine.h"
#include "lib_cci/IsoVtcApi.h"
#include "AppIso/App_VTClientLev2.h"

#include "lemca.h"

#include "uart/my_uart.h"
void debugIsobusMessage(uint8_t canNode_u8, twai_message_t* twai_msg_ps, uint8_t isRX){
    /*uint32_t u32PGN;
    u32PGN = (twai_msg_ps->identifier & 0x03FFFF00uL) >> 8u;
    if ((u32PGN & 0x00FF00uL) < PGN_PDU2_240_X)
    {  // PDU 1 -> remove DA
        u32PGN &= 0x03FF00uL;
    }


    hw_DebugPrint("$CAN,%8.8X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%4.4X,*\n", twai_msg_ps->identifier,
         twai_msg_ps->data[0], twai_msg_ps->data[1], twai_msg_ps->data[2], twai_msg_ps->data[3],
         twai_msg_ps->data[4], twai_msg_ps->data[5], twai_msg_ps->data[6], twai_msg_ps->data[7], u32PGN);*/
}

void OnLightingCommand(twai_message_t* twai_msg_ps){ //FE41 65089
    /*int daytime_running_lights = (twai_msg_ps->data[0] & 0x03);   //1.1
    int alternate_headlights = (twai_msg_ps->data[0] & 0x0C) >> 2;  //1.3
    int low_beam_headlights  = (twai_msg_ps->data[0] & 0x30) >> 4;  //1.5
    int high_beam_headlights  = (twai_msg_ps->data[0] & 0xC0) >> 6; //1.7
    
    int tractor_front_fog_lights = (twai_msg_ps->data[1] & 0x03);*/ //2.1
    //int rotating_beacon_light = (twai_msg_ps->data[1] & 0x0C) >> 2; //2.3
    /*int right_turn_signal_lights  = (twai_msg_ps->data[1] & 0x30) >> 4; //2.5
    int left_turn_signal_lights  = (twai_msg_ps->data[1] & 0xC0) >> 6; //2.7
    
    int back_up_lights_and_alarm_horn = (twai_msg_ps->data[2] & 0x03); //3.1
    int centre_stop_lights = (twai_msg_ps->data[2] & 0x0C) >> 2; //3.3
    int right_stop_lights  = (twai_msg_ps->data[2] & 0x30) >> 4; //3.5
    int Left_stop_lights  = (twai_msg_ps->data[2] & 0xC0) >> 6;*///3.7

    /*int tractor_side_low_mounted_work_lights = (twai_msg_ps->data[5] & 0x03); //6.1
    int tractor_side_high_mounted_work_lights = (twai_msg_ps->data[5] & 0x0C) >> 2; //6.3
    int tractor_front_low_mounted_work_lights  = (twai_msg_ps->data[5] & 0x30) >> 4; //6.5
    int tractor_front_high_mounted_work_lights  = (twai_msg_ps->data[5] & 0xC0) >> 6;//6.7*/

    //7 command

    //int lighting_data_message_request_command = (twai_msg_ps->data[7] & 0x03);  //8.1
    //int implement_right_facing_work_lights = (twai_msg_ps->data[7] & 0x0C) >> 2;
    //int implement_left_facing_work_lights  = (twai_msg_ps->data[7] & 0x30) >> 4;
    //int implement_rear_work_lights = (twai_msg_ps->data[7] & 0xC0) >> 6;

    /*if(truc == 0){
        setAutoWorkLamp(0);
    } else if(truc == 1){
        setAutoWorkLamp(1);
    }*/
}

void OnWheelBasesSpeed(twai_message_t* twai_msg_ps){ //FE48 65096
    int speed = twai_msg_ps->data[0] | (twai_msg_ps->data[1] << 8);
    double speed_km_h = 0.0036*speed;
    /*int distance = (twai_msg_ps->data[5] << 24) | twai_msg_ps->data[4] << 16 | (twai_msg_ps->data[3] << 8) | twai_msg_ps->data[2];
    double distance_m = 0.001*distance;
    int power = twai_msg_ps->data[6];
    int direction = (twai_msg_ps->data[7] & 0x03); //8.1
    int state = (twai_msg_ps->data[7] & 0x0C) >> 2; //8.2
    int start_stop = (twai_msg_ps->data[7] & 0x30) >> 4; //8.3
    int reversed = (twai_msg_ps->data[7] & 0xC0) >> 6; //8.4*/

    /*hw_DebugPrint("$CAN_DEBUG,WHEEL_SPEED,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,    %2.2X,*\n",
         twai_msg_ps->data[0], twai_msg_ps->data[1], twai_msg_ps->data[2], twai_msg_ps->data[3],
         twai_msg_ps->data[4], twai_msg_ps->data[5], twai_msg_ps->data[6], twai_msg_ps->data[7]);

    hw_DebugPrint("$CAN_DEBUG,WHEEL_SPEED_2 , %4.4X,   %8.8X,%2.2X,%1.1X,%1.1X,%1.1X,%1.1X,*\n",
         speed, distance, power, direction, state, start_stop, reversed);
    hw_DebugPrint("$CAN_DEBUG,WHEEL_SPEED_3 , %f km/h,%f m,%f min\n",
         speed_km_h, distance_m, power);*/

    setSpeedKmH(speed_km_h);
}

void OnRearHitch(twai_message_t* twai_msg_ps){ //FE45 65093
    //int position = (twai_msg_ps->data[0]);
    //double position_perc = 0.4*position;
    //int inwork = (twai_msg_ps->data[1] & 0xC0) >> 6;
    //int status = (twai_msg_ps->data[1] & 0x38) >> 3;
    //hw_DebugPrint("$CAN_DEBUG,REAR_HITCH,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%2.2X,%4.4X,*\n",
        //twai_msg_ps->data[0], twai_msg_ps->data[1], twai_msg_ps->data[2], twai_msg_ps->data[3],
        //twai_msg_ps->data[4], twai_msg_ps->data[5], twai_msg_ps->data[6], twai_msg_ps->data[7]);
    //hw_DebugPrint("$CAN_DEBUG,REAR_HITCH_2 , %2.2X*\n",
        //position);
    //hw_DebugPrint("CAN_DEBUG,REAR_HITCH_3 , %f perc,%i status,%i inwork\n",
        //position_perc, status, inwork);
    //setRearWork(inwork);
}

void onIsobusMessage(uint8_t canNode_u8, twai_message_t* twai_msg_ps, uint8_t isRX){
    debugIsobusMessage(canNode_u8, twai_msg_ps, isRX);
    uint32_t u32PGN;
    u32PGN = (twai_msg_ps->identifier & 0x03FFFF00uL) >> 8u;
    if ((u32PGN & 0x00FF00uL) < PGN_PDU2_240_X)
    {  /* PDU 1 -> remove DA */
        u32PGN &= 0x03FF00uL;
    }
    switch(u32PGN){
        case PGN_LIGHTING_COMMAND: //FE41 65089
            OnLightingCommand(twai_msg_ps);
            break;
        case PGN_REAR_HITCH: //FE45 65093
            OnRearHitch(twai_msg_ps);
            break;
        case PGN_GROUND_BASED_SPEED: //Test PGN 65097 radar speed
            OnWheelBasesSpeed(twai_msg_ps);
            break;
        
    }

}



//PGN_REAR_HITCH

