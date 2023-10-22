/****************************************************************************/
/*!
   \file        IsoPgnDef.h
   \brief       PGN and SPN definitions and data for initialising of SPNs in application 

   \author      Hammerl Erwin
   \date        Created 12.07.2011

   \copyright   Competence Center ISOBUS e.V.

   \par HISTORY:
   \par
   16.03.2012 - author P. Wegscheider
   - FMI defines updated
   \par
   16.10.2014 - author E. Hammerl
   - Added SPN defines of ISO11783-8 ( provided of Eric ) 
   \par
   13.05.2015 - author E. Hammerl
   - Added PGN defines for TIM
   \par
   29.11.2016 - author P. Wegscheider
   - Added PGN define for heartbeat message
   \par
   09.03.2018 - author P. Wegscheider
   - BugID 8519: Replace Defines XY with ISO_XY
   \par
   10.07.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files \n
     removed 64-bit defines NMEA_ERROR_INDI_ULL and NMEA_NOT_AVAILABLE_ULL
   \par
   09.11.2020 - author E. Hammerl
   - All implements stop operations switch state SPNs added
*/
#ifndef DEF_ISOPGNDEF_H
    #define DEF_ISOPGNDEF_H

/* ************************************************************************ */
/** \addtogroup isopgns
@{ 
*/
/* ************************************************************************ */
/* PGNs PDU1 and Group Functions                                            */
/* ************************************************************************ */

#define PGN_TORQUE_SPEED_CONTROL1                  (0x0000UL)      /**< 00000 - TSC1 */
#define PGN_TRANSMISSION_CONTROL1                  (0x0100UL)      /**< 00256 - TC1 */
#define PGN_TIMS_TO_TIMC                           (0x2300UL)      /**< 08960 - TIM server to client */
#define PGN_TIMC_TO_TIMS                           (0x2400UL)      /**< 09216 - TIM client to server */
#define PGN_AUTC_TO_AUTS                           (0x6F00UL)      /**< 28416 - Auth client to server */
#define PGN_AUTS_TO_AUTC                           (0x7000UL)      /**< 28672 - Auth server to client */
#define PGN_SCC_TO_SCM                             (0x8D00UL)      /**< 36096 - SCC - Sequence Control Annex B.1.a */
#define PGN_SCM_TO_SCC                             (0x8E00UL)      /**< 36352 - SCM - Sequence Control Annex B.1.a*/
#define PGN_NAME_MANAGEMENT                        (0x9300UL)      /**< 37632 - NAME management (NM) message Part-5:2011(E)*/

#define PGN_AUX_IO_STATUS_2                        (0xA700UL)      /**< 42752 - AUXIO2 */
#define PGN_FSC_TO_FS                              (0xAA00UL)      /**< 43520 - FSC - Part 13 File Server Annex C.1.1.b */
#define PGN_FS_TO_FSC                              (0xAB00UL)      /**< 43776 - FS  - Part 13 File Server Annex C.1.1.a */

#define PGN_GUIDANCE_MACHINE_STATUS                (0xAC00UL)      /**< 44032 - GMS   */
#define PGN_GUIDANCE_SYSTEM_COMMAND_MSG            (0xAD00UL)      /**< 44288 - GMC - see Part 7 - B.27.1 */
#define PGN_GENPURPOSE_VALVE_COMMAND               (0xC400UL)      /**< 50176 -    */
#define PGN_GENPURPOSE_VALVE_MEASFLOW              (0xC500UL)      /**< 50432 -    */
#define PGN_GENPURPOSE_VALVE_ESTIMFLOW             (0xC600UL)      /**< 50688 -    */
#define PGN_ETP_DT                                 (0xC700UL)      /**< 50944 - ETP_DT - extended data transport */
#define PGN_ETP_CM                                 (0xC800UL)      /**< 51200 - ETP_CM - connection managem. for ETP */
#define PGN_REQUEST2_PGN                           (0xC900UL)      /**< 51456 - REQUEST2 */
#define PGN_TRANSFER_PGN                           (0xCA00UL)      /**< 51712 - TRANSFER */
#define PGN_PROCESS_DATA                           (0xCB00UL)      /**< 51968 - Process data */
#define PGN_REQ_FOR_REP_RATE                       (0xCC00UL)      /**< 52224 - Request for repetition rate */
#define PGN_DoCAN_MIXED_FUNCTIONAL                 (0xCD00UL)      /**< 52480 - DoCAN3 - ISO15765 */
#define PGN_DoCAN_MIXED_PHYSICAL                   (0xCE00UL)      /**< 52736 - DoCAN4 - ISO15765 */
#define PGN_CONTINUOUSTORQUE                       (0xCF00UL)      /**< 52992 - CTL */
#define PGN_CAB_ILLUMINATION                       (0xD000UL)      /**< 53248 - CL */
#define PGN_AIRSUSPENSION_CONTROL6                 (0xD100UL)      /**< 53504 */
#define PGN_AIRSUSPENSION_CONTROL2                 (0xD200UL)      /**< 53760 */
#define PGN_CALIBRATION_INFORMATION                (0xD300UL)      /**< 54016 - DM19 */
#define PGN_DATA_SECURITY                          (0xD500UL)      /**< 54528 - DM18 */
#define PGN_BOOT_LOAD_DATA                         (0xD600UL)      /**< 54784 - DM17 */
#define PGN_BINARY_DATA_TRANSFER                   (0xD700UL)      /**< 55040 - DM16 */
#define PGN_MEMORY_ACCESS_RESPONSE                 (0xD800UL)      /**< 55296 - DM15 */
#define PGN_MEMORY_ACCESS_REQUEST                  (0xD900UL)      /**< 55552 - DM14 */
#define PGN_DoCAN_NORMAL_PHYSICAL                  (0xDA00UL)      /**< 55808 - DoCAN1 - ISO15765 */
#define PGN_DoCAN_NORMAL_FUNCTIONAL                (0xDB00UL)      /**< 56064 - DoCAN2 - ISO15765 */
#define PGN_ANTI_SHEFT_STATUS                      (0xDC00UL)      /**< 56320 - ATS */
#define PGN_ANTI_SHEFT_REQUEST                     (0xDD00UL)      /**< 56576 - ATR */
#define PGN_RESET                                  (0xDE00UL)      /**< 56832 - RESET */
#define PGN_STOP_START_BROADCAST                   (0xDF00UL)      /**< 57088 - DM13 */
#define PGN_CAB_MESSAGE1                           (0xE000UL)      /**< 57344 - CM1 */
#define PGN_CMD_NONCONTIN_MONITOR                  (0xE300UL)      /**< 58112 - DM7 */

/* Virtual Terminal - 11783-6 */
#define PGN_VTtoECU                                (0xE600UL)      /**< 58880 - VT to ECU */
#define PGN_ECUtoVT                                (0xE700UL)      /**< 59136 - ECU to VT */

/* Data Link Layer - 11783-3 */
#define PGN_N_ACK                                  (0xE800UL)      /**< 59392 - ACKM */
#define PGN_REQUEST_PGN                            (0xEA00UL)      /**< 59904 - RQST */
#define PGN_TP_DT                                  (0xEB00UL)      /**< 60160 - TP_DT  - J1939 PGN data transport */
#define PGN_TP_CM                                  (0xEC00UL)      /**< 60416 - TP_CM  - connection managem. for TP */

/* Network Layer - 11783-4 */
#define PGN_NETWORK_LAYER                          (0xED00UL)      /**< 60672 - NIU   - Part 4 network message */

/* Network management - 11783-5 */
#define PGN_ADDRESS_CLAIMED                        (0xEE00UL)      /**< 60928 - AC */
#define PGN_CANNOT_CLAIM_SA                        (0xEE00UL)      /**< 60928 - AC */

/* PDU2 - Application Layer ( vehicle, implement, diagnostic ) */
#define PGN_PDU1_PropA                             (0xEF00UL)      /**< 61184 - PDU1 manufacturer proprietary */
#define PGN_PDU1_PropA2                           (0x1EF00UL)      /**< 126720 - PDU1 manufacturer proprietary */
#define PGN_PDU2_240_X                             (0xF000UL)      /**< 61440 - see J1939-71, 73, 75, ISO 11783-8 */
#define PGN_PDU2_254_Y                             (0xFE00UL)      /**< 65024 - see J1939-71, 73, 75, ISO 11783-7 */
#define PGN_PDU2_PropB                             (0xFF00UL)      /**< 65280 - PDU2 proprietary */



/* ************************************************************************ */
/* PGNs PDU2                                                                */
/* ************************************************************************ */

