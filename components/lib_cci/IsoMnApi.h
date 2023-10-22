/****************************************************************************/
/*!
   \file        IsoMnApi.h               
   \brief       API for revised network management and application layer for versions from 4.80
   \author      Hammerl Erwin
   \date        Created XX.07.11
   \copyright   Competence Center ISOBUS e.V.

   \par         History:
   \par
   20.12.2011 - author E. Hammerl
   - Added function iso_AlKeySwitchStateRead() for start over KeySwitchState of implements

   \par
   08.12.2011 - author E. Hammerl
   - Input parameter for array size in functions iso_NmReadListOf...() added

   \par 
   25.01.2012 - author E. Hammerl
   - Added iso_AlPgnTxSpecificSend(), iso_AlPgnTxBroadcastSend(), iso_DlCanBusSet,
     iso_SpnDataReadCom()
   - REPRATE_DEF renamed in REPRATE_INACTIVE
   - iso_NmMemberDelete renamed in iso_NmMemberLoggedOut
   - Added functions for DM ( diagnostic messages )

   \par
   30.03.2012 - author P. Wegscheider
   - changes for Doxygen output generation
   \par
   04.03.2013 - author P. Wegscheider
   - internal base driver restructuring 
   - Function iso_DlCanBusSet() removed from multi CAN node API (Version 06.02.00)
   \par
   25.04.2013 - author P. Wegscheider
   - Added function iso_NmMbrExternAdd()
   \par
   02.05.2013 - author P. Wegscheider
   - Added function iso_NmGetMemHandleofName()
   \par
   19.02.2014 -  author E. Hammerl
   - Added function iso_AlPgnDisable() for completely inactivation of PGNs
   \par
   10.03.2015 - author P. Wegscheider
   - Function iso_AlKeySwitchStateRead() replaced with iso_DlKeySwitchStateRead()
   - Function iso_DlPgnAcknowledge() added
   - Function iso_DlPgnSend() added
   - Function iso_DlPgnRequest() added
   \par
   08.04.2016 - author P. Wegscheider
   - added external NIU interface
   \par
   10.11.2016 - author P. Wegscheider
   - Feature request ID 4510: can send should get a return value
      - Changed iso_DlDrvCanInit()
      - Added iso_DlGetSendMsgFiFoSize()
   \par
   25.11.2016 - author P. Wegscheider
   - Feature request ID 4205: iso_AlPgnTxNew() with an additional callback parameter
   \par
   29.11.2016 - author P. Wegscheider
   - Feature request ID 4690: Heartbeat Message for safety critical path
   \par
   13.01.2017 - author P. Wegscheider
   - Feature request ID 4690: Heartbeat Message for safety critical path
      - Added optional #ISO_HBS_CbEvent_t event callback iso_HBServer_Install()
   \par
   26.01.2017 - author P. Wegscheider
   - Feature ID  4209: declare pointer parameter in functions as const* where applicable
      - iso_NmMemberNew() - set callback functions parameters ISONETEVENT_T and ISO_TPINFO_T as const
      - iso_AlPgnRxNew() - set callback functions parameter PGNDAT_T as const
   \par
   04.04.2017 -author P.Wegscheider
   - Added optional function iso_DlPgnSendEx() to send ETPs with a data size greater than 65KB \n
     The function can be enabled with the IsoConf.h define ISO_DL_EXTENSION.
   \par
   10.05.2017 -author P.Wegscheider
   - Feature request ID 4114: Improved C++ support \n
     Merged changes from v09-evaluation branch (optional define CCI_ISO_USE_USER_PARAM)
   \par
   07.02.2018 - author P. Wegscheider
   - Feature request ID 7504: Split Base Driver into "Core" and "Base"
      - Moved data link and network management API functions from IsoMnApi.h to IsoCoreApi.h
      - Moved external NIU API functions from IsoMnApi.h to IsoCoreApi.h
   \par
   16.02.2018 - author P.Wegscheider
   - Feature ID 7528: add user parameter to callback functions
   \par
   06.05.2018 - author P.Wegscheider
   - Feature ID 3910: header files should include header files they depend on
   \par
   12.06.2018 -author P.Wegscheider
   - Feature request ID 8459: use iso_u8 for ISOBUS addresses in API
   - Replaced PGNDAT_T iso_u16 u16SAPGNSender with iso_u8 u8SAPGNSender
   \par
   12.07.2018 -author P.Wegscheider
   - Feature request ID 8000: updated external handle parameter to iso_s16 for iso_AlPgnTxNew(), iso_AlPgnRxNew() and iso_AlPgnChangeSrcDestination().
   \par
   10.08.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files
   \par
   07.02.2020 - author P.Wegscheider
   - Feature request BugID 11700: rename CCI_BASE_API into ISO_BASE_API
   - Feature request ID 10185: refactor TL - Added "const" to the definition of the PGNDAT_T field pau8Data
   \par
   07.09.2020 - E. Hammerl
   - Feature request ID 12635: Added PGN to struct ISO_AL_TX_INFO_Ts (Extends possibilities for AL TX callbacks)
*/

#ifndef DEF_MnApi_H
    #define DEF_MnApi_H

/* include configuration, driver standard types and common definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Al - Application layer interface */
/** \addtogroup apla Application Layer 
*/
/**@{*/

#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoMnApi.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */

#define HANDLE_AL_OFFSET       0x1000      /**< Offset for first PGN handle value */
#define REPRATE_INACTIVE       0xFFFFu     /**< Repetition rate inactive */

#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

