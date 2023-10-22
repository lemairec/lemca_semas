/* ************************************************************************ */
/*!
   \file
   \brief       ECU Driver Clients API Header File
   \author      Wegscheider Peter
   \date        Created XX.01.13

   \copyright   Competence Center ISOBUS e.V.

   \par         History:
   \par
   24.01.2013 - author P. Wegscheider
   - ISO 11783 Clients API declarations moved form IsoDef.h to this file
   \par
   15.05.2014 - author E. Hammerl
   - Version number updated
   - Added function IsoCFControlCbSet()
   \par
   08.04.2015 - author P. Wegscheider
   - Version number updated
   \par
   07.04.2016 - author P. Wegscheider
   - added IsoClientsGetTimeMs()
   \par
   14.12.2016 - author P. Wegscheider
   - Feature ID  4209: declare pointer parameter in functions as const* where applicable
      - IsoCbDataOfBasicDistributor() - set ISO_TPINFO_T as const
   \par
   26.01.2017 - author P. Wegscheider
   - Feature ID  4209: declare pointer parameter in functions as const* where applicable
      - #iso_fnCbCFControl_t - set ISOCFEVENT_T as const
   \par
   20.02.2017 - author P. Wegscheider
   - Feature ID 6003: client interfaces should only use handles (rather then ISOBUS NAME)
     - Added function IsoClGetCfHandleToName()
     - Replaced IsoSetWorkingSetMaster() parameter rabWsMasterName with s16CfHandleMaster
     - Replaced IsoAddWorkingSetMember() parameter rabWsMasterName with s16CfHandleMaster
     - Replaced IsoCFControlCbSet() parameter rabWsMasterName with s16CfHandleMaster
     - Replaced IsoReadAuxInputDevModIdentCode() parameter rabAuxInputDeviceName with s16CfHandleAuxInputDevice
   \par
   11.12.2017 - author P. Wegscheider
   - IsoClGraphicAuxCbSet() added for BugID 8108 to set a callback function for forwarding "VT" messages 
     from a graphical aux to the application
   \par
   13.02.2018 -author P.Wegscheider
   - Feature request ID 7504: Split Base Driver into "Base" and "AppInterface"
      - updated IsoClientsInit()
   \par
   06.05.2018 - author P.Wegscheider
   - Feature ID 3910: header files should include header files they depend on
   \par
   14.06.2018 -author P.Wegscheider
   - Feature request ID 8424: use ISO_CF_NAME_T in API functions
   \par
   02.08.2018 - author P. Wegscheider
   - BugID 9103: iso_s16 IsoCFControlCbSet() misses the user parameter
   \par
   10.03.2020 - author P.Wegscheider
   - Feature request BugID 11571: passing ETP packages between base and core should be extended between clients and base
   \par
   09.02.2021 - author P.Wegscheider
   - Feature BugID 12831: add a clientApi together with a client CF info copy
   - Moved define NULL_OBJECTID to IsoCommonDef.h
*/
/* ************************************************************************ */
#ifndef DEF_IsoClientsApi_H
    #define DEF_IsoClientsApi_H

/* include configuration, driver standard types and common definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* ************************************************************************ */
/* ************************************************************************ */
/** \defgroup clientsshared Clients Shared
    \ingroup  clients
*/
/* ************************************************************************ */
/** \defgroup clientscommon Clients Common
    \ingroup  clientsshared
*/

/* ************************************************************************ */
/** \addtogroup cfcontrol
@{
*/
/** \brief Event of alive control */
typedef enum
{
    IsoCF_Active,          /**< Client/Server cyclic message is received */
    IsoCF_Lost,            /**< Client/Server cyclic message is missing */
    IsoCF_LCReceived       /**< Server has sent a Language command */
} ISOCFEXT_EVENT_e;

/*! \brief Client/Server alive control event stucture */
typedef struct
{
    ISOCFEXT_EVENT_e  eCFEvent;        /**< \brief Client/Server active or lost */
    ISO_USERFUNC_e    eIsoUserFunct;   /**< \brief Function of the user on the bus */
    iso_s16           s16Handle;       /**< \brief Network member handle of the CF / network member */
    ISO_USER_PARAM_T  userParam;       /**< \brief User defined parameter set with IsoCFControlCbSet() */
} ISOCFEVENT_T;

/* **************************************************************************************** */
/*! \brief Typedef of the callback function pointer  */
typedef void (*iso_fnCbCFControl_t)( const ISOCFEVENT_T* psCfEvent);

