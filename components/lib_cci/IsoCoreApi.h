/* ************************************************************************ */
/*!
   \file
   \brief       ISOBUS ECU driver core functions
   \details     Contain the core driver API functions

   \author      Wegscheider Peter
   \date        Created 07.02.2018

   \copyright   Competence Center ISOBUS e.V.

   \par  History:
   \par
   27.02.2015 - author P. Wegscheider
   - added
   \par
   07.04.2016 - author P. Wegscheider
   - added IsoDrvGetTimeMs()
   - Feature request ID 3846 - Added CFG_PARAM_REQ_FOR_ACL_ONCE, CFG_PARAM_IGNORE_SELF_CONFIG
   \par
   25.01.2018 - author P. Wegscheider
   - Feature ID 7493: ETP Transfer option using "file read / write". (for APA AUX) \n
      - Added optional define ISO_ETP_IN_PKG to enable this special mode for receiving ETPs.
      - Added functions iso_DlSetETPMemoryExCb() and iso_DlSetETPFlushMemoryCb() 
        to set the needed callback functions.
   \par
   07.02.2018 - author P. Wegscheider
   - Feature request ID 7504: Split Base Driver into "Core" and "Base"
      - Moved code and history from IsoBaseApi.h to IsoCoreApi.h
   \par
   14.02.2018 - author P. Wegscheider
   - Feature request ID 7528: add a user parameter to CF and PGN callback functions
   \par
   28.02.2018 - author P. Wegscheider
   - Feature request ID 7504: Added API function iso_NmMemberAdd()
   \par
   05.03.2018 - author P. Wegscheider
   - Feature request ID 8263: Added API function iso_NmChangeSourceAddress()
   - Feature request ID 8115: Added API function IsoNmMember_SetPresenceTimeout()
   \par
   07.03.2018 - author P. Wegscheider
   - Feature request ID 8305, 8275: Consolidation of the "ETP memory" functionality\n
     Removed ISO_ETP_Memory_fpt and iso_CoreSetETPMemoryCb() declarations and \n
     renamed ISO_ETP_MemoryEx_fpt to ISO_ETP_Memory_fpt and \n
     iso_CoreSetETPMemoryExCb() with iso_CoreSetETPMemoryCb(). \n
     Marked iso_CoreSetETPFlushMemoryCb() optional/deprecated since the data
     can now also forwarded for ISO_ETP_IN_PKG with TP status record_etp_in_pkg. 
   \par
   08.06.2018 - author P. Wegscheider
   - Feature request ID 7504: Moved internal CF network and data link callbacks from Core to Base.
   \par
   12.06.2018 - author P. Wegscheider
   - Feature request ID 8459: use iso_u8 for ISOBUS addresses in API
   \par
   14.06.2018 - author P. Wegscheider
   - Feature request ID 8424: use ISO_CF_NAME_T in API functions
   \par
   24.07.2018 - author P.Wegscheider
   - Feature request ID 8156: allow for optional usage of low level CAN FiFo channels. \n
     Can be enabled with the define CCI_ENABLE_CAN_CHANNEL_PRIO.
   \par
   10.08.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files
   \par
   28.08.2018 - author P. Wegscheider
   - BugID 8115: Renamed function IsoNmMember_SetPresenceTimeout() to iso_NmMemberSetPresenceTimeout()
   \par
   17.01.2019 - author P.Wegscheider
   - Feature request ID 9668: make CCI_CORE_MUTEX available as ISO_CORE_MUTEX.
   - Feature request ID 7913: Use settings of network management part 5 second edition as default \n
   \par
   29.11.2019 - author P.Wegscheider
   - Feature request ID 10185: refactor TL \n
     Updated iso_CoreInit() parameters
   \par
   20.02.2020 - author P.Wegscheider
   - Added function iso_NmReadListOfCfHandles()
   \par
   03.04.2020 - author P.Wegscheider
   - Feature request BugID 11634: add a function to enable / disable the drivers safe state \n
     Added functions iso_CoreSetState(), iso_CoreGetState() and iso_CoreSetCustomStateCb()
   \par
   27.08.2020 - author P.Wegscheider
   - Feature BugID 12562: Added API function iso_CoreSetCanSnifferCb() to set a callback function
     for forwarding external CF to external CF PDU1 CAN messages to the application.
   \par
   12.01.2021 - author P.Wegscheider
   - Feature BugID 12772: removed deprecated functions 
     iso_NmReadListOfInternHandles(), iso_NmReadListOfExternHandles(), iso_NmReadListOfExtHandWithFunc() and iso_NmGetDataOfMember()
*/
/* ************************************************************************ */

#ifndef DEF_ISO_CORE_API_H
#define DEF_ISO_CORE_API_H

/* include configuration and common driver definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* ************************************************************************ */
/*! 
   \ingroup core_general
   \brief         Returns the current time since startup in milliseconds
   \retval        iso_s32
                  Time stamp in milliseconds

   The function uses the application-specific function of time, which was passed with iso_DlCallbacksInit().
*/
#if (!defined(ISO_CORE_MUTEX)) || defined(ISO_CORE_MUTEX_RECURSIVE)
ISO_CORE_API
#endif /* (!defined(ISO_CORE_MUTEX)) || defined(ISO_CORE_MUTEX_RECURSIVE) */
iso_s32 IsoDrvGetTimeMs(void);

/* Core Driver global functions  */
/** \addtogroup core_init Initialisation and Runtime 
*/
/**@{*/

