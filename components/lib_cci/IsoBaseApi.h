/* ************************************************************************ */
/*!
   \file
   \brief       ISOBUS ECU driver base API
   \details     Contains the base driver API functions

   \author      Wegscheider Peter
   \date        Created 27.02.2015

   \copyright   Competence Center ISOBUS e.V.

   \par  History:
   \par
   14.12.2016 - author P. Wegscheider
   - Feature ID  4209: declare pointer parameter in functions as const* where applicable
   - IsoDrvCbBasicDataInstall() - set ISO_TPINFO_T as const
   \par
   07.02.2018 - author P. Wegscheider
   - Feature request ID 7504: Split Base Driver into "Core" and "Base"
   - Moved code and history from IsoBaseApi.h to IsoCoreApi.h
   \par
   28.02.2018 - author P.Wegscheider
   - Feature request ID 7504: Added API function iso_BaseMemberAdd()
   \par
   08.06.2018 - author P.Wegscheider
   - Feature request ID 7504: Moved internal CF network and data link callbacks from Core to Base.
   \par
   12.06.2018 - author P.Wegscheider
   - Feature request ID 8459: use iso_u8 for ISOBUS addresses in API
   \par
   27.07.2018 - author P. Wegscheider
   - Feature BugID 8787: Replaced iso_DlPgnSend() with iso_DlPgnSendEx().
    \par
   25.10.2018 - author P.Wegscheider
   - Added optional definition CCI_PART12_DIAG_CB, the typedef ISO_CbPart12DiagReqMsg_t and the function iso_BaseSetPart12DiagCB() 
     to forward diagnose PGN requests with the specified callback function to the application.
   \par
   19.11.2019 - author P.Wegscheider
   - Feature request ID 10185: refactor TL -- use case for dual CPU implementations \n
     Removed define CCI_TL_IN_BASE     
   - Replaced optional definition CCI_PART12_DIAG_CB with define CCI_MODULE_PDU2, 
     typedef ISO_CbPart12DiagReqMsg_t with ISO_CbPDU2Msg_t and function iso_BaseSetPart12DiagCB with iso_BaseSetPDU2CB()
     to forward PDU2 messages with the specified callback function to the application.
   \par
   05.02.2020 - author P.Wegscheider
   - Feature request BugID 11700: rename CCI_BASE_API into ISO_BASE_API
   - Feature request BugID 9285: obtain PART12 diagnostic automatically
   \par
   09.04.2020 - author P.Wegscheider
   - Feature request BugID 10773: register a client server connection
   \par
   16.08.2020 - author P.Wegscheider
   - Feature request BugID 12443: added function iso_BaseGetCfHandleOfSA()
   - Feature request BugID 12487: added functions iso_BaseMemberLoggedOut() and iso_BaseMemberExternAdd()
   \par
   11.01.2021 - author P.Wegscheider
   - Feature BugID 12703: rename CCI_BASE_SHADOW_COPY to ISO_BASE_SHADOW_COPY
*/
/* ************************************************************************ */

#ifndef DEF_ISOBASEAPI_H
#define DEF_ISOBASEAPI_H

/* include configuration and common driver definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* ************************************************************************ */
/*! 
   \ingroup base_general
   \brief         Returns the current time since startup in milliseconds
   \retval        iso_s32
                  Time stamp in milliseconds

   The function uses the application-specific function of time, which was passed with iso_DlCallbacksInit().
*/
#if (!defined(ISO_BASE_MUTEX)) || defined(ISO_BASE_MUTEX_RECURSIVE)
ISO_BASE_API
#endif /* (!defined(ISO_BASE_MUTEX)) || defined(ISO_BASE_MUTEX_RECURSIVE) */
iso_s32  iso_BaseGetTimeMs( void );

/* Base Driver global functions  */
/** \addtogroup base_mn_init Initialisation and Runtime
*/
/**@{*/