/* J1939-71  - Vehicle Application layer */
#define PGN_ELEC_RETARDER_CONTROLLER               (0xF000UL)     /**< 61440 - ERC1 */
#define PGN_ELEC_BRAKE_CONTROLLER                  (0xF001UL)     /**< 61441 - EBC1 */
#define PGN_ELEC_TRANSMISS_CONTROLLER_1            (0xF002UL)     /**< 61442 - ETC1 */
#define PGN_ELEC_ENGINE_CONTROLLER_2               (0xF003UL)     /**< 61443 - EEC2 */
#define PGN_ELEC_ENGINE_CONTROLLER_1               (0xF004UL)     /**< 61444 - EEC1 */
#define PGN_ELEC_TRANSMISS_CONTROLLER_2            (0xF005UL)     /**< 61445 - ETC2 */
#define PGN_ELEC_AXLE_CONTROLLER_1                 (0xF006UL)     /**< 61446 - EAC1 */
#define PGN_FORW_LANE_IMAGE_URGENT_MSG             (0xF007UL)     /**< 61447 - FLI1 */
#define PGN_HYDRAULIC_PRESS_GOVER_INFO             (0xF008UL)     /**< 61448 - HPG  */
#define PGN_VEHICLE_DYN_STAB_CTRL_2                (0xF009UL)     /**< 61449 - VDC2 */
#define PGN_MACHINE_SELECTED_SPEED                 (0xF022UL)     /**< 61474 - 11783-7, B.28.1 */
#define PGN_ENGINE_GAS_FLOW_RATE                   (0xF00AUL)     /**< 61450 - EGF1 */
#define PGN_HEARTBEAT                              (0xF0E4UL)     /**< 61668 - Heartbeat message PGN */
#define PGN_PRODUCT_IDENTIFICATION                 (0xFC8DUL)     /**< 64653 - 11783-12, B.10 */
#define PGN_FUNCTIONALI_CHARACTERISTICS            (0xFC8EUL)     /**< 64654 - 11783-12, B.9 */
#define PGN_STOP_BUTTON                            (0xFD02UL)     /**< 64770 - 11783-7, B.30 */
#define PGN_IMPLEMENT_OPERATING_STATE              (0xFD03UL)     /**< 64771 - 11783-7, B.29 */
#define PGN_ECU_DIAGNOSTIC_PROTOCOL                (0xFD32UL)     /**< 64818 - 11783-12, B.5 */    
#define PGN_ISOBUS_COMPLIANCE_CERTIFICA            (0xFD42UL)     /**< 64834 - 11783-7, B.28, 11783-12, B.3 */ 
#define PGN_MACHINE_SELECT_SPEED_CMD               (0xFD43UL)     /**< 64835 - 11783-7, B.28.2 */
#define PGN_ENGINE_OPERATING_INFORMATIO            (0xFD92UL)     /**< 64914 - EOI */
#define PGN_ECU_IDENTIFICATION_INFO                (0xFDC5UL)     /**< 64965 - 11783-12, B.1 */ 
#define PGN_COLD_START_AIDS                        (0xFDC6UL)     /**< 64966 - CSA */
#define PGN_OFFHIGHW_ENGINE_CTRL_SELECT            (0xFDCBUL)     /**< 64971 - OHECS */
#define PGN_FMS_STANDARD_INTERFAC_IDENT            (0xFDD1UL)     /**< 64977 - FMS  */
#define PGN_ECU_PERFORMANCE                        (0xFDD2UL)     /**< 64978 - EP   */
#define PGN_TURBOCHARGER_INFORMATION_6             (0xFDD3UL)     /**< 64979 - TCI6 */
#define PGN_CAB_MESSAGE_3                          (0xFDD4UL)     /**< 64980 - CM3  */
#define PGN_ELEC_ENGINE_CONTROLLER_5               (0xFDD5UL)     /**< 64981 - EEC5 */
#define PGN_BASIC_JOYSTICK_MESSAGE_1               (0xFDD6UL)     /**< 64982 - BJM1 */
#define PGN_EXTENDED_JOYSTICK_MESSAGE_1            (0xFDD7UL)     /**< 64983 - EJM1 */
#define PGN_BASIC_JOYSTICK_MESSAGE_2               (0xFDD8UL)     /**< 64984 - BJM2 */
#define PGN_EXTENDED_JOYSTICK_MESSAGE_2            (0xFDD9UL)     /**< 64985 - EJM2 */
#define PGN_BASIC_JOYSTICK_MESSAGE_3               (0xFDDAUL)     /**< 64986 - BJM3 */
#define PGN_EXTENDED_JOYSTICK_MESSAGE_3            (0xFDDBUL)     /**< 64987 - EJM1 */
#define PGN_MARINE_CONTROL_INFORMATION             (0xFDDCUL)     /**< 64988 - MCI  */
#define PGN_AMBIENT_CONDITIONS_2                   (0xFDDEUL)     /**< 64992 - AMB2 */
#define PGN_CAB_A_C_CLIMATE_SYST_INFO              (0xFDE1UL)     /**< 64993 - CACI */
#define PGN_SUPPLY_PRESSURE_DEMAND                 (0xFDE2UL)     /**< 64994 - SPR  */
#define PGN_EQUIPM_OPERATION_AND_CONTR             (0xFDE3UL)     /**< 64995 - EOAC */
#define PGN_EQUIPMENT_PERFORMANCE_DATA             (0xFDE4UL)     /**< 64996 - EPD  */
#define PGN_MAX_VEHIC_SPEED_LIMIT_STAT             (0xFDE5UL)     /**< 64997 - MVS  */
#define PGN_HYDRAULIC_BRAKING_SYSTEM               (0xFDE6UL)     /**< 64998 - HBS  */
/* 64999 - 65030 J1939-75, see later */
#define PGN_EXHAUST_TEMPERATURE                    (0xFE07UL)     /**< 65031 - ET   */
/* ISO 11783 - Part 7 */
#define PGN_REQUIRED_TRACTOR_FACILITIES            (0xFE08UL)     /**< 65032 - RTF   */
#define PGN_TRACTOR_FACILITIES_RESPONSE            (0xFE09UL)     /**< 65033 - TFR   */
#define PGN_IMP_REMOTE_CMD_TRACTOR_RESP            (0xFE0AUL)     /**< 65033 - IRCR  */
#define PGN_IMPLEMENT_REMOTE_CONTR_CMD             (0xFE0BUL)     /**< 65035 - IRC   */
#define PGN_WORKING_SET_MEMBER                     (0xFE0CUL)     /**< 65036 - WSMEM */
#define PGN_WORKING_SET_MASTER                     (0xFE0DUL)     /**< 65037 - WSMSTR */
#define PGN_RESP_FOR_REPETITION_RATE               (0xFE0EUL)     /**< 65038 - RESRR */
#define PGN_LANGUAGE_COMMAND                       (0xFE0FUL)     /**< 65039 - LC*/
#define PGN_AUX_VALVE_0_EST_FLOW                   (0xFE10UL)     /**< 65040 - AV00EF */
#define PGN_AUX_VALVE_0_MEAS_FLOW                  (0xFE20UL)     /**< 65056 - AV00MF */
#define PGN_AUX_VALVE_0_COMMAND                    (0xFE30UL)     /**< 65072 - AV00C  */
#define PGN_AUX_VALVE_1_EST_FLOW                   (0xFE11UL)     /**< 65041 - AV01EF */
#define PGN_AUX_VALVE_1_MEAS_FLOW                  (0xFE21UL)     /**< 65057 - AV01MF */
#define PGN_AUX_VALVE_1_COMMAND                    (0xFE31UL)     /**< 65073 - AV01C  */
#define PGN_AUX_VALVE_2_EST_FLOW                   (0xFE12UL)     /**< 65042 - AV02EF */
#define PGN_AUX_VALVE_2_MEAS_FLOW                  (0xFE22UL)     /**< 65058 - AV02MF */
#define PGN_AUX_VALVE_2_COMMAND                    (0xFE32UL)     /**< 65074 - AV02C  */
#define PGN_AUX_VALVE_3_EST_FLOW                   (0xFE13UL)     /**< 65043 - AV03EF */
#define PGN_AUX_VALVE_3_MEAS_FLOW                  (0xFE23UL)     /**< 65059 - AV03MF */
#define PGN_AUX_VALVE_3_COMMAND                    (0xFE33UL)     /**< 65075 - AV03C  */
#define PGN_AUX_VALVE_4_EST_FLOW                   (0xFE14UL)     /**< 65044 - AV04EF */
#define PGN_AUX_VALVE_4_MEAS_FLOW                  (0xFE24UL)     /**< 65060 - AV04MF */
#define PGN_AUX_VALVE_4_COMMAND                    (0xFE34UL)     /**< 65076 - AV04C  */
#define PGN_AUX_VALVE_5_EST_FLOW                   (0xFE15UL)     /**< 65045 - AV05EF */
#define PGN_AUX_VALVE_5_MEAS_FLOW                  (0xFE25UL)     /**< 65061 - AV05MF */
#define PGN_AUX_VALVE_5_COMMAND                    (0xFE35UL)     /**< 65077 - AV05C  */
#define PGN_AUX_VALVE_6_EST_FLOW                   (0xFE16UL)     /**< 65046 - AV06EF */
#define PGN_AUX_VALVE_6_MEAS_FLOW                  (0xFE26UL)     /**< 65062 - AV06MF */
#define PGN_AUX_VALVE_6_COMMAND                    (0xFE36UL)     /**< 65078 - AV06C  */
#define PGN_AUX_VALVE_7_EST_FLOW                   (0xFE17UL)     /**< 65047 - AV07EF */
#define PGN_AUX_VALVE_7_MEAS_FLOW                  (0xFE27UL)     /**< 65063 - AV07MF */
#define PGN_AUX_VALVE_7_COMMAND                    (0xFE37UL)     /**< 65079 - AV07C  */
#define PGN_AUX_VALVE_8_EST_FLOW                   (0xFE18UL)     /**< 65048 - AV08EF */
#define PGN_AUX_VALVE_8_MEAS_FLOW                  (0xFE28UL)     /**< 65064 - AV08MF */
#define PGN_AUX_VALVE_8_COMMAND                    (0xFE38UL)     /**< 65080 - AV08C  */
#define PGN_AUX_VALVE_9_EST_FLOW                   (0xFE19UL)     /**< 65049 - AV09EF */
#define PGN_AUX_VALVE_9_MEAS_FLOW                  (0xFE29UL)     /**< 65065 - AV09MF */
#define PGN_AUX_VALVE_9_COMMAND                    (0xFE39UL)     /**< 65081 - AV09C  */
#define PGN_AUX_VALVE_10_EST_FLOW                  (0xFE1AUL)     /**< 65050 - AV10EF */
#define PGN_AUX_VALVE_10_MEAS_FLOW                 (0xFE2AUL)     /**< 65066 - AV10MF */
#define PGN_AUX_VALVE_10_COMMAND                   (0xFE3AUL)     /**< 65082 - AV10C  */
#define PGN_AUX_VALVE_11_EST_FLOW                  (0xFE1BUL)     /**< 65051 - AV11EF */
#define PGN_AUX_VALVE_11_MEAS_FLOW                 (0xFE2BUL)     /**< 65067 - AV11MF */
#define PGN_AUX_VALVE_11_COMMAND                   (0xFE3BUL)     /**< 65083 - AV11C  */
#define PGN_AUX_VALVE_12_EST_FLOW                  (0xFE1CUL)     /**< 65052 - AV12EF */
#define PGN_AUX_VALVE_12_MEAS_FLOW                 (0xFE2CUL)     /**< 65068 - AV12MF */
#define PGN_AUX_VALVE_12_COMMAND                   (0xFE3CUL)     /**< 65084 - AV12C  */
#define PGN_AUX_VALVE_13_EST_FLOW                  (0xFE1DUL)     /**< 65053 - AV13EF */
#define PGN_AUX_VALVE_13_MEAS_FLOW                 (0xFE2DUL)     /**< 65069 - AV13MF */
#define PGN_AUX_VALVE_13_COMMAND                   (0xFE3DUL)     /**< 65085 - AV13C  */
#define PGN_AUX_VALVE_14_EST_FLOW                  (0xFE1EUL)     /**< 65054 - AV14EF */
#define PGN_AUX_VALVE_14_MEAS_FLOW                 (0xFE2EUL)     /**< 65070 - AV14MF */
#define PGN_AUX_VALVE_14_COMMAND                   (0xFE3EUL)     /**< 65086 - AV14C  */
#define PGN_AUX_VALVE_15_EST_FLOW                  (0xFE1FUL)     /**< 65055 - AV15EF */
#define PGN_AUX_VALVE_15_MEAS_FLOW                 (0xFE2FUL)     /**< 65071 - AV15MF */
#define PGN_AUX_VALVE_15_COMMAND                   (0xFE3FUL)     /**< 65087 - AV15C  */
/* Lighting data and command in J1939 and ISO */
#define PGN_LIGHTING_DATA                          (0xFE40UL)     /**< 65088 - LD    */
#define PGN_LIGHTING_COMMAND                       (0xFE41UL)     /**< 65089 - LC    */
#define PGN_COMMAND_HITCH_PTO                      (0xFE42UL)     /**< 65090 - HPTOC */
#define PGN_REAR_PTO                               (0xFE43UL)     /**< 65091 - RPTO  */
#define PGN_FRONT_PTO                              (0xFE44UL)     /**< 65092 - FPTO  */
#define PGN_REAR_HITCH                             (0xFE45UL)     /**< 65093 - RHS   */
#define PGN_FRONT_HITCH                            (0xFE46UL)     /**< 65094 - FHS   */
#define PGN_MAINTAIN_POWER                         (0xFE47UL)     /**< 65095 - MP    */
#define PGN_WHEEL_BASED_SPEED                      (0xFE48UL)     /**< 65096 - WBSD  */
#define PGN_GROUND_BASED_SPEED                     (0xFE49UL)     /**< 65097 - GBSD  */
/* ISO 11783 - Part 7 - end */
#define PGN_TRANSMISSIONG_CONFIG_2                 (0xFE4BUL)     /**< 65099 - TCFG2 */
#define PGN_MILITARY_LIGHTING_COMMAND              (0xFE4CUL)     /**< 65100 - ML    */
#define PGN_TOTAL_AVERAGED_INFORMATION             (0xFE4DUL)     /**< 65101 - TAVG  */
#define PGN_DOOR_CONTROL                           (0xFE4EUL)     /**< 65102 - DC    */
#define PGN_VEHICLE_DYN_STAB_CTRL_1                (0xFE4FUL)     /**< 61103 - VDC1  */
#define PGN_BATTERY_TEMPERATURE                    (0xFE50UL)     /**< 65104 - BT1   */
#define PGN_ADAPT_CRUISE_CONTR_OPER_INP            (0xFE51UL)     /**< 65105 - ACC2  */
#define PGN_VEHICLE_ELECTRICAL_POWER_3             (0xFE52UL)     /**< 65106 - VP3   */
#define PGN_RETARD_TORQUE_SPEED_LIMIT              (0xFE53UL)     /**< 65107 - RTC1  */
#define PGN_ENGINE_TORQUE_SPEED_LIMIT              (0xFE54UL)     /**< 65108 - ETC1  */
#define PGN_GASEOUS_FUEL_PROPERTIES                (0xFE55UL)     /**< 65109 - GFD   */
#define PGN_TANK_INFORMATION_1                     (0xFE56UL)     /**< 65110 - TI1   */
#define PGN_AIR_SUSPENSION_CONTROL_5               (0xFE57UL)     /**< 65111 - ASC5  */
#define PGN_AIR_SUSPENSION_CONTROL_4               (0xFE58UL)     /**< 65112 - ASC4  */
#define PGN_AIR_SUSPENSION_CONTROL_3               (0xFE59UL)     /**< 65113 - ASC3  */
#define PGN_AIR_SUSPENSION_CONTROL_1               (0xFE5AUL)     /**< 65114 - ASC1  */
#define PGN_FORWARD_LANE_IMAGE                     (0xFE5BUL)     /**< 65115 - FLI2  */
#define PGN_BATTERY_MAIN_SWITCH_INFO               (0xFE66UL)     /**< 65126 - BM    */
#define PGN_CLIMATE_CONTR_CONFIGURATION            (0xFE67UL)     /**< 65127 - CCC   */
#define PGN_VEHICLE_FLUIDS                         (0xFE68UL)     /**< 65128 - VF    */
#define PGN_ENGINE_TEMPERATURE_3                   (0xFE69UL)     /**< 65129 - ET3   */
#define PGN_ENGINE_FUEL_LUBE_SYSTEMS               (0xFE6AUL)     /**< 65130 - EFS   */
#define PGN_DRIVERS_IDENTIFICATION                 (0xFE6BUL)     /**< 65131 - DI    */
#define PGN_TACHOGRAPH                             (0xFE6CUL)     /**< 65132 - TCO1  */
#define PGN_HEATER_INFORMATION                     (0xFE6DUL)     /**< 65133 - HTR   */
#define PGN_HIGH_RESOLUTION_WHEEL_SPEED            (0xFE6EUL)     /**< 65134 - HRW   */
#define PGN_ADAPTIVE_CRUISE_CONTROL                (0xFE6FUL)     /**< 65135 - ACC1  */
#define PGN_COMBINATION_VEHICLE_WEIGHT             (0xFE70UL)     /**< 65136 - CVW   */
#define PGN_LASER_TRACER_POSITION                  (0xFE71UL)     /**< 65137 - LTP   */
#define PGN_LASER_LEVEL_SYS_BLADE_CONTR            (0xFE72UL)     /**< 65138 - LBC   */
#define PGN_LASER_RECEIVER_MAST_POS                (0xFE73UL)     /**< 65139 - LMP   */
#define PGN_MODIFY_LEVEL_CTRL_SET_POINT            (0xFE74UL)     /**< 65140 - LSP   */
#define PGN_LASER_LVL_SYS_VERTIC_DEVIAT            (0xFE75UL)     /**< 65141 - LVD   */
#define PGN_LASER_LVL_SYS_POS_DISP_DATA            (0xFE76UL)     /**< 65142 - LVDD  */
#define PGN_AUXILIARY_PRESSURES                    (0xFE77UL)     /**< 65143 - AP    */
#define PGN_TIRE_PRESS_CONTR_UNIT_STAT             (0xFE78UL)     /**< 65144 - TP1   */
#define PGN_TIRE_PRESS_CTRL_TARGET_PRES            (0xFE79UL)     /**< 65145 - TP2   */
#define PGN_TIRE_PRESS_UNIT_CURR_PRESS             (0xFE7AUL)     /**< 65146 - TP3   */
#define PGN_COMBUSTION_TIME_1                      (0xFE7BUL)     /**< 65147 - CT1   */
#define PGN_COMBUSTION_TIME_2                      (0xFE7CUL)     /**< 65148 - CT2   */
#define PGN_COMBUSTION_TIME_3                      (0xFE7DUL)     /**< 65149 - CT3   */
#define PGN_COMBUSTION_TIME_4                      (0xFE7EUL)     /**< 65150 - CT4   */
#define PGN_COMBUSTION_TIME_5                      (0xFE7FUL)     /**< 65151 - CT5   */
#define PGN_COMBUSTION_TIME_6                      (0xFE80UL)     /**< 65152 - CT6   */
#define PGN_FUEL_INFORMATION_2                     (0xFE81UL)     /**< 65153 - GFI2  */
#define PGN_IGNITION_TIMING_1                      (0xFE82UL)     /**< 65154 - IT1   */
#define PGN_IGNITION_TIMING_2                      (0xFE83UL)     /**< 65155 - IT2   */
#define PGN_IGNITION_TIMING_3                      (0xFE84UL)     /**< 65156 - IT3   */
#define PGN_IGNITION_TIMING_4                      (0xFE85UL)     /**< 65157 - IT4   */
#define PGN_IGNITION_TIMING_5                      (0xFE86UL)     /**< 65158 - IT5   */
#define PGN_IGNITION_TIMING_6                      (0xFE87UL)     /**< 65159 - IT6   */
#define PGN_IGNITION_TRANSF_SECOND_OP1             (0xFE88UL)     /**< 65160 - ISO1  */
#define PGN_IGNITION_TRANSF_SECOND_OP2             (0xFE89UL)     /**< 65161 - ISO2  */
#define PGN_IGNITION_TRANSF_SECOND_OP3             (0xFE8AUL)     /**< 65162 - ISO3  */
#define PGN_GASEOUS_FUEL_PRESSURE                  (0xFE8BUL)     /**< 65163 - GFP   */
#define PGN_AUXILIARY_ANALOG_INFO                  (0xFE8CUL)     /**< 65164 - AAI   */
#define PGN_VEHICLE_ELECTRICAL_POWER_2             (0xFE8DUL)     /**< 65165 - VP2   */
#define PGN_SERVICE_2                              (0xFE8EUL)     /**< 65166 - S2    */
#define PGN_SUPPLY_PRESSURE_2                      (0xFE8FUL)     /**< 65167 - SP2   */
#define PGN_ENGINE_TORQUE_HISTORY                  (0xFE90UL)     /**< 65168 - ETH   */
#define PGN_FUEL_LEAKAGE                           (0xFE91UL)     /**< 65169 - FL    */
#define PGN_ENGINE_INFORMATION                     (0xFE92UL)     /**< 65170 - EI    */
#define PGN_ENGINE_ELECTR_SYST_MOD_INFO            (0xFE93UL)     /**< 65171 - EES   */
#define PGN_ENGINE_AUXILIARY_COOLANT               (0xFE94UL)     /**< 65172 - EAC   */
#define PGN_REBUILD_INFORMATION                    (0xFE95UL)     /**< 65173 - RBI   */
#define PGN_TURBOCHARGER_WASTEGATE                 (0xFE96UL)     /**< 65174 - TCW   */
#define PGN_TURBOCHARGER_INFORMATION_5             (0xFE97UL)     /**< 65175 - TCI5  */
#define PGN_TURBOCHARGER_INFORMATION_4             (0xFE98UL)     /**< 65176 - TCI4  */
#define PGN_TURBOCHARGER_INFORMATION_3             (0xFE99UL)     /**< 65177 - TCI3  */
#define PGN_TURBOCHARGER_INFORMATION_2             (0xFE9AUL)     /**< 65178 - TCI2  */
#define PGN_TURBOCHARGER_INFORMATION_1             (0xFE9BUL)     /**< 65179 - TCI1  */
#define PGN_MAIN_BEARING_TEMPERATURE_3             (0xFE9CUL)     /**< 65180 - MBT3  */
#define PGN_MAIN_BEARING_TEMPERATURE_2             (0xFE9DUL)     /**< 65181 - MBT2  */
#define PGN_MAIN_BEARING_TEMPERATURE_1             (0xFE9EUL)     /**< 65182 - MBT1  */
#define PGN_EXHAUST_PORT_TEMPERATURE_5             (0xFE9FUL)     /**< 65183 - EPT5  */
#define PGN_EXHAUST_PORT_TEMPERATURE_4             (0xFEA0UL)     /**< 65184 - EPT4  */
#define PGN_EXHAUST_PORT_TEMPERATURE_3             (0xFEA1UL)     /**< 65185 - EPT3  */
#define PGN_EXHAUST_PORT_TEMPERATURE_2             (0xFEA2UL)     /**< 65186 - EPT2  */
#define PGN_EXHAUST_PORT_TEMPERATURE_1             (0xFEA3UL)     /**< 65187 - EPT1  */
#define PGN_ENGINE_TEMPERATURE_2                   (0xFEA4UL)     /**< 65188 - ET2   */
#define PGN_INTAKE_MANIFOLD_INFO_2                 (0xFEA5UL)     /**< 65189 - IMT2  */
#define PGN_INTAKE_MANIFOLD_INFO_1                 (0xFEA6UL)     /**< 65190 - IMT1  */
#define PGN_ALTERNATOR_TEMPEATURE                  (0xFEA7UL)     /**< 65191 - AT    */
#define PGN_ARTICULATION_CONTROL                   (0xFEA8UL)     /**< 65192 - AC    */
#define PGN_EXHAUST_OXYGEN_1                       (0xFEA9UL)     /**< 65193 - EO1   */
#define PGN_ALTERNATE_FUEL_2                       (0xFEA6UL)     /**< 65194 - AF2   */
#define PGN_ELECTRONIC_TRANSM_CONTR_6              (0xFEABUL)     /**< 65195 - ETC6  */
#define PGN_WHEEL_BRAKE_LIN_REMAIN_INFO            (0xFEACUL)     /**< 65196 - EBC4  */
#define PGN_WHEEL_APPL_PRESS_HI_RGE_INF            (0xFEADUL)     /**< 65197 - EBC3  */
#define PGN_AIR_SUPPLY_PRESSURE                    (0xFEAEUL)     /**< 65198 - AIR1  */
#define PGN_FUEL_CONSUMPTION_GASEOUS               (0xFEAFUL)     /**< 65199 - GFC   */
#define PGN_TRIP_TIME_INFORMATON_2                 (0xFEB0UL)     /**< 65200 - TTI2  */
#define PGN_ECU_HISTORY                            (0xFEB1UL)     /**< 65201 - EH    */
#define PGN_FUEL_INFORMATION_1_GASEOUS             (0xFEB2UL)     /**< 65202 - GFI1  */
#define PGN_FUEL_INFORMATION_LIQUID                (0xFEB3UL)     /**< 65203 - LFI   */
#define PGN_TRIP_TIME_INFORMATION_1                (0xFEB4UL)     /**< 65204 - TTI1  */
#define PGN_TRIP_SHUTDOWN_INFORMATION              (0xFEB5UL)     /**< 65205 - TSI   */
#define PGN_TRIP_VEHIC_SPEED_DIST_INFO             (0xFEB6UL)     /**< 65206 - TVI   */
#define PGN_ENGINE_SPEED_LOAD_FAC_INFO             (0xFEB7UL)     /**< 65207 - LF    */
#define PGN_TRIP_FUEL_INFO_GASEOUS                 (0xFEB8UL)     /**< 65208 - GTFI  */
#define PGN_TRIP_FUEL_INFO_LIQUID                  (0xFEB9UL)     /**< 65209 - LTFI  */
#define PGN_TRIP_DISTANCE_INFO                     (0xFEBAUL)     /**< 65210 - TDI   */
#define PGN_TRIP_FAN_INFO                          (0xFEBBUL)     /**< 65211 - TFI   */
#define PGN_COMPRES_SERVICE_BRAKE_INFO             (0xFEBCUL)     /**< 65212 - CBI   */
#define PGN_FAN_DRIVE                              (0xFEBDUL)     /**< 65213 - FD    */
#define PGN_ELECTRONIC_ENGIN_CONTROL_4             (0xFEBEUL)     /**< 65214 - EEC4  */
#define PGN_WHEEL_SPEED_INFORMATION                (0xFEBFUL)     /**< 65215 - EBC2  */
#define PGN_SERVICE_INFORMATION                    (0xFEC0UL)     /**< 65216 - SERV  */
#define PGN_HIGH_RESOLUTION_VEHIC_DIST             (0xFEC1UL)     /**< 65217 - VDHR  */
#define PGN_ELEC_RETARDER_CONTROLLER_2             (0xFEC2UL)     /**< 65218 - ERC2  */
#define PGN_ELEC_TRANSMISSION_CONTR_5              (0xFEC3UL)     /**< 65219 - ETC5  */
#define PGN_ELEC_TRANSMISSION_CONTR_4              (0xFEC5UL)     /**< 65221 - ETC4  */
#define PGN_ELEC_TRANSMISSION_CONTR_3              (0xFEC7UL)     /**< 65223 - ETC3  */