/** @} */ /* END cfcontrol    */

/** \addtogroup clientscommon
@{
*/
/*****************************************************************************/
/*!
   \brief          This function installs the necessary callback functions for time base, watchdog and error handler

   Installs callback functions for clients and initialises the client modules.
   \param[in]    \wp{pfGetTimeMs, ISO_CbGetTimeMs_t }  
                  Pointer to the application specific timestamp callback function.
   \param[in]    \wp{pfTriggerWatchdog, ISO_CbTriggerWatchdog_t}  
                  Pointer to the watchdog trigger callback function or NULL pointer if not needed.
   \param[in]    \wp{pfErrorHandler, ISO_CbErrorHandler_t}
                     Pointer to the  error handler callback function or NULL pointer.  \n 
                     ( see also \ref errorhand for more information )

   \retval        iso_s16
                   - #E_NO_ERR  on success
                   - #E_RANGE rpfTime function pointer is the NULL pointer
   \note
   You must also call iso_BaseInit() to add a callback function to receive messages for the clients. \n
   See IsoCbDataOfBasicDistributor() for a single threading sample.
*/
ISO_CLIENT_API
iso_s16 IsoClientsInit( ISO_CbGetTimeMs_t pfGetTimeMs,
                        ISO_CbTriggerWatchdog_t pfTriggerWatchdog, 
                        ISO_CbErrorHandler_t pfErrorHandler );


/***************************************************************************************/
/*!
   \brief       MainCyclic Call function for clients

   This function executes the cyclic functions of all modules of the clients ( VTC, SCC, TCC ..)

   \retval      iso_s16
                - E_NO_ERR
*/

ISO_CLIENT_API
iso_s16  IsoClientsCyclicCall( void );

/************************************************************************************/
/*!
   \brief        This is the default receive callback function of all messages and infos for the clients
   \details
    \param[in]   \wpp{psMsgInfo, const #ISO_CORE_DD_MSGINFO_T*}
                 Pointer to the message information data
    \param[in]   \wpp{pau8Data, const #iso_u8 HUGE_C []}
                 Pointer to the message data byte array or NULL pointer
    \param[in]   \wp{u32DataSize, iso_u32}
                  Size of the given message data byte array \n
                  Range 0 to 1785 (max TP size) (with ISO_ETP_IN up to 117440512 (max ETP size))

   \par Sample
   Initialise ECU driver clients in single thread
   \code
    iso_BaseInit( TimeMs_get, fvWatchdog, CbErrorOutp, IsoCbDataOfBasicDistributor, 0 );
    IsoClientsInit( TimeMs_get, fvWatchdog, CbErrorOutp );
   \endcode
*/

ISO_CLIENT_API
void IsoCbDataOfBasicDistributor( const ISO_CORE_DD_MSGINFO_T *psMsgInfo, const iso_u8 HUGE_C pau8Data[], iso_u32 u32DataSize );

/* ************************************************************************ */
/*!
   \brief         Returns the current time since startup in milliseconds
   \retval        iso_s32
                  Time stamp in milliseconds

   The function uses the application-specific function of time, which was passed with IsoClientsInit().
*/
ISO_CLIENT_API
iso_s32 IsoClientsGetTimeMs(void);


/* ************************************************************************ */
/** @} */ /* END clientscommon                                              */
/* ************************************************************************ */


/* ************************** IsoWoSe.c  ********************************** */
/* ************************************************************************ */
/** \defgroup workset WorkingSet
    \ingroup  clientsshared
*/

/* ************************************************************************ */
/** \addtogroup workset
@{
*/

/******************************************************************************/
/*!
    \brief        This function sets a new working set master

    This function extends a normal CF to a working set master. VT and TC clients
    can only work on the base of a working set master.

    \param[in]    \wp{s16CfHandleMaster, iso_s16} 
                   CF handle of working set master
    \retval      iso_s16
                  - #E_NO_ERR
                  - #E_ERROR_INDI  - master already set
                  - #E_NO_INSTANCE - there is no empty working set entry 
                  - #E_USER_ERROR  - CF handle is not valid
    \par
    Use IsoClGetCfHandleToName(ISO_CAN_VT, ...) to get the CF handle for an ISOBUS NAME. 
*/
ISO_CLIENT_API
	 iso_s16 IsoSetWorkingSetMaster( iso_s16 s16CfHandleMaster);