/* ************************************************************************ */
/*!
    \brief        Base Driver initalisation.
                  This function installs the necessary callback functions
                  and initialises all base modules of the driver. 
                  The Core Driver modules and the Client modules have to be initialised separately 
                  with iso_CoreInit() and iso_ClientsInit().
    \param[in]    \wp{pfGetTimeMs, ISO_CbGetTimeMs_t }  
                    Pointer to the application specific timestamp callback function.
    \param[in]    \wp{pfTriggerWatchdog, ISO_CbTriggerWatchdog_t}  
                     Pointer to the watchdog trigger callback function or NULL pointer if not needed.
    \param[in]    \wp{pfErrorHandler, ISO_CbErrorHandler_t}
                     Pointer to the  error handler callback function or NULL pointer.  \n 
                     ( see also IsoErrorOut() and \ref errorhand for more information ) 
    \param[in]    \wp{pfDoMsg, ISO_BaseClients_CbDoMsg_t}  
                     Pointer to the message callback function for the Clients \n 
    \param[in]    \wp{fpEtpMemAllocFreeCb, ISO_ETP_Memory_fpt}
                     Pointer to the ETP extended memory management callback function or NULL pointer. \n
                     Is needed only for receiving incoming ETP messages. Use the NULL pointer to disable the functionality (normal case).

    \retval         iso_s16
                    - #E_NO_ERR on success
                    - #E_RANGE if rpfTime is a NULL pointer 
                      or if _LAY6_, _LAY10_ or _LAY13_ is defined and  pfDoMsg is a NULL pointer.

   \par Sample
   Install the application specific callback functions and the default clients callback function IsoCbDataOfBasicDistributor().
   \code
   iso_BaseInit(  AppTimeMs,
                  AppWatchDog,
                  AppErrorHndler,
                  IsoCbDataOfBasicDistributor, 0 );
   \endcode
*/
ISO_BASE_API
iso_s16 iso_BaseInit(
   ISO_CbGetTimeMs_t pfGetTimeMs,
   ISO_CbTriggerWatchdog_t pfTriggerWatchdog, /* optional */
   ISO_CbErrorHandler_t pfErrorHandler,       /* optional */
   ISO_BaseClients_CbDoMsg_t pfDoMsg,         /* IsoCbDataOfBasicDistributor for default callback function */
   ISO_ETP_Memory_fpt fpEtpMemAllocFreeCb);   /* use NULL pointer if receiving of ETPs is not needed */

/* ************************************************************************ */
/*!
   \brief       Base driver cyclic function

   This function executes the cyclic functions of all modules of the base driver.

   \par
    Time behavior: This function should called about every 10ms or faster. 
*/
ISO_BASE_API
void iso_BaseCyclic(void);

/* ************************************************************************ */
/*!
   \brief   Base driver data distribution function.
   \details This is the default distribution callback function 
            which must be set with iso_CoreInit() in case of no external base distributor. 
   \param[in]   \wpp{psMsgInfo, const #ISO_CORE_DD_MSGINFO_T*}
                 Pointer to the message information data
   \param[in]   \wpp{pau8Data, const #iso_u8 HUGE_C []}
                 Pointer to the message data byte array or NULL pointer
   \param[in]   \wp{u32DataSize, iso_u32}
                  Size of the given message data byte array
*/
ISO_BASE_API
void IsoCbBaseDataDistributor(const ISO_CORE_DD_MSGINFO_T* psMsgInfo, const iso_u8 HUGE_C pau8Data[], iso_u32 u32DataSize);


/* ************************************************************************ */
/*!
   \brief   Base driver network event distribution function.
   \details This is the default network event callback function 
            which must be set with iso_CoreInit() in case of no external base distributor. 
   \param[in]   \wpp{ psNetEv, const #ISONETEVENT_T*}
                 Vaild pointer to network event structure        
*/
ISO_BASE_API
void IsoCbBaseNetworkDistributor(const ISONETEVENT_T* psNetEv);

#if defined(ISO_CLIENT_NETWORK_DISTRIBUTOR)
/* ************************************************************************ */
/* \brief Function to set an optional application specific client network event callback function
   \param[in]    \wp{pfIsoNetworkCb, ISO_CoreBase_CbIsoNetwork_t}
                  Pointer to a client network event callback function or NULL pointer if not needed
*/
ISO_BASE_API
void iso_BaseSetClientNetworkDistributor(ISO_CoreBase_CbIsoNetwork_t pfIsoNetworkCb);
#endif /* defined(ISO_CLIENT_NETWORK_DISTRIBUTOR) */