/** \brief Typedef struct for controlling the receiption of PGNs  */
typedef struct 
{
   iso_s16       s16HandleOfSender;    /**< Handle of sender or HANDLE_UNVALID */
#if !defined(CCI_OMIT_ADDRESS) /* to be removed in V13 */
   iso_u8        u8SAPGNSender;        /**< SA of user which send data */
#endif /* !defined(CCI_OMIT_ADDRESS) */
   iso_u32       u32PGN;               /**< PGN of DATA */
   iso_u32       u32NumbofBytes;       /**< Number of bytes recorded */
   const iso_u8 HUGE_C *pau8Data;      /**< Pointer on data buffer */
   iso_u8        bPgnPriority;         /**< Priority of received Pgn */
   iso_bool      qTimedOut;            /**< True means cyclic PGN is not received timely */
   /* Added for V10.0 */
   iso_s16       s16PgnHandle;         /**< \brief Identifier of this entry */
   iso_s16       s16HandleOfReceiver;  /**< \brief Internal CF handle ir HANDLE_GLOBAL */
   iso_s16       s16OwnCfHnd;          /**< \brief CF handle of the entry for which the callback is triggered (if receiver entry is HANDLER_GLOBAL) */
   ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with iso_AlPgnRxNew() */
#if defined(CCI_TIMESTAMP)
   iso_s32        s32TimeStamp;        /**< \brief Time stamp of the message in ms */
#endif /* defined(CCI_TIMESTAMP) */
} PGNDAT_T;

typedef PGNDAT_T *PGNDAT_t;            /**< Pointer typedef for #PGNDAT_T */

/** \brief Typedef struct for send callback informations of PGNs  */
typedef struct
{
   iso_s16       s16PgnHandle;         /**< \brief Identifier of this entry */
   iso_s16       s16OwnCfHnd;          /**< \brief Internal CF handle of the entry for which the callback is triggered  ????? */
   iso_u32       u32PGN;               /**< \brief PGN of PGN handle and releated data  */
   ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with iso_AlPgnRxNew() */
} ISO_AL_TX_INFO_Ts;

/*! \brief  Callback function pointer declaration for a function to manipulate the message data before sending. 
   
   \param[in]     \wpp{psTxInfo, const #ISO_AL_TX_INFO_Ts*}
                  Handle of the TxPGN entry
   \param[in,out] \wp{pu16DataSize, iso_u16*}
                  Pointer to the message data length; \n
                  Pointer content value:
                  - [in]  current data length
                  - [out] new or same data length  
   \param[in,out] \wp{pau8PtrData, iso_u8*[]}
                  Pointer to the data byte array
                  Pointer content value:
                  - [in]  current data array pointer
                  - [out] new or same data array pointer
   \param[in,out] \wp{pu8Priority, iso_u8*}
                  Pointer to the CAN priority for this PGN entry
                  Pointer content value:
                  - [in]  current priority
                  - [out] new or same priority
                  
   \retval        iso_s16
                  - #E_NO_ERR on success
                  - < 0 -> Don not send (if cyclic call again in next cyclic run, else skip)

   \par Hint:
   The callback function can be set with iso_AlPgnTxNew(). \n
   It is called on an external request, cyclic (if enabled) and from iso_AlPgnTxSend(). \n
   The main goal of this function is to update the message data before sending.  \n
   It is also possible to change the data length, the array location and the message priority.
   The changes are also stored in the entry and will be the defaults for the next call.
   The application is responsible to make sure that the data length is not greater as the given data array.

   \par Sample callback function
   \code{.c}
   static iso_s16 CbIsoAlSetTxPgnData(const ISO_AL_TX_INFO_Ts* psTxInfo, iso_u16* pu16DataSize, iso_u8* pau8PtrData[], iso_u8* pu8Priority)
   {
   iso_s16 s16Ret = E_NO_ERR;

   if (psTxInfo->s16PgnHandle == s16MyPgnHandle)  // check not needed if CB is only for one PGN entry 
    {  
       (*pu8Priority) = ((*pu8Priority) == 3u) ? 4u : 3u;
       (*pu16DataSize) = u16MsgSize;

       if (u16MsgSize > 8u)
       {  // set our static array (else we could also use the internal 8 byte array)
          *pau8PtrData = au8MsgData;
       }

       if (u16MsgSize >= 2u)
       {  // add some data
          (*pau8PtrData)[u16MsgSize - 2u] = 2u;
          (*pau8PtrData)[u16MsgSize - 1u] = (iso_u8)u16MsgSize;
       }
    }

    return s16Ret;
   }
   \endcode
   \par Sample for using iso_AlPgnTxNew() to set the callback function
   \code{.c}
   s16MyPgnHandle = iso_AlPgnTxNew( s16MyCfHandle, PGN_PDU1_PropA, s16CfHndDest,
                                    8u, 0, 3u, 2000u, userParam, CbIsoAlSetTxPgnData);
   iso_AlPgnActivate(s16MyPgnHandle);
   \endcode
*/
 typedef iso_s16 (*ISO_AL_CbSetTxData_t)(const ISO_AL_TX_INFO_Ts* psTxInfo, iso_u16* pu16DataSize, iso_u8* pau8PtrData[], iso_u8* pu8Priority);
  

 /* ******************************************************************** */
 /*!
    \brief          This function installs a Transmit PGN (TX) 
    
    \param[in]  \wp{s16NmHandle, iso_s16}    
                 Handle of network member assigned of Network management
    \param[in]  \wp{u32Pgn, iso_u32}         
                 PGN - Range: 0 - 0x3FFFF   
    \param[in]  \wp{s16NmDestin, iso_s16}      
                 Destination address of this (Transmit-) PGN
                  - 0 - 0xFD - SA of unclaimed network member 
                  - ISO_GLOBAL_ADDRESS - broadcast 
                  - Handle of extern network member
    \param[in]  \wp{u16DaSize, iso_u16}   
                 Data length of this PGN ( if variable set new size with iso_AlPgnTxChangeDataSize )
    \param[in]  \wp{pu8PtrData, iso_u8}   
                 Pointer to data located in application ( must be used if > 8 bytes ) \n
                  <= 8 bytes driver intern storage should be used and this pointer shall be zero 
    \param[in]  \wp{u8Priority, iso_u8}   
                  Default priority of this PGN
    \param[in]  \wp{u16DefRepRate, iso_u16}  
                  Default transmission repetition rate \n
                  Range: 0 ... 0xFDFF ms for time interval of cyclic transmission \n
                  Cyclic transmission is switched off with REPRATE_INACTIVE \n
                     -> Activation is then not possible 
    \param[in]  \wpp{userParam, const #ISO_USER_PARAM_T}
                  User parameter value for the callback function calls. \n
                  Use #ISO_USER_PARAM_DEFAULT if not used/needed.
    \param[in]  \wp{pfCbSetTxData, ISO_AL_CbSetTxData_t}  
                  NULL pointer or a pointer to a callback function which should be called before sending. \n
  
    \retval          iso_s16
                     - PGN-handle on success ( The handle numbers are starting with #HANDLE_AL_OFFSET \n
                        and will be incremented for every new RX or TX entry ) 
                     - #HANDLE_UNVALID in case of an error ( PGN-handle not valid )

    \par
    It is possible to add more than one entry for a specific sender and pgn, 
    to send in parallel multiple Tx-messages with same PGN, specific dest. and repetition rate. \n
    To use this functionality, make sure that at least the data buffer is different.
    \par
    PGNs created with iso_AlPgnTxNew() are disabled by default. That means they do not react to Requests. \n
    Use the function iso_AlPgnDeactivate() to switch on the response to requests and iso_AlPgnActivate() 
    to additionally switch on the sending of the TX-PGN.
    \par
    It is not allowed to use HANDLE_UNVALID (-1) as destination address (u16NmDestin). \n
    If needed use HANDLE_GLOBAL or ISO_GLOBAL_ADDRESS instead of HANDLE_UNVALID.
*/
   