/*****************************************************************************/
/*!
   \brief       Adding of a new member to the working set

   \param[in]    \wp{s16CfHandleMaster, iso_s16} 
                   CF handle of working set master
   \param[in]    \wpp{rpabNewMemberName, const #ISO_CF_NAME_T*}
                    Name of new member of the working set
   \retval        iso_s16
                   - #E_NO_ERR             - OK
                   - #E_OVERFLOW           - Array full
                   - #E_USER_ERROR         - WorkingSetMaster unknown
   \note  \par
        - Use IsoClGetCfHandleToName(ISO_CAN_VT, ...) to get the CF handle for an ISOBUS NAME. 
        - NAME can be created with IsoSetName()
        - Working set member functionality is not supported of driver ( -> manual handling )
*/
ISO_CLIENT_API
     iso_s16 IsoAddWorkingSetMember(iso_s16 s16CfHandleMaster, const ISO_CF_NAME_T* rpabNewMemberName );

/*****************************************************************************/
/*! 
   \brief         Function to get the "Model identification code" of an auxiliary input device
   \param[in]     \wp{s16CfHandleAuxInputDevice, iso_s16} 
                  CF handle of auxiliary input device
   \param[out]    \wp{psMic, iso_u16*} 
                  Returned "Model identification code" of the auxiliary unit device
   \retval        iso_s16
                - E_NO_ERR
                - E_ERROR_INDI - Working set not found
                - E_NOT_AVAILABLE - CF is not an auxiliary input device
*/
ISO_CLIENT_API
   iso_s16 IsoReadAuxInputDevModIdentCode(iso_s16 s16CfHandleAuxInputDevice, iso_u16 * psMic );
   
/* ************************************************************************ */
/** @} */ /* END workingset */
/* ************************************************************************ */

/* ************************************************************************ */
/** \defgroup cfcontrol Extern Client and Server Control
    \ingroup  clientsshared
*/

/* ************************************************************************ */
/** \addtogroup cfcontrol
@{
*/
/* ************************************************************************ */
/*! 
    \brief     Set optional "alive control" event callback function

    This function sets for a working set master the extern implement/server event callback
    ( CFs with cyclic messages )

    \param[in]  \wp{s16CfHandleMaster, iso_s16} 
                 CF handle of the working set master
    \param[in] \wpp{userParam, const #ISO_USER_PARAM_T}
                 User parameter value for the callback function calls. \n
                 Use #ISO_USER_PARAM_DEFAULT if not used/needed.
    \param[in]  \wp{pfnCallbackFunction, iso_fnCbCFControl_t}
                 Pointer to the callback function.
    \retval iso_s16
                 - #E_NO_ERR
                 - #E_NO_INSTANCE - Working set not found
    \par
    This function must be called after the IsoSetWorkingSetMaster() call!
*/
ISO_CLIENT_API
iso_s16 IsoCFControlCbSet( iso_s16 s16CfHandleMaster, const ISO_USER_PARAM_T userParam, iso_fnCbCFControl_t pfnCallbackFunction );

/* ************************************************************************* */
/*! 
   \brief          Read list of extern CFs

   The function reads a list of extern CFs which have a periodic status or maintenance message.
   It can be used only for following control functions:
   - working_set_master
   - task_controller
   - datalogger
   - virtual_terminal
   - auxiliary (unit devices)
   - sequenz_control_master
   - file_server
   - tim_server (master)
   - tim_server_slave

   \param[in]      \wp{eCFfunction, ISO_USERFUNC_e} 
                   Userfunction ( limited ) of the searched CFs
   \param[in]      \wp{s16ArrSizeForHand, iso_s16} 
                   Size of application array for handles see next parameter \n
                   Range: maximum ISO_USER_MAX 
   \param[out]     \wp{as16Handles, iso_s16 []} 
                   Pointer to a array of iso_s16 ( Size depends on bus good size is 10 - 30 ) \n
                   The driver entries all handles of extern network members here.
   \param[out]     \wp{s16NumbOfHa, iso_s16*} 
                   Number of extern network members 
   \retval         iso_s16          
                 - #E_NO_ERR
                 - #E_OVERFLOW - Application array is to small
                 - #E_RANGE - Input parameter unvalid
   \note  \par
        A CF is here only available after receiving of the first status or maintenance message
*/
ISO_CLIENT_API
iso_s16 IsoClientsReadListofExtHandles( ISO_USERFUNC_e eCFfunction, iso_s16 s16ArrSizeForHand,
                                        iso_s16 as16Handles[],       iso_s16* s16NumbOfHa );

