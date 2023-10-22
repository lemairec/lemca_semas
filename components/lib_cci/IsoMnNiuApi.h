/* ************************************************************************ */
/*!
   \file                       
   \brief       Part 4 - API for the network interconnection unit (NIU) service management 
   \author      Wegscheider Peter
   \date        Created XX.07.12

   \copyright   Competence Center ISOBUS e.V.
           
   \par         History:
   \par
   17.07.2012 - author P. Wegscheider
   - changes for Doxygen output generation   
   \par
   04.07.2013 - author P. Wegscheider
   - SRL1 Lint code review updates
   - Module version define VERSION_NIU added
   \par
   06.05.2018 - author P.Wegscheider
   - Feature ID 3910: header files should include header files they depend on
   \par
   12.06.2018 - author P.Wegscheider
   - Feature request ID 8459: use iso_u8 for ISOBUS addresses in API
   \par
   14.06.2018 - author P.Wegscheider
   - Feature request ID 8424: use ISO_CF_NAME_T in API functions
   \par
   10.08.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files
*/
/* ************************************************************************ */

#ifndef DEF_MnNiu_H
    #define DEF_MnNiu_H

/* include configuration, driver standard types and common definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */
/* ************************************************************************ */

/*! \defgroup niuapi Network Interconnection Unit
    \ingroup core 
    \brief  Part 4 - Network interconnection unit service

    This part contains the NIU service configuration and management functions. 

    For the module version see \ref grp_versions #VERSION_NIU 
*/

/*! \defgroup niuconfig NIU-Service Configuration
    \ingroup niuapi
    \brief NIU-Service definitions for IsoConf.h
*/
 
/*! \defgroup niutypedef NIU-Service Type Definitions
    \ingroup niuapi
    \brief NIU-Service public defines, structure and enum definitions

    This part contains the structure, enum and type definitions for the NIU-Service management module.
*/
/* ************************************************************************ */
/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */
/*! \addtogroup niuapi 
  @{
    \name Enable NIU-Service Module in IsoConf.h 
  @{ */
/* ************************************************************************ */
#ifdef DOXYGEN
/*! \def _LAY4_  
    \brief Add the define _LAY4_ to IsoConf.h to enable the NIU service functionality. 
    \n Use the defines in the \ref niuconfig "configuration" section to configure the service.
*/
#define _LAY4_  
#endif
/* ************************************************************************ */
/*! @} */
/*! @} */
/* ************************************************************************ */
/* ************************************************************************ */

/* ************************************************************************ */
/*! \addtogroup niuconfig
  @{ */
/* ************************************************************************ */

/*! \def NIU_MAX_CAN_PORTS
    \brief Number of CAN ports, last port number ( default = ISO_CAN_NODES ) 
    \details Range: 2u .. 14u 
    The mapping of the NIU internal port numbers to the driver CAN node index is fix.\n
    IsoNL_Port_1 has the CAN node index 0, IsoNL_Port_2 has the index 1, ...\n
    Port range: IsoNL_Port_1 .. NIU_MAX_CAN_PORTS
*/
#ifndef NIU_MAX_CAN_PORTS
    #define NIU_MAX_CAN_PORTS   (ISO_CAN_NODES)  
#endif

/*! \def NIU_MAX_PORT_BINDINGS
    \brief Maximum number of possible bindings between CAN ports \n
           This value depends on NIU_MAX_CAN_PORTS and can not be changed in the config file.
*/
#define NIU_MAX_PORT_BINDINGS   ( (NIU_MAX_CAN_PORTS * ( NIU_MAX_CAN_PORTS - 1u )) / 2u )  

/*! \def NIU_MAX_FILTER_DBS
    \brief Number of filter databases ( the default is NIU_MAX_PORT_BINDINGS * 2u ) 
    \details Range: 0u .. NIU_MAX_PORT_BINDINGS * 2u \n
    The number of filter databases can not be greater than 182. 
*/
#ifndef NIU_MAX_FILTER_DBS
    #define NIU_MAX_FILTER_DBS      (NIU_MAX_PORT_BINDINGS * 2u)    
#endif

/*! \def NIU_MAX_FILTER_PGN_ENTRIES
    \brief Size of the PGN filter array ( the default is NIU_MAX_FILTER_DBS * 100u ) 
    \details Range: 0u .. 32000u \n
    Since the number of PGN entries for a port pair should not be greater than 594, 

*/
#ifndef NIU_MAX_FILTER_PGN_ENTRIES
    #define NIU_MAX_FILTER_PGN_ENTRIES      (NIU_MAX_FILTER_DBS * 100u)    
#endif

/*! \def NIU_MAX_FILTER_PGN_NAME_ENTRIES
    \brief Size of the PGN/Name filter array ( the default is NIU_MAX_FILTER_DBS * 10 ) 
    \details Range: 0u .. 32000u
*/
#ifndef NIU_MAX_FILTER_PGN_NAME_ENTRIES
    #define NIU_MAX_FILTER_PGN_NAME_ENTRIES      (NIU_MAX_FILTER_DBS * 10u)    
#endif

/*! \def NIU_MAX_ROUTER_CONNECTIONS
    \brief Size of the routing connection array ( the default is NIU_MAX_PORT_BINDINGS * 5u ) 
*/
#ifndef NIU_MAX_ROUTER_CONNECTIONS
    #define NIU_MAX_ROUTER_CONNECTIONS      (NIU_MAX_PORT_BINDINGS * 5u)    
#endif

/*! \def NIU_MAX_MSG_TRANSFERS
    \brief Size of the CAN message transfer lookup array ( the default is NIU_MAX_PORT_BINDINGS * 20u ) 
    \details This array is also used for the PGN/Name max. transfer rate check. 
*/
#ifndef NIU_MAX_MSG_TRANSFERS
    #define NIU_MAX_MSG_TRANSFERS      (NIU_MAX_PORT_BINDINGS * 20u)    