/* 65226 - 65236 - J1939-73, see later */
#define PGN_ALTERNATOR_SPEEED                      (0xFED5UL)     /**< 65237 - AS       */
#define PGN_COMMANDED_ADDRESS                      (0xFED8UL)     /**< 65240 - CA       */
#define PGN_AUXIL_INPUT_OUTP_STATUS                (0xFED9UL)     /**< 65241 - AUXIO    */
#define PGN_SOFTWARE_IDENTIFICATION                (0xFEDAUL)     /**< 65242 - ISO11783-12 B.2 */
#define PGN_ENGIN_FLUID_LEV_PRESSURE_2             (0xFEDBUL)     /**< 65243 - EFL_P2   */
#define PGN_IDLE_OPERATION                         (0xFEDCUL)     /**< 65244 - IO       */
#define PGN_TURBOCHARGER                           (0xFEDDUL)     /**< 65245 - TC       */
#define PGN_AIR_START_PRESSURE                     (0xFEDEUL)     /**< 65246 - AIR2     */
#define PGN_ELEC_ENGINE_CONTROLLER_3               (0xFEDFUL)     /**< 65247 - EEC3     */
#define PGN_VEHICLE_DISTANCE                       (0xFEE0UL)     /**< 65248 - VD       */
#define PGN_RETARDER_CONFIGURATION                 (0xFEE1UL)     /**< 65249 - RC       */
#define PGN_TRANSMISSION_CONFIGURATION             (0xFEE2UL)     /**< 65250 - TCFG     */
#define PGN_ENGINE_CONFIGURATION                   (0xFEE3UL)     /**< 65251 - EC       */
#define PGN_SHUTDOWN                               (0xFEE4UL)     /**< 65252 - SHUTDOWN */
#define PGN_ENGINE_HOURS_REVOLUTIONS               (0xFEE5UL)     /**< 65253 - HOURS    */
#define PGN_TIME_DATA                              (0xFEE6UL)     /**< 65254 - TD       */
#define PGN_VEHICLE_HOURS                          (0xFEE7UL)     /**< 65255 - VH       */
#define PGN_VEHICLE_DIRECTION_SPEED                (0xFEE8UL)     /**< 65256 - VDS      */
#define PGN_FUEL_CONSUMPTION_LIQUID                (0xFEE9UL)     /**< 65257 - LFC      */
#define PGN_VEHICLE_WEIGHT                         (0xFEEAUL)     /**< 65258 - VW       */
#define PGN_COMPONENT_IDENTIFICATION               (0xFEEBUL)     /**< 65259 - CI       */
#define PGN_VEHICLE_IDENTIFICATION                 (0xFEECUL)     /**< 65260 - VI       */
#define PGN_CRUIS_CTR_VEHIC_SPEED_SETUP            (0xFEEDUL)     /**< 65261 - CCSS     */
#define PGN_ENGINE_TEMPERATURE_1                   (0xFEEEUL)     /**< 65262 - ET1      */
#define PGN_ENGINE_FLUID_LEVEL_PRESS_1             (0xFEEFUL)     /**< 65263 - EFL_P1   */
#define PGN_POWER_TAKEOFF_INFORMATION              (0xFEF0UL)     /**< 65264 - PTO      */
#define PGN_CRUISE_CONTROL_VEHIC_SPEED             (0xFEF1UL)     /**< 65265 - CCVS     */
#define PGN_FUEL_ECONOMY_LIQUID                    (0xFEF2UL)     /**< 65266 - LFE      */
#define PGN_VEHICLE_POSITION                       (0xFEF3UL)     /**< 65267 - VP       */
#define PGN_TIRE_CONDITION                         (0xFEF4UL)     /**< 65268 - TIRE     */
#define PGN_AMBIENT_CONDITIONS                     (0xFEF5UL)     /**< 65269 - AMB      */
#define PGN_INLET_EXHAUST_CONDITIONS_1             (0xFEF6UL)     /**< 65270 - IC1      */
#define PGN_VEHICLE_ELECTRICAL_POWER               (0xFEF7UL)     /**< 65271 - VEP1     */
#define PGN_TRANSMISSION_FLUIDS                    (0xFEF8UL)     /**< 65272 - TF       */
#define PGN_AXLE_INFORMATION                       (0xFEF9UL)     /**< 65273 - AI       */
#define PGN_BRAKES                                 (0xFEFAUL)     /**< 65274 - B        */
#define PGN_RETARDER_FLUIDS                        (0xFEFBUL)     /**< 65275 - RF       */
#define PGN_DASH_DISPLAY                           (0xFEFCUL)     /**< 65276 - DD       */
#define PGN_ALTERNATE_FUEL_1                       (0xFEFDUL)     /**< 65277 - A1     */
#define PGN_AUXIL_WATER_PUMP_PRESS                 (0xFEFEUL)     /**< 65278 - AWPP   */
#define PGN_WATER_IN_FUEL_INDICATOR                (0xFEFFUL)     /**< 65279 - WFI    */