/* ***************************************************************************************** */
/*!
    \brief        Core Driver initalisation.
                  This function installs the necessary callback functions
                  and initialises all core modules of the driver. 
                  The Base Driver modules and the Client modules have to be initialised separately 
                  with iso_BaseInit() and iso_ClientsInit().

    \param[in]    \wp{pfGetTimeMs, ISO_CbGetTimeMs_t }  
                    Pointer to the application specific timestamp callback function.
    \param[in]    \wp{pfTriggerWatchdog, ISO_CbTriggerWatchdog_t}  
                     Pointer to the watchdog trigger callback function or NULL pointer if not needed.
    \param[in]    \wp{pfErrorHandler, ISO_CbErrorHandler_t}
                     Pointer to the  error handler callback function or NULL pointer.  \n 
                     ( see also IsoErrorOut() and \ref errorhand for more information ) 

    \param[in]    \wp{pfCanSend, ISO_DL_CbCanSend_t}  
                     CAN message send callback function pointer
    \param[in]    \wp{pfGetFreeCanSendFiFo, ISO_DL_CbGetFreeCanSendFiFo_t}  
                     Get available CAN message FIFO size callback function pointer or NULL pointer 

    \param[in]    \wp{pfDoMsg, ISO_CoreBase_CbDoMsg_t}  
                     Pointer to the Base Driver CAN message distribution function. \n
                     Use IsoCbBaseDataDistributor() if base and core are located in the same thread. 
    \param[in]    \wp{pfIsoNetwork, ISO_CoreBase_CbIsoNetwork_t}  
                     Network event callback function pointer. \n
                     This callback is called to forward the network events to the the CFs. \n
                     Use IsoCbBaseNetworkDistributor() if base and core are located in the same thread.  
    \param[in]    \wp{fpTpFilterCb, ISO_TP_Filter_fpt}
                     Pointer to the callback function or NULL pointer. \n
                     For more information see #ISO_TP_Filter_fpt.

    \retval         iso_s16
                    - #E_NO_ERR on success
                    - #E_RANGE if rpfTime or pfCanSend is a NULL pointer
                    - #E_WARN Only pfDoMsg or pfIsoNetwork is used the other is a NULL pointer (unusual configuration)  
*/
ISO_CORE_API
iso_s16 iso_CoreInit(
   ISO_CbGetTimeMs_t pfGetTimeMs,
   ISO_CbTriggerWatchdog_t pfTriggerWatchdog, /* optional */
   ISO_CbErrorHandler_t pfErrorHandler, /* optional */
   ISO_DL_CbCanSend_t pfCanSend,
   ISO_DL_CbGetFreeCanSendFiFo_t pfGetFreeCanSendFiFo, /* optional */
   ISO_CoreBase_CbDoMsg_t pfDoMsg,  /* IsoCbBaseDataDistributor (default for single threaded) */
   ISO_CoreBase_CbIsoNetwork_t pfIsoNetwork, /* IsoCbBaseNetworkDistributor (default for single threaded) */
   ISO_TP_Filter_fpt fpTpFilterCb );  /* optional */

/* ********************************************************************* */
/*!
   \brief       Core driver cyclic function

   This function executes the cyclic functions of all modules of the minimal core driver.

   \par
    Time behaviour: This function should called about every 10ms or faster. \n
    Calling this function and iso_CoreCanMsgRec() must be single threaded. 
*/
ISO_CORE_API
void iso_CoreCyclic(void);


 /* ********************************************************************* */
 /*!
    \brief         Initialising of the repetition value of the TP in one loop

    \param[in]    \wp{u8CanIdx, iso_u8}  
                   CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 ) \n
                   At the moment the value has to be set to ISO_CAN_VT       
    \param[in]    \wp{s16TPSpeed, iso_s16}  
                   Number of TP cyclic calls in one loop to adapt the TP busload on the used hardware \n  
                   Range: 1 - about 10 (depends on CAN-buffer, bus traffic, network partner ..) \n
                   Default: 1         
    \retval       iso_s16                        
                   - #E_NO_ERR on success    
 */
ISO_CORE_API
iso_s16 iso_CoreTPRepeatSet( iso_u8 u8CanIdx, iso_s16 s16TPSpeed );

 /* ********************************************************************* */
 /*!
    \brief         The driver gets a single received message of CAN bus

       With this function gets the driver a single message of the CAN bus. This 
       message is analysed and processed immediatly. 

    \param[in]    \wp{u8CanIdx, iso_u8}  
                   CAN-bus number 0, 1, ..., ( ISO_CAN_NODES - 1 )
    \param[in]    \wp{u32Id, iso_u32}  
                   (29bit)-CAN-Identifier \n
                    Range: 0 - 0x1FFFFFFF
    \param[in]    \wpp{apu8Data, const iso_u8[]}  
                   Pointer to received data array
    \param[in]    \wp{u8Length, iso_u8}   
                   Number of received bytes \n
                   Range: 0 - 8
    \note  \par
       The received message is routed to the correct instance into the
       corresponding module. Most PDU2 messages are given to the application
       over the multi node application layer module. Calling this function and iso_DlCyclicGlobal()
       must be single threaded. For multi thread this function must be locked.
 */
ISO_CORE_API
 void  iso_CoreCanMsgRec(iso_u8 u8CanIdx, iso_u32 u32Id, const iso_u8 apu8Data[], iso_u8 u8Length );