/****************************************************************************/
/*!
    \brief        Reads the Language command of a server

    \param[in]   \wpp{rs16ServHandle, const #iso_s16 }
                   CF server handle
    \param[out]  \wpp{au8LanguageCmd, #iso_u8[] }
                   Pointer to Language command data\n
                   Hint: The size of the given array must be at least 8 bytes \n 
                   (Bytes 7 and 8 contain the country code or FF FF if not available)
    \retval       iso_s16  
                  - #E_NO_ERR
                  - #E_USER_ERROR
                  - #E_NOT_AVAILABLE - There are no valid LC data
*/
ISO_CLIENT_API
iso_s16 IsoClServ_ReadLCOfServer(const iso_s16 rs16ServHandle, iso_u8 au8LanguageCmd[]);

/****************************************************************************/
/*!
    \brief        Reads the Language command of the primary TECU

    \param[out]  \wpp{au8LanguageCmd, #iso_u8[]  }
                   Pointer to Language command data \n
                   Hint: The size of the given array must be at least 8 bytes \n 
                   (Bytes 7 and 8 contain the country code or FF FF if not available)
    \retval       iso_s16  
                  - #E_NO_ERR
                  - #E_NOT_AVAILABLE - There are no valid LC data of the primary TECU
*/
ISO_CLIENT_API
iso_s16 IsoClServ_ReadLCofTECU(iso_u8 au8LanguageCmd[]);

/* ************************************************************************ */
/** @} */ /* END cfcontrol */
/* ************************************************************************ */

/* ************************************************************************ */
/** \defgroup dlclients DataLink layer functions of the client layer
    \ingroup  clientsshared
*/

/* ************************************************************************ */
/** \addtogroup dlclients
@{
*/
/* ************************************************************************ */

/* ************************************************************************ */
/*!
   \brief      Sending of PGN messages to a destination

   This function starts the sending of a CAN message for specific PGN to a receiver  \n
   In case of more than 8 data bytes using of TP (or BAM) or ETP is included.
   The function should be used from client layer applications instead of iso_DlPgnSend() in multi thread environments.

   \param[in]  \wp{u8Priori, iso_u8}
                  Priority of PGN (normal default see J1939-71, ISO11783-7,8 ...) \n
                  Range: 0 - 7
   \param[in]  \wp{u32Pgn, iso_u32}
                  PGN of the CAN message \n
                  Range: 0 ... 0x3FFFF
   \param[in]  \wp{u32DataLength, iso_u32}
                  Number of data bytes to send
                  -    0 ..     8 : Single CAN message
                  -    9 ..  1785 : Transport protocol is automatic used
                  - 1786 .. ETP limit: Extended transport protocol is automatic used
   \param[in]  \wpp{pu8Data, const #iso_u8 []}
                  Pointer to data byte array
   \param[in]  \wp{s16HndSender, iso_s16}
                  CF handle of the internal sender 
   \param[in]  \wp{s16HndReceiver, iso_s16}
                  CF handle of the destination  \n
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
*/
ISO_CLIENT_API
iso_s16 IsoCl_PgnSend(iso_u8 u8Priori, iso_u32  u32Pgn,
   iso_u32  u32DataLength, const iso_u8 pu8Data[],
   iso_s16  s16HndSender, iso_s16  s16HndReceiver);

/* ************************************************************************ */
/** @} */ /* END dlclients */
/* ************************************************************************ */

/* ************************************************************************ */
/** \defgroup cfnmclients Network management functions of the client layer
    \ingroup  clientsshared
*/

/* ************************************************************************ */
/** \addtogroup cfnmclients
@{
*/
/* ************************************************************************ */

#if defined(ISO_CLIENT_NETWORK_DISTRIBUTOR)
/* function must be implemented by the application */
/*!
   \brief   Optional client driver network event distribution function.
   \details This is the default network event callback function
            which can be set with iso_BaseSetClientNetworkDistributor() in case of no external client distributor.
   \param[in]   \wpp{ psNetEv, const #ISONETEVENT_T*}
                 Vaild pointer to network event structure
   \par Hint: For multi threading this callback function can not set directly with iso_BaseSetClientNetworkDistributor().
              In this case the application must implement an own wrapper.
*/
ISO_CLIENT_API
void IsoCbClientNetworkDistributor(const ISONETEVENT_T* psNetEv);

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
   \par Hint:
   Only available with define ISO_CLIENT_NETWORK_DISTRIBUTOR