/* J1939-73 / 11783-12, B.x - Application layer - Diagnostics */
#define PGN_ACTIVE_DIAG_TROUBLE_CODES              (0xFECAUL)     /**< 65226 - DM1    */
#define PGN_PREV_ACTIV_DIAG_TROUBLE_COD            (0xFECBUL)     /**< 65227 - DM2    */
#define PGN_DIAGNOSTIC_DATA_CLEAR                  (0xFECCUL)     /**< 65228 - DM3    */
#define PGN_FREEZE_FRAME_PARAMETERS                (0xFECDUL)     /**< 65229 - DM4    */
#define PGN_DIAGNOSTIC_READINESS                   (0xFECEUL)     /**< 65230 - DM5    */
#define PGN_CONTIN_MONI_SYST_TEST_RESUL            (0xFECFUL)     /**< 65231 - DM6    */
#define PGN_TEST_RESUL_NON_CONT_MONITOR            (0xFED0UL)     /**< 65232 - DM8    */
#define PGN_NON_CONTIN_MONITOR_SYS_TEST            (0xFED2UL)     /**< 65234 - DM10   */
#define PGN_DIAG_DATA_CLEAR_ACTIV_DTC              (0xFED3UL)     /**< 65235 - DM11   */
#define PGN_EMISS_RELAT_ACT_DIAG_TROUB             (0xFED4UL)     /**< 65236 - DM12   */

/* J1939-75 - Application layer - Generator Sets and Industrial */
#define PGN_BUS_1_UTIL_SYNC_CHECK_STATU            (0xFDE7UL)     /**< 64999 - BUSC   */
#define PGN_BUS_1_GENERA_SYNC_CH_STAT              (0xFDE8UL)     /**< 65000 - BGSC   */
#define PGN_BUS_1_PHASE_C_BASIC_AC_QUAN            (0xFDE9UL)     /**< 65001 - BPCAC  */
#define PGN_BUS_1_PHASE_B_BASIC_AC_QUAN            (0xFDEAUL)     /**< 65002 - BPBAC  */
#define PGN_BUS_1_PHASE_A_BASIC_AC_QUAN            (0xFDEBUL)     /**< 65003 - BPAAC  */
#define PGN_BUS_1_AVERAGE_BASIC_AC_QUAN            (0xFDECUL)     /**< 65004 - BAAC   */
#define PGN_UTIL_TOTAL_AC_ENERGY                   (0xFDEDUL)     /**< 65005 - UTACE  */
#define PGN_UTIL_PHASE_C_AC_REACT_POWER            (0xFDEEUL)     /**< 65006 - UPCACR */
#define PGN_UTIL_PHASE_C_AC_POWER                  (0xFDEFUL)     /**< 65007 - UPCACP */
#define PGN_UTIL_PHASE_C_AC_BASIC_QUANT            (0xFDF0UL)     /**< 65008 - UPCAC  */
#define PGN_UTIL_PHASE_B_AC_REACT_POWER            (0xFDF1UL)     /**< 65009 - UPBACR */
#define PGN_UTIL_PHASE_B_AC_POWER                  (0xFDF2UL)     /**< 65010 - UPBACP */
#define PGN_UTIL_PHASE_B_AC_BASIC_QUANT            (0xFDF3UL)     /**< 65011 - UPBAC  */
#define PGN_UTIL_PHASE_A_AC_REACT_POWER            (0xFDF4UL)     /**< 65012 - UPAACR */
#define PGN_UTIL_PHASE_A_AC_POWER                  (0xFDF5UL)     /**< 65013 - UPAACP */
#define PGN_UTIL_PHASE_A_AC_BASIC_QUANT            (0xFDF6UL)     /**< 65014 - UPAAC  */
#define PGN_UTIL_AC_REACTIVE_POWER                 (0xFDF7UL)     /**< 65015 - UTACR  */
#define PGN_UTIL_TOTAL_AC_POWER                    (0xFDF8UL)     /**< 65016 - UTACP  */
#define PGN_UTIL_AVERACE_BASIC_AC_QUANT            (0xFDF9UL)     /**< 65017 - UAAC   */
#define PGN_GENERATOR_TOTAL_AC_ENERGY              (0xFDFAUL)     /**< 65018 - GTACE  */
#define PGN_GENERA_PHAS_C_AC_REACT_PWR             (0xFDFBUL)     /**< 65019 - GPCACR */
#define PGN_GENERATOR_PHASE_C_AC_POWER             (0xFDFCUL)     /**< 65020 - GPCACP */
#define PGN_GENERA_PHASE_C_BAS_AC_QUANT            (0xFDFDUL)     /**< 65021 - GPCAC  */
#define PGN_GENERA_PHASE_B_AC_REACT_PWR            (0xFDFEUL)     /**< 65022 - GPBACR */
#define PGN_GENERATOR_PHASE_B_AC_POWER             (0xFDFFUL)     /**< 65023 - GPBACP */
#define PGN_GENERA_PHASE_B_BAS_AC_QUANT            (0xFE00UL)     /**< 65024 - GPBAC  */
#define PGN_GENERA_PHASE_A_AC_REACT_PWR            (0xFE01UL)     /**< 65025 - GPAACR */
#define PGN_GENERATOR_PHASE_A_AC_POWER             (0xFE02UL)     /**< 65026 - GPAACP */
#define PGN_GENERA_PHASE_A_BAS_AC_QUANT            (0xFE03UL)     /**< 65027 - GPAAC  */
#define PGN_GENERA_TOTAL_AC_REACT_POWER            (0xFE04UL)     /**< 65028 - GTACR  */
#define PGN_GENERATOR_TOTAL_AC_POWER               (0xFE05UL)     /**< 65029 - GTACP  */
#define PGN_GENERA_TOTAL_BAS_AC_QUANTI             (0xFE06UL)     /**< 65030 - GAAC   */