/* ************************************************************************ */
/*! \brief Forward message to the CF data link layer callback function.
    \details   This function is used from the default distributor function IsoCbBaseDataDistributor()
               and should only be used from an application in a custom distributor implementation.
    \param[in]   \wp{u8CanIdx, iso_u8}
                  CAN node number (index)
    \param[in]   \wp{eDataTransStatus, ISO_TPREP_E}
                  Transport status
    \param[in]   \wpp{psTpInfo, const #ISO_TPINFO_T*}
                 Pointer to the message data
*/
ISO_BASE_API
void iso_BaseForwardToDataLinkCb(iso_u8 u8CanIdx, ISO_TPREP_E eDataTransStatus, const ISO_TPINFO_T* psTpInfo);


/* ************************************************************************ */
#ifdef DOXYGEN
#define ISO_CLIENT_SERVER_CONNECTION_MAX  (1u) /* set to 1u to generate documentation */
#endif

/* ************************************************************************ */
/*! \def ISO_CLIENT_SERVER_CONNECTION_MAX
   \brief   Maximum number of client server connections (default 0u). 
   \details Number of connection entries 
            which can be setup with iso_BaseSetClientServerConnection().
*/
#ifndef ISO_CLIENT_SERVER_CONNECTION_MAX 
#define ISO_CLIENT_SERVER_CONNECTION_MAX  (0u)
#endif /* ISO_CLIENT_SERVER_CONNECTION_MAX*/

/* ************************************************************************ */
/*! \brief CAN message information structure used by the client server connection callback function */
typedef struct
{
   ISO_TPREP_E    eTpStatus;        /**< \brief Message transport status */
   iso_u8         u8CanIdx;         /**< \brief CAN node index */
   iso_u8         u8Priority;       /**< \brief Bits 0-3: Priority of PGN ( 7 for (E)TP ); Bits 4-7: Optional CAN channel priority (0 is default) */
   iso_bool       qSended;          /**< \brief ISO_TRUE if sended else received */
   iso_u32        u32PGN;           /**< \brief PGN of the transported message */
   iso_s16        s16HndIntern;     /**< \brief Network member handle of the internal CF ( or #HANDLE_GLOBAL for incoming PDU2 )  */
   iso_s16        s16HndPartner;    /**< \brief Network member handle of the external CF ( or #HANDLE_GLOBAL for outgoing  PDU2 ) */
#if defined(CCI_TIMESTAMP)
   iso_s32        s32TimeStamp;     /**< \brief Time stamp of the message in ms */
#endif /* defined(CCI_TIMESTAMP) */
} ISO_BASE_MSGINFO_T;

/* ************************************************************************ */
/*!
    \brief  Callback function pointer declaration for forwarding CAN messages to client server connections 

    \param[in]   \wpp{psMsgInfo, const #ISO_BASE_MSGINFO_T*}
                 Pointer to the message information data
    \param[in]   \wpp{pau8Data, const #iso_u8 HUGE_C []}
                 Pointer to the message data byte array or NULL pointer
    \param[in]   \wp{u32DataSize, iso_u32}
                  Size of the given message data byte array

    \retval    iso_bool
               - #ISO_TRUE  - Message handled from the application (no more actions needed)
               - #ISO_FALSE - Message not handled (driver should handle/forward request)
*/
typedef iso_bool (*ISO_Cb_BaseMsg_t)(const ISO_BASE_MSGINFO_T* psMsgInfo, const iso_u8 HUGE_C pau8Data[], iso_u32 u32DataSize);