#endif


/*! \def NIU_CYCLE_TIME
    \brief Time in milliseconds between two calls of the NIU management cyclic run function. 
    \details Range: 0..1000 msec (default: 250).  
*/
#ifndef NIU_CYCLE_TIME
    #define NIU_CYCLE_TIME     (ISO_TIME(250L))    
#endif

/*! \def NL_CYCLE_TIME
    \brief Time in milliseconds between two calls of the NIU service cyclic run function. 
    \details Range: 0..200 msec (default: 20).  
*/
#ifndef NL_CYCLE_TIME
    #define NL_CYCLE_TIME     (ISO_TIME(20L))   
#endif


/*! \def NIU_MAX_RESPONSE_BUFFFER
    \brief Maximum size of the iso_u8 array for building the request response. 
    \details Default: TP_SIZE_MAX (1785 bytes)
*/
#ifndef NIU_MAX_RESPONSE_BUFFFER
    #define NIU_MAX_RESPONSE_BUFFFER      (0x06F9u)    
#endif

#ifdef DOXYGEN
/* Misra # undef NIU_PGN_NAME_MASK_KEY */
/*! \def NIU_PGN_NAME_MASK_KEY  
    \brief (Optional) Use PGN && (Name & Mask) as the PGN/Name entry key (the default is PGN && Name). 
*/
#define NIU_PGN_NAME_MASK_KEY     
#endif

/* ************************************************************************ */
/** \name Configuration parameter (group) 
    \brief Used with iso_NiuSetParam() and iso_NiuGetParam()
@{ 
*/

/* ************************************************************************ */
/** \def NIU_PARAM_BRIDGE_ALL
    \brief      Bridge: Transfer all CAN messages without checking desination address / port.  
    \details    Default value: NIU_VAL_OFF \n
                Set the value for this parameter to NIU_VAL_ON to transfer destination specefic CAN mesages \n
                to all ports and not only to the port of the destination cf. Use this option if you want to see all messages on all bridget network segments. \n
                If it set to NIU_VAL_OFF the destination specific messages between cf's of one port are not transfert to any other port \n
                and destination specific messages between cf's located on two different ports are only transfert to the port of the destination cf. \n
                This reduces the busload on the other ports.
*/
#define NIU_PARAM_BRIDGE_ALL        0u  

/* ************************************************************************ */
/** \def NIU_PARAM_ROUTE_GLOBAL
    \brief      Router: Transfer global CAN messages if the source address is a virtual CF on the destination port. 
    \details    Default value: NIU_VAL_OFF \n
                Set the value for this parameter to NIU_VAL_ON to transfer the global CAN mesages to the destination port. \n
                Only global messages of a cf with a virtual cf on the destination port which have passed the filter for this port pair direction are transfered. \n
                Enable this feature if the members of a connection use also PDU2 or other global destination messages for their communication. \n
*/ 
#define NIU_PARAM_ROUTE_GLOBAL      1u  

/* ************************************************************************ */
/** \def NIU_PARAM_ROUTE_FILTER
    \brief      Router: Filter specific CAN messages between connected CFs. 
    \details    Default value: NIU_VAL_OFF \n
                Set the value for this parameter to NIU_VAL_ON to filter CAN mesages between connection members before transfering them to the destination port. \n
                If set to NIU_VAL_ON the filter database is also used to filter the destination specific messages for this connection. \n
*/ 
#define NIU_PARAM_ROUTE_FILTER      2u

/** @} */

/* ************************************************************************ */
/** \name Configuration common values 
    \brief Used with iso_NiuSetParam() and iso_NiuGetParam()
@{ 
*/
#define NIU_VAL_OFF 0x00u                   /**< \brief Configuration value: 0 = off, disabled, ...  */ 
#define NIU_VAL_ON  0x01u                   /**< \brief Configuration value: 1 = on, enabled, ...  */
#define NIU_RET_ERROR  0xFFFFu              /**< \brief Get return value: 0xFFFF = value not valid */
/** @} */

/* ************************************************************************ */
/*! @} */  /* END  niuconfig                                      */
/* ************************************************************************ */
/* ************************************************************************ */
#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoMnNiuApi.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */

/* ************************************************************************ */
/** \addtogroup errorhand 
@{ 
*/
/*! \name NIU Management specific error handler function numbers
    \brief used with the error location numbers M_NIU
  @{ */
#define ISONIU_FUNCTION             0u
#define ISONIU_FN_INIT              1u
#define ISONIU_FN_PROCESS_REQUEST   2u
#define ISONIU_FN_CYCLIC_RUN        3u
/*! @} */
/*! \name NIU Service specific error handler function numbers
    \brief used with the error location numbers M_NL 
  @{ */
#define ISONL_FUNCTION              0u
#define ISONL_FN_INIT               1u
#define ISONL_FN_PROCESS_CAN_MSG    2u
#define ISONL_FN_CYCLIC_RUN         3u
#define ISONL_FN_DO_BRIDGING        4u
#define ISONL_FN_DO_ROUTING         5u
#define ISONL_FN_FILTER_MSG         6u
#define ISONL_FN_TRANSMIT_MSG       7u
#define ISONL_FN_UPD_STAT           8u
#define ISONL_FN_TR_TABLE           9u
/*! @} */
/*! @} */
/* ************************************************************************ */
#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */


/* ************************************************************************ */
/* ************************************************************************ */
/*! \addtogroup niutypedef 
  @{ */ 
/* ************************************************************************ */
#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
/* IsoMnNiuApi.hpp is already included above */
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */

/* ************************************************************************ */
/*! \name NIU Mode
    \brief NIU CAN message transfer mode between two CAN ports. 
  @{ */