/* NMEA */
#define PGN_NMEA_REQCMDACKGROUPFUNCION             (0x1ED00UL)    /**< 126208 - SF NO */
#define PGN_PGNLIST_GROUPFUNCTION                  (0x1EE00UL)    /**< 126464 - SF NO */
#define PGN_SYTEMTIME                              (0x1F010UL)    /**< 126992 - SF YES */
#define PGN_PRODUKTINFORMATION                     (0x1F014UL)    /**< 126996 - SF NO */
#define PGN_CONFIGURATIONINFORMATION               (0x1F016UL)    /**< 126998 - SF NO */
#define PGN_HEADING_TRACKCONTROL                   (0x1F105UL)    /**< 127237 - SF NO */
#define PGN_RUDDER                                 (0x1F10DUL)    /**< 127245 - SF YES */
#define PGN_VESSEL_HEADING                         (0x1F112UL)    /**< 127250 - SF YES */
#define PGN_RATE_OF_TURN                           (0x1F113UL)    /**< 127251 - SF YES */
#define PGN_ATTITUDE                               (0x1F119UL)    /**< 127257 - SF YES */
#define PGN_MAGNETIC_VARIATION                     (0x1F11AUL)    /**< 127258 - SF YES */
#define PGN_ENGINE_PARA_RAPID_UPDATE               (0x1F200UL)    /**< 127488 - SF YES */
#define PGN_ENGINE_PARA_DYNAMIC                    (0x1F201UL)    /**< 127489 - SF NO */
#define PGN_TRANSMISSION_PARA_DYNAMIC              (0x1F205UL)    /**< 127493 - SF YES */
#define PGN_TRIP_PARAMETERS_VESSEL                 (0x1F208UL)    /**< 127496 - SF NO */
#define PGN_TRIP_PARAMETERS_ENGINE                 (0x1F209UL)    /**< 127497 - SF NO */
#define PGN_ENGINE_PARAMETERS_STATIC               (0x1F20AUL)    /**< 127498 - SF NO */
#define PGN_BINARY_SWITCH_BANK_STATUS              (0x1F20DUL)    /**< 127501 - SF YES */
#define PGN_SWITCH_BANK_CONTROL                    (0x1F20EUL)    /**< 127502 - SF YES */
#define PGN_AC_INPUT_STATUS                        (0x1F20FUL)    /**< 127503 - SF NO */
#define PGN_AC_OUTPUT_STATUS                       (0x1F210UL)    /**< 127504 - SF NO */
#define PGN_FLUID_LEVEL                            (0x1F211UL)    /**< 127505 - SF YES */
#define PGN_DCDETAILED_STATUS                      (0x1F212UL)    /**< 127506 - SF NO */
#define PGN_CHARGER_STATUS                         (0x1F213UL)    /**< 127507 - SF NO */
#define PGN_BATTERY_STATUS                         (0x1F214UL)    /**< 127508 - SF YES */
#define PGN_INVERTER_STATUS                        (0x1F215UL)    /**< 127509 - SF NO */
#define PGN_CHARGER_CONFIG_STATUS                  (0x1F216UL)    /**< 127510 - SF NO */
#define PGN_INVERTER_CONFIG_STATUS                 (0x1F217UL)    /**< 127511 - SF NO */
#define PGN_AGS_CONFIG_STATUS                      (0x1F218UL)    /**< 127512 - SF NO */
#define PGN_BATTERY_CONFIG_STATUS                  (0x1F219UL)    /**< 127513 - SF NO */
#define PGN_AGS_STATUS                             (0x1F21AUL)    /**< 127514 - SF NO */
#define PGN_SPEED_WATERREF                         (0x1F503UL)    /**< 128259 - SF YES */
#define PGN_WATER_DEPTH                            (0x1F216UL)    /**< 127510 - SF YES */
#define PGN_DISTANCED_LOG                          (0x1F513UL)    /**< 128275 - SF NO */
#define PGN_TRACKED_TARGET_DATA                    (0x1F608UL)    /**< 128520 - SF NO */
#define PGN_POSITION_RAPID_UPDATE                  (0x1F801UL)    /**< 129025 - SF YES */
#define PGN_COG_SOG_RAPID_UPDATE                   (0x1F802UL)    /**< 129026 - SF YES */
#define PGN_POSITION_DELTA_HP_RAPID_UPD            (0x1F803UL)    /**< 129027 - SF YES */
#define PGN_ALTITUDE_DELTA_HP_RAPID_UPD            (0x1F804UL)    /**< 129028 - SF YES */
#define PGN_GNSS_POSITION_DATA                     (0x1F805UL)    /**< 129029 - SF NO */
#define PGN_NMEA_TIME_DATE                         (0x1F809UL)    /**< 129033 - SF YES */
#define PGN_AIS_CLASSA_POSITION_REPORT             (0x1F80EUL)    /**< 129038 - SF NO */
#define PGN_AIS_CLASSB_POSITION_REPORT             (0x1F80FUL)    /**< 129039 - SF NO */
#define PGN_AIS_CLASSB_EXTPOS_REPORT               (0x1F810UL)    /**< 129040 - SF NO */
#define PGN_DATUM                                  (0x1F814UL)    /**< 129044 - SF NO */
#define PGN_USER_DATUM_SETTINGS                    (0x1F815UL)    /**< 129045 - SF NO */
#define PGN_CROSS_TRACK_ERROR                      (0x1F903UL)    /**< 129283 - SF YES */
#define PGN_NAVIGATION_DATA                        (0x1F904UL)    /**< 129284 - SF NO */
#define PGN_NAVIGATION_ROUTEWP_INFO                (0x1F905UL)    /**< 129285 - SF NO */
#define PGN_SET_DRIFT_RAPID_UPDATE                 (0x1F90BUL)    /**< 129291 - SF YES */
#define PGN_TIME_TOFROM_MARK                       (0x1F915UL)    /**< 129301 - SF NO */
#define PGN_BEARING_DIST_BET_TWO_MARKS             (0x1F916UL)    /**< 129302 - SF NO */
#define PGN_GNSS_CONTROL_STATUS                    (0x1FA02UL)    /**< 129538 - SF NO */
#define PGN_GNSS_DOPS                              (0x1FA03UL)    /**< 129539 - SF YES */
#define PGN_GNSS_SATS_IN_VIEW                      (0x1FA04UL)    /**< 129540 - SF NO */
#define PGN_ALMANAC_DATA                           (0x1FA05UL)    /**< 129541 - SF NO */
#define PGN_GNSS_PSEUDOOR_NOISE_STATIST            (0x1FA06UL)    /**< 129542 - SF NO */
#define PGN_GNSS_RAIM_OUTPUT                       (0x1FA09UL)    /**< 129545 - SF NO */
#define PGN_GNSS_RAIM_SETTINGS                     (0x1FA0AUL)    /**< 129546 - SF YES */
#define PGN_GNSS_PSEUDOOR_ERROR_STATIST            (0x1FA0BUL)    /**< 129547 - SF NO */
#define PGN_DGNSS_CORRECTIONS                      (0x1FA0DUL)    /**< 129549 - SF NO */
#define PGN_GNSS_DIFF_CORR_RECEI_INTERF            (0x1FA0EUL)    /**< 129550 - SF YES */
#define PGN_GNSS_DIFF_CORR_RECEIVE_SIGN            (0x1FA0FUL)    /**< 129551 - SF NO */
#define PGN_GLONASS_ALMANAC_DATA                   (0x1FA14UL)    /**< 129556 - SF NO */
/* AIS  */
#define PGN_AIS_DGNSS_BROADC_BIN_MESSAG            (0x1FB00UL)    /**< 129792 - SF NO */
#define PGN_AIS_UTC_AND_DATE_REPORT                (0x1FB01UL)    /**< 129793 - SF NO */
#define PGN_AIS_CLASS_A_STAT_VOYAGE_DAT            (0x1FB02UL)    /**< 129794 - SF NO */
#define PGN_AIS_ADDRESSED_BINARY_MESSAG            (0x1FB03UL)    /**< 129795 - SF NO */
#define PGN_AIS_ACKNOWLEDGE                        (0x1FB04UL)    /**< 129796 - SF NO */
#define PGN_AIS_BINARY_BROADCAST_MESSAG            (0x1FB05UL)    /**< 129797 - SF NO */
#define PGN_AIS_SAR_AIRCRAFT_POS_REPORT            (0x1FB06UL)    /**< 129798 - SF NO */
#define PGN_RADIO_FREQUENCY_MODE_POWER             (0x1FB07UL)    /**< 129799 - SF NO */
#define PGN_AIS_UTC_DATE_INQUIRY                   (0x1FB08UL)    /**< 129800 - SF NO */
#define PGN_AIS_ADDRESS_SAFE_REL_MESSAG            (0x1FB09UL)    /**< 129801 - SF NO */
#define PGN_AIS_SAFE_RELD_BROADC_MESSAG            (0x1FB0AUL)    /**< 129802 - SF NO */
#define PGN_AIS_INTERROGATION                      (0x1FB0BUL)    /**< 129803 - SF NO */
#define PGN_AIS_ASSIGNMENT_MODE_COMMAND            (0x1FB0CUL)    /**< 129804 - SF NO */
#define PGN_DSC_CALL_INFORMATION                   (0x1FB10UL)    /**< 129808 - SF NO */
#define PGN_LORAN_C_TD_DATA                        (0x1FC04UL)    /**< 130052 - SF NO */
#define PGN_LORAN_C_RANGE_DATA                     (0x1FC05UL)    /**< 130053 - SF NO */
#define PGN_LORAN_C_SIGNAL_DATA                    (0x1FC06UL)    /**< 130054 - SF NO */
#define PGN_ROUTE_WP_SERVICE_DB_LIST               (0x1FC10UL)    /**< 130064 - SF NO */
#define PGN_ROUTE_WP_SERVICE_ROUTE_LIST            (0x1FC11UL)    /**< 130065 - SF NO */
#define PGN_ROUTE_WP_SERVICE_WP_ATTRIB             (0x1FC12UL)    /**< 130066 - SF NO */
#define PGN_ROUTE_WP_SERVICE_WP_NAM_POS            (0x1FC13UL)    /**< 130067 - SF NO */
#define PGN_ROUTE_WP_SERVICE_QP_NAME               (0x1FC14UL)    /**< 130068 - SF NO */
#define PGN_ROUTE_WP_SERVICE_XTE_LIMIT             (0x1FC15UL)    /**< 130069 - SF NO */
#define PGN_ROUTE_WP_SERVICE_WP_COMMENT            (0x1FC16UL)    /**< 130070 - SF NO */
#define PGN_ROUTE_WP_SERVICE_ROUTE_COM             (0x1FC17UL)    /**< 130071 - SF NO */
#define PGN_ROUTE_WP_SERVICE_DB_COMMENT            (0x1FC18UL)    /**< 130072 - SF NO */
#define PGN_ROUTE_WP_SERVICE_RADIU_TURN            (0x1FC19UL)    /**< 130073 - SF NO */
#define PGN_ROUTE_WP_SERVICE_WP_LIS_NAM            (0x1FC1AUL)    /**< 130074 - SF NO */
#define PGN_WIND_DATA                              (0x1FD02UL)    /**< 130306 - SF YES */
#define PGN_ENVIRONMENT_PARAMETERS                 (0x1FD06UL)    /**< 130310 - SF YES */
#define PGN_ENVIRONMENT_PARAMETERS_2               (0x1FD07UL)    /**< 130311 - SF YES */
#define PGN_TEMPERATURE                            (0x1FD08UL)    /**< 130312 - SF YES */
#define PGN_HUMIDITY                               (0x1FD09UL)    /**< 130313 - SF YES */
#define PGN_ACTUAL_PRESSURE                        (0x1FD0AUL)    /**< 130314 - SF YES */
#define PGN_SET_PRESSURE                           (0x1FD0BUL)    /**< 130315 - SF YES */
#define PGN_TIDE_STATION_DATA                      (0x1FD10UL)    /**< 130320 - SF NO */
#define PGN_SALINITY_STATION_DATA                  (0x1FD11UL)    /**< 130321 - SF NO */
#define PGN_CURRENT_STATION_DATA                   (0x1FD12UL)    /**< 130322 - SF NO */
#define PGN_METEOROLOGICAL_STATION_DATA            (0x1FD13UL)    /**< 130323 - SF NO */
#define PGN_MOORED_BUOY_STATION_DATA               (0x1FD14UL)    /**< 130324 - SF NO */
#define PGN_SMALL_CRAFT_STATUS                     (0x1FE10UL)    /**< 130576 - SF YES */
#define PGN_DIRECTION_DATA                         (0x1FE11UL)    /**< 130577 - SF NO */
#define PGN_VESSEL_SPEED_COMPONENTS                (0x1FE12UL)    /**< 130578 - SF NO */

/** @} */ /* END isopgns */


/* ************************************************************************ */
/** \addtogroup isospns
*/
/**@{*/

#ifndef NO_SPN_DEFINES  /* use the SPN defines of the ECU Driver */

/* ************************************************************************ */
/* SPN DEFINES for ISO11783-8 */

/* Off-Highway Engine Control Selection (to Engine) */
    #define SPN_ALTERNATE_LOW_IDLE_SWITCH       (2883UL)
    /* iso_SpnDefineSpn( x, SPN_ALTERNATE_LOW_IDLE_SWITCH , 1u, 5u, 2u, SpnValStandard ); */

/* Torque/Speed Control (to Engine) */
    #define SPN_OVERRIDE_CONTROL_MODE            (695UL) /**< \brief Part 8 App B */
    #define SPN_ENGINE_REQU_SPEED_CONTR_CON      (696UL)
    #define SPN_OVERRIDE_CONTR_MODE_PRIORIT      (897UL)
    #define SPN_ENGINE_REQU_SPEED_LIMIT          (898UL)
    #define SPN_ENGINE_REQU_TORQUE_LIMIT         (518UL)
    /* iso_SpnDefineSpn( x, SPN_OVERRIDE_CONTROL_MODE, 1u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_REQU_SPEED_CONTR_CON, 1u, 3u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_OVERRIDE_CONTR_MODE_PRIORIT  , 1u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_REQU_SPEED_LIMIT , 2u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_REQU_TORQUE_LIMIT , 4u, 1u, 8u, SpnValStandard ); */

/* Electronic Engine Controller */
    #define SPN_ENGINE_TORQUE_MODE               (899UL) /**< \brief Part 8 App B */
    #define SPN_DRIVERS_DEMAND_ENGINE            (512UL)
    #define SPN_ACTUAL_ENGINETORQUE              (513UL)
    #define SPN_ENGINESPEED                      (190UL)
    #define SPN_SOURCE_ADDRESS_CONTR_DEVICE     (1483UL)
    #define SPN_ENGINE_DEMAND                   (2432UL)
    /* iso_SpnDefineSpn( x, SPN_ENGINE_TORQUE_MODE, 1u, 1u, 4u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_DRIVERS_DEMAND_ENGINE, 2u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ACTUAL_ENGINETORQUE, 3u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINESPEED, 4u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SOURCE_ADDRESS_CONTR_DEVICE, 6u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_DEMAND, 8u, 1u, 8u, SpnValStandard ); */

/* Engine Configuration */
    #define SPN_ENGINE_SPEED_AT_IDLE_POINT1      (188UL) /**< \brief Part 8 App B */
    #define SPN_ENGINE_PERCENT_TORQUE_POIN1      (539UL)
    #define SPN_ENGINE_SPEED_AT_POINT2      	    (528UL)
    #define SPN_ENGINE_PERCENT_TORQUE_POIN2      (540UL)
    #define SPN_ENGINE_SPEED_AT_POINT3           (529UL)
    #define SPN_ENGINE_PERCENT_TORQUE_POIN3      (541UL)
    #define SPN_ENGINE_SPEED_AT_POINT4   	  	    (530UL)
    #define SPN_ENGINE_PERCENT_TORQUE_POIN4      (542UL)
    #define SPN_ENGINE_SPEED_AT_POINT5   	  	    (531UL)
    #define SPN_ENGINE_PERCENT_TORQUE_POIN5      (543UL)
    #define SPN_ENGINE_SPEED_HIGH_POINT6         (532UL)
    #define SPN_ENGINE_REFERENCE_TORQUE       	 (544UL)
    #define SPN_ENGINE_MAX_MOMENT_OV_SPEED       (533UL)
    #define SPN_ENGINE_MAX_OVER_TIME_LIMIT       (534UL)
    #define SPN_ENGINE_MOMENT_INERTIA           (1794UL)
    /* iso_SpnDefineSpn( x, SPN_ENGINE_SPEED_AT_IDLE_POINT1, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_PERCENT_TORQUE_POIN1, 3u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_SPEED_AT_POINT2, 4u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_PERCENT_TORQUE_POIN2, 6u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_SPEED_AT_POINT3, 7u, 1u, 16, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_PERCENT_TORQUE_POIN3, 9u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_SPEED_AT_POINT4, 10u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_PERCENT_TORQUE_POIN4, 12u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_SPEED_AT_POINT5, 13u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_PERCENT_TORQUE_POIN5, 15u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_SPEED_HIGH_POINT6, 16u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_REFERENCE_TORQUE, 20u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_MAX_MOMENT_OV_SPEED, 22u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_MAX_OVER_TIME_LIMIT, 24u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_MOMENT_INERTIA, 31u, 1u, 16u, SpnValStandard ); */