/* ************************************************************************ */
/** \brief Function for returning the current free available CAN message FIFO size.
    \details This function calls only the callback function which is given to the driver with iso_DlDrvCanInit()
    \param[in]    \wp{u8CanIdx, iso_u8}
                  CAN-bus index number \n
                  Range: 0u .. ( ISO_CAN_NODES - 1u )
    \param[in]    \wp{u8MsgPrio, iso_u8}
                  An ISO 11783 CAN message priority \n
                  The priority corresponds to the the priority bits 26 to 28 of a can message ID.
    \retval       iso_s16
                  -   0 .. 0x7FFF available FIFO
                  - < 0 in case of an error
                  - #E_COM on bus-off

*/
ISO_CORE_API
iso_s16 iso_CoreGetSendMsgFiFoSize(iso_u8 u8CanIdx, iso_u8 u8MsgPrio);

#if defined(CCI_SNIFFER) || defined (DOXYGEN)

/* ************************************************************************ */
/** \brief type definiton for the callback function to forward PDU1 CAN messages of external CFs 
    \param[in] \wp{s16CfHndSender, iso_s16}
                Network member handle of the external sender
    \param[in] \wp{s16CfHndReceiver, iso_s16}
                Network member handle of the external receiver
    \param[in] \wpp{pau8Data, const #iso_u8[]}
                Pointer to the message data byte array or NULL pointer
    \param[in] \wp{u8DataSize, iso_u8}
                Size of the given message data byte array
*/
typedef void (*ISO_Core_CbDoExternalMsg_t)(
   iso_s16   s16CfHndSender,
   iso_s16   s16CfHndReceiver,
   iso_u32   u32PGN,
   const iso_u8 pau8Data[8], iso_u8 u8DataSize);

/* ************************************************************************ */
/** \brief Function to set the CAN message sniffer callback function.
    \details The callback function can be used to receive all CAN messages 
             from an external CF to another external CF that are not processed by the driver.
    \param[in] \wp{pfDoExternalMsg, ISO_Core_CbDoExternalMsg_t}
                  Pointer to the callback function or NULL pointer to disable the forwarding.
*/
ISO_CORE_API
void iso_CoreSetCanSnifferCb(ISO_Core_CbDoExternalMsg_t pfDoExternalMsg);


#endif /* defined(CCI_SNIFFER) || defined (DOXYGEN) */

/**@}*/


/* ************************************************************************ */
/* Core Driver work state functions  */
/** \defgroup core_state Safe State Functions
    \ingroup core_general

    \brief The core driver offers the application the possibility 
    to set the working state of the library at runtime.
    This can be used to ensure the safe state defined for the application for the ISOBUS.

*/
/**@{*/

/* ************************************************************************ */
/** \brief Core driver (safe) states */
typedef enum 
{ 
   IsoWorkState_Enabled  = 0,       /**< Process all CAN messages (default state) */
   IsoWorkState_Disabled = 1,       /**< Receiving and sending of all CAN messages is disabled (safe state) */
   IsoWorkState_AllowACL = 2,       /**< Receiving and sending of address claimed messages are allowed */
   IsoWorkState_AllowDiagACL = 3,   /**< Receiving and sending of diagnostic and address claimed messages  */
   IsoWorkState_IsobusDisabled = 4, /**< Receiving and sending of all CAN messages is disabled only on the ISOBUS CAN node (#ISO_CAN_VT) */
   IsoWorkState_Custom = 5          /**< Use callback function set with iso_CoreSetCustomStateCb() to check messages */
} ISO_WORK_STATE_E;

/* ************************************************************************ */
/*! \brief Type definition of the optional custom state CAN messages filter call back function

   If set with iso_CoreSetCustomStateCb() and enabled with iso_CoreSetState(IsoWorkState_Custom), 
   the callback function can be used to check incoming and outgoing CAN messages 
   and reject for this state disallowed messages. 

   \param[in]    \wp{u8CanIdx, iso_u8}  
                  CAN-bus number 0, 1, ..., ( ISO_CAN_NODES - 1 )
   \param[in]  \wp{u32PGN,  iso_u32}
                  PGN of the message \n 
                  or if #PGN_REQUEST_PGN or #PGN_N_ACK the containing PGN
   \param[in]  \wp{qIsTx,  iso_bool}
                  - #ISO_TRUE for outgoing messages which should be transmitted
                  - #ISO_FALSE for incoming messages

   \retval  iso_bool
               - #ISO_TRUE  - CAN message is allowed and can be processed
               - #ISO_FALSE - CAN message is not allowed and should not be processed

   Hint: See IsoData.c function DoFilterCanMessage() for an example.
*/
typedef iso_bool ( *ISO_State_CAN_Filter_fpt )(iso_u8 u8CanIdx,iso_u32 u32PGN, iso_bool qIsTx);


/* ************************************************************************ */
/*! \brief Function to set the work state of the ISOBUS deriver library

   \param[in]    \wp{eNewState, ISO_WORK_STATE_E}  
                  New work state

   \retval  iso_s16
               - #E_NO_ERR - on success
               - #E_CONFIG - for #IsoWorkState_Custom without setting a custom callback with iso_CoreSetCustomStateCb() \n
                 In this case the state is set to #IsoWorkState_Disabled (safe state)
*/
ISO_CORE_API
iso_s16 iso_CoreSetState(ISO_WORK_STATE_E eNewState);

/* ************************************************************************ */
/*! \brief Function to get the current work state

   \retval  ISO_WORK_STATE_E
            Current work state
*/
ISO_CORE_API
ISO_WORK_STATE_E iso_CoreGetState( void );