ISO_BASE_API
 iso_s16 iso_AlPgnTxNew( iso_s16 s16NmHandle,
                         iso_u32 u32Pgn,
                         iso_s16 s16NmDestin,
                         iso_u16 u16DaSize,
                         iso_u8* pu8PtrData,
                         iso_u8  u8Priority,
                         iso_u16 u16DefRepRate,
                         const ISO_USER_PARAM_T userParam,
                         ISO_AL_CbSetTxData_t pfCbSetTxData);

 /* ********************************************************************* */
 /*!
    \brief          This function installs a Receive PGN (RX) 

    \param[in]      \wp{s16NmHandle, iso_s16}         
                     Handle of network member assigned of Network management
    \param[in]      \wp{u32Pgn, iso_u32}     
                     PGN - Range: 0 - 0x3FFFF
    \param[in]      \wp{s16NmSource, iso_s16}    
                     Source of this PGN
                     - 0 - 0xFD - SA of unclaimed network member  
                     - ISO_GLOBAL_ADDRESS - sender is don't care  
                     - Handle of extern network member (specific sender)  
    \param[in]      \wp{u16DaSize, iso_u16}   
                     Data length of this PGN ( if variable maximum expected size must be entered )
    \param[in]      \wp{pu8PtrData, iso_u8*} 
                     Pointer to data located in application ( must be used if > 8 bytes and rpfCbPgn is the NULL pointer ) \n
                     <= 8 bytes driver intern storage should be used and this pointer shall be zero 
    \param[in]      \wp{u8Priority, iso_u8}  
                     Default priority of this PGN ( not used e. g. in order to filter PGNs )
    \param[in]      \wp{u16CtrlTime, iso_u16}  
                     Control time of a receive PGN \n
                     Range: 0 ... 0xFDFF ms \n
                     REPRATE_INACTIVE - time control is switched off
    \param[in]      \wpp{userParam, const #ISO_USER_PARAM_T}
                     User parameter value for the callback function calls. \n
                     Use #ISO_USER_PARAM_DEFAULT if not used/needed.
    \param[in]      \wpp{rpfCbPgn, void(*)(const #PGNDAT_T*)}  
                     It can be installed a own callback function for this PGN, if this callback 
                     is not used set this parameter to 0 (NULL) 

    \retval          iso_s16           
                     - PGN-handle on success ( The handle numbers are starting with #HANDLE_AL_OFFSET \n
                        and will be incremented for every new RX or TX entry ) 
                     - #HANDLE_UNVALID in case of an error ( PGN-handle not valid )

   \par             
                    If the callback function parameter rpfCbPgn is not NULL \n
                    and the received data are greater than the defined data buffer size, \n
                    the callback function uses the original TP buffer. \n
                    ( This buffer is only valid during the call...)

   \par
                    It is not allowed to use HANDLE_UNVALID (-1) as source address (u16NmSource). \n
                    If needed use HANDLE_GLOBAL or ISO_GLOBAL_ADDRESS instead of HANDLE_UNVALID.
 
*/
ISO_BASE_API
iso_s16 iso_AlPgnRxNew(  iso_s16 s16NmHandle,
                         iso_u32 u32Pgn,
                         iso_s16 s16NmSource,
                         iso_u16 u16DaSize,
                         iso_u8* pu8PtrData,
                         iso_u8  u8Priority,
                         iso_u16 u16CtrlTime,
                         const ISO_USER_PARAM_T userParam,
                         void  (*rpfCbPgn)( const PGNDAT_T* psPgnDat ) );