/* Engine Hours */
    #define SPN_ENGINE_TOTAL_HOURS               (247UL) /**< \brief Part 8 App B */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_TOTAL_HOURS, 1u, 1u, 32u, SpnValStandard ); */

/* Fuel Consumption */
    #define SPN_ENGINE_TRIP_FLUEL                (182UL) /**< \brief Part 8 App B */
    #define SPN_ENGINE_TOTAL_FLUEL_USED          (250UL)
    /* iso_SpnDefineSpn( x, SPN_ENGINE_TRIP_FLUEL, 1u, 1u, 32u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TOTAL_FLUEL_USE, 5u, 1u, 32u, SpnValStandard ); */

/* Engine temperature ET1 - PGN_ENGINE_TEMPERATURE_1 */
    #define SPN_ENGINE_COOLANT_TEMPERATURE       (110UL)
    #define SPN_ENGINE_FUEL_TEMPERATURE          (174UL)
    #define SPN_ENGINE_OIL_TEMPERATURE           (175UL)
    /* iso_SpnDefineSpn( x, SPN_ENGINE_COOLANT_TEMPERATURE, 1u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FUEL_TEMPERATURE, 2u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_OIL_TEMPERATURE, 3u, 1u, 16u, SpnValStandard ); */

/* Engine Fluid Level */
    #define SPN_ENGINE_OIL_LEVEL                  (98UL)
    #define SPN_ENGINE_OIL_PRESSURE              (100UL)
    #define SPN_ENGINE_COOLANT_LEVEL             (111UL)
    /* iso_SpnDefineSpn( x, SPN_ENGINE_OIL_LEVEL, 3u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_OIL_PRESSURE, 4u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_ENGINE_COOLANT_LEVEL, 7u, 1u, 8u, SpnValStandard ); */

/* Fuel Economy Liquid */
   #define SPN_ENGINE_FUEL_RATE                (183UL)
   #define SPN_ENGINE_INSTANT_FUEL_ECONOMY     (184UL)
   #define SPN_ENGINE_AVERAGE_FUEL_ECONOMY     (185UL)
   #define SPN_ENGINE_THROTTLE_POSITION        (51UL)
   #define SPN_ENGINE_THROTTLE_2_POSITON       (3673UL)
   /* iso_SpnDefineSpn( x, SPN_ENGINE_FUEL_RATE, 1u, 1u, 16u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_ENGINE_INSTANTANEOUS_FUEL_ECO, 3u, 1u, 16u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_ENGINE_AVERAGE_FUEL_ECONOMY, 5u, 1u, 16u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_ENGINE_THROTTLE_POSITION, 7u, 1u, 8u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_ENGINE_THROTTLE_2_POSITON, 8u, 1u, 8u, SpnValStandard ); */

/* Inlet/Exhaust Conditions */
    #define SPN_ENGINTAKEMANI_1PRESSURE          (102UL)
    #define SPN_ENGINTAKEMANI_1TEMPERATURE       (105UL)
   /* iso_SpnDefineSpn( x, SPN_ENGINTAKEMANI_1PRESSURE, 2u, 1u, 8u, SpnValStandard ); */
	/* iso_SpnDefineSpn( x, SPN_ENGINTAKEMANI_1TEMPERATURE, 3u, 1u, 8u, SpnValStandard ); */

/* Vehicle Electrical Power */
    #define SPN_BATTERY_POTENTIAL                (168UL)
    #define SPN_KEYSWITCH_BATTERY_POTENTIAL      (158UL)
   /* iso_SpnDefineSpn( x, SPN_BATTERY_POTENTIAL, 5u, 1u, 16u, SpnValStandard ); */
	/* iso_SpnDefineSpn( x, SPN_KEYSWITCH_BATTERY_POTENTIAL, 7u, 1u, 16u, SpnValStandard ); */

/* Electronic engine controller 2 */
    #define SPN_ENGINELOAD                        (92UL)  /**< Part 8 App B */
    /* iso_SpnDefineSpn( x, SPN_ENGINELOAD, 3u, 1u, 8u, SpnValStandard ); */

/* Dash Display */
    #define SPN_FUELLEVEL1                        (96UL)  /**< Part 8 App B */
    /* iso_SpnDefineSpn( x, SPN_FUELLEVEL1, 2u, 1u, 8u, SpnValStandard ); */

/* Engine Hours, Revolutions */
    #define SPN_ENGINEHOURS                      (247UL)  /**< Part 8 App B */
    /* iso_SpnDefineSpn( x, SPN_ENGINEHOURS, 1u, 1u, 32u, SpnValStandard ); */

/* Electronic engine controller 2 */
    #define SPN_TRANSMISSION_CURRENTGEAR         (523UL)  /**< Part 8 App B */
    /* iso_SpnDefineSpn( x, SPN_TRANSMISSION_CURRENTGEAR, 4u, 1u, 8u, SpnValStandard ); */

/* Aftertreatment 1 SCR Reagent Tank 1 Information */
    #define SPN_SCR_CATALYST_TANKLEVEL          (1761UL)  /**< Part 8 App B */
    /* iso_SpnDefineSpn( x, SPN_SCR_CATALYST_TANKLEVEL, 1u, 1u, 8u, SpnValStandard ); */

/* Auxiliary I/O #22 */
    #define SPN_AUX_IO_22                       (3845UL)  /**< \brief J1939-71 */
    /* iso_SpnDefineSpn( x, SPN_AUX_IO_22, 2u, 5u, 2u, SpnValStandard ); */

/* ************************************************************************ */
/* SPN DEFINES for ISO11783-7 */
/* All implements stop operations switch state (0xFD02) */
    #define SPN_ALLIMPL_STOPOPERATIONS          (5140UL)  /**< \brief Part 7 A.25.3 */
    #define SPN_ALLIMPL_STOPOPERATIONS_TRNR     (7443UL)  /**< \brief Part 7 A.25.4 */

/* Ground-based speed and distance */
    #define SPN_GROUNDBASEDMACHINESPEED         (1859UL)  /**< \brief Part 7 A.5  */   
    #define SPN_GROUNDBASEDMACHINEDISTANCE      (1860UL)  /**< \brief Part 7 A.6  */
    #define SPN_GROUNDBASEDMACHINEDIRECT        (1861UL)  /**< \brief Part 7 A.7 */
    /* iso_SpnDefineSpn( x, SPN_GROUNDBASEDMACHINESPEED, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_GROUNDBASEDMACHINEDISTANCE, 3u, 1u, 32u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_GROUNDBASEDMACHINEDIRECT, 8u, 1u, 2u, SpnValStandard ); */ 

/* Wheel-based speed and distance */
    #define SPN_WHEELBASEDMACHINESPEED          (1862UL)  /**< \brief Part 7 A.8  */
    #define SPN_WHEELBASEDMACHINEDISTANCE       (1863UL)  /**< \brief Part 7 A.9  */
    #define SPN_WHEELBASEDMACHINEDIRECTION      (1864UL)  /**< \brief Part 7 A.10 */
    #define SPN_KEYSWITCHSTATE                  (1865UL)  /**< \brief Part 7 A.11 */
    #define SPN_MAXI_TIMEOFTRACPOWER            (1866UL)  /**< \brief Part 7 A.12 */
    #define SPN_OPERATOR_DIREC_REVERSED         (5244UL)
    #define SPN_START_STOP_STATE                (5203UL)
    /* iso_SpnDefineSpn( x, SPN_WHEELBASEDMACHINESPEED, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_WHEELBASEDMACHINEDISTANCE, 3u, 1u, 32u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_WHEELBASEDMACHINEDIRECTION, 8u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_KEYSWITCHSTATE, 8u, 3u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_MAXI_TIMEOFTRACPOWER, 7u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_OPERATOR_DIREC_REVERSED, 8u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_START_STOP_STATE, 8u, 5u, 8u, SpnValStandard ); */

/* Machine selected speed */
    #define SPN_SELECTEDMACHINESPEED		      (4305UL)  /**< \brief Part 7 A.30.1  */
    #define SPN_SELECTEDMACHINEDISTANCE           (4306UL)  /**< \brief Part 7 A.30.2  */
    #define SPN_SELECTEDMACHINELIMITSTATUS        (4307UL)  /**< \brief Part 7 A.30.8  */
    #define SPN_SELECTEDMACHINESOURCE             (4308UL)  /**< \brief Part 7 A.30.4  */
    #define SPN_SELECTEDMACHINEDIRECTION	      (4309UL)  /**< \brief Part 7 A.30.3  */
    #define SPN_SELECTEDMACHINE_EXIT_REASON_CODE  (5818UL)  /**< \brief Part 7 A.30.9  */
    /* iso_SpnDefineSpn( x, SPN_SELECTEDMACHINESPEED, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SELECTEDMACHINEDISTANCE, 3u, 1u, 32u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SELECTEDMACHINE_EXIT_REASON_CODE, 7u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SELECTEDTMACHINEDIRECTION, 8u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SELECTEDMACHINESOURCE, 8u, 3u, 3u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SELECTEDMACHINELIMITSTATUS, 8u, 6u, 3u, SpnValStandard ); */

/* Machine selected speed command */
    #define SPN_SELECTED_SPEED_SETPOINT_CMD         (4310UL)
    #define SPN_SELECTED_SPEED_SETPOINT_LIMIT_CMD   (4311UL)
    #define SPN_SELECTED_DIRECTION_CMD              (4312UL)
    /* iso_SpnDefineSpn( x, SPN_SELECTED_SPEED_SETPOINT_CMD, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SELECTED_SPEED_SETPOINT_LIMIT_CMD, 3u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SELECTED_DIRECTION_CMD, 8u, 1u, 2u, SpnValStandard ); */

/* Maintain power */
    #define SPN_MAINTAIN_ECUPOWER               (1867UL)  /**< \brief Part 7 A.13  */
    #define SPN_MAINTAIN_ACTUATORPOWER          (1868UL)  /**< \brief Part 7 A.14  */
    #define SPN_IMPLEMENT_TRANSPORTSTATE        (1869UL)  /**< \brief Part 7 A.15  */
    #define SPN_IMPLEMENT_PARKSTATE             (1870UL)  /**< \brief Part 7 A.16  */
    #define SPN_IMPLEMENT_WORKSTATE             (1871UL)  /**< \brief Part 7 A.17  */
    /* iso_SpnDefineSpn( x, SPN_MAINTAIN_ECUPOWER, 1u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_MAINTAIN_ACTUATORPOWER, 1u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_IMPLEMENT_TRANSPORTSTATE, 2u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_IMPLEMENT_PARKSTATE, 2u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_IMPLEMENT_WORKSTATE, 2u, 3u, 2u, SpnValStandard ); */

/* Lighting command */
    #define SPN_BACKUPLIGHT_ALARMHORNCMD        (2391UL) /**< \brief J1939-71 */
    /* iso_SpnDefineSpn( x, SPN_BACKUPLIGHT_ALARMHORNCMD, 3u, 1u, 2u, SpnValStandard ); */

/* Implement operating state command */
    #define SPN_IMPLEMENT_OPSTATECOMMAND	    (5139UL) /**< Part 7 A.25.1 */
    /* iso_SpnDefineSpn( x, SPN_IMPLEMENT_OPSTATECOMMAND, 8u, 1u, 2u, SpnValStandard ); */