#define ISONL_NIU_Disabled          0x00u   /**< \brief NIU services is disabled for this port pair. */ 
#define ISONL_NIU_Bridge            0x01u   /**< \brief NIU services is configured as bridge for this port pair. */
#define ISONL_NIU_Router            0x02u   /**< \brief NIU services is configured as connection router for this port pair. */
#define ISONL_NIU_Autodetection     0x03u   /**< \brief NIU services is configured to autodetect the mode for this port pair. */
/*! @} */

/* ************************************************************************ */
/*! \name NIU CAN Ports 
    \brief Part 4 chapter 6.5.3 Port numbers. 
  @{ */
/** \def ISONL_Port_Local
    \brief "alias" for the port number which receives the CAN message. 
    \details Used in requests if the external CF does not know the number of the connecting port.
*/
#define ISONL_Port_Local        0x00u   
#define ISONL_Port_1            0x01u   /**< \brief NIU CAN port 1.  */ 
#define ISONL_Port_2            0x02u   /**< \brief NIU CAN port 2.  */
#define ISONL_Port_3            0x03u   /**< \brief NIU CAN port 3.  */
#define ISONL_Port_4            0x04u   /**< \brief NIU CAN port 4.  */
#define ISONL_Port_5            0x05u   /**< \brief NIU CAN port 5.  */
#define ISONL_Port_6            0x06u   /**< \brief NIU CAN port 6.  */
#define ISONL_Port_7            0x07u   /**< \brief NIU CAN port 7.  */
#define ISONL_Port_8            0x08u   /**< \brief NIU CAN port 8.  */
#define ISONL_Port_9            0x09u   /**< \brief NIU CAN port 9.  */
#define ISONL_Port_10           0x0Au   /**< \brief NIU CAN port 10. */
#define ISONL_Port_11           0x0Bu   /**< \brief NIU CAN port 11. */
#define ISONL_Port_12           0x0Cu   /**< \brief NIU CAN port 12. */
#define ISONL_Port_13           0x0Du   /**< \brief NIU CAN port 13. */
#define ISONL_Port_14           0x0Eu   /**< \brief NIU CAN port 14. */
#define ISONL_Port_Global       0x0Fu   /**< \brief Do request for all (from or to) ports. */
/*! @} */

/* ************************************************************************ */
/*! \name NIU Port Options / Status Defines
    \brief NIU data state flags. 
  @{ */
#define ISONL_Port_Disabled     0x0000u   /**< \brief NIU-Service management are not available for this port  */ 
#define ISONL_Port_Enabled      0x0001u   /**< \brief NIU-Service management are available for this port. */
/*! @} */

/* ************************************************************************ */
/*! \name NIU States
    \brief NIU data state flags. 
  @{ */
#define ISONL_State_Active      0x00u   /**< \brief Data entry is valid. */ 
#define ISONL_State_Modified    0x01u   /**< \brief Data entry is modified (added or updated). The entry is valid. */
#define ISONL_State_Deleted     0x02u   /**< \brief Data entry is not valid (marked for deletion). */
#define ISONL_State_Invalid     0x03u   /**< \brief Data entry is not valid. */ 
#define ISONL_State_Inprogress  0x04u   /**< \brief Data entry is currently not valid. */ 
#define ISONL_State_Inactive    0x05u   /**< \brief Data entry is disabled. */ 
/*! @} */


/* ************************************************************************ */
/*! \name NIU Filter Modes
  @{ */
#define ISONL_FM_BLOCK_SPECIFIC     0x00u   /**< \brief Filter mode: Block-secific PGNs (default = pass all)*/
#define ISONL_FM_PASS_SPECIFIC      0x01u   /**< \brief Filter mode: Pass-secific PGNs (default = block all)*/
/*! @} */

/* ************************************************************************ */
/*! \name NIU Filter Entry Types
  @{ */
#define ISONL_PGN_ENTRY             0x00u   /**< \brief PGN filter DB entry*/
#define ISONL_PGN_NAME_ENTRY        0x01u   /**< \brief PGN/Name filter DB entry*/
/*! @} */

/* ************************************************************************ */
/*! \name NIU Port Pair Defines 
  @{ */
#define ISONL_PP_NULL               0x00u   /**< \brief  port pair not valid */
#define ISONL_PP_GLOBAL             0xFFu   /**< \brief  no specific port pair */
/*! @} */

/* ************************************************************************ */

/* ************************************************************************ */
/*! \name NIU Message Function Code Defines 
  @{ */
#define ISONL_FC_REQ_FILTER_DB      0x00u   /**< \brief Function code: Request a copy of filter database */
#define ISONL_FC_RES_FILTER_DB      0x01u   /**< \brief Function code: Response to a request for a copy of filter database */
#define ISONL_FC_ADD_FILTER         0x02u   /**< \brief Function code: Request to add an entry to the filter database */
#define ISONL_FC_DEL_FILTER         0x03u   /**< \brief Function code: Request to delete an entry from the filter database */
#define ISONL_FC_CLEAR_FILTER_DB    0x04u   /**< \brief Function code: Request to clear (delete) a filter database */
#define ISONL_FC_CREATE_FILTER_DB   0x06u   /**< \brief Function code: Request to create a filter database */
#define ISONL_FC_ADD_NAME_FILTER    0x07u   /**< \brief Function code: Request to add NAME qualified filter database entries */

#define ISONL_FC_REQ_SA_LIST        0x40u   /**< \brief Function code: Request a source address list */
#define ISONL_FC_RES_SA_LIST        0x41u   /**< \brief Function code: Response to a request for a source address list */
#define ISONL_FC_REQ_SA_NAME_LIST   0x42u   /**< \brief Function code: Request a source address and NAME list */
#define ISONL_FC_RES_SA_NAME_LIST   0x43u   /**< \brief Function code: Response to a request for a source address and NAME list */