/* ************************************************************************ */
/*!  \brief    This add or removes a client server connection with its specific PGNs 

   Use ISO_DD_CONNECTION_MAX to set the maximum number of entries (default 0u) 

   \param[in]      \wp{u32SenderPGN, iso_u32}
                   Internal PGN which is used for sending messages 
   \param[in]      \wp{u32ReceivePGN, iso_u32}
                   External PGN which should be used to detect received messages 
   \param[in]      \wp{pfMsgCb, ISO_Cb_BaseMsg_t}
                     Callback function to get the messages 
                     or NULL pointer to remove an existing entry.
   \retval         iso_s16
                    - #E_NO_ERR on success
                    - #E_RANGE if parameter not valid
                    - #E_OVERFLOW if array is full
*/
ISO_BASE_API
iso_s16 iso_BaseSetClientServerConnection(iso_u32 u32SenderPGN, iso_u32 u32ReceivePGN, ISO_Cb_BaseMsg_t pfMsgCb);


/* ************************************************************************ */
/* TODO for ISO version \addtogroup xxxx */
/*! \brief  Function pointer declaration for global PART 7 PDU2 callback function
    \details This function must be implemented from the application and given to the driver with iso_BaseSetPDU2CB()
    \param[in]  \wp{eTpRep,  ISO_TPREP_E}
                   Status of the message
    \param[in]  \wpp{psMsgInfo, const #ISO_TPINFO_T *}
                    Pointer to the message data
    \retval         iso_bool
                    - #ISO_TRUE  - Message handled from the application (no more actions needed)
                    - #ISO_FALSE - Message not handled (driver should handle/forward request)
*/
typedef iso_bool (*ISO_CbPDU2Msg_t)(ISO_TPREP_E eTpRep, const ISO_TPINFO_T* psMsgInfo);


#if defined(CCI_MODULE_PDU2)
/* ************************************************************************ */
/*! \brief Function to set a global callback function to get all PART 7 PDU2 messages.
    \param[in]      \wp{pfDataTransCb, ISO_DD_CbDaTrans_t}
                     Callback function to get all PART 7 PDU2 messages \n
                     or NULL pointer.
                     See also #ISO_TPINFO_T for more information.
    \retval         iso_s16
                    - #E_NO_ERR 
*/
ISO_BASE_API
iso_s16 iso_BaseSetPDU2CB(ISO_CbPDU2Msg_t pfPDU2Cb);

#endif /* defined(CCI_MODULE_PDU2) */

/** @} */

#if defined(ISO_MODULE_DIAG)
/** \addtogroup diagapi Diagnostic Module
  @{ 
*/

/** \brief
Defines (bitcoded) for selection of diagnostic protocol messages
  @{
*/
#define PGN_ECUIDENT       0x0001u     /**< Bitcoded selector for ECU identification  0xFDC5  */
#define PGN_SWIDENT        0x0002u     /**< Bitcoded selector for Software identification  0xFEDA  */
#define PGN_CCID           0x0004u     /**< Bitcoded selector for ISOBUS certification  0xFD42  */
#define PGN_DIAGPROT       0x0008u     /**< Bitcoded selector for Diagnostic protocol  0xFD32  */
#define PGN_CFFUNC         0x0010u     /**< Bitcoded selector for CF functionalities  0xFC8E  */
#define PGN_PRODUCTID      0x0020u     /**< Bitcoded selector for Product identification  0xFC8D  */
/** @} */

/* ************************************************************************ */
/*!  \brief  This function triggers the requesting of diagnostic data

   \param[in]      \wp{s16CFint, iso_s16}
                   Handle of intern CF which requests diagnostic data
   \param[in]      \wp{s16CFext, iso_s16}
                   Handle of extern CF which is requested for diagnostic data
   \param[in]      \wp{u16PGNstoReq, iso_u16}
                   Preselection which diagnostic message ought be requested
                   (PGN_ECUIDENT, PGN_SWIDENT, PGN_CCID, PGN_DIAGPROT, PGN_CFFUNC, PGN_PRODUCTID)
   \param[in]      \wp{pfDiagCb, ISO_CbPDU2Msg_t}
                     Callback function to get diagnostic messages or NULL pointer.
                     See also #ISO_TPINFO_T for more information.
    \retval         iso_s16
                    - #E_NO_ERR
                    - #E_RANGE
                    - #E_NO_INSTANCE
*/
ISO_BASE_API
iso_s16 iso_BaseDiagTriggerReq(iso_s16 s16CFint, iso_s16 s16CFext, iso_u16 u16PGNstoReq, ISO_CbPDU2Msg_t pfDiagCb);