/***********************************************************************/
/*!
   \brief        This function activates a PGN

     Activation of a PGN means:  
      - Receive PGN:  Enable reception and (if initialised) time control  
      - Transmit PGN: Starts the cyclic sending with the initialised repetition rate   
   
   \param[in]     \wp{s16PgnHandle, iso_s16}  
                    Handle of PGN assigned of iso_AlPgnTx/RxNew()      
   \retval        iso_s16
                   - #E_NO_ERR on success
                   - #E_PGN_UNKNOWN  PGN not found  
   \note  \par
      (De-)Activation for Transmit PGNs means Off/On of transmitting. A PGN is anyway
      responded if it is requested of the network. 
 */
ISO_BASE_API
 iso_s16 iso_AlPgnActivate( iso_s16 s16PgnHandle );

/* ********************************************************************* */
/*!
   \brief        This function deactivates a PGN
     Deactivation of a PGN means:  
     - Receive PGN:  Disable reception and (if initialised) time control  
     - Transmit PGN: Stops the cyclic sending with the initialised repetition rate

   \param[in]   \wp{s16PgnHandle, iso_s16}  
                  Handle of PGN assigned of iso_AlPgnTx/Rx-New()   
   \retval      iso_s16             
                  - #E_NO_ERR on success
                  - #E_PGN_UNKNOWN  PGN not found       
     
*/
ISO_BASE_API
 iso_s16 iso_AlPgnDeactivate( iso_s16 s16PgnHandle );

/* ********************************************************************* */
/*!
   \brief        This function disables a PGN

    Disabling means a PGN stops activity completely 

   \param[in]     \wp{s16PgnHandle, iso_s16}
                  Handle of PGN assigned of iso_AlPgnTx/Rx-New()
   \retval       iso_s16
                  - #E_NO_ERR on success
                  - #E_PGN_UNKNOWN  PGN not found
*/
ISO_BASE_API
iso_s16 iso_AlPgnDisable( iso_s16 s16PgnHandle );

/* ********************************************************************* */
/*!
   \brief           This function changes the priority
  
   \param[in]     \wp{s16PgnHandle, iso_s16}  
                   Handle of PGN assigned of iso_AlPgnTxNew()   
   \param[in]     \wp{u8Priority, iso_u8}    
                   New priority of PGN
   \retval        iso_s16
                   - #E_NO_ERR on success
                   - #E_PGN_UNKNOWN PGN not found       
*/
ISO_BASE_API
iso_s16 iso_AlPgnTxChangePriority( iso_s16 s16PgnHandle, iso_u8 u8Priority );

/*  ******************************************************************** */
/*!
   \brief        This function changes the data length of (variable) TX-PGNs 

   \param[in]     \wp{s16PgnHandle, iso_s16}  
                   Handle of PGN assigned of iso_AlPgnTxNew()
   \param[in]     \wp{u16DataSize, iso_u16}   
                    New data length of the PGN
  
   \retval         iso_s16   
                    - #E_NO_ERR  on success
                    - #E_PGN_UNKNOWN  PGN not found
                    - #E_OVERFLOW  data size for the internal buffer is limited to 8 bytes 
   \note  \par
   - This function can be used to adapt the data length of e. g. DM1, DM2
*/
ISO_BASE_API
iso_s16 iso_AlPgnTxChangeDataSize( iso_s16 s16PgnHandle, iso_u16 u16DataSize );

/* ********************************************************************* */
/*!
   \brief           This function changes the destination or the source of a PGN
   \param[in]       \wp{rs16PgnHandle, iso_s16}  
                     Handle of PGN assigned of iso_AlPgnTx/Rx-New()   
   \param[in]       \wp{s16SrcDestination, iso_s16}  
                     New Destination( TX ) or Source(RX) of this PGN
                     - 0 - 0xFC - SA of unclaimed network member  
                     - ISO_GLOBAL_ADDRESS - broadcast  
                     - Handle of extern network member  
   \retval         iso_s16
                    - #E_NO_ERR on success
                    - #E_PGN_UNKNOWN  PGN not found    
            
*/
ISO_BASE_API
iso_s16 iso_AlPgnChangeSrcDestination( iso_s16 rs16PgnHandle, iso_s16 s16SrcDestination );

/* ********************************************************************* */
/*!
    \brief         This function sets a new transmission repetition rate
    \param[in]     \wp{s16PgnHandle, iso_s16}  
                    Handle of PGN assigned of iso_AlPgnTxNew()
    \param[in]     \wp{u16RepetitionRateMs, iso_u16}  
                    New repetition rate of this PGN, Range: 0 ... 0xFAFF ms
    \retval        iso_s16      
                   - #E_NO_ERR  on success
                   - #E_PGN_UNKNOWN  PGN not found  
                   - #E_CONFIG  there are no limits ( iso_AlPgnTxSetLimitsReqForRepet() not called ) 
                   - #E_VALUE_WRONG  New repetition rate is outside the limits
    \note  \par
                  Precondition: iso_AlPgnTxSetLimitsReqForRepet() must be called \n
*/
ISO_BASE_API
iso_s16 iso_AlPgnTxSetRepetitionRateMs( iso_s16 s16PgnHandle, iso_u16 u16RepetitionRateMs );

/* ******************************************************************** */
/*!
   \brief         This function reads the actual transmission repetition rate
   \param[in]     \wp{s16PgnHandle, iso_s16}  
                    Handle of PGN assigned of iso_AlPgnTxNew()    
   \param[out]    \wp{u16RepetitionRateMs,  iso_u16*}  
                    Value of the used repetition rate, Valid range: 0 ... 0xFAFF ms
   \retval        iso_s16        
                  - #E_NO_ERR       on success
                  - #E_PGN_UNKNOWN  PGN not found
                  - #E_RANGE        u16RepetitionRateMs is NULL pointer

*/
ISO_BASE_API
iso_s16 iso_AlPgnTxGetRepetitionRateMs( iso_s16 s16PgnHandle, iso_u16* u16RepetitionRateMs );