#define ISONL_FC_REQ_GENERAL_PARAM  0x80u   /**< \brief Function code: Request NIU general parametrics */
#define ISONL_FC_RES_GENERAL_PARAM  0x81u   /**< \brief Function code: Response to a request for NIU general parametrics */
#define ISONL_FC_RESET_GENERAL      0x82u   /**< \brief Function code: Command to reset general statistic parametrics */
#define ISONL_FC_REQ_SPECIFIC_PARAM 0x83u   /**< \brief Function code: Request NIU specific parametrics */
#define ISONL_FC_RES_SPECIFIC_PARAM 0x84u   /**< \brief Function code: Response to a request for NIU specific parametrics */
#define ISONL_FC_RESET_SPECIFIC     0x85u   /**< \brief Function code: Command to reset specific statistic parametrics */

#define ISONL_FC_REQ_OPEN_CONN      0xC0u   /**< \brief Function code: Request to open connection */
#define ISONL_FC_RES_OPEN_CONN      0xC2u   /**< \brief Function code: Response to request to open connection */
#define ISONL_FC_REQ_CLOSE_CONN     0xC1u   /**< \brief Function code: Request to close connection */
#define ISONL_FC_RES_CLOSE_CONN     0xC3u   /**< \brief Function code: Response to request to close connection */

#define ISONL_FC_NONE               0xFFu   /**< \brief Function code is not valid */

/*! @} */

/* ************************************************************************ */

/* ************************************************************************ */
/*! \name NIU Callback Return Value Defines 
  @{ */
#define ISONL_RET_ACCEPT            0       /**< \brief Request execution is permitted  */
#define ISONL_RET_CANCEL            1       /**< \brief Request execution is not permitted  */
#define ISONL_RET_NOT_VALID         2       /**< \brief Request parameter are not valid */
/*! @} */

/* ************************************************************************ */
/*! \name NIU Callback Message Type Value Defines 
  @{ */
#define ISONL_MSG_UNKOWN            0x00u   /**< \brief message is not valid */
#define ISONL_MSG_REQUEST           0x01u   /**< \brief Request execution permission  */
#define ISONL_MSG_FINISHED          0x02u   /**< \brief Request execution is finished */
/*! @} */

/* ************************************************************************ */
/*! \name NIU Prametric Identifier Defines 
  @{ */
#define ISONL_PID_REQ_ALL               0x00u   /**< \brief  Used to request all statistic parameters */
#define ISONL_PID_BUFFER_SIZE           0x01u   /**< \brief  Request buffer size (bytes) */
#define ISONL_PID_MAX_DB_SIZE           0x02u   /**< \brief  Request maximum filter database size (bytes) */
#define ISONL_PID_NO_DB_ENTRIES         0x03u   /**< \brief  Request number of filter database entries */
#define ISONL_PID_MAX_MSG_RECEIVED      0x04u   /**< \brief  Request maximum number of messages, that can be received per second */
#define ISONL_PID_MAX_MSG_FORWARDED     0x05u   /**< \brief  Request maximum number of messages, that can be forwarded per second */
#define ISONL_PID_MAX_MSG_FILTERED      0x06u   /**< \brief  Request maximum number of messages, that can be filtered per second */
#define ISONL_PID_MAX_TRANSIT_DELAY     0x07u   /**< \brief  Request maximum transit delay time (ms) */
#define ISONL_PID_AVG_TRANSIT_DELAY     0x08u   /**< \brief  Request average transit delay time (ms) */
#define ISONL_PID_NO_MSG_OVERFLOW       0x09u   /**< \brief  Request number of messages lost due to buffer overflow */
#define ISONL_PID_NO_MSG_EXCESS_DELAY   0x0Au   /**< \brief  Request number of messages with excess transit delay */
#define ISONL_PID_AVG_MSG_RECEIVED      0x0Bu   /**< \brief  Request average number of messages received per second */
#define ISONL_PID_AVG_MSG_FORWARDED     0x0Cu   /**< \brief  Request average number of messages forwarded per second */
#define ISONL_PID_AVG_MSG_FILTERED      0x0Du   /**< \brief  Request average number of messages filtered per second */
#define ISONL_PID_UPTIME                0x0Eu   /**< \brief  Request uptime since last power on reset (seconds) */
#define ISONL_PID_NO_PORTS              0x0Fu   /**< \brief  Request number of ports */
#define ISONL_PID_NIU_TYPE              0x10u   /**< \brief  Request network interconnection unit type */
/*! @} */

/* ************************************************************************ */
/*! \name Miscellaneous NIU Defines 
  @{ */

#define ISONL_TR_NO_RATE            0xFFu   /**< \brief  no transfer rate reduction (PGN/Name filter entry)*/

/*! @} */

#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

/* ************************************************************************ */
/*! \brief Port pair status */
typedef struct 
{
    iso_u16  u16ModeOptions;     /**< \brief NIU Mode - Bits 0..1: #ISONL_NIU_Disabled, #ISONL_NIU_Bridge, #ISONL_NIU_Router, #ISONL_NIU_Autodetection */         
    iso_u16  u16Status;          /**< \brief NIU Status Bits 0..1: #ISONL_NIU_Disabled, #ISONL_NIU_Bridge, #ISONL_NIU_Router */
    iso_u8   u8PortPair;         /**< \brief Bits 0..3: lower port numer, Bits 4..7: higher port number */
} ISO_NL_PORTPAIR_STATUS_T;

/* ************************************************************************ */
/*! \brief Filter database status */
typedef struct 
{
    iso_u8   u8State;            /*!< \brief Filter database status: On of the NIU data state flags. */
    iso_u8   u8PortPair;         /*!< \brief Bits 0..3: to port, Bits 4..7: from port */ 
    iso_u8   u8FilterMode;       /**< \brief NIU Filter Mode: #ISONL_FM_BLOCK_SPECIFIC, #ISONL_FM_PASS_SPECIFIC */
    iso_s16  s16EntryCount;      /*!< \brief Number of filter database entries (PGN and PGN/Name). */ 
} ISO_NL_FILTER_DB_STATUS_T;