/* ************************************************************************ */
/*! \brief  This function sets a callback which is triggered in case received diagnostic data requests

   \param[in]      \wp{rpfDiagCb, ISO_CbPDU2Msg_t}
                   Callback function called with receiving requests for diagnostic data
   \retval         iso_s16
                    - #E_NO_ERR
*/
ISO_BASE_API
iso_s16 iso_BaseDiagSetCbForResp(ISO_CbPDU2Msg_t rpfDiagCb);
/** @} */
#endif /* defined(ISO_MODULE_DIAG) */


/* ************************************************************************ */
/** \defgroup driverpart3 Part 3 Configuration
   \ingroup base_general

   \brief Special Part 3 Data Link Layer configuration options.
*/

/* ************************************************************************ */
/** \addtogroup driverpart3
@{
*/
/* ************************************************************************ */

#ifdef DOXYGEN
#define ISO_ETP_IN      /*!< \brief Enable the receiving of data messages using the extended transport protocol. */
#define ISO_ETP_IN_PKG  /*!< \brief Enable the packet group write mode. */
#endif

/* ************************************************************************ */
/*! \brief Function to set the ETP extended memory management 
           and TP RTS/CTS callback function.

   For more information see #ISO_ETP_Memory_fpt.

   \param[in]  \wp{fpEtpMemAllocFreeCb, ISO_ETP_Memory_fpt}
                  Pointer to the callback function or NULL pointer.
   \retval  iso_s16
               - E_NO_ERR

   Hints: 
   - For ISO_ETP_IN_PKG we can not report the received data with #ISO_TPINFO_T (pabData = 0).
     This must be done by the application in the ISO_ETP_FlushMemory_fpt callback...

*/ 
ISO_BASE_API
iso_s16 iso_BaseSetETPMemoryCb(ISO_ETP_Memory_fpt fpEtpMemAllocFreeCb );

#if defined(ISO_ETP_IN_PKG) 
/*! \brief   Declaration of the ETP_IN_PKG packet group write function  
    \details The function must be implemented form the application   
             to use #ISO_ETP_IN_PKG with a null pointer as memory buffer
             (See #ISO_ETP_Memory_fpt for more information).

   \param[in]  \wp{u32PGN,  iso_u32}
                  PGN of the transported message
   \param[in]  \wp{s16CfHndIntern,  iso_s16}
                  Network member handle of the internal CF
   \param[in]  \wp{s16CfHndPartner,  iso_s16}
                  Network member handle of the external CF
   \param[in]  \wp{u32StartIndex,  iso_u32}
                ETP offset (start index) of this packet group ( equal size of the already written bytes; starts with 0 for the first data byte)
   \param[in]  \wpp{au8Data, const #iso_u8 HUGE_C []}
                  Pointer to data byte array 
   \param[in]  \wp{u32DataLength,  iso_u32}
                Size of the new data group in bytes

*/
void iso_BaseEtpBufferWrite( iso_u32 u32PGN, iso_s16 s16CfHndIntern, iso_s16 s16CfHndPartner,
                                iso_u32 u32StartIndex, const iso_u8 HUGE_C au8Data[], iso_u32 u32DataLength );
#endif /* defined(ISO_ETP_IN_PKG) */

/* ************************************************************************ */
/** @} */  /* END group driverpart3 Part 3 Configuration                    */
/* ************************************************************************ */




/** \addtogroup base_nmma Network Management
*/
/**@{*/