/* ************************************************************************ */
/*! \brief Function to set a custom CAN message filter callback function 

   This function is used to filter the CAN messages, if the work state is set
   to #IsoWorkState_Custom with the function iso_CoreSetState().

   \param[in]    \wp{fpCanFilterCb, ISO_State_CAN_Filter_fpt}  
                  Custom CAN message filter function (or NULL pointer)

   \retval  iso_s16
               - #E_NO_ERR - on success
               - #E_NOACT - if fpCanFilterCb is the NULL pointer 
                 and the current work state is #IsoWorkState_Custom 
*/
ISO_CORE_API
iso_s16 iso_CoreSetCustomStateCb( ISO_State_CAN_Filter_fpt fpCanFilterCb );

/*! \brief internal define (used for exposing functions) */
#define ISO_DLWSTATE_DEFINED

/**@}*/

/* ************************************************************************ */
/** \defgroup drivernodeconfig Part 5 Configuration
    \ingroup nmma

    \brief Use this defines and functions to configure the CAN node specific behavior. \n\n
    You can also add the define ISO_PART5_FE to your IsoConf.h file \n
    to enable the obsolete behavior of the first edition of Part 5 for all nodes (not recommended). \n

    \par Parameter and default settings
    - CFG_PARAM_PART5 - ISO Part 5:
        - CFG_VAL_PART5_FIRST_EDITON (0 = frist edition)
        - CFG_VAL_PART5_SECOND_EDITON (1 = second edition)
        - 2 = reserved
        - 3 = reserved
    - CFG_PARAM_COMMANDED_ADRESS - Commanded address message
        - CFG_VAL_OFF  = disabled (default for Part 5 SE)
        - CFG_VAL_ON   = enabled  (default for Part 5 first edition)
    - CFG_PARAM_ADDRESS_CLAIM - Send address claim
        - CFG_VAL_ON  = enabled ( ISO conform, default)
        - CFG_VAL_OFF = disabled ( e.g. diagnostic )
    - CFG_PARAM_EXTERNAL_ADDR_CLAIM - external address claim required
        - CFG_VAL_ON  = yes ( ISO conform, default)
        - CFG_VAL_OFF = no ( e.g. diagnostic )
    - CFG_PARAM_CANNOT_CLAIM_ADDRESS - On Request, respond with cannot claim source address
        - CFG_VAL_ON  = enabled ( ISO conform, is the default for Part 5 SE)
        - CFG_VAL_OFF = disabled ( to avoid bus off )
    - CFG_PARAM_CHECK_ADDR_VIOLATION - Check if an external msg has the same SA as an internal CF
        - CFG_VAL_ON  = enabled ( ISO conform, is the default for Part 5 SE)
        - CFG_VAL_OFF = disabled ( default for Part 5 first edition )
    - CFG_PARAM_REQ_FOR_ACL_ON_START - Request for ACL will be send on startup
        - CFG_VAL_ON  = enabled ( ISO conform, default)
        - CFG_VAL_OFF = disabled ( for simple ECUs. Used in combination with CFG_PARAM_EXTERNAL_ADDR_CLAIM )
    - CFG_PARAM_REQ_FOR_ACL_ONCE - Request for ACL will be send only for announcing the first CF
        - CFG_VAL_ON  = enabled ( #CFG_PARAM_REQ_FOR_ACL_ON_START must also be enabled, used to avoid unneeded messages )
        - CFG_VAL_OFF = disabled ( strict ISO conform, default)
    - CFG_PARAM_IGNORE_SELF_CONFIG - Ignore the self-configurable address bit of the NAME for detecting equal CFs
        - CFG_VAL_ON  = enabled ( Ignores the self-configurable bit of the NAME for equal check )
        - CFG_VAL_OFF = disabled ( strict ISO conform, default)

*/
/* ************************************************************************ */
/** \addtogroup drivernodeconfig
@{
*/
/* ************************************************************************ */
#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoCoreApi.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */

/* ************************************************************************ */
/** \name Configuration parameter (group)
@{
*/
#define CFG_PARAM_PART5                (0u)     /**< \brief ISO Part 5 (edition) settings  */
#define CFG_PARAM_COMMANDED_ADRESS     (2u)     /**< \brief Commanded address message settings  */

#define CFG_PARAM_ADDRESS_CLAIM        (3u)     /**< \brief Internal address claim message settings  */
#define CFG_PARAM_EXTERNAL_ADDR_CLAIM  (4u)     /**< \brief External address claim response settings  */
#define CFG_PARAM_CANNOT_CLAIM_ADDRESS (5u)     /**< \brief On Request, respond with cannot claim source address */
#define CFG_PARAM_CHECK_ADDR_VIOLATION (6u)     /**< \brief Check if an external msg has the same SA as an internal CF */
#define CFG_PARAM_REQ_FOR_ACL_ON_START (7u)     /**< \brief Request for ACL will be send on startup  */
#define CFG_PARAM_REQ_FOR_ACL_ONCE     (8u)     /**< \brief Request for ACL will be send only for announcing the first CF  */
#define CFG_PARAM_IGNORE_SELF_CONFIG   (9u)     /**< \brief Ignore the self-configurable address bit of the NAME for detecting equal CFs  */
/** @} */

/* ************************************************************************ */
/** \name Configuration common values
@{
*/
#define CFG_VAL_OFF 0x00u                   /**< \brief Configuration value: 0 = off, disabled, ...  */
#define CFG_VAL_ON  0x01u                   /**< \brief Configuration value: 1 = on, enabled, ...  */
#define CFG_RET_ERROR  0xFFFFu              /**< \brief Get return value: 0xFFFF = value not valid */
/** @} */