/* ************************************************************************ */
/*! \brief Filter database PGN/Name entry */
typedef struct 
{
    iso_u8   u8State;            /*!< \brief Filter entry status: On of the NIU data state flags. */
    iso_u8   u8EntryType;        /*!< \brief Filter entry type value: #ISONL_PGN_ENTRY or #ISONL_PGN_NAME_ENTRY */
    iso_u8   u8PortPair;         /*!< \brief Bits 0..3: to port, Bits 4..7: from port */ 
    iso_u32  u32PGN;             /*!< \brief PGN: Parameter group name */ 
    iso_u8   au8Name[8];         /*!< \brief CF network name */ 
    iso_u8   au8NameMask[8];     /*!< \brief CF network name mask */ 
    iso_u8   u8MaxTransferRate;  /*!< \brief Max messages per second - Range: 1..255 (Default: #ISONL_TR_NO_RATE (255)) */ 
} ISO_NL_FILTER_ENTRY_T;

/* ************************************************************************ */
/*! \brief Filter database entry */
typedef struct 
{
    iso_u8                   u8State;        /*!< \brief Filter database entry state: On of the NIU data state flags. */
    iso_u8                   u8PortPair;     /*!< \brief Bits 0..3: to port, Bits 4..7: from port */
    iso_u8                   u8FilterMode;   /**< \brief NIU Filter Mode: #ISONL_FM_BLOCK_SPECIFIC, #ISONL_FM_PASS_SPECIFIC */
    iso_s16                  s16EntryCount;  /*!< \brief Number of filter database entries (PGN and PGN/Name). */ 
    ISO_NL_FILTER_ENTRY_T*   pasEntries;     /*!< \brief Null pointer or pointer to a ISO_NL_FILTER_ENTRY_T array. */ 
} ISO_NL_FILTER_DB_T;


/* ************************************************************************ */
/*! \brief Typedef of the callback message data structure.

*/
typedef struct 
{
    iso_u8                  u8MsgType;          /*!< \brief NIU callback message type \n (#ISONL_MSG_REQUEST, #ISONL_MSG_FINISHED) */ 
    iso_u8                  u8MsgFunctionCode;  /*!< \brief NIU message function code */
    iso_u8                  u8PortPair;         /*!< \brief Bits 0..3: to port, Bits 4..7: from port */

    iso_u8                  u8ReceiverPort;     /*!< \brief CAN port on which the message received */

    ISO_TPREP_E             eTpStatus;          /*!< \brief TP Status */
    ISO_TPINFO_T*           psTpInfo;           /*!< \brief Pointer to the TP message */

} ISO_NL_CBDATA_T;

/* ************************************************************************ */

/* ************************************************************************ */
/*! \brief Typedef call back function for notifying the application.

    The ISO_NL_CBDATA_t data pointer and the referenced data are only valid during the call back.
    If the application return a value unequal to E_NO_ERR the service cancel the current action.
    \param[in,out]  \wp{psData, ISO_NL_CBDATA_T*} 
                    Pointer to the callback message data.
    \retval         iso_s16
*/
typedef iso_s16 (*ISO_NL_CbAppFunc_t)( ISO_NL_CBDATA_T* psData ); 

/* ************************************************************************ */
/*! \brief Typedef call back function for transmiting CAN Messages 

    In the error case the application should return a value unequal to E_NO_ERR.

    \param[in]  \wp{u8CanIdx, iso_u8}   
                CAN node index \n
                Range: 0 .. < ISO_CAN_NODES 
    \param[in]  \wp{u32Id,  iso_u32}        
                CAN message identifier
    \param[in]  \wp{pau8Data, iso_u8*}    
                Pointer to CAN message data array
    \param[in]  \wp{u8Length, iso_u8}      
                Number of CAN message data bytes \n 
                Range: 0 .. 8
    \retval     iso_s16
                - E_NO_ERR
                - E_UNKNOWN_ERR - sending is not possible
*/
typedef iso_s16 (*ISO_NL_CbCanMsgSendFunc_t)( iso_u8 u8CanIdx, iso_u32 u32Id, iso_u8* pau8Data, iso_u8 u8Length );

/* ************************************************************************ */
/*! @} */   /* END niutypedef                                               */
/* ************************************************************************ */
/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */
/*! \addtogroup    niuapi
  @{ 
    \name NIU-Service Initialization 

    Use this functions to initialize the NIU Service
  @{ 
*/
/* ************************************************************************ */

/* ************************************************************************ */
/*!
   \brief       This function installs the necessary callback function
   \param[in]   \wp{pCbAppFunction, ISO_NL_CbAppFunc_t}       
                Pointer to (callback-)function for notifying the application. 
   \param[in]   \wp{pCbCanMsgSendFunction, ISO_NL_CbCanMsgSendFunc_t}     
                Pointer to (callback-)function for sendung (transmiting) CAN messages to an other can network. \n
                If NULL the standard CAN send callback functions are used. 
   \retval      iso_s16                        
                - E_NO_ERR 
                - E_RANGE   - pCbAppFunction is a NULL pointer 
                - E_CONFIG  - NIU module not available  
    \details    Call this function before using any other NIU function.
*/
/* ************************************************************************ */
ISO_CORE_API
iso_s16  iso_NiuInit( ISO_NL_CbAppFunc_t pCbAppFunction, ISO_NL_CbCanMsgSendFunc_t pCbCanMsgSendFunction );