/* ********************************************************************* */
/*!
   \brief         This function sets the minimum and maximum transmission repetition rate for a TX PGN.

   Calling this function is necessary that the "Request for repetition rate" message is accepted. \n
   The Request is only accepted for a cyclic TX PGN if the the destination address  
   ( set with iso_AlPgnRxNew() ) is the global address or the requester address.

   \param[in]     \wp{rs16PgnHandle, iso_s16}  
                   Handle of PGN assigned of iso_AlPgnTxNew() 
   \param[in]     \wp{ru16TimeRepRateMinMs, iso_u16}  
                   Minimum value for the repetition value of a Transmit PGN  \n
                   Range: 0 ... 0xFAFF ms
   \param[in]     \wp{ru16TimeRepRateMaxMs, iso_u16}   
                   Maximum value for the repetition value of a Transmit PGN  \n
                  Range: 0 ... 0xFAFF ms, must be higher than minimum
   \retval        iso_s16
                  - #E_NO_ERR  on success
                  - #E_PGN_UNKNOWN  PGN not found 
                  - #E_VALUE_WRONG  Parameter is invalid see range, minimum higher than maximum .. 
*/
ISO_BASE_API
iso_s16 iso_AlPgnTxSetLimitsReqForRepet( iso_s16 rs16PgnHandle, 
                                         iso_u16 ru16TimeRepRateMinMs, 
                                         iso_u16 ru16TimeRepRateMaxMs   );


/* ********************************************************************* */
/*!
   \brief      This function sets a new alive timeout value
   \param[in]  \wp{s16PgnHandle, iso_s16}
               Handle of PGN assigned of iso_AlPgnRxNew()
   \param[in]  \wp{u16TimeoutMs, iso_u16}
               Time in ms to wait for next message \n
               Range: 0 ... 0xFDFF ms \n
               #REPRATE_INACTIVE - time control is switched off
   \retval     iso_s16
               - #E_NO_ERR  on success
               - #E_PGN_UNKNOWN  PGN not found
               - #E_VALUE_WRONG  New timeout value is outside the limits
*/
ISO_BASE_API
iso_s16 iso_AlPgnRxSetAliveTimeoutMs( iso_s16 s16PgnHandle, iso_u16 u16TimeoutMs );


/* ******************************************************************** */
/*!
   \brief      This function reads the actual alive timeout value 
   \param[in]  \wp{s16PgnHandle, iso_s16}
               Handle of PGN assigned of iso_AlPgnRxNew()
   \param[out] \wp{u16TimeoutMs,  iso_u16*}
               Value of the used alive timeout, Valid range: 0 ... 0xFAFF ms
   \retval     iso_s16
               - #E_NO_ERR       on success
               - #E_PGN_UNKNOWN  PGN not found
               - #E_RANGE        u16TimeoutMs is NULL pointer
*/
ISO_BASE_API
iso_s16 iso_AlPgnRxGetAliveTimeOutMs( iso_s16 s16PgnHandle, iso_u16* u16TimeoutMs );


/* ********************************************************************* */
/*!
   \brief         This function releases a single request for a RX PGN
   \param[in]     \wp{rs16PgnHandle, iso_s16}  
                  Handle of PGN assigned of iso_AlPgnRxNew()
   \retval        iso_s16
                  - #E_NO_ERR  on success
                  - #E_PGN_UNKNOWN  PGN not found
   \note  \par
      The destination address of the request is the source entry of the initialisation of this PGN
*/
ISO_BASE_API
iso_s16 iso_AlPgnRxRequest( iso_s16 rs16PgnHandle );

/* ********************************************************************* */
/*!
   \brief         This function releases the cyclic sending of requests for a RX PGN
   \param[in]     \wp{rs16PgnHandle, iso_s16}  
                   Handle of PGN assigned of iso_AlPgnRXNew()
   \param[in]     \wp{ru16TimeMsCyclic, iso_u16}  
                   Repetition time in ms for the requests, 
                  - Valid Range: 10 ... 0xFAFF ms
   \retval        iso_s16
                  - #E_NO_ERR  on success
                  - #E_PGN_UNKNOWN  PGN not found
                  - #E_VALUE_WRONG  Time parameter is not in a valid range 
   \note  \par
     This function includes activation of this RX-PGN.
*/
ISO_BASE_API
iso_s16 iso_AlPgnRxRequestCyclic( iso_s16 rs16PgnHandle, iso_u16 ru16TimeMsCyclic );

/* ******************************************************************** */
/*!
   \brief         This function sends a TX-PGN on the bus (manual sending)
   \param[in]     \wp{rs16PgnHandle, iso_s16}  
                  Handle of PGN assigned of iso_AlPgnTxNew()
   \retval        iso_s16
                  - #E_NO_ERR  on success
                  - #E_PGN_UNKNOWN  PGN not found   
   \note  \par 
     This function sends a PGN regardless if activated or not after iso_AlPgnTxNew().
*/
ISO_BASE_API
iso_s16 iso_AlPgnTxSend( iso_s16 rs16PgnHandle );