/* ************************************************************************ */
/*!
    \brief          Base Driver wrapped function to add a new (intern) logic network member (CF) to the bus 

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
    \param[in]      \wpp{userParam, const #ISO_USER_PARAM_T}
                     User parameter value for the callback function calls. \n
                     Use #ISO_USER_PARAM_DEFAULT if not used/needed.
    \param[in]      \wp{pfNetworkEventCb, ISO_NM_CbCfEvent_t}
                     Callback function for the network management to inform this user / CF 
                     about changes of the announcement state of this or another internal or external CF. \n
                     See #ISONETEVENT_T for more information.
    \param[in]      \wp{pfDataTransCb, ISO_DD_CbDaTrans_t}
                     Callback function for the data link layer to inform this user / CF about all ISO messages 
                     which aren't processed from an internal module ( like the application layer, TC, VT, ... ). \n
                     See #ISO_TPINFO_T for more information.

     \retval         iso_s16      
                    - >= 0            CF handle of the network member
                    - #HANDLE_UNVALID Parameter error or user list is full
    \par  
       After getting an dynamic address the application reports this with the help
       of a callback function. This function indicates the application the releasing of the ISO-bus, too.
       This function controls if the new user has been already entered in the user list. If yes nothing
       occurs except of an error message, if not the new user is entered. After calling the cyclic
       function of the ISO driver this user sends its address claim.
 */
ISO_BASE_API
iso_s16 iso_BaseMemberAdd(iso_u8 u8CanIdx,
                          iso_u8 u8WishedSA,
                          const ISO_CF_NAME_T* au8Descript,
                          ISO_USERFUNC_e eUserFunction,
                          const ISO_USER_PARAM_T userParam,
                          ISO_NM_CbCfEvent_t pfNetworkEventCb,
                          ISO_DD_CbDaTrans_t pfDataTransCb
                      );

#if defined(CCI_HSI)
/* for high speed ISOBUS test implementation */
ISO_BASE_API
iso_s16 iso_BaseSetHsiActive(iso_s16 s16CfHandle, iso_bool bActive);
#endif /* defined(CCI_HSI) */


/* ********************************************************************* */
/*!
    \brief         Function to deactivate a network member  
    \param[in]     \wp{s16CfHandle, iso_s16}
                   Handle of the network member (control function)
    \retval        iso_s16                                
                    - #E_NO_ERR       on success 
                    - #E_USER_ERROR   member not found
    \par Hint:
    The network member is not deleted from list. The entry is only set to inactive.
    If an external CF sends again the address claimed message, the entry will be reactivated. \n
    An internal CF should only be logged off after all used client instances of this CF (VTC, TCC, ...) 
    have been closed and removed.
*/
ISO_BASE_API
iso_s16 iso_BaseMemberLoggedOut( iso_s16 s16CfHandle );

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
ISO_BASE_API
iso_s16 iso_BaseMemberExternAdd( iso_u8 u8CanIdx, iso_u8 u8SA );

/* ********************************************************************* */
/*!
   \brief        This function determines the handle of a network member over CAN-Node and SA

   \param[in]    \wp{u8CanIdx, iso_u8}
                  CAN-bus number 0, 1, ... ( ISO_CAN_NODES - 1 )  
   \param[in]    \wp{u8SourceAddress, iso_u8}
                   Source address of network member 
   \retval       iso_s16    
                  - Handle of network member of concrete CAN-bus   
                  - HANDLE_UNVALID if there is no valid network member with this SA     
*/
ISO_BASE_API
iso_s16 iso_BaseGetCfHandleOfSA( iso_u8 u8CanIdx, iso_u8 u8SourceAddress );


/* ********************************************************************* */
/*!
   \brief        This function returns the network member information for a valid CF handle.
   \param[in]    \wp{s16CfHandle,iso_s16}
                  Handle of the control function (network member)
   \param[out]   \wp{psCfInfo,ISO_CF_INFO_T*}
                  Pointer to the structure which should be filled

   \retval      iso_s16            
                - #E_NO_ERR on success 
                - #E_USER_ERROR Network member not found (psCfInfo not filled)
                - #E_RANGE if psUserInfo is the NULL pointer
*/ 
ISO_BASE_API
iso_s16 iso_BaseGetCfInfo( iso_s16 s16CfHandle, ISO_CF_INFO_T* psCfInfo );