/* ************************************************************************ */
/*! \brief Use this function to configure the NIU behavior 
    \param[in]  \wp{u16Param, iso_u16}       
                Configuration parameter. 
    \param[in]  \wp{u16Value, iso_u16}       
                Configuration parameter value. 
    \retval     iso_s16                        
                - E_NO_ERR
                - E_RANGE   - u16Param is not valid
                - E_CONFIG  - NIU module not available  

    \par Sample:
    \code
    iso_s16              s16Ret = E_NO_ERR; 

    s16Ret = iso_NiuSetParam( NIU_PARAM_BRIDGE_ALL, NIU_VAL_OFF );
    s16Ret = iso_NiuSetParam( NIU_PARAM_ROUTE_GLOBAL, NIU_VAL_ON );
    s16Ret = iso_NiuSetParam( NIU_PARAM_ROUTE_FILTER, NIU_VAL_OFF );
    \endcode
*/
ISO_CORE_API
iso_s16  iso_NiuSetParam( iso_u16 u16Param, iso_u16 u16Value );

/* ************************************************************************ */
/*! \brief This function returns the configured value for given parameter 
    \param[in]  \wp{u16Param, iso_u16}       
                Configuration parameter. 
    \retval     iso_u16                        
                - NIU_RET_ERROR in case of an error (u16Param is not valid) 
                - Configuration parameter value 
*/
ISO_CORE_API
iso_u16  iso_NiuGetParam( iso_u16 u16Param );


/* ************************************************************************ */
/*! @} */
/*! @} */
/* ************************************************************************ */
/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */
/*! \addtogroup    niuapi 
  @{ 
    \name NIU-Service Configuration

    Use this functions to configure the NIU Service ports and bindings
  @{
*/
/* ************************************************************************ */

/* ************************************************************************ */
/*! \brief Configure the binding between two NIU CAN ports  
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair. 
    \param[in]  \wp{u16ModeOptions, iso_u16}
                NIU type for this binding - Values:
                - ISONL_NIU_Disabled 
                - ISONL_NIU_Bridge
                - ISONL_NIU_Router
                - ISONL_NIU_Autodetection 
    \retval iso_s16 E_NO_ERR or E_RANGE

    \details Use this function to enable the NIU functionality between two CAN ports. \n
             The port binding between two ports has no direction. \n
             The binding between #ISONL_Port_2 and #ISONL_Port_1 is equal to \n 
             the binding between #ISONL_Port_1 and #ISONL_Port_2.
    
    \par Sample:
    Configure the binding between the CAN ports  ISONL_Port_1 and ISONL_Port_2 
    as bridge without message filtering ("Repeater Mode"): 
    \code
    iso_s16              s16Ret; 
    iso_u16              u16ModeOptions;
    iso_u8               u8PortPair;
    ISO_NL_FILTER_DB_T  sFilterDB;

    u8PortPair     = iso_NiuBuildPortPair( ISONL_Port_2, ISONL_Port_1 );
    u16ModeOptions = ISONL_NIU_Bridge;
    s16Ret = iso_NiuSetPortBinding( u8PortPair, u16ModeOptions );
    if( s16Ret == E_NO_ERR )
    {
        u8PortPair = iso_NiuBuildPortPair( ISONL_Port_1, ISONL_Port_2 );
        s16Ret     = iso_NiuBuildFilterDB( & sFilterDB, u8PortPair, ISONL_FM_BLOCK_SPECIFIC );
        s16Ret    |= iso_NiuSetFilterDB( & sFilterDB );

        u8PortPair = iso_NiuBuildPortPair( ISONL_Port_2, ISONL_Port_1 );
        s16Ret    |= iso_NiuBuildFilterDB( & sFilterDB, u8PortPair, ISONL_FM_BLOCK_SPECIFIC );
        s16Ret    |= iso_NiuSetFilterDB( & sFilterDB );
        
        if( s16Ret != E_NO_ERR )
        {
            s16Ret = iso_NiuSetPortBinding( u8PortPair, ISONL_NIU_Disabled );
        }
    }
    \endcode
*/
ISO_CORE_API
iso_s16 iso_NiuSetPortBinding( iso_u8 u8PortPair, iso_u16 u16ModeOptions);

/* ************************************************************************ */
/*! \brief Get the status of the binding between two NIU CAN ports  
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair. 
    \param[in,out]  \wp{psStatus, ISO_NL_PORTPAIR_STATUS_T*}
                Pointer to the status structure
    \retval iso_s16 E_NO_ERR or E_RANGE
*/
ISO_CORE_API
iso_s16 iso_NiuGetStatus( iso_u8 u8PortPair, ISO_NL_PORTPAIR_STATUS_T* psStatus );


/* ************************************************************************ */
/*! \brief Set the NIU-Service management member (CF) for a valid port 

    \param[in]  \wp{u8Port, iso_u8}       
                Valid port pair. 
    \param[in]  \wp{u16Options, iso_u16}
                #ISONL_Port_Enabled, #ISONL_Port_Disabled
    \param[in]  \wp{u8WishedSA, iso_u8}
                CF source address
    \param[in]  \wpp{pau8Name, const #ISO_CF_NAME_T*}
                Pointer to the CF name ( 8 iso_u8 array )

    \retval iso_s16 E_NO_ERR, E_RANGE or E_OVERFLOW if the user list is full
    
    \details The function enables the external NIU management for a port. \n
    The NIU also announce the CF on the network.

*/
ISO_CORE_API
iso_s16 iso_NiuSetPortMember( iso_u8 u8Port, iso_u16 u16Options, iso_u8 u8WishedSA, const ISO_CF_NAME_T* pau8Name );

/* ************************************************************************ */
/*! \brief Set the NIU-Service management member (CF) for a valid port 
    \param[in]  \wp{u8Port, iso_u8}       
                Valid port pair. 
    \param[in]  \wp{u16Options, iso_u16}
                #ISONL_Port_Enabled, #ISONL_Port_Disabled
    \param[in]  \wp{s16MnHandle, iso_s16}
                Valid CF member handle
    \retval iso_s16 E_NO_ERR or E_RANGE 

    \details The function enables the external NIU management for a port. \n
    The CF must be already announced.
*/
ISO_CORE_API
iso_s16 iso_NiuSetPortToMember( iso_u8 u8Port, iso_u16 u16Options, iso_s16 s16MnHandle );