/**@}*/
/* Spn - Initialising, setting and reading of SPNs */
/** \addtogroup spni SPN Support 
    \ingroup  apla
*/
/**@{*/

    #ifndef NUMBERSPN_MAX
    /** \brief Maximum number of SPNs - predefined with 20
		  \details 	Number of SPNsNumber of PGNs which can be initialised in the revised 
						application layer which can be initialised in the revised application layer -
                  SPN-Support deactivation: NUMBERSPN_MAX = 0 -> IsoMnSpn.c must not be compiled */
    #define NUMBERSPN_MAX        20
    #endif /* NUMBERSPN_MAX */

    /** \brief Enum in order to initialise the analyse of SPN data   */
    typedef enum 
    {
      SpnValStandard,         /**< See Signal Ranges ISO 11783 Part 7 Tabel 1 - 3 */
      SpnValSpecial,
      SpnValUndef
    } SPNVALINT_e;

/* ************************************************************************ */
/*! 
   \brief         This function initialises a SPN which belongs to a PGN handle. SPN see 
                  parameter definitions in ISO11783-7 Annex A, J1939-71 Annex B and iso_u8- and bitpositions 
                  see ISO11783-7 Annex B, J1939-71 Annex C

   \param[in]     \wp{rs16PgnHandle,iso_s16}
                   Handle of PGN assigned of iso_AlPgnTx(RX)New()
   \param[in]     \wp{ru32Spn,iso_u32}
                   SPN
   \param[in]     \wp{ru16BytePos,iso_u16}
                   Byteposition of data field of this PGN, 1...n
   \param[in]     \wp{ru8BitPos,iso_u8}
                   Bitposition of a iso_u8 of this PGN - allowed values 1 - 8  \n
                   For (Bit-)Length 8, 16, 24, 32 only bitposition 1 is allowed
   \param[in]     \wp{ru16BitLength,iso_u16}
                  (Bit-)Length of parameter - allowed values 1 - 10, 16, 24, 32
   \param[in]     \wp{eSpnInterpret,SPNVALINT_e}
                   - SpnValStandard - normal interpretation of parameter   \n
                                     See Signal Ranges ISO 11783 Part 7 Tabel 1 - 3 
                   - SpnValSpecial - Error or NotAvailable detection switched off 
   \retval        iso_s16        
                  - #E_NO_ERR       on success
                  - #E_PGN_UNKNOWN  PGN of SPN not found
                  - #E_RANGE        Bytepos, Bitpos or Length not supported
*/  
ISO_BASE_API
 iso_s16 iso_SpnDefineSpn( iso_s16 rs16PgnHandle,
                           iso_u32 ru32Spn,
                           iso_u16 ru16BytePos,
                           iso_u8  ru8BitPos,
                           iso_u16 ru16BitLength,
                           SPNVALINT_e eSpnInterpret
                          );

/* ************************************************************************** */
/*!
    \brief         This function sets a parameter value of a SPN

    \param[in]     \wp{rs16PgnHandle, iso_s16}
                    Handle of PGN assigned of iso_AlPgnTx(RX)New()
    \param[in]     \wp{ru32Spn, iso_u32}
                    SPN
    \param[in]     \wp{u32Write, iso_u16}
                    New parameter value 
    \retval        iso_s16        
                   - #E_NO_ERR       on success
                   - #E_PGN_UNKNOWN  PGN of SPN not found  
                   - #E_RANGE        Bitlength is not supported
*/
ISO_BASE_API
iso_s16 iso_SpnDataSet( iso_s16 rs16PgnHandle, iso_u32 ru32Spn, iso_u32 u32Write );


/* ************************************************************************* */
/*!
    \brief         This function reads a parameter value of a SPN

    \param[in]     \wp{rs16PgnHandle, iso_s16}
                    Handle of PGN assigned of iso_AlPgnTx(RX)New()
    \param[in]     \wp{ru32Spn, iso_u32}
                    SPN
    \param[out]    \wp{u32Result, iso_u32*}
                    Value of a SPN
    \retval        iso_s16      
                   - Errorcodes:
                      - #E_PGN_UNKNOWN     PGN of SPN not found 
                      - #E_RANGE           Bitlength is not supported
                   - Value information code:
                      - #E_NO_ERR          OK, Value in valid range see Part 7 Table 1 - 3  
                      - #E_ERROR_INDI      Value Error indicator see Part 7 Table 1 - 3  
                      - #E_NOT_AVAILABLE   Value Not Available see Part 7 Table 1 - 3  
*/
ISO_BASE_API
iso_s16 iso_SpnDataRead( iso_s16 rs16PgnHandle, iso_u32 ru32Spn, iso_u32 *u32Result );

/* ************************************************************************ */
/*! 
    \brief         This function reads a parameter value direct with startbit and length

    This function reads parameter direct. It can be used e. g. when data are received in own callbackfunctions.

    \param[in]     \wp{u8BitAdr, iso_u8}
                    StartBitaddress of the SPN - Range 0 - 63 
    \param[in]     \wp{u8BitLen, iso_u8} 
                   Bitlength - Range: 0 - 32
    \param[in]     \wpp{pau8Data, const iso_u8[]} 
                    Pointer to data
    \param[out]    \wp{pu32Result, iso_u32*} 
                    Value of a parameter (SPN)
    \retval        iso_s16           
                   - #E_NO_ERR     on success
                   - #E_OVERFLOW   Addressbit or length is wrong \n
*/  
ISO_BASE_API
iso_s16 iso_SpnDataReadCom( iso_u8 u8BitAdr, iso_u8 u8BitLen, const iso_u8 pau8Data[], iso_u32 *pu32Result );

/* ************************************************************************ */
/*!
    \brief        DM1, DM2 support: Initialises an array for DM1 or DM2 messages

    \param[in]    \wp{pau8Array, iso_u8[]} 
                   Pointer to application array for DTCs
    \param[in]    \wp{s16ArraySize, iso_s16} 
                   Size of array
    \param[in]    \wp{ps16NumbOfDTCs, iso_s16*} 
                  
*/
ISO_BASE_API
void iso_SpnDMResetDTC( iso_u8 pau8Array[], iso_s16 s16ArraySize, iso_s16* ps16NumbOfDTCs );