/* ************************************************************************ */
/** \name Configuration CFG_PARAM_PART5 specific values
@{
*/
#define CFG_VAL_PART5_FIRST_EDITON  0x00u   /**< \brief Network Management mode = ISO Part 5 - First edition  */
#define CFG_VAL_PART5_SECOND_EDITON 0x01u   /**< \brief Network Management mode = ISO Part 5 - Second edition  */
/** @} */

#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

/* ************************************************************************ */
/** \name Configuration Functions
@{
*/

/* ************************************************************************ */
/*!
    \brief         Set the CAN node specific driver configuration
    \param[in]     \wp{u8CanIdx, iso_u8}
                    CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )
    \param[in]     \wp{cfgParam, iso_u16 }
                    Configuration parameter  ( CFG_PARAM_xxx defines )
    \param[in]     \wp{cfgValue, iso_u16 }
                    Configuration value      ( CFG_VAL_xxx defines )
    \retval        iso_s16
                    - E_NO_ERR
                    - E_RANGE
    \par Sample
      iRet = iso_NodeConfigSet( ISO_CAN_VT, CFG_PARAM_PART5, CFG_VAL_PART5_SECOND_EDITON); \n
      iRet = iso_NodeConfigSet( ISO_CAN_VT, CFG_PARAM_COMMANDED_ADRESS, CFG_VAL_OFF);      \n
*/
ISO_CORE_API
iso_s16 iso_NodeConfigSet( iso_u8 u8CanIdx, iso_u16 cfgParam, iso_u16 cfgValue );

/* ************************************************************************ */
/*!
    \brief         Set the CAN node specific driver configuration
    \param[in]     \wp{u8CanIdx, iso_u8 }
                   CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )
    \param[in]     \wp{cfgParam, iso_u16 }
                    Configuration parameter  ( CFG_PARAM_xxx defines )

    \retval        iso_u16
                    - Current configuration value  ( CFG_VAL_xxx defines )
                    - CFG_RET_ERROR
    \par Sample
       uVal = iso_NodeConfigGet( ISO_CAN_VT, CFG_PARAM_PART5); \n
*/
ISO_CORE_API
iso_u16 iso_NodeConfigGet( iso_u8 u8CanIdx, iso_u16 cfgParam );

/** @} */   /* END name Configuration Functions */

/* ************************************************************************ */
/** @} */  /* END group drivernodeconfig - Driver / Node Configuration      */
/* ************************************************************************ */

/* Core Dl - Data link layer interface */
/** \addtogroup coredl Core DataLink Layer 
 @{
*/

/* ************************************************************************ */
/*!
   \brief      Sending of PGN messages to a destination 

   This function starts the sending of a PGN message to a receiver  \n
   In case of more than 8 bytes using of TP (or BAM) is included.

   \param[in]  \wp{u8Priori, iso_u8}
                  - Bits 0-3: Priority of PGN (normal default see J1939-71, ISO11783-7,8 ...) \n
                    Range: 0 - 7 
                  - Bits 4-7: Optional CAN channel priority. ( Must be enabled with the define CCI_ENABLE_CAN_CHANNEL_PRIO) \n 
                    Range: 0- 7 (0 means default channel priority)
   \param[in]  \wp{u32Pgn, iso_u32}
                  PGN of the CAN message \n
                  Range: 0 ... 0x3FFFF
   \param[in]  \wp{u32DataLength, iso_u32}
                  Number of data bytes to send
                  -    0 ..     8 : Single transport
                  -    9 ..  1785 : Transport protocol is automatic used \n
                  - 1786 .. ETP limit : not possible \n
                    For extended transport protocol use base driver function iso_DlPgnSend()
   \param[in]  \wpp{pu8Data, const #iso_u8 HUGE_C[]}
                  Pointer to data byte array
   \param[in]  \wp{s16HndSender, iso_s16}
                  Sender generally own intern CF handle
   \param[in]  \wp{s16HndReceiver, iso_s16}
                  Destination CF handle \n
                  HANDLE_GLOBAL for broadcast send
   \retval     iso_s16
               - #E_NO_ERR - Transfer is started
               - #E_OVERFLOW - Transfers are busy (buffer full)
               - #E_USER_ERROR - CF ( sender or receiver ) is not logged
               - #E_RANGE - Parameter not valid
               - #E_OVERFLOW on send FIFO full
               - #E_COM on bus-off
   \par
         - Attention: data >1785 bytes are not copied into the driver 
           and must be static in application.

   \par    
         With the define CCI_ENABLE_CAN_CHANNEL_PRIO the higher nibble of the parameter u8Priori
         can contain a CAN channel priority. This channel priority is forwarded to the application specific 
         CAN send callback function (#ISO_DL_CbCanSend_t) in the higher nibble of the parameter u8CanIdx.
*/
ISO_CORE_API
iso_s16 iso_CorePgnSend( iso_u8   u8Priori,      iso_u32  u32Pgn,
                         iso_u32  u32DataLength, const iso_u8 HUGE_C pu8Data[],
                         iso_s16  s16HndSender,  iso_s16  s16HndReceiver
                       );


/********************************************************************************/
/*!
   \brief         Reading the key switch state for starting the implement
   \param[in]    \wp{u8CanIdx, iso_u8}
                  CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )
   \retval  iso_u8
            Key switch state ( ISO_DISABLED, ISO_ENABLED, ISO_ERROR_INDI_2Bit, ISO_NOT_AVAILABLE_2Bit )
*/
ISO_CORE_API
iso_u8 iso_CoreKeySwitchStateRead(iso_u8 u8CanIdx);

/**@}*/