/* ************************************************************************* */
/*!
   \brief Function which fills an array with CF handles, which fulfill the search options.
   \param[in]  \wp{u8CanIdx, iso_u8}
               CAN node index 
   \param[in]  \wp{bGetOnlyFullyAnnounced, iso_bool}
               Set to ISO_TRUE to get only fully announced CFs; ISO_FALSE to get all entries
   \param[in]  \wp{eSearchLocation, ISO_CF_LOCATION_e}
               Search mode: internal, external or all CFs
   \param[in]  \wp{u16ArrSizeForCfHandles, iso_u16}
               Size of the array to fill  
   \param[out]  \wp{as16CfHandles, iso_s16[]}
               Pointer to the array to fill with CF handles 
   \param[out]  \wp{pu16NumberOfCfs, iso_u16*}
               Pointer to the variable where to store the number of handles (array entices) found 
   \retval     iso_s16
               E_NO_ERR on success else error code
*/
ISO_BASE_API
iso_s16  iso_BaseGetListOfCfHandles(iso_u8 u8CanIdx, iso_bool bGetOnlyFullyAnnounced, ISO_CF_LOCATION_e eSearchLocation,
                                    iso_u16 u16ArrSizeForCfHandles, iso_s16 as16CfHandles[], iso_u16* pu16NumberOfCfs);


#if defined(ISO_BASE_SHADOW_COPY) 
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
               E_NO_ERR on success else error code
*/
ISO_BASE_API
iso_s16  iso_BaseGetListOfCfHandlesOfFunc(iso_u8 u8CanIdx, iso_bool bGetOnlyFullyAnnounced, ISO_CF_LOCATION_e eSearchLocation, iso_u8 u8NameFunction,
                                          iso_u16 u16ArrSizeForCfHandles, iso_s16 as16CfHandles[], iso_u16* pu16NumberOfCfs);
#endif /* defined(ISO_BASE_SHADOW_COPY) */

/**@}*/

/* Dl - Data link layer interface */
/** \addtogroup mndl DataLink Layer 
 @{
*/

/* ************************************************************************ */
/*!
   \brief   Possibility for (intern) network members to request a defined PGN

   This function enables to request a defined PGN according to ISO 11783 - 3. It realizes
   a low level data link layer functionality. 

   \param[in]  \wp{u32Pgn, iso_u32}
                  Requested PGN \n
                  Lower iso_u8 of PDU1-PGNs must be zero \n
                  Range: 0 ... 0x3FFFF
   \param[in]  \wp{s16CfHndSender, iso_s16}
                  CF handle of the sender of the request
   \param[in]  \wp{s16CfHndReceiver, iso_s16}
                  Destination address of this request
                  - "OneToOne"-Request: a certain CF handle of the network
                  - "OneToMany"-Request (Broadcast): HANDLE_GLOBAL ( for ISO_GLOBAL_ADDRESS )
   \retval     iso_s16
                  - #E_NO_ERR - OK
                  - #E_USER_ERROR - invalid CF handle
                  - #E_OVERFLOW on send FIFO full
                  - #E_COM on bus-off
*/
ISO_BASE_API
iso_s16 iso_DlPgnRequest( iso_u32 u32Pgn, iso_s16 s16CfHndSender, iso_s16 s16CfHndReceiver );

/* ********************************************************************* */
/*!
   \brief         This function sends an acknowledgement
   \param[in]     \wp{reControl, ISO_ACK_E}
                  Control iso_u8 of acknowledgement (N)ACK message
   \param[in]     \wp{ru32ConcernPgn, iso_u32}
                  PGN which is (N)ACK
   \param[in]     \wp{u8GroupFunValue, iso_u8}
                  Group function value
   \param[in]     \wp{u8Byte5, iso_u8}
                  Byte 5 of acknowledgement message
   \param[in]     \wp{rs16HndSender, iso_s16}
                  Handle of sender
   \param[in]     \wp{rs16HndReceiver, iso_s16}
                  Handle of receiver ( or HANDLE_GLOBAL )
   \retval        iso_s16
                  - #E_NO_ERR  on success
                  - #E_RANGE if rs16HndReceiver is global and reControl not an ACK
                  - #E_OVERFLOW on send FIFO full
                  - #E_COM on bus-off
*/
ISO_BASE_API
iso_s16 iso_DlPgnAcknowledge( ISO_ACK_E reControl, iso_u32 ru32ConcernPgn,
                             iso_u8 u8GroupFunValue, iso_u8 u8Byte5,
                             iso_s16 rs16HndSender, iso_s16 rs16HndReceiver );