*/
ISO_CLIENT_API
iso_s16  IsoCl_GetListOfCfHandlesOfFunc(iso_u8 u8CanIdx, iso_bool bGetOnlyFullyAnnounced, ISO_CF_LOCATION_e eSearchLocation, iso_u8 u8NameFunction,
   iso_u16 u16ArrSizeForCfHandles, iso_s16 as16CfHandles[], iso_u16* pu16NumberOfCfs);


#endif /* defined(ISO_CLIENT_NETWORK_DISTRIBUTOR) */

/* ************************************************************************ */
/*!
   \brief      This function returns the network member information for a valid CF handle.
   \param[in]  \wp{s16CfHandle,iso_s16}
                Handle to network member / CF
   \param[out] \wp{psCfInfo,ISO_CF_INFO_T*}
                Pointer to the structure which should be filled
   \retval     iso_s16
                 - #E_NO_ERR on success
                 - #E_USER_ERROR Network member not found (psCfInfo not filled)
                 - #E_RANGE if psUserInfo is the NULL pointer
*/
ISO_CLIENT_API
iso_s16 IsoCl_GetCfInfo(iso_s16 s16CfHandle, ISO_CF_INFO_T* psCfInfo);

/* ************************************************************************* */
/*! \brief      Test if a control function / user is (full) announced

   \param[in]   \wp{s16CfHandle, iso_s16}
                  CF / user handle
   \retval      iso_bool  
                  ISO_TRUE if CF is announced else ISO_FALSE
*/
ISO_CLIENT_API
iso_bool IsoCl_CfIsAnnounced(iso_s16 s16CfHandle);

/* ************************************************************************* */
/*!
   \brief      Returns the member handle of a CF for a given ISO NAME
   \param[in]  \wp{u8CanIdx, iso_u8}
            CAN bus node index
   \param[in]  \wpp{pau8Name, const #ISO_CF_NAME_T*}
            Pointer to the 8 byte CF name array
   \retval	    iso_s16
            CF member handle or HANDLE_UNVALID
*/
ISO_CLIENT_API
iso_s16 IsoCl_GetCfHandleToName(iso_u8 u8CanIdx, const ISO_CF_NAME_T* pau8Name);

/* ************************************************************************* */
/*!
   \brief      Returns the member handle of a CF for a given source address
   \param[in]  \wp{u8CanIdx, iso_u8}
            CAN bus node index
   \param[in]  \wp{u8SA, iso_u8}
            Source address of the CF
   \param[in]  \wp{qCheckAnnounced, iso_bool}
            If ISO_TRUE the CF handle is only returned
            if the CF is almost full announced.
            If ISO_FALSE the state is not checked.
   \retval	    iso_s16
            CF member handle or HANDLE_UNVALID
*/
ISO_CLIENT_API
iso_s16 IsoCl_GetCfHandleToSA(iso_u8 u8CanIdx, iso_u8 u8SA, iso_bool qCheckAnnounced);


/* ************************************************************************ */
/*!
    \brief      Returns the CF member handle of a CF for a given ISO NAME
    \param[in]  \wp{u8CanIdx, iso_u8}
                CAN bus node index \n
                Should be set to #ISO_CAN_VT for the clients.
    \param[in]  \wpp{au8CfName, const #ISO_CF_NAME_T*}
                Pointer to the 8 byte CF name array
    \retval	    iso_s16
                CF member handle or HANDLE_UNVALID
    \par Hint:
    Deprecated: use IsoCl_GetCfHandleToName() instead
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoClGetCfHandleToName(iso_u8 u8CanIdx, const ISO_CF_NAME_T* au8CfName);

/* ************************************************************************ */
/** @} */ /* END cfnmclients */
/* ************************************************************************ */


/* TODO added for later implementation */

#if defined(ISO_CLIENT_MUTEX)
#if defined(ISO_CLIENT_MUTEX_RECURSIVE)
/*! \brief locks the clients mutex */
ISO_CLIENT_API
void iso_ClientMutexLock(void);
/*! \brief unlocks the clients mutex */
ISO_CLIENT_API
void iso_ClientMutexUnLock(void);
#else /* defined(ISO_CLIENT_MUTEX_RECURSIVE) */
/* CoreMutexLock may only be used in driver internal routines */
/*! \brief locks the clients mutex */
void iso_ClientMutexLock(void);
/*! \brief unlocks the clients mutex */
void iso_ClientMutexUnLock(void);
#endif /* defined(ISO_CLIENT_MUTEX_RECURSIVE) */
#endif /* defined(ISO_CLIENT_MUTEX) */

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_IsoClientsApi_H */
/* ************************************************************************ */