/* ************************************************************************ */
/*! \brief Returns the NIU-Service management member handle for a given port 
    \param[in]  \wp{u8Port, iso_u8}       
                Valid port. 
\retval iso_s16 CAN network member handle or HANDLE_UNVALID in case of an error
*/
ISO_CORE_API
iso_s16 iso_NiuGetPortMember( iso_u8 u8Port );

/* ************************************************************************ */
/*! @} */
/*! @} */
/* ************************************************************************ */
/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */
/*! \addtogroup    niuapi 
  @{
    \name NIU-Service Filter Management Functions 
    \brief Use this functions to manage the filter databases
    \details Make shure that you setup always two filter databases 
             for one port binding (One for each direction). 

  @{ 
*/
/* ************************************************************************ */

/* ************************************************************************ */
/*! \brief Get the filter database entry for a valid port pair
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair. 
    \param[out]  \wp{psFilterDB, ISO_NL_FILTER_DB_T*}       
                Pointer to a filter DB entry structure. 
    \retval iso_s16 E_NO_ERR or E_RANGE
    
    \details The function fills a ISO_NL_FILTER_DB_T structure with the current filter DB settings for the given port pair.
    
    \par Sample:
    Get the filter database settings for filtering CAN message from ISONL_Port_2 to ISONL_Port_1
    \code
    iso_s16              s16Ret;
    iso_u8               u8PortPair;
    ISO_NL_FILTER_DB_T  sFilterDB;

    u8PortPair = iso_NiuBuildPortPair( ISONL_Port_2, ISONL_Port_1 );
    s16Ret = iso_NiuGetFilterDB( u8PortPair, & sFilterDB );
    if( s16Ret == E_NO_ERR )
    {
        app_SaveNiuFilterDB( & sFilterDB ); 
    }
    \endcode

*/
ISO_CORE_API
iso_s16 iso_NiuGetFilterDB( iso_u8 u8PortPair, ISO_NL_FILTER_DB_T* psFilterDB);

/* ************************************************************************ */
/*! \brief Get the current number of filter database entries. 
    \retval iso_s16 Number of filter database entries or E_CONFIG.
*/
ISO_CORE_API
iso_s16 iso_NiuGetFilterDBCount( void );

/* ************************************************************************ */
/*! \brief Get the filter database entry for a valid index 
    \param[in]  \wp{s16Index, iso_s16}       
                Valid array index. \n
                Range: 0 .. iso_NiuGetFilterDBCount() - 1
    \param[out]  \wp{psFilterDB, ISO_NL_FILTER_DB_T*}       
                Pointer to a filter DB entry structure. 
    \retval sin16 E_NO_ERR or E_RANGE

    \details The function fills a ISO_NL_FILTER_DB_T structure with the current filter DB settings for the given port pair.

    \par Sample:
    Get all filter databases for saving...
    \code
    iso_s16 s16I, s16C, s16Ret;
    ISO_NL_FILTER_DB_T sDB;

    s16C = iso_NiuGetFilterDBCount();
    for( s16I=0; s16I < s16C; i++ )
    {
        sDB. pasEntries = ISO_NULL_PTR; 
        s16Ret = iso_NiuGetFilterDBfromIndex( s16I, & sDB );
        if( s16Ret == E_NO_ERR )
        {
            app_SaveNiuFilterDB( & sDB );
        }
    }
    \endcode
*/
ISO_CORE_API
iso_s16 iso_NiuGetFilterDBfromIndex( iso_s16 s16Index, ISO_NL_FILTER_DB_T* psFilterDB);

/* ************************************************************************ */
/*! \brief Get the filter database status for a valid port pair 
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair. 
    \param[out]  \wp{psStatus, ISO_NL_FILTER_DB_STATUS_T*}       
                Pointer to a filter DB status structure. 
    \retval iso_s16 E_NO_ERR or E_RANGE
*/
ISO_CORE_API
iso_s16 iso_NiuGetFilterDBStatus( iso_u8 u8PortPair, ISO_NL_FILTER_DB_STATUS_T* psStatus);

/* ************************************************************************ */
/*! \brief Set the filter database entry for a valid port pair
    \param[in]  \wpp{psFilterDB, const #ISO_NL_FILTER_DB_T*}       
                Pointer to a filter DB entry structure. 
    \retval iso_s16 E_NO_ERR, E_RANGE, E_CONFIG
    
    \details This function configures the filter database settings for the given port pair.
    See iso_NiuSetPortBinding() for a simple exsample.

*/
ISO_CORE_API
iso_s16 iso_NiuSetFilterDB( const ISO_NL_FILTER_DB_T* psFilterDB);

/* ************************************************************************ */

/* ************************************************************************ */
/*! \brief Get the PGN or PGN/Name filter entry for a valid index 
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair or ISONL_PP_GLOBAL.
    \param[in]  \wp{s16Index, iso_s16}       
                Index of the PGN filter entry. \n
                Range: 0 <= s16Index < iso_NiuGetFilterEntryCount( u8PortPair )
    \param[out]  \wp{psFilterEntry, ISO_NL_FILTER_ENTRY_T*}       
                Pointer to a PGN filter entry structure. 
    \retval iso_s16 E_NO_ERR, E_RANGE or E_CONFIG

    \details todo...

*/
ISO_CORE_API
iso_s16 iso_NiuGetFilterEntry( iso_u8 u8PortPair, iso_s16 s16Index, ISO_NL_FILTER_ENTRY_T* psFilterEntry);

/* ************************************************************************ */
/*! \brief Returns the current number of filter entries in the PGN table for a given port pair.
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair or ISONL_PP_GLOBAL to get the number of all entries. 
    \retval iso_s16 Number of PGN and PGN/Name filter entries or E_RANGE.
*/
ISO_CORE_API
iso_s16 iso_NiuGetFilterEntryCount( iso_u8 u8PortPair);