/* ************************************************************************ */
/*!
   \brief      Sending of PGNs to a destination 

   This function starts the sending of a PGN to a receiver  \n
   In case of more than 8 bytes using of TP (or BAM) or ETP is included.
   The function can be used without _LAY78_

   \param[in]  \wp{u8Priori, iso_u8}
                  Priority of PGN (normal default see J1939-71, ISO11783-7,8 ...) \n
                  Range: 0 - 7
   \param[in]  \wp{u32Pgn, iso_u32}
                  PGN which shall be send \n
                  Range: 0 ... 0x3FFFF
   \param[in]  \wp{u32DataLength, iso_u32}
                  Number of data bytes to send
                  -    0 ..     8 : Single transport
                  -    9 ..  1785 : Transport protocol is automatic used
                  - 1786 .. ETP limit: Extended transport protocol is automatic used
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

   \par Incompatible to V9.1 and prior if the HUGE_C define is used.
    The following function can be used as sample how to migrate to V10:
   \code{.c}  
   iso_s16 iso_DlPgnSendV9toV10( iso_u8   u8Priori,
                            iso_u32  u32Pgn,
                            iso_u16  u16DataLength,
                            const   iso_u8 pu8Data[],
                            iso_s16  s16HndSender,
                            iso_s16  s16HndReceiver
   )
   {
      iso_s16  s16Ret;
      const iso_u8 HUGE_C *pu8DataTmp;
      // cast to HUGE_C (also if define is empty) 
      pu8DataTmp = CAST_TO_U8_HUGE_PTR(pu8Data);
      s16Ret = iso_DlPgnSend(u8Priori, u32Pgn, (iso_u32)u16DataLength, pu8DataTmp, s16HndSender, s16HndReceiver);
      return s16Ret;
   }
   \endcode
*/
ISO_BASE_API
iso_s16 iso_DlPgnSend( iso_u8   u8Priori,
                       iso_u32  u32Pgn,
                       iso_u32  u32DataLength,
                       const    iso_u8 HUGE_C pu8Data[],
                       iso_s16  s16HndSender,
                       iso_s16  s16HndReceiver
                     );

/**@}*/


#if defined(DOXYGEN) 
/* make sure that the documentation is generated */
#define ISO_BASE_MUTEX
#endif /* not defined(DOXYGEN) */

/*! \defgroup grp_base_mutex Base Driver Mutex Interface
\ingroup base
\brief  Base Driver Mutex Interface

This interface functions must be implemented by the application to make the base driver API calls thread safe.
The define #ISO_BASE_MUTEX must be added to your IsoConf.h to enable the option.

@{
   \def ISO_BASE_MUTEX
   \brief Optional define to enable the application specific base mutex compilation.
*/

#if defined(ISO_BASE_MUTEX)
#if defined(ISO_BASE_MUTEX_RECURSIVE)
/*! \brief locks the base mutex */
ISO_BASE_API
void iso_BaseMutexLock(void);
/*! \brief unlocks the base mutex */
ISO_BASE_API
void iso_BaseMutexUnLock(void);
#else /* defined(ISO_BASE_MUTEX_RECURSIVE) */
/* BaseMutexLock may only be used in driver internal routines */
/*! \brief locks the base mutex */
void iso_BaseMutexLock(void);
/*! \brief unlocks the base mutex */
void iso_BaseMutexUnLock(void);
#endif /* defined(ISO_BASE_MUTEX_RECURSIVE) */
#endif /* defined(ISO_BASE_MUTEX) */

/* Currently only recursive mutexes are allowed. */
#if defined(ISO_BASE_MUTEX) && (!defined(ISO_BASE_MUTEX_RECURSIVE))
#error Currently only recursive mutexes are allowed for the base driver. Add also define ISO_CORE_MUTEX_RECURSIVE to your IsoConf.h if your mutex is recursive. 
#endif /* defined(ISO_BASE_MUTEX) && (!defined(ISO_BASE_MUTEX_RECURSIVE)) */

/**@}*/

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_ISOBASEAPI_H */
/* ************************************************************************ */