/* Secondary or front hitch status */
    #define SPN_FRONT_HITCH_POSITION                    (1872UL)  /**< \brief Part 7 A.19.1  */
    #define SPN_FRONT_HITCH_WORK_INDICATION             (1876UL)  /**< \brief Part 7 A.19.5  */
    #define SPN_FRONT_HITCH_POS_LIMIT_STATUS            (5150UL)
    #define SPN_FRONT_HITCH_NOMINAL_LOWER_LINK_FORCE    (1880UL)
    #define SPN_FRONT_HITCH_DRAFT                       (1878UL)  /**< \brief Part 7 A.19.7  */
    #define SPN_FRONT_HITCH_EXIT_REASON_CODE            (5816UL)
    /* iso_SpnDefineSpn( x, SPN_FRONT_HITCH_POSITION, 1u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_HITCH_WORK_INDICATION, 2u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_HTICH_POS_LIMIT_STATUS, 2u, 4u, 3u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_NOMINAL_LOWER_LINK_FORCE, 3u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_DRAFT, 4u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_HITCH_EXIT_REASEON_CODE, 6u, 1u, 8u, SpnValStandard ); */

/* Primary or rear hitch status */
    #define SPN_REAR_HITCH_POSITION                 (1873UL)  /**< \brief Part 7 A.19.2  */
    #define SPN_REAR_HITCH_WORK_INDICATION          (1877UL)  /**< \brief Part 7 A.19.6  */
    #define SPN_REAR_HITCH_POS_LIMIT_STATUS         (5151UL)
    #define SPN_REAR_HITCH_NOMINAL_LOWER_LINK_FORCE (1881UL)
    #define SPN_REAR_HITCH_DRAFT                    (1879UL)  /**< \brief Part 7 A.19.8  */
    #define SPN_REAR_HITCH_EXIT_REASON_CODE         (5819UL)
    /* iso_SpnDefineSpn( x, SPN_REAR_HITCH_POSITION, 1u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_HITCH_WORK_INDICATION, 2u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_HTICH_POS_LIMIT_STATUS, 2u, 4u, 3u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_HITCH_NOMINAL_LOWER_LINK_FORCE, 3u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_HITCH_DRAFT, 4u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_HITCH_EXIT_REASEON_CODE, 6u, 1u, 8u, SpnValStandard ); */


/* Secondary or front PTO output shaft */
    #define SPN_FRONT_PTO_OUTP_SHAFT_SPEED      (1882UL)  /**< \brief Part 7 A.20.1  */
    #define SPN_FRONT_PTO_OUTP_SH_SPEED_SET     (1884UL)  /**< \brief Part 7 A.20.3  */ 
    #define SPN_FRONT_PTO_ENGAGEMENT            (1888UL)  /**< \brief Part 7 A.20.7  */
    #define SPN_FRONT_PTO_MODE                  (1889UL)  /**< \brief Part 7 A.20.9  */
    #define SPN_FRONT_PTO_ECONOMY_MODE          (1891UL)  /**< \brief Part 7 A.20.11 */
    #define SPN_FRONT_PTO_ENGAGEMENT_REQ        (5152UL)  /**< \brief Part 7 A.20.19 */
    #define SPN_FRONT_PTO_MODE_REQ_STATUS       (5153UL)
    #define SPN_FRONT_PTO_ECONOMY_MODE_REQ_STAT (5154UL)
    #define SPN_FRONT_PTO_SH_SPEED_LIMIT_STAT   (5155UL)
    #define SPN_FRONT_PTO_EXIT_REASON_CODE      (5817UL)
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_OUTP_SHAFT_SPEED, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_OUTP_SH_SPEED_SET, 3u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_NGAGEMENT, 5u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_MODE, 5u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_ECONOMY_MODE , 5u, 3u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_ENGAGEMENT_REQ, 5u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_MODE_REQ_STATUS, 6u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_ECONOMY_MODE_REQ_STAT, 6u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_SH_SPEED_LIMIT_STAT, 6u, 2u, 3u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FRONT_PTO_EXIT_REASON_CODE, 7u, 1u, 8u, SpnValStandard ); */

/* Primary or rear PTO output shaft */
    #define SPN_REAR_PTO_OUTP_SHAFT_SPEED       (1883UL)  /**< \brief Part 7 A.20.2  */
    #define SPN_REAR_PTO_OUTP_SH_SPEED_SET      (1885UL)  /**< \brief Part 7 A.20.4  */ 
    #define SPN_REAR_PTO_ENGAGEMENT             (2408UL)  /**< \brief Part 7 A.20.8  */
    #define SPN_REAR_PTO_MODE                   (1890UL)  /**< \brief Part 7 A.20.10  */
    #define SPN_REAR_PTO_ECONOMY_MODE           (1892UL)  /**< \brief Part 7 A.20.12 */
    #define SPN_REAR_PTO_ENGAGEMENT_REQ         (5156UL)  /**< \brief Part 7 A.20.23 */
    #define SPN_REAR_PTO_MODE_REQ_STATUS        (5157UL)
    #define SPN_REAR_PTO_ECONOMY_MODE_REQ_STAT  (5158UL)
    #define SPN_REAR_PTO_SH_SPEED_LIMIT_STAT    (5159UL)
    #define SPN_REAR_PTO_EXIT_REASON_CODE       (5820UL)
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_OUTP_SHAFT_SPEED, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_OUTP_SH_SPEED_SET, 3u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_ENGAGEMENT, 5u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_MODE, 5u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_ECONOMY_MODE , 5u, 3u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_ENGAGEMENT_REQ, 5u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_MODE_REQ_STATUS, 6u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_ECONOMY_MODE_REQ_STAT, 6u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_SH_SPEED_LIMIT_STAT, 6u, 2u, 3u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REAR_PTO_EXIT_REASON_CODE, 7u, 1u, 8u, SpnValStandard ); */

/* Hitch and PTO commands */
   #define SPN_FRONT_HITCH_POS_COMMAND          (1874UL)  /**< \brief Part 7 A.19.3  */
   #define SPN_REAR_HITCH_POS_COMMAND           (1875UL)  /**< \brief Part 7 A.19.4  */ 
   #define SPN_FRONT_OUTP_SH_SPEED_SET_CMD      (1886UL)  /**< \brief Part 7 A.20.5  */
   #define SPN_REAR_OUTP_SH_SPEED_SET_CMD       (1887UL)  /**< \brief Part 7 A.20.6  */
   #define SPN_FRONT_PTO_ENGAGEMENT_CMD         (1893UL)  /**< \brief Part 7 A.20.13 */
   #define SPN_REAR_PTO_ENGAGEMEN_CMDT          (1894UL)  /**< \brief Part 7 A.20.14 */
   /* iso_SpnDefineSpn( x, SPN_FRONT_HITCH_POS_COMMAND, 1u, 1u, 8u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_REAR_HITCH_POS_COMMAND, 2u, 1u, 8u, SpnValStandard ); */
	/* iso_SpnDefineSpn( x, SPN_FRONT_OUTP_SH_SPEED_SET, 3u, 1u, 16u, SpnValStandard ); */
	/* iso_SpnDefineSpn( x, SPN_REAR_OUTP_SH_SPEED_SET, 5u, 1u, 16u, SpnValStandard ); */
	/* iso_SpnDefineSpn( x, SPN_FRONT_PTO_ENGAGEMENT, 7u, 7u, 2u, SpnValStandard ); */
	/* iso_SpnDefineSpn( x, SPN_REAR_PTO_ENGAGEMENT, 7u, 5u, 2u, SpnValStandard ); */


/* Auxiliary valve estimated flow */
   #define SPN_AUX_VALVE_EXT_EST_FLOW           (2337UL)  /**< \brief Part 7 A.21.19  */
   #define SPN_AUX_VALVE_RET_EST_FLOW           (2338UL)  /**< \brief Part 7 A.21.20  */ 
   #define SPN_AUX_VALVE_FAIL_SAFE_MOD          (2346UL)  /**< \brief Part 7 A.21.28  */
   #define SPN_AUX_VALVE_VALVE_STATE            (2339UL)  /**< \brief Part 7 A.21.21  */
   #define SPN_AUX_VALVE_ESTIM_LIMIT            (5192UL)  /**< \brief Part 7 A.21.47  */
   #define SPN_AUX_VALVE_EXIT_REASON_CODE       (5815UL)
   /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_EXT_EST_FLOW, 1u, 1u, 8u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_RET_EST_FLOW, 2u, 1u, 8u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_FAIL_SAFE_MOD, 3u, 7u, 2u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_VALVE_STATE, 3u, 1u, 4u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_ESTIM_LIMIT, 4u, 6u, 3u, SpnValStandard ); */
   /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_EXIT_REASON_CODE, 5u, 1u, 8u, SpnValStandard ); */


/* Auxiliary valve command */
    #define SPN_AUX_VALVE_PORT_FLOW_COMMAND         (2343UL)
    #define SPN_AUX_VALVE_STATE_COMMAND             (2344UL)  /**< \brief Part 7 A.21.26  */
    #define SPN_AUX_VALVE_FAIL_SAFE_MODE_COMMAND    (2345UL)
    /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_PORT_FLOW_COMMAND, 1u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_15_STATE_COMMAND, 3u, 1u, 4u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_FAIL_SAFE_MODE_COMMAND, 3u, 7u, 2u, SpnValStandard ); */

/* Auxiliary valve measured flow */
    #define SPN_AUX_VALVE_LIMITSTATUS           (5190UL)  /**< \brief Part 7 A.21.29  */
    /* iso_SpnDefineSpn( x, SPN_AUX_VALVE_LIMITSTATUS, 8u, 6u, 3u, SpnValStandard ); */

/* Guidance system command */
    #define SPN_CURVATURE_COMMAND               (5237UL)  /**< \brief Part 7 A.28.1  */
    #define SPN_CURVATURE_COMMAND_STATUS        (5239UL)  /**< \brief Part 7 A.28.3  */
    /* iso_SpnDefineSpn( x, SPN_CURVATURE_COMMAND, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_CURVATURE_COMMAND_STATUS, 3u, 1u, 2u, SpnValStandard ); */

/* Guidance machine status */
    #define SPN_ESTIMATED_CURVATURE             (5238UL)  /**< \brief Part 7 A.28.2  */
    #define SPN_REQUEST_RESET_COMM_STATUS       (5240UL)  /**< \brief Part 7 A.28.4  */
    #define SPN_STEERING_INP_POS_STATUS         (5241UL)  /**< \brief Part 7 A.28.5  */
    #define SPN_SYSTEM_READINESS                (5242UL)  /**< \brief Part 7 A.28.6  */
    #define SPN_MECHANICAL_SYSTEM_LOCKOUT       (5243UL)  /**< \brief Part 7 A.28.7  */ 
    #define SPN_GUIDANCE_LIMIT_STATUS           (5726UL)
    #define SPN_GUID_SYS_COM_EXIT_REASON_CODE   (5725UL)
    /* iso_SpnDefineSpn( x, SPN_ESTIMATED_CURVATURE , 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_REQUEST_RESET_COMM_STATUS, 3u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_STEERING_INP_POS_STATUS, 3u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_SYSTEM_READINESS, 3u, 3u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_MECHANICAL_SYSTEM_LOCKOUT, 3u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_GUIDANCE_LIMIT_STATUS, 4u, 6u, 3u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_GUID_SYS_COM_EXIT_REASON_CODE, 5u, 1u, 6u, SpnValStandard ); */

/* Vehicle hours */
    #define SPN_TOTAL_VEHICLE_HOURS             (246UL)
    #define SPN_TOTAL_POWER_TAKEOFF_HOURS       (248UL)
    /* iso_SpnDefineSpn( x, SPN_TOTAL_VEHICLE_HOURS, 1u, 1u, 32u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TOTAL_POWER_TAKEOFF_HOURS, 5u, 1u, 32u, SpnValStandard ); */

/* Tire Condition */
    #define SPN_TIRE_LOCATION                   (929UL)
    #define SPN_TIRE_PRESSURE                   (241UL)
    #define SPN_TIRE_TEMPERATURE                (242UL)
    #define SPN_CTI_WHEEL_SENSOR_STATUS         (1699UL)
    #define SPN_CTI_TIRE_STATUS                 (1698UL)
    #define SPN_WHEEL_END_ELECTRICAL_FAULT      (1697UL)
    #define SPN_TIRE_LEAKAGE_RATE               (2586UL)
    #define SPN_TIRE_PRESSURE_THRESHOLD_DETECTION   (2587UL),
    /* iso_SpnDefineSpn( x, SPN_TIRE_LOCATION, 1u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TIRE_PRESSURE, 2u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TIRE_TEMPERATURE, 3u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_CTI_WHEEL_SENSOR_STATUS, 5u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_CTI_TIRE_STATUS, 5u, 3u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_WHEEL_END_ELECTRICAL_FAULT, 5u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TIRE_LEAKAGE_RATE, 6u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TIRE_PRESSURE_THRESHOLD_DETECTION, 8u, 6u, 2u, SpnValStandard ); */

/* Language Command */
    #define SPN_LANGUAGE_CMD_1                   (2410UL)
    #define SPN_LANGUAGE_CMD_2                   (2411UL)