/* ************************************************************************ */
/*! \brief Set a PGN or PGN/Name filter entry for a valid port pair 
    \param[in]  \wpp{psFilterEntry, const #ISO_NL_FILTER_ENTRY_T*}       
                Pointer to a vaild PGN filter entry structure. 
    \retval iso_s16 
                - E_RANGE or E_CONFIG in case of an error
                - 0 Entry updated or already deleted
                - 1 Entry created or deleted
*/
ISO_CORE_API
iso_s16 iso_NiuSetFilterEntry( const ISO_NL_FILTER_ENTRY_T* psFilterEntry);

/* ************************************************************************ */
/*! @} */
/*! @} */
/* ************************************************************************ */
/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */
/*! \addtogroup    niuapi 
  @{
    \name NIU-Service Parametrics Management Functions 
    \brief Use this functions to manage the status and statistics values.
  @{ 
*/
/* ************************************************************************ */

/* ************************************************************************ */
/*! \brief Get the statistic value of a prametric identifier for a given port pair 
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair or #ISONL_PP_GLOBAL.
    \param[in]  \wp{u8ParamID, iso_u8}       
                Valid prametric identifier (#ISONL_PID_REQ_ALL is not allowed).

    \retval iso_u32 Value of the parametric identifier or 0xFFFFFFFFuL if not available.
*/
ISO_CORE_API
iso_u32 iso_NiuGetStatistic( iso_u8 u8PortPair, iso_u8 u8ParamID);

/* ************************************************************************ */
/*! \brief Set the statistic value of a prametric identifier for a given port pair 
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair or #ISONL_PP_GLOBAL.
    \param[in]  \wp{u8ParamID, iso_u8}       
                Valid prametric identifier (#ISONL_PID_REQ_ALL is not allowed).
    \param[in]  \wp{u32Value, iso_u32}       
                Value of the parametric identifier.

    \retval iso_s16 E_NO_ERR or ISONL_RET_NOT_VALID
*/
ISO_CORE_API
iso_s16 iso_NiuSetStatistic( iso_u8 u8PortPair, iso_u8 u8ParamID, iso_u32 u32Value);

/* ************************************************************************ */
/*! \brief Reset the reset able statistic values for a given port pair 
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair.

    \retval iso_s16 E_NO_ERR or ISONL_RET_NOT_VALID
*/
ISO_CORE_API
iso_s16 iso_NiuResetStatistic( iso_u8 u8PortPair );

/* ************************************************************************ */
/*! @} */
/*! @} */
/* ************************************************************************ */
/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */
/*! \addtogroup    niuapi 
  @{
    \name NIU-Helper Functions 
    \ingroup    niuapi 
  @{ 
*/
/* ************************************************************************ */

/* ************************************************************************ */
/*! \brief Build the port pair value for the two CAN ports numbers. 
    \param[in]  \wp{fromPort, iso_u8}       
                Valid source port number.
    \param[in]  \wp{toPort, iso_u8}       
                Valid destination port number.
    \retval iso_u8 port pair
*/
ISO_CORE_API
iso_u8 iso_NiuBuildPortPair( iso_u8 fromPort, iso_u8 toPort );

/* ************************************************************************ */
/*! \brief Build / Intialize the filter database entry structue
    \param[in,out]  \wp{psFilterDB, ISO_NL_FILTER_DB_T*}       
                Pointer to a filter DB entry structure. 
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair.
    \param[in]  \wp{u8FilterMode, iso_u8}       
                #ISONL_FM_BLOCK_SPECIFIC or #ISONL_FM_PASS_SPECIFIC.
    \retval iso_s16 E_NO_ERR, E_RANGE
*/
ISO_CORE_API
iso_s16 iso_NiuBuildFilterDB( ISO_NL_FILTER_DB_T* psFilterDB, iso_u8 u8PortPair, iso_u8 u8FilterMode );

/* ************************************************************************ */
/*! \brief Build / Intialize a PGN filter entry sturcture. 
    \param[in,out]  \wp{psFilterEntry, ISO_NL_FILTER_ENTRY_T*}       
                Pointer to a vaild PGN filter entry structure.
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair.
    \param[in]  \wp{u32PGN, iso_u32}       
                Valid parameter group number .
    \retval iso_s16 E_NO_ERR
*/
iso_s16 iso_NiuBuildPGNEntry(ISO_NL_FILTER_ENTRY_T* psFilterEntry, iso_u8 u8PortPair, iso_u32 u32PGN);

/* ************************************************************************ */
/*! \brief Build / Intialize a PGN/Name filter entry sturcture. 
    \param[in,out]  \wp{psFilterEntry, ISO_NL_FILTER_ENTRY_T*}       
                Pointer to a vaild PGN filter entry structure.
    \param[in]  \wp{u8PortPair, iso_u8}       
                Valid port pair.
    \param[in]  \wp{u32PGN, iso_u32}       
                Valid parameter group number.
    \param[in]  \wpp{pau8Name, const iso_u8 []}       
                Pointer to a valid CF NAME array.
    \param[in]  \wpp{pau8Mask, const iso_u8 []}       
                Pointer to a valid NAME mask array.
    \retval iso_s16 E_NO_ERR
*/
ISO_CORE_API
iso_s16 iso_NiuBuildPGNNameEntry( ISO_NL_FILTER_ENTRY_T* psFilterEntry, iso_u8 u8PortPair, iso_u32 u32PGN, 
                                 const iso_u8 pau8Name[], const iso_u8 pau8Mask[]);


/* ************************************************************************ */
/*! @} */
/*! @} */
/* ************************************************************************ */
/* ************************************************************************ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_MnNiu_H */

/* ************************************************************************ */