/* Nm - Network management interface */
/** \addtogroup nmma Network Management 
*/
/**@{*/

 /***********************************************************************/
 /*!
    \brief          A new (intern) logic network member is connected to the bus 

                    Start of the login of an intern ISO network member.

    \param[in]      \wp{u8CanIdx, iso_u8}
                     CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )   
    \param[in]      \wp{u8WishedSA, iso_u8}
                     Preferred ISO Source address of new user \n  
                     See ISO PART 1 - Annex C and D
    \param[in]      \wpp{au8Descript, const #ISO_CF_NAME_T*}
                     NAME of the new ISO user ( see IsoSetName() )
    \param[in]      \wp{eUserFunction, ISO_USERFUNC_e} 
                     Intern meaning of the ISO member \n
                     ( working_set_member, auxiliary, tractor_ecu ..)

     \retval         iso_s16      
                    - >= 0            CF handle of the network member
                    - #HANDLE_UNVALID Parameter error or user list is full
    \par  
       Core driver function without callbacks. Use iso_BaseMemberAdd() for adding Cfs with user parameter and callbacks. \n
       This function controls if the new user has been already entered in the user list. If yes nothing
       occurs except of an error message, if not the new user is entered. After calling the cyclic
       function of the ISO driver this user sends its address claim.
 */
ISO_CORE_API
iso_s16 iso_NmMemberAdd( iso_u8  u8CanIdx,
                         iso_u8  u8WishedSA,
                         const ISO_CF_NAME_T* au8Descript,
                         ISO_USERFUNC_e eUserFunction
                      );


 /* *************************************************************************** */
 /*!
    \brief          Add an extern network member manually to the user list 

                    The function can be used to add a external CF, 
                    that does not send a address claimed message, 
                    manually to the user array. \n
                    The added external CF is managed like a normal CF 
                    that has send an address claimed message.

    \param[in]      \wp{u8CanIdx, iso_u8}
                     CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )   
    \param[in]      \wp{u8SA, iso_u8}
                    Source address of the extern user / CF \n  
                    See ISO PART 1 - Annex C and D
    \retval         iso_s16                                
                    - #E_NO_ERR       Adding was successful    
                    - #E_OVERFLOW     Userlist is full
                    - #E_WARN         User is in list and active 
     \note   
          The use of this function is not ISO 11783 Part 5 conform. \n
          Use this function only if you must communicate with an external CF, \n
          that does not send a address claimed message. \n
          An address claimed message of an external CF with the same source address \n
          will replace this manual added member entry.  \n
          The function works independent from the configuration of the #CFG_PARAM_EXTERNAL_ADDR_CLAIM parameter. \n
          The added CF will be set to announced in the next iso_DlCyclicGlobal() run. 
 */
ISO_CORE_API
 iso_s16 iso_NmMbrExternAdd( iso_u8 u8CanIdx, iso_u8 u8SA );

/***********************************************************************/
/*!
    \brief         Function to deactivate a network member 
    \param[in]     \wp{s16MemHandle, iso_s16}
                   Handle to wished network member
    \retval        iso_s16                                
                    - #E_NO_ERR       delete of member successful 
                    - #E_USER_ERROR   Member not found
    \par Hint:
    The network member is not deleted from list. The entry is only set to inactive.
    If an external CF sends again the address claimed message, the entry will be reactivated. \n
    An internal CF should only be logged off after all used client instances of this CF (VTC, TCC, ...) 
    have been closed and removed.
*/
ISO_CORE_API
 iso_s16 iso_NmMemberLoggedOut( iso_s16 s16MemHandle );

/* ********************************************************************* */
/*! 
   \brief         An active (internal) network member is "logged out" 
                  and announced again using the new source address  
   \param[in]    \wp{s16CfHandle, iso_s16}
                  Handle of the internal network member
   \param[in]    \wp{u8NewSA, iso_u8}
                  New source address of the ISO user
   \param[in]    \wp{qTriggerLogoutEvent, iso_bool}
                  - if ISO_TRUE the Isonet_MemberInactive / Isonet_MemberActive is triggered for this CF, 
                    else the CF claims the new SA and triggers only the Isonet_MemberNewAddress event.
   \retval        iso_s16                                
                  - #E_NO_ERR       Scheduled announcing with new source address     
                  - #E_USER_ERROR   Member not found
                  - #E_RANGE        new source address already in use from an other CF

   Hint: For qTriggerLogoutEvent equal ISO_TRUE, \n
         it takes at least 500ms (2*250ms) before the network member is fully announced, \n
         else it takes at least 250ms.
*/
ISO_CORE_API
iso_s16 iso_NmChangeSourceAddress(iso_s16 s16CfHandle, iso_u8 u8NewSA, iso_bool qTriggerLogoutEvent);

 /* ********************************************************************* */
 /*!
    \brief        This function determines the handle of a network member over CAN-Node and SA

    \param[in]     \wp{u8CanIdx, iso_u8}
                    CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )  
    \param[in]     \wp{u8SourceAddress, iso_u8}
                    Source address of network member 
    \retval       iso_s16    
                  - Handle of network member of concrete CAN-bus   
                  - HANDLE_UNVALID if there is no network member with this SA                                                          
      
*/
ISO_CORE_API
iso_s16 iso_NmGetMemHandleofSA( iso_u8 u8CanIdx, iso_u8 u8SourceAddress );

 /* *************************************************************************** */
 /*! 
    \brief        This function determines the handle of a network member over CAN-Node and Name

    \param[in]     \wp{u8CanIdx,iso_u8}
                    CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )  
    \param[in]     \wpp{au8Name, const #ISO_CF_NAME_T*}
                    NAME of the network member ( see IsoSetName() )
    \retval       iso_s16    
                  - Handle of network member of concrete CAN-bus   
                  - HANDLE_UNVALID if there is no network member with this Name                                                          
     
*/
ISO_CORE_API
iso_s16 iso_NmGetMemHandleofName( iso_u8 u8CanIdx, const ISO_CF_NAME_T* au8Name );