/* ************************************************************************ */
/*!
    \brief         DM1, DM2 support: Adding a DTC entry into an array

    \param[in]     \wp{pau8Array, iso_u8[]} 
                    Pointer to application array for DTCs
    \param[in]     \wp{s16ArraySize, iso_s16} 
                    Size of array
    \param[in]     \wp{ps16NumbOfDTCs, iso_s16*} 
                    Pointer to number of DTC entries
    \param[in]     \wp{u32Spn, iso_u32} 
                    SPN of new entry
    \param[in]     \wp{u8FMI, iso_u8} 
                    FMI of new entry
    \param[in]     \wp{u16OccurenceCount, iso_u16} 
                    Occurence counter
    \retval        iso_s16           
                   - #E_NO_ERR      on success
                   - #E_OVERFLOW    DTC not entried because buffer is to small
*/
ISO_BASE_API
iso_s16 iso_SpnDMAddDTC( iso_u8 pau8Array[], iso_s16 s16ArraySize, iso_s16* ps16NumbOfDTCs,
                         iso_u32 u32Spn,     iso_u8  u8FMI,        iso_u16  u16OccurenceCount );

/**@}*/

/* ************************************************************************ */
/* Interface of the heartbeat client / server */
/* ************************************************************************ */

/** \addtogroup hbapi Heartbeat Client / Server
  @{ */

/* ************************************************************************ */
/*! 
   \brief Enum Heartbeat client events 
*/
   typedef enum
   {
      IsoHBC_RequestTimeout,     /*!< \brief Heartbeat (HB) server does not answer on request for repetition rate. \n
                                             We do not try again (connection failed) */
      IsoHBC_MessageTimeout,     /*!< \brief HB server communication error. \n
                                             Next HB message was not received in time (ISO_HB_MSG_TIME_OUT_FACTOR * "repetition rate"). \n
                                             Client will stay in running state and try to recover. */
      IsoHBC_SequenceError,      /*!< \brief More than #ISO_HB_MISSMAX HB message sequence numbers missed. \n
                                             Client will stay in running state and try to recover.*/
      IsoHBC_ServerReset,        /*!< \brief HB message sequence number 251 received \n
                                             Client will stay in running state.*/
      IsoHBC_TransmissionError,  /*!< \brief HB message sequence number 254 received. \n
                                             Client will stay in running state and try to recover.*/
      IsoHBC_GracefulShutdown,   /*!< \brief HB message sequence number 255 received. \n
                                             Client is stopped. */
      IsoHBC_SequenceOperational /*!< \brief HB server is valid */
   } ISO_HBC_EVENT_e;


/* ************************************************************************ */
/*! 
   \brief Heartbeat client event callback information structure 
*/
   typedef struct
   {
      ISO_HBC_EVENT_e eClEvent;     /**< \brief Heartbeat client event */
      iso_s16 s16CfHandleClient;    /**< \brief CF handle of the internal client which has requested the HB server. */ 
      iso_s16 s16CfHandleServer;    /**< \brief CF handle of the external heartbeat server */
      ISO_USER_PARAM_T userParam;   /**< \brief User parameter set with iso_HBClient_Request() */
   } ISO_HBC_EVENT_DATA_Ts;

/* ************************************************************************ */
/*! 
   \brief Type definition of the heartbeat client event callback function.
   \details This function must be implemented from the application and given to the HBC with iso_HBClient_Request().
            The function is called from the driver in case of a state change.
            The event #IsoHBC_SequenceOperational signals that the requested HB server is valid. 
   \param[in]  \wpp{psClientEventData, const #ISO_HBC_EVENT_DATA_Ts*}
               Pointer to the event data / information.
*/
   typedef  void(*ISO_HBC_CbEvent_t)(const ISO_HBC_EVENT_DATA_Ts* psClientEventData);

/* ************************************************************************ */
/*! 
   \brief Enum Heartbeat server shutdown reason 
*/
   typedef enum
   {
      IsoHBS_Stop,               /*!< \brief Stop sending heartbeat message immediately and disable server instance */
      IsoHBS_TransmissionError,  /*!< \brief Send #ISO_HB_MISSMAX times heartbeat message with "error condition" before disabling the server instance */
      IsoHBS_GracefulShutdown    /*!< \brief Send #ISO_HB_MISSMAX times heartbeat message with "not available" before disabling the server instance */
   } ISO_HBS_STOPMODE_e;

/*! 
   \brief Enum Heartbeat server shutdown event 
*/
   typedef enum
   {
      IsoHBS_EvNone,    /*!< \brief event source not used */
      IsoHBS_Stopped    /*!< \brief Stopped sending heartbeat messages (server instance shutdown complete) */
   } ISO_HBS_EVENT_e;


/* ************************************************************************ */
/*! 
   \brief Heartbeat server callback information structure 
*/
   typedef struct
   {
      ISO_HBS_EVENT_e eSrvEvent;     /**< \brief Heartbeat server event */
      iso_s16 s16CfHandleServer;    /**< \brief CF handle of the internal heartbeat server */
      ISO_USER_PARAM_T userParam;   /**< \brief User parameter set with iso_HBServer_Install() */
   } ISO_HBS_DATA_Ts;