/*    #define SPN_DECIMAL_SYMBOL                  (2411UL)
    #define SPN_DATE_FORMAT                     (2412UL)
    #define SPN_TIME_FORMAT                     (2413UL)
    #define SPN_DISTANCE_UNITS                  (2414UL)
    #define SPN_AREA_UNITS                      (2415UL)
    #define SPN_VOLUME_UNITS                    (2416UL)
    #define SPN_MASS_UNITS                      (2417UL)
    #define SPN_TEMPERATURE_UNITS               (5194UL)
    #define SPN_PRESSURE_UNITS                  (5195UL)
    #define SPN_FORCE_UNITS                     (5196UL)
    #define SPN_UNITS_SYSTEM                    (5197UL) */
    /* iso_SpnDefineSpn( x, SPN_LANGUAGE_CODE, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TIME_FORMAT, 3u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_DECIMAL_SYMBOL, 3u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_DATE_FORMAT, 4u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_MASS_UNITS, 5u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_VOLUME_UNITS, 5u, 3u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_AREA_UNITS, 5u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_DISTANCE_UNITS, 5u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_UNITS_SYSTEM, 6u, 1u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_FORCE_UNITS, 6u, 3u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_PRESSURE_UNITS, 6u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TEMPERATURE_UNITS, 6u, 7u, 2u, SpnValStandard ); */

/* Time / Date */
    #define SPN_TIME_SECOND                     (959UL)
    #define SPN_TIME_MINUTE                     (960UL)
    #define SPN_TIME_HOUR                       (961UL)
    #define SPN_DATE_MONTH                      (963UL)
    #define SPN_DATE_DAY                        (962UL)
    #define SPN_DATE_YEAR                       (964UL)
    #define SPN_LOCAL_MINUTE_OFFSET             (1601UL)
    #define SPN_LOCAL_HOUR_OFFSET               (1602UL)
    /* iso_SpnDefineSpn( x, SPN_TIME_SECOND, 1u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TIME_MINUTE, 2u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_TIME_HOUR, 3u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_DATE_MONTH, 4u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_DATE_DAY, 5u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_DATE_YEAR, 6u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_LOCAL_MINUTE_OFFSET, 7u, 1u, 8u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_LOCAL_HOUR_OFFSET, 8u, 1u, 8u, SpnValStandard ); */

/* Lighting Command & Lighting Data */
    #define SPN_LIGHTING_DATA_1                     (2347UL)
    #define SPN_LIGHTING_DATA_2                     (2371UL)
    #define SPN_LIGHTING_DATA_3                     (2361UL)
    #define SPN_LIGHTING_DATA_4                     (2597UL)
    #define SPN_RIGHT_TURN_SIGNAL_CMD               (2369UL)
    #define SPN_LEFT_TURN_SIGNAL_CMD                (2367UL)
    #define SPN_RIGHT_TURN_LIGHTS                   (2370UL)
    #define SPN_LEFT_TURN_LIGHTS                    (2368UL)
    /* iso_SpnDefineSpn( x, SPN_LIGHTING_DATA_1, 1u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_LIGHTING_DATA_2, 3u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_LIGHTING_DATA_3, 5u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_LIGHTING_DATA_4, 7u, 1u, 16u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_RIGHT_TURN_SIGNAL_CMD, 2u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_LEFT_TURN_SIGNAL_CMD, 2u, 7u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_RIGHT_TURN_LIGHTS, 2u, 5u, 2u, SpnValStandard ); */
    /* iso_SpnDefineSpn( x, SPN_LEFT_TURN_LIGHTS, 2u, 5u, 2u, SpnValStandard ); */


/* ************************************************************************ */
/* SPN DEFINES for ISO11783-12 */

/* Software Identification */
    #define SPN_SWIDENT_NUMBER_SWFIELDS           (965u)
    #define SPN_SW_IDENT_SW_VERSION               (234u)
    /* iso_SpnDefineSpn( x, SPN_SWIDENT_NUMBER_SWFIELDS, 1u, 1u, 8u, SpnValStandard ); */
    /* SPN_SW_IDENT_SW_VERSION is a string */

/* ISOBUS Certification (CCID) */
    #define SPN_CCID_TESTPROTOCOL_PUBLICYEAR     (4313u)    /* ISOBUS compliance test protocol publication year */
    #define SPN_CCID_TESTPROTOCOL_REVISION       (4314u)    /* ISOBUS compliance test protocol revision */
    #define SPN_CCID_LABORATORY_ID               (4316u)    /* ISOBUS Compliance certification laboratory ID */
    #define SPN_CCID_LABORATORY_TYPE             (4315u)    /* ISOBUS compliance certification laboratory type */
    #define SPN_CCID_MESSAGE_REVISION            (7446u)    /* ISOBUS Compliance certification message revision */
    #define SPN_CCID_REFERENCE_NUMBER            (4330u)    /* ISOBUS Compliance certification reference number */
    /* There are special set functions */

#endif /* ifndef NO_SPN_DEFINES */

/**@}*/ /* end group SPNs */

/* ************************************************************************ */
/**  \addtogroup isofmis 
*/
/**@{*/

    #define FMI_DATA_VALID_ABOVE_NORMAL          (0u) /**< \brief Data Valid But Above Normal Operational Range - Most Severe Level */
    #define FMI_DATA_VALID_BELOW_NORMAL          (1u) /**< \brief Data Valid But Below Normal Operational Range - Most Severe Level */
    #define FMI_DATA_ERRATIC                     (2u) /**< \brief Data Erratic, Intermittent Or Incorrect */
    #define FMI_VOLTAGE_ABOVE_NORMAL             (3u) /**< \brief Voltage Above Normal, Or Shorted To High Source */
    #define FMI_VOLTAGE_BELOW_NORMAL             (4u) /**< \brief Voltage Below Normal, Or Shorted To Low Source */
    #define FMI_CURRENT_ABOVE_NORMAL             (5u) /**< \brief Current Below Normal Or Open Circuit */
    #define FMI_CURRENT_BELOW_NORMAL             (6u) /**< \brief Current Above Normal Or Grounded Circuit */
    #define FMI_MECH_SYSTEM_NOT_RESPONDING       (7u) /**< \brief Mechanical System Not Responding Or Out of Adjustment */
    #define FMI_ABNORMAL_FREQUENCY               (8u) /**< \brief Abnormal Frequency Or Pulse Width Or Period */
    #define FMI_ABNORMAL_UPDATERATE              (9u) /**< \brief Abnormal Update Rate */
    #define FMI_ABNORMAL_RATEOFCHANGE           (10u) /**< \brief Abnormal Rate Of Change */
    #define FMI_ROOT_CAUSE_NOT_KNOWN            (11u) /**< \brief Root Cause Not Known */
    #define FMI_BAD_INTELLIGENT_DEVICE          (12u) /**< \brief Bad Intelligent Device Or Component */
    #define FMI_OUT_OF_CALIBRATION              (13u) /**< \brief Out Of Calibration */
    #define FMI_SPECIAL_INSTRUCTIONS            (14u) /**< \brief Special Instructions */
    #define FMI_DATA_ABOVE_NORM_LEAST_SEVER     (15u) /**< \brief Data Valid But Above Normal Operating Range - Least Severe Level */
    #define FMI_DATA_ABOVE_NORMAL_MOD_SEVER     (16u) /**< \brief Data Valid But Above Normal Operating Range - Moderately Severe Level */
    #define FMI_DATA_BELOW_NORMAL_LEAST_SEV     (17u) /**< \brief Data Valid But Below Normal Operational Range - Least Severe Level */
    #define FMI_DATA_BELOW_NORMAL_MOD_SEVER     (18u) /**< \brief Data Valid But Below Normal Operational Range - Moderately Severe Level */
    #define FMI_RECEIV_NETW_DATA_IN_ERROR       (19u) /**< \brief Received Network Data in Error */
    /* 20-30, */ /* Reserved for future assignment */
    #define FMI_CONDITION_EXISTS                (31u) /**< \brief Condition Exists */

/**@}*/ /* end group FMIs */

/* ************************************************************************ */
/** \addtogroup isodefslayer78
*/
/**@{*/
          /* Common definitions for LAYER 7, 8 */
#define   ISO_REVERSE                     ( 0x0u )      /**< Direction reverse */
#define   ISO_DISABLED                    ( 0x0u )      /**< Not enabled */
#define   ISO_DISENGAGED                  ( 0x0u )      /**< Switched off */
#define   ISO_FORWARD                     ( 0x1u )      /**< Direction forward */
#define   ISO_ENABLED                     ( 0x1u )      /**< Enabled */
#define   ISO_ENGAGED                     ( 0x1u )      /**< Switched on */

#define   ISO_ERROR_INDI_2Bit              ( 0x2u )      /**< 2 bit error indicator */
#define   ISO_NOT_AVAILABLE_2Bit           ( 0x3u )      /**< 2 bit not available */
#define   ISO_DONT_CARE_2bit               ( 0x3u )      /**< 2 bit dont care */
#define   ISO_ERROR_INDI_3Bit              ( 0x6u )      /**< 3 bit error indicator */
#define   ISO_NOT_AVAILABLE_3Bit           ( 0x7u )      /**< 3 bit not available */
#define   ISO_DONT_CARE_3bit               ( 0x7u )      /**< 3 bit dont care */
                                                
#define   ISO_ERROR_INDI_4bit              ( 0xEu )      /**< 4 bit error indicator */
#define   ISO_NOT_AVAILABLE_4bit           ( 0xFu )      /**< 4 bit not available */
#define   ISO_DONT_CARE_4bit               ( 0xFu )      /**< 4 bit dont care */
                                         
#define   ISO_VALID_SIGNAL_B              ( 0xFAu )      /**< 8 bit max value of valid signal */
#define   ISO_ERROR_INDI_B                ( 0xFEu )      /**< 8 bit error indicator */
#define   ISO_NOT_AVAILABLE_B             ( 0xFFu )      /**< 8 bit not available */
#define   ISO_DONT_CARE_B                 ( 0xFFu )      /**< 8 bit dont care */

#define   ISO_VALID_SIGNAL_W            ( 0xFAFFu )      /**< 16 bit max value of valid signal */
#define   ISO_ERROR_INDI_W              ( 0xFE00u )      /**< 16 bit error indicator min */
#define   ISO_NOT_AVAILABLE_W           ( 0xFF00u )      /**< 16 bit not available min */
#define   ISO_ERROR_INDI_WM             ( 0xFEFFu )      /**< 16 bit error indicator max */
#define   ISO_NOT_AVAILABLE_WM          ( 0xFFFFu )      /**< 16 bit not available max */
#define   ISO_DONT_CARE_W               ( 0xFFFFu )      /**< 16 bit dont care */

#define   ISO_VALID_SIGNAL_DW     (   0xFAFFFFFFuL )       /**< 32 bit max value of valid signal */
#define   ISO_ERROR_INDI_DW       (   0xFE000000uL )       /**< 32 bit error indicator min */
#define   ISO_NOT_AVAILABLE_DW    (   0xFF000000uL )       /**< 32 bit not available min */
#define   ISO_ERROR_INDI_DWM      (   0xFEFFFFFFuL )       /**< 32 bit error indicator max */
#define   ISO_NOT_AVAILABLE_DM    (   0xFFFFFFFFuL )       /**< 32 bit not available max */
 

#define   ISO_LIMIT_MAX           (   0x7FFFFFFFL )        /**< Threshold limit signed long max */
#define   ISO_LIMIT_MIN           (  -0x7FFFFFFFL )        /**< Threshold limit signed long min */

#define   NMEA_ERROR_INDI_B       (        0xFEu )          /**< NMEA Error indicator for  8 bit value */
#define   NMEA_ERROR_INDI_W       (      0xFFFEu )          /**< NMEA Error indicator for 16 bit value */
#define   NMEA_ERROR_INDI_DW      ( 0xFFFFFFFEuL )          /**< NMEA Error indicator for 32 bit value */
/* not used #define   NMEA_ERROR_INDI_ULL     ( 0xFFFFFFFFFFFFFFFEuLL ) NMEA Error indicator for 64 bit value */
#define   NMEA_NOT_AVAILABLE_B    (        0xFFu )          /**< NMEA Not available for  8 bit value */
#define   NMEA_NOT_AVAILABLE_W    (      0xFFFFu )          /**< NMEA Not available for 16 bit value */
#define   NMEA_NOT_AVAILABLE_DW   ( 0xFFFFFFFFuL )          /**< NMEA Not available for 32 bit value */
/* not used #define   NMEA_NOT_AVAILABLE_ULL  ( 0xFFFFFFFFFFFFFFFFuLL ) NMEA Not available for 64 bit value */

/**@}*/ /* end group Common definitions for LAYER 7, 8 */

#endif /* DEF_ISOPGNDEF_H */