/* ********************************************************************* */
/*! 
   \brief         Monitor the CAN messages for an external network member. 

   \param[in]    \wp{s16CfHandle, iso_s16}
                  Handle of the internal network member
   \param[in]    \wp{s16TimeoutMs, iso_s16}
                  Timeout in milliseconds
                  - < 0: not valid
                  - 0:  disable monitoring
                  - > 0: activate monitoring
   \retval        iso_s16                                
                  - #E_NO_ERR       on success     
                  - #E_USER_ERROR   Member not found or internal CF
                  - #E_RANGE        Parameter not valid
                  - #E_CONFIG       if not enabled with define ISO_NM_MSG_MONITOR

   \par Hint:
   The optional feature must be enabled with the define ISO_NM_MSG_MONITOR.

*/
ISO_CORE_API
iso_s16 iso_NmMemberSetPresenceTimeout(iso_s16 s16CfHandle, iso_s16 s16TimeoutMs);


/* ************************************************************************* */
/*!
   \brief Function which fills an array with CF handles, which fulfill the search options.
   \param[in]  \wp{u8CanIdx, iso_u8}
               CAN node index 
   \param[in]  \wp{bGetOnlyFullyAnnounced, iso_bool}
               Set to ISO_TRUE to get only fully announced CFs; ISO_FALSE to get all entries
   \param[in]  \wp{eSearchLocation, ISO_CF_LOCATION_e}
               Search mode: internal, external or all CFs
   \param[in]  \wp{u8NameFunction, iso_u8}
               Search for ISO name function code: Set to 0xFFu for all name functions
   \param[in]  \wp{u16ArrSizeForCfHandles, iso_u16}
               Size of the array to fill  
   \param[out]  \wp{as16CfHandles, iso_s16[]}
               Pointer to the array to fill with CF handles 
   \param[out]  \wp{pu16NumberOfCfs, iso_u16*}
               Pointer to the variable where to store the number of handles (array entices) found 
   \retval     iso_s16
               - #E_NO_ERR on success
               - #E_OVERFLOW Application array is to small
               - #E_RANGE u8CanIdx or u16ArrSizeForCfHandles not valid
*/
ISO_CORE_API
iso_s16 iso_NmReadListOfCfHandles( iso_u8 u8CanIdx, iso_bool bGetOnlyFullyAnnounced, ISO_CF_LOCATION_e eSearchLocation, iso_u8 u8NameFunction,
                                   iso_u16 u16ArrSizeForCfHandles, iso_s16 as16CfHandles[], iso_u16* pu16NumberOfCfs );

/* ********************************************************************* */
/*!
    \brief            This function returns the network member information for a valid CF handle.
    \param[in]        \wp{s16MnHandle,iso_s16}
                       Handle to network member / CF
    \param[out]       \wp{psCfInfo,ISO_CF_INFO_T*}
                       Pointer to the structure which should be filled
    \retval           iso_s16            
                      - #E_NO_ERR on success 
                      - #E_USER_ERROR Network member not found (psCfInfo not filled)
                      - #E_RANGE if psUserInfo is the NULL pointer
*/ 
ISO_CORE_API
iso_s16 iso_NmGetCfInfo( iso_s16 s16MnHandle, ISO_CF_INFO_T* psCfInfo );

/* *************************************************************************** */
/*!
   \brief          This function returns the number of CF / user entries for a CAN node.
   \param[in]      \wp{u8CanIdx, iso_u8}
                    CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )
   \param[in]      \wp{qUsedOnly, iso_bool}
                    Values:
                    - #ISO_TRUE to return the current number of managed CFs for this CAN node.
                    - #ISO_FALSE to return the list size for this CAN node.  
   \retval         iso_s16
                   - Number of entries ( 0 to list size )
*/
ISO_CORE_API
iso_s16 iso_NmGetCfNumber(iso_u8 u8CanIdx, iso_bool qUsedOnly);

/* *************************************************************************** */
/*!
   \brief          This function returns the handle of the CF / user 
                   for a CAN node at the given index number.
   \param[in]      \wp{u8CanIdx, iso_u8}
                    CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )
   \param[in]      \wp{s16Number,iso_s16}
                    Index number of the CF. \n
                    Range: 0 to iso_NmGetCfNumber(u8CanIdx, ISO_TRUE)
   \retval         iso_s16
                   - #HANDLE_UNVALID in case of a parameter error
                   - Handle of the CF 
   \par     Hint:
   The handle returned for a given index number can change during runtime.
*/
ISO_CORE_API
iso_s16 iso_NmGetCfHandleToNumber(iso_u8 u8CanIdx, iso_s16 s16Number);

#if defined(ISO_NM_EXTENSION) 

/* ********************************************************************* */
/*! 
   \brief         An active (internal) network member is logged out 
                  and announced again using the new name  
   \param[in]     \wp{s16MemHandle, iso_s16}
                  Handle of the internal network member
   \param[in]      \wpp{au8NewName, const #ISO_CF_NAME_T*}
                  new NAME of the ISO user ( see IsoSetName() )
   \retval        iso_s16                                
                  - #E_NO_ERR       Announcing with new name successful     
                  - #E_USER_ERROR   Member not found
                  - #E_RANGE        new NAME already exists

      Hint: It takes at least 500ms (2*250ms) before the network member is fully announced.
*/
ISO_CORE_API
iso_s16 iso_NmMemberChangeName(iso_s16 s16MnHandle, const ISO_CF_NAME_T* au8NewName);