/* ************************************************************************ */
/*! 
   \brief Type definition of the heartbeat server callback function.
   \details This function can be implemented from the application and given to the HBS with iso_HBServer_Install().
            The function is called from the driver to get the next heartbeat sequence number value from the application.
            The driver sends this value without any validations.
   \param[in]  \wpp{psServerData, const #ISO_HBS_DATA_Ts*}
               Pointer to the server information. 
   \retval     iso_u8           
               - Heartbeat sequence number \n
                  Range: 0x00u - 0xFFu
*/
   typedef  iso_u8 (*ISO_HBS_CbGetSequenceNumber_t)(const ISO_HBS_DATA_Ts* psServerData);

/* ************************************************************************ */
/*! 
   \brief Type definition of the heartbeat server event callback function.
   \details This function can be implemented from the application and given to the HBS with iso_HBServer_Install().
            The function is called from the driver to signal the in #ISO_HBS_EVENT_e defined events.
   \param[in]  \wpp{psServerData, const #ISO_HBS_DATA_Ts*}
               Pointer to the server information. 
*/
   typedef  void (*ISO_HBS_CbEvent_t)(const ISO_HBS_DATA_Ts* psServerData);

/* ************************************************************************** */
/*! 
   \brief        Function to request the HB message of an external HB server
   \details      The client and server CF must be fully announced, before the function can be called.
   \param[in]    \wp{s16CfHandleInternal, iso_s16}
                  CF handle of the internal user/network member (client)
   \param[in]    \wp{s16CfHandleServer, iso_s16}
                  CF handle of an external heartbeat server 
   \param[in]    \wp{u16CtrlInterval, iso_u16}
                  Needed interval for the heartbeat message in ms (should be 100)
   \param[in]    \wpp{userParam, const #ISO_USER_PARAM_T}
                  User parameter value for the callback function calls. \n
                  Use #ISO_USER_PARAM_DEFAULT if not used/needed.
   \param[in]    \wp{pfCbClEvent, ISO_HBC_CbEvent_t}
                  Event callback function, which should be triggered in case of a state change 
   \retval        iso_s16           
                  - #E_NO_ERR on success
                  - #E_RANGE on a parameter error
                  - #E_USER_ERROR if one of the CF handles is invalid or not announced
                  - #E_OVERFLOW if HB client array is full (#ISO_HBC_MAX entries in use)
*/
ISO_BASE_API
   iso_s16 iso_HBClient_Request(iso_s16 s16CfHandleInternal, iso_s16 s16CfHandleServer, iso_u16 u16CtrlInterval,
                                const ISO_USER_PARAM_T userParam, ISO_HBC_CbEvent_t pfCbClEvent);

/* ************************************************************************** */
/*! 
   \brief        Function to remove a HB client-server entry
   \details      The function removes an entry, set with iso_HBClient_Request(), 
                 immediately and independent from the HB client state.
                 The callback function is not triggered. 
   \param[in]    \wp{s16CfHandleInternal, iso_s16}
                  CF handle of the internal user/network member (client)
   \param[in]    \wp{s16CfHandleServer, iso_s16}
                  CF handle of an external heartbeat server 
       
                  - #E_NO_ERR on success
                  - #E_RANGE on a parameter error

   \par Hints:
   It is possible to use #HANDLE_GLOBAL as CF handle for the client and/or the server 
   to skip the equal check for the parameter.
*/
ISO_BASE_API
   iso_s16 iso_HBClient_Remove(iso_s16 s16CfHandleInternal, iso_s16 s16CfHandleServer);

/* ************************************************************************** */
/*! 
   \brief      Function to setup the heartbeat server functionality for an internal CF.

   \param[in]  \wp{s16CfHandleInternal, iso_s16}
               CF handle of the internal heartbeat server 
   \param[in]  \wpp{userParam, const #ISO_USER_PARAM_T}
               User parameter value for the callback function calls. \n
               Use #ISO_USER_PARAM_DEFAULT if not used/needed.
   \param[in]  \wp{pfCbSvEvent, ISO_HBS_CbEvent_t}
               Optional callback function to inform the application  
               about the #ISO_HBS_EVENT_e defined state changes
               or NULL pointer.
   \param[in]  \wp{pfCbGetSeqNum, ISO_HBS_CbGetSequenceNumber_t}
               Optional callback function to allow the application to set 
               the heartbeat sequence number before sending.
               Use a NULL pointer to use the internal sequence number generator.
   \param[in]  \wp{qRestart, iso_bool}
               - #ISO_TRUE if the HB server should be restarted 
   \retval     iso_s16           
               - E_NO_ERR on success
               - #E_RANGE on a parameter error
               - #E_USER_ERROR if s16CfHandleInternal is unknown or in an error state
               - #E_OVERFLOW if HB server array is full (#ISO_HBS_MAX entries in use)
               - #E_NOACT if shutdown is not finished
*/
ISO_BASE_API
   iso_s16 iso_HBServer_Install(iso_s16 s16CfHandleInternal, const ISO_USER_PARAM_T userParam,
                                ISO_HBS_CbEvent_t pfCbSvEvent, ISO_HBS_CbGetSequenceNumber_t pfCbGetSeqNum, iso_bool qRestart);

/* ************************************************************************** */
/*! 
   \brief      Function to stop the heartbeat server for an internal CF.
   \param[in]  \wp{s16CfHandleInternal, iso_s16}
               CF handle of the internal heartbeat server 
   \param[in]  \wp{eMode, ISO_HBS_STOPMODE_e}
               Reason for stopping the HB server.  
   \retval     iso_s16           
               - #E_NO_ERR on success
               - #E_RANGE on a parameter error
*/
ISO_BASE_API
   iso_s16 iso_HBServer_Shutdown(iso_s16 s16CfHandleInternal, ISO_HBS_STOPMODE_e eMode);

/**@}*/



/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_MnApi_H */
/* ************************************************************************ */