#endif /* defined(ISO_NM_EXTENSION)  */

/**@}*/

/* ************************************************************************ */
/* Special interface for an external NIU */
/* ************************************************************************ */

#if defined(DOXYGEN) 
/* make sure that the documentation is generated */
   #define ISO_EXTERNAL_NIU
   #define _LAY4_EXTERNAL
#endif 

#if defined(ISO_EXTERNAL_NIU) 

/*! \defgroup grp_extniu External Network Interconnection Unit Interface
   \ingroup core
   \brief  Part 4 - External Network Layer Interface
   
   This part contains interface for integrating an external NIU into the Driver.
   The define #_LAY4_EXTERNAL must be added to your IsoConf.h to enable the external NIU integration.
*/

/*! \defgroup grp_extniuconfig External NIU Configuration
   \ingroup grp_extniu
   \brief External NIU definitions for IsoConf.h

   \def _LAY4_EXTERNAL
   \ingroup grp_extniuconfig
   \brief Define to enable the external NIU interface compilation.
   This define must be added to the IsoConf.h to enable the interface.
*/

/*! \defgroup grp_extniutypedef External NIU Type Definitions
   \ingroup grp_extniu
   \brief NIU-Service public defines, structure and enum definitions

   This part contains the structure, enum and type definitions for the NIU-Service management module.
*/

/* ************************************************************************ */
/** \addtogroup grp_extniu 
   @{
*/

/* ************************************************************************** */
/*! \brief Sets the callback functions for the external NIU.

   \param[in]  \wp{pfCanReceivedFunction, ISO_NL_CbMsgReceived_t}
               Pointer to the CAN message received callback function of the external NIU.
   \param[in]  \wp{pfCyclicFunction, ISO_NL_CbCyclicCall_t}
               Pointer to the cyclic callback function of the external NIU. \n
               If the pointer is set to NULL the Base Driver doesn't call the external NIU in it's cyclic function.
   \retval     iso_s16
               - #E_NO_ERR on success

   After calling this function the external NIU is treated as enabled and the called from the Base Driver.
*/
ISO_CORE_API
iso_s16 iso_NlSetCallbacks(ISO_NL_CbMsgReceived_t pfCanReceivedFunction, ISO_NL_CbCyclicCall_t pfCyclicFunction);
 
/* ************************************************************************** */
/*! \brief Transmit a CAN message on the destination CAN node

   \param[in]  \wp{psMessage, ISO_NL_CAN_MSG_T*}
               Pointer to the message. 
   \retval     iso_s16
               - #E_NO_ERR on success

   The function forwards the message to the physical CANBUS and queues the message to forward
   it also to the internal CFs of this CAN node. 
   Since this is a low level function the field values of ISO_NL_CAN_MSG_T are not validated.

   \par Hint:
   The size of the internal used message queue can be set with the define #ISO_CANMSG_QUEUE_SIZE.
*/
ISO_CORE_API
iso_s16 iso_NlTransmitMsg(ISO_NL_CAN_MSG_T* psMessage);


/* ************************************************************************** */
/*!
   \brief       This function installs a callback function which sends the
                network management events to the external NIU
   \param[in]   \wpp{pfCbNiu, void (*)(#ISONETEVENT_T*)}
                Pointer to function or NULL to disable sending
*/
ISO_CORE_API
void iso_NlSetNetCallback(void(*pfCbNiu)(const ISONETEVENT_T* psEv));

/**@}*/
/* ************************************************************************ */
#endif /* ISO_EXTERNAL_NIU */

/* ************************************************************************ */
/* Special interface for an external core driver mutex implementation */
/* ************************************************************************ */

#if defined(DOXYGEN) 
/* make sure that the documentation is generated */
#define ISO_CORE_MUTEX
#else /* not defined(DOXYGEN) */
/* check if internal NIU is disabled */
#if defined (ISO_CORE_MUTEX) && defined(_LAY4_) && !defined(_LAY4_OWN_MUTEX)
#error Configuration error: Core driver mutex can not be used with internal NIU.
#endif
#endif /* not defined(DOXYGEN) */

/*! \defgroup grp_core_mutex Core Driver Mutex Interface
\ingroup core
\brief  Core Driver Mutex Interface

This interface functions must be implemented by the application to make the core driver API calls thread safe.
The define #ISO_CORE_MUTEX must be added to your IsoConf.h to enable the option.

@{
   \def ISO_CORE_MUTEX
   \brief Optional define to enable the application specific core mutex compilation.
*/

#if defined(ISO_CORE_MUTEX)
#if defined(ISO_CORE_MUTEX_RECURSIVE)
/*! \brief locks the core mutex */
ISO_CORE_API
void iso_CoreMutexLock(void);
/*! \brief unlocks the core mutex */
ISO_CORE_API
void iso_CoreMutexUnLock(void);
#else /* defined(ISO_CORE_MUTEX_RECURSIVE) */
/* CoreMutexLock may only be used in driver internal routines */
/*! \brief locks the core mutex */
void iso_CoreMutexLock(void);
/*! \brief unlocks the core mutex */
void iso_CoreMutexUnLock(void);
#endif /* defined(ISO_CORE_MUTEX_RECURSIVE) */
#endif /* defined(ISO_CORE_MUTEX) */

/**@}*/

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_ISO_CORE_API_H */
/* ************************************************************************ */

