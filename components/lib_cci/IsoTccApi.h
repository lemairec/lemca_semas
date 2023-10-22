/* ************************************************************************ */
/*!
   \file
   \brief       ECU Driver TC Client API Header File
   \author      Wegscheider Peter
   \date        Created XX.07.13

   \copyright   Competence Center ISOBUS e.V.

   \par         History:
   \par
   04.07.2013 - author P. Wegscheider
   - API declarations moved to this file
   - Module version define added
   \par
   12.12.2013 - author E. Hammerl
   - Config- and TC versions defines moved from IsoTaskC.c to here
   - Added IsoTC_SetVersionMsg()
   \par
   11.06.2014 - author E. Hammerl
   - Version updated to 2.2
   - Added IsoTC_SetPrefTC() 
   - Added IsoTC_Read_TCHandle()
   \par
   25.03.2015 - author E. Hammerl
   - Datalogger and Version 4 extensions
   \par
   10.05.2016 - author E. Hammerl
   - Added peer control functionality ( without API changes )
   - Added Event IsoEvLanguageCmdReceived ( called if LC of TC ( >=V4 ) is changed 
   - Structure label parameter changed from iso_char to iso_u8
   \par
   07.12.2016 - author E. Hammerl
   - Added Process Data Error Codes and IsoValueCommandAcknow
   \par
   16.12.2016 - author E. Hammerl
   - Feature request ID 4629: client interfaces should only use handles
   - SA deleted of fun. IsoTC_ReloadDDObjects(), IsoTC_ChangeDesignator_Send(),
     IsoTC_SetDPDValue() and IsoTC_StatusInfoGet() 
   - IsoTcClosePool, IsoDlClosePool deleted
   \par
   21.02.2017 - author P. Wegscheider
   - Feature request ID 6003: client interfaces should only use handles (rather then ISOBUS NAME)
   - Replaced working set master NAME  parameter with CF handle for functions
     IsoTC_InstCmd(), IsoTC_SetPrefTC(), IsoTC_SetPrefDL(), IsoTC_Read_TCHandle() and IsoTC_Read_DLHandle()
   \par
   13.02.2018 - author P. Wegscheider
   - Feature request ID 7676: missing const in callback parameter \n
     Added const to TC callback function to parameter psTcCbConn, 
     installed with IsoTC_InstallCbConnection().
   \par
   20.02.2018 - author P.Wegscheider
   - Feature ID 7528: add user parameter to callback functions
   \par
   06.05.2018 - author P.Wegscheider
   - Feature ID 3910: header files should include header files they depend on
   \par
   14.06.2018 - author P.Wegscheider
   - Feature request ID 8424: use ISO_CF_NAME_T in API functions
   \par
   01.08.2018 - author P.Wegscheider
   - BugID 9093: mark IsoTC_Device_Set() as deprecated
   \par
   10.08.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files
   \par
   16.10.2018 - author P.Wegscheider
   - Feature request ID 9304: Wait in Event IsoEvLoadObjects \n
     Added function IsoTC_TriggerEventAgain().
   \par
   28.01.2019 - author P.Wegscheider
   - Feature BugID 10041: Make DPD trigger checking more uniform \n
     Added define #TC_LOOPCYCLEMAX_PDS to limit the number of PD entries checked in a cycle (default 100) \n
     and set the default for #TC_SENDCYCLEMAX_PDS to 50.
   \par 
   26.10.2020 - author P. Wegscheider
   - BugID 11528: Add ClNum to ISO_TCLINK_T
*/
/* ************************************************************************ */
#ifndef DEF_IsoTccApi_H
    #define DEF_IsoTccApi_H

/* include configuration, driver standard types and common definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */
/* ********************************* IsoTaskC.c  ************************** */
/** \defgroup taskc TC-Client
    \ingroup  clients
    \brief Part 10 - Task Controller Client
*/
/* ************************************************************************ */
/** \addtogroup taskc
@{
*/
/* ************************************************************************ */

   #ifndef PROCESSDATA_MAX
      #define   PROCESSDATA_MAX            (20u)  /**< Predefined number of process data ( -> more IsoConf.h) */
   #endif /* PROCESSDATA_MAX */
   #ifdef DOXYGEN
      #define   DEVICEDESCRIPTION_SIZE  (1000uL) /**< Predefined size of buffer for device description pool ( -> more IsoConf.h) */
   #endif /* DOXYGEN */
   #ifndef TC_NUMB_TCCLIENTS
      #define   TC_NUMB_TCCLIENTS           (1)  /**< Predefined number of possible TC/DL-Clients ( -> more IsoConf.h) */
   #endif /* TC_NUMB_TCCLIENTS */
   #ifndef TC_NUMNESTED_DE
      #define   TC_NUMNESTED_DE            (10)  /**< Predefined size of number of nested Device elements ( -> more IsoConf.h) */
   #endif /* TC_NUMNESTED_DE */
   #ifndef TC_DEFTCM_BOOTTIME
      #define   TC_DEFTCM_BOOTTIME        (10u)  /**< Predefined boottime for the preferred TC ( -> more IsoConf.h) */
   #endif /* TC_DEFTCM_BOOTTIME */
   #ifndef TC_TIMECYCLEMIN_PDS
      #define   TC_TIMECYCLEMIN_PDS      (ISO_TIME(15L)) /**< Predefined minimum timecycle for working with PDs  */
   #endif /* TC_TIMECYCLEMIN_PDS */
   #ifndef TC_SENDCYCLEMAX_PDS
      #define   TC_SENDCYCLEMAX_PDS       (50u)  /**< Predefined maximum of PDs which should be send in one cyclic call  */
   #endif /* TC_SENDCYCLEMAX_PDS */
   #ifndef TC_LOOPCYCLEMAX_PDS
      #define   TC_LOOPCYCLEMAX_PDS      (100u)  /**< Predefined maximum of PDs which should be checked in one cyclic call  */
   #endif /* TC_LOOPCYCLEMAX_PDS */

#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoTccApi.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */

   #define TCCLIENT_UNKNOWN        (0xFFu)   /**< Unvalid TC client (handle) */

   /* TC versions */  
   #define TC_DIS                      (0u)  /**< TC DIS     - first edition */
   #define TC_FDIS                     (1u)  /**< TC FDIS    - first edition */
   #define TC_ISO_1                    (2u)  /**< TC IS      - first edition - Default */
   #define TC_R2DIS                    (3u)  /**< TC DIS     - second edition */
   #define TC_R2IS                     (4u)  /**< TC FDIS/IS - second edition */

   /* Provided option bits */
   #define TC_SUPPORT_DOCU          (0x01u)  /**< Provided option: Supports documentation */
   #define TC_SUPPORT_TIME_POS      (0x02u)  /**< Provided option: Deprecated Version 3 for time and pos logging */
   #define TC_SUPPORT_TC_GEO_NOPOS  (0x02u)  /**< Provided option: GEO without positon based control */
   #define TC_SUPPORT_TC_GEO        (0x04u)  /**< Provided option: GEO with positon based control */
   #define TC_SUPPORT_PEER_CTRL     (0x08u)  /**< Provided option: Supports peer control assignment */
   #define TC_SUPPORT_TC_SC         (0x10u)  /**< Provided option: Supports implement section control */
   #define TC_SUPPORT_OPT2          (0x00u)  /**< Provided option iso_u8 2: Reserved as zero */           

   /* PD properties */
   #define TC_PROP_DEFAULT_SET      (0x01u)  /**< PD is member of default set */
   #define TC_PROP_SETABLE          (0x02u)  /**< PD is settable */
   #define TC_PROP_CONTROL_SOURCE   (0x04u)  /**< Control source */

   /* PD trigger methods */
   #define TC_TRIG_TIMEINTERVAL     (0x01u)  /**< PD Triggermethod time interval */
   #define TC_TRIG_DISTANCEINTERVAL (0x02u)  /**< PD Triggermethod distance interval */
   #define TC_TRIG_THRESHOLD_LIMITS (0x04u)  /**< PD Triggermethod threshold limits */
   #define TC_TRIG_ON_CHANGE        (0x08u)  /**< PD Triggermethod onchange */
   #define TC_TRIG_TOTAL            (0x10u)  /**< PD Triggermethod total */

   /* DDI definitions */
   #define TC_DDI_REQUEST_DEFAULT_PD    (0xDFFFu)  /**< DDI - RequestDefaultProcessData  */

   /* Process data error codes used in PDACK */
   #define  no_Pd_error                      (0u)  /**< PDACK no error */
   #define  err_PdCommandNotSupported        (1u)  /**< PDACK Command not supported ( intern used ) */
   #define  err_PdInvalidElementNumber       (2u)  /**< PDACK Invalid element number ( intern used ) */
   #define  err_PdDDINotSupportedByElement   (4u)  /**< PDACK DDI not supported by element ( intern used ) */
   #define  err_PdTriggerMethodNotSupported  (8u)  /**< PDACK Trigger method not supported ( intern used ) */
   #define  err_PdProcessDataNotSettable    (16u)  /**< PDACK PD not settable( intern used ) */
   #define  err_PdInvalidInterOrThreshold   (32u)  /**< PDACK Invalid/Unsupported interval/threshold( intern used ) */
   #define  err_PdNotConformDDIDefinition   (64u)  /**< PDACK PD value not conform to DDI definition */
   #define  err_PdOutsideOperationalRange  (128u)  /**< PDACK PD value is outside operational range of this device */

#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

#ifdef DOXYGEN
   /*! \def ISO_EXTERNAL_DDOPBUFFER  
      \brief  Add the define #ISO_EXTERNAL_DDOPBUFFER to IsoConf.h to enable the external pool RAM buffer functionality.
      \details The define is needed to replace the internal buffer with an external pool RAM buffer. \n
               The external buffer must have the size defined by DEVICEDESCRIPTION_SIZE. \n
               The pointer to this buffer must be set with IsoTcPoolSetBuffer(). 
   */
   #define ISO_EXTERNAL_DDOPBUFFER
#endif

   /** \brief
   Device element types
   */
   typedef enum
   {
      de_undef,
      de_device,
      de_function,
      de_bin,
      de_section,
      de_unit,
      de_connector,
      de_navigation,
      de_lastentry
   } DevElemType_e;

   /** \brief
   Enum of Login status of task controller client instance
   */
   typedef enum
   {
     InstanceUnused,
     ClientIsLoggedOut,
     ClientRestart,
     Address_claim,
     Waiting_6_seconds,
     WaitingTaskControllerStatus,
     WSMasterSend,
     WSMemberSend,
     WSTaskMessageSend,
     RequestVersionMessageSend,
     VersionMessageWaiting,
     TCVersionRequestWaiting,
     RequestLanguageCommandSend,
     LanguageCommandWaiting,
     LoadObjectsOfApp,
     RequestStructureLabelSend,
     StructureLabelResponseWaiting,
     RequestLocalizationLabelSend,
     LocalizationLabelWaiting,
     RequestObjectPoolTransferSend,
     ObjPoolTransferWaiting,
     ObjPoolDeleteSend,
     ObjPoolDeleteRespWaiting,
     ObjPoolActivateRespWaiting,
     TcRunning
   } ISOTC_ANNOUNCE_e;

   /** \brief
   Enum of status info
   */
   typedef enum
   {
      TC_ALIVE,                         /**< TC alive check - TC status message ok? */
      TCC_STATEOFANNOUNCING,            /**< see intern state machine of login (only for development) */
      TCC_STATE_ACT                     /**< Task active or not */
   } ISOTC_STATUS_e;

   /** \brief
   Enum which indicates the type of client ( TC or DL )
   */
   typedef enum
   {
      IsoClType_TC,                    /**< Client type: task controller */
      IsoClType_DL,                    /**< Client type: datalogger */
      IsoClType_DontCare               /**< Type is dont care if func work with client number */
   } ISO_CLTYPE_e;

   /** \brief
   Enum of command for setting the device description
   */
   typedef enum
   {
      IsoTcOpenInst,                    /**< Open a TC client instance  */
      IsoTcGetPointOfInst,              /**< Getting the number of a TC Client instance  */
      IsoTcLogOut,                      /**< Shut down and re-initialisation of a TC client */
      IsoDlOpenInst,                    /**< Open a DL client instance  */
      IsoDlGetPointOfInst,              /**< Getting the number of a DL Client instance  */
      IsoDlLogOut                       /**< Shut down and re-initialisation of a DL client */
   } ISO_TC_CMD_e;

   /** \brief
   Enum which indicates the type of TC process data callback 
   */
   typedef enum
   {
      IsoRequestValueCommand,           /**< Actual value - lValueNew shall be set with actual value  */
      IsoValueCommand,                  /**< Set point of TC - should be stored of application */
      IsoValueCommandAcknow,            /**< Set point of TC - should be stored of application */
      IsoResponseToCommand,             /**< Response of e. g. change designator message */
      IsoTaskStartStop,                 /**< Shows start, stop, resume of a task */
      IsoTCSizeOfDD,                    /**< Returns the real value of the DD in lValueNew */
      IsoTCVersionReceived,             /**< Deprecated: TC has sended the Version message */
      IsoTCPDACKReceived,               /**< TC od DL sends a PDACK */
      IsoTCtoAppLast
   } ISO_TCAPP_e;

   /** \brief
   Struct which is used as interface to the application
   */
   typedef struct
   {
      iso_u8      u8ClNo;               /**< Number of client instance */
      iso_u16     wDDObjID;             /**< Object ID of device description object */
      iso_u16     wDevElementNumb;      /**< Requested element number of TC (only process data) */
      iso_u16     wDDI;                 /**< Data dictionary identifier (only process data)*/
      iso_s32     lValueNew;            /**< New value for a #IsoRequestValueCommand \n
                                             or for #IsoValueCommandAcknow no_Pd_error or an error code */
      ISO_TCAPP_e ePDCmd;               /**< Kind of TC callback calling */
      ISO_USER_PARAM_T  userParam;      /**< User parameter set with IsoTC_InstallCbConnection() */
   } ISO_TCLINK_T;

   /** \brief
   Task Controller Version message data
   */
   typedef struct
   {
       iso_u8 u8VersionNumber;                /**< Version number of this TC client */
       iso_u8 u8Boottime;                     /**< Boottime - Number of seconds from power cycle to TC status */
       iso_u8 u8ProvidedOptions;              /**< First options iso_u8 of version message */
       iso_u8 u8ProvidedOptions2;             /**< Second options iso_u8 of version message */
       iso_u8 u8NumberBoomsForSC;             /**< Number of booms for section control */
       iso_u8 u8NumberSectionsForSC;          /**< Number of sections for section control */
       iso_u8 u8NumberControlChannels;        /**< Number of control channels for position based control */
   } ISO_TCVERS_T;

   /** \brief
   Enum which indicates the type of TC connection management callback 
   */
   typedef enum
   {
      IsoEvPrefServerNotAvailable,  /**< Select/set (another) preferred TC/DL (-> if Preferred TC/DL is not on the network) */
      IsoEvServerVersionAvailable,  /**< Version of server is available */
      IsoEvLanguageCmdReceived,     /**< Language and metrics are received */
      IsoEvLoadObjects,             /**< Create DDOP and PD list */
      IsoEvActivated,               /**< Login finished - client is in state TcRunning */
      IsoEvDeactivated,             /**< Client is deactivated ( logged out ) */
      IsoEvCmdSafeState,            /**< Application shall go into safe state 
                                         - Move to another TC or TC status msg not received */
      IsoEvTick,                    /**< Called every cycle */
      IsoEvLoginAborted,            /**< Uncoverable error during Login */
      IsoEvReloadDDOs,              /**< Request for reload objects (DVC and/or DVP) */
      IsoEvReloadFinished           /**< Pool activated after reload */
   } ISO_TCDLEVENT_e;

   /** \brief
   Struct which is used as interface for the connection callback
   */
   typedef struct
   {
      ISO_TCDLEVENT_e eClEvent;     /**< Requested event of driver see enum */
      iso_u8          u8ClNum;      /**< Number of client */
      ISO_USER_PARAM_T  userParam;  /**< User parameter set with IsoTC_InstallCbConnection() */
   } ISO_TCCBCONN_T;


/** \name TC Client Management Functions

Use this functions to create and connect a TC client

@{
*/
/*******************************************************************************/
/*!
   \brief         This function is for starting and stopping of TC/DL clients

   This function prepares with "IsoTcOpenInst/IsoDlOpenInst" a TC/DL client for login. 
   A running client has to be logout with this function before it can restarted with this 
   function again.

   \param[in]     \wp{s16CfHandleMaster, iso_s16}
                    CF handle of working set master which uses a TC Client
   \param[in]     \wpp{userParam, const #ISO_USER_PARAM_T}
                    User parameter value for the callback function calls. \n
                    Use #ISO_USER_PARAM_DEFAULT if not used/needed.
   \param[in]     \wpp{rpfPdCall, void(*)(#ISO_TCLINK_T*)}
                    Communication interface with task controller (Callbackfun.)
   \param[in]     \wpp{rpfCbClConn,  void(*)(const #ISO_TCCBCONN_T*)}
                    Callback function for connection control
   \param[in]     \wp{eCommand, ISO_TC_CMD_e}
                       Command - what shall this function do? \n
                              - IsoTcOpenInst - Open an new TC Client instance  
                              - IsoTcGetPointOfInst - Returns the number of a TC Client instance
                              - IsoTcLogOut - Shut down a TC client
                              - Same for datalogger e. g. IsoDlOpenInst
   \retval         iso_u8
                     - 0 ... (TC_NUMB_TCCLIENTS - 1) - Number of TC client instance  \n
                     - TCCLIENT_UNKNOWN: No TCC instance, CF not a WS Master or TCC not logged out

   \par Hint:
   The following parameter are only used if a connection gets created; eCommand = { IsoTcOpenInst, IsoDlOpenInst}
   - const ISO_USER_PARAM_T userParam
   - void (*rpfPdCall)( ISO_TCLINK_T* psTcLi )
   - void(*rpfCbClConn)(const ISO_TCCBCONN_T * psTcCbConn)
*/
ISO_CLIENT_API
iso_u8  IsoTC_InstCmd( iso_s16 s16CfHandleMaster,
                       const ISO_USER_PARAM_T userParam,
		                 void (*rpfPdCall)( ISO_TCLINK_T* psTcLi ),
                       void (*rpfCbClConn)( const ISO_TCCBCONN_T * psTcCbConn ),
			              ISO_TC_CMD_e eCommand
							);

/*****************************************************************************/
/*!
   \brief         Setting the preferred TC Server with its boottime

   This function sets the NAME of the preferred TC Server and its boottime. \n
   It only works correct if called immediately after creating a TC client or 
   for event IsoEvPrefServerNotAvailable.

   \param[in]     \wpp{s16CfHandleMaster, const #iso_s16}
                    CF handle of working set master which uses a TC Client
   \param[in]     \wpp{rapu8NamePreferredTC, const #ISO_CF_NAME_T*}
                    Pointer to NAME of the preferred TC \n
   \param[in]     \wpp{u16PrefTCBoottime, const iso_u16}
                    Boottime of the preferred TC in seconds \n
                    that means waittime for first TC status message
   \retval         iso_s16
                      - #E_NO_ERR        - 0K
                      - #E_NO_INSTANCE   - wrong instance 
                      - #E_NOACT         - TC statemachine > WaitingTaskControllerStatus
                      - #E_RANGE         - Null pointer given for rapu8NamePreferredTC
*/
ISO_CLIENT_API
iso_s16 IsoTC_SetPrefTC( const iso_s16 s16CfHandleMaster,
                         const ISO_CF_NAME_T*  rapu8NamePreferredTC,
                         const iso_u16 u16PrefTCBoottime );

/*****************************************************************************/
/*!
   \brief         Setting the preferred DL Server with its boottime

   This function sets the NAME of the preferred DL Server and its boottime. \n
   It only works correct if called immediately after creating a DL client or 
   for event IsoEvPrefServerNotAvailable.

   \param[in]     \wpp{s16CfHandleMaster, const #iso_s16}
                    CF handle of working set master which uses a DL Client
   \param[in]     \wpp{rapu8NamePreferredDL, const #ISO_CF_NAME_T*}
                    Pointer to NAME of the preferred TC \n
   \param[in]     \wpp{u16PrefDLBoottime, const iso_u16}
                    Boottime of the preferred DL in seconds \n
                    that means waittime for first TC status message
   \retval         iso_s16
                  - #E_NO_ERR        - 0K
                  - #E_NO_INSTANCE   - wrong instance
                  - #E_NOACT         - TC statemachine > WaitingTaskControllerStatus
                  - #E_RANGE         - Null pointer given for rapu8NamePreferredDL
*/
ISO_CLIENT_API
iso_s16 IsoTC_SetPrefDL(const iso_s16 s16CfHandleMaster,
                        const ISO_CF_NAME_T* rapu8NamePreferredDL,
                        const iso_u16 u16PrefDLBoottime);

/*****************************************************************************/
/*!
   \brief        Move to another TC/DL

   \param[in]   \wpp{u8ClInst, const iso_u8}
                 Number of TC Client instance
                 - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \param[in]   \wpp{rapu8NameNewServer, const #ISO_CF_NAME_T*}
                  Pointer to NAME of the TC or DL \n
   \param[in]   \wpp{u16PrefServerBoottime, const iso_u16}
                  Boottime of the TC or DL in seconds \n
                  that means wait time for first TC status message
   \retval       iso_s16
                 - #E_NO_ERR        - 0K
                 - #E_NO_INSTANCE   - Wrong instance
                 - #E_RANGE         - rapu8NameNewServer is a NULL pointer
*/
ISO_CLIENT_API
iso_s16 IsoTC_MoveToAnotherTCoDL( const iso_u8 u8ClInst,
                                 const ISO_CF_NAME_T* rapu8NameNewServer,
                                 const iso_u16 u16PrefServerBoottime);

/*****************************************************************************/
/*!
   \brief         Setting the data for the TCC Version message

   Default of version message data are TC Version number 2.
   The application must call this function for TC versions 3 or higher.

   \param[in]  \wpp{u8ClInst, iso_u8}
                 Number of TC Client instance
                 - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \param[in]  \wpp{u8VersionNumber, const #iso_u8}
                 Version number of this TC client see ISO-Standard 
   \param[in]  \wpp{u8ProvidedOptions, const #iso_u8}
                 First option iso_u8 of this TC client see defines #TC_SUPPORT_DOCU ff.
                 - 0xFF for TC-Version 2
   \param[in]  \wpp{u8ProvidedOptions2, const #iso_u8}
                 Second option iso_u8
                 - 0xFF for TC-Version 2
   \param[in]  \wpp{u8NumberBoomsForSC, const #iso_u8}
                 Number of required booms for section control
                 - 0xFF for TC-Version 2
   \param[in]  \wpp{u8NumberSectionsForSC, const #iso_u8}
                 Number of required sections for section control
                 - 0xFF for TC-Version 2
   \param[in]  \wpp{u8NumberControlChannels, const #iso_u8}
                 Number of required control channels for position based control
                 - 0xFF for TC-Version 2
   \retval      iso_s16
                 - #E_NO_ERR        - 0K
                 - #E_ERROR_INDI    - Instance not open for setting
                 - #E_NO_INSTANCE   - wrong instance    
   \note  \par
   Calling of this function is only allowed during building of DD
*/
ISO_CLIENT_API
iso_s16 IsoTC_SetVersionMsg( const iso_u8 u8ClInst,
                            const iso_u8 u8VersionNumber,
                            const iso_u8 u8ProvidedOptions,
                            const iso_u8 u8ProvidedOptions2,
                            const iso_u8 u8NumberBoomsForSC,
                            const iso_u8 u8NumberSectionsForSC,
                            const iso_u8 u8NumberControlChannels
                          );

/*****************************************************************************/
/*!
   \brief        Reading the data of the version message of the connected TC/DL

   \param[in]   \wpp{u8ClInst, const iso_u8}
                 Number of TC Client instance
                 - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \param[out]   \wpp{psVersDat, ISO_TCVERS_T*}
                 Pointer to version message struct
   \retval       iso_s16
                 - #E_NO_ERR        - 0K
                 - #E_NO_INSTANCE   - wrong instance
                 - #E_RANGE         - psVersDat is a NULL pointer
*/
ISO_CLIENT_API
iso_s16 IsoTC_ReadVersionOfServer(const iso_u8 u8ClInst, ISO_TCVERS_T* psVersDat);

/*****************************************************************************/
/*!
   \brief        Reading the Language command data for this connection

   \param[in]   \wpp{u8ClInst, const iso_u8}
                 Number of TC Client instance
                 - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \param[out]   \wpp{au8LCdata, iso_u8}
                 Pointer to LC data
   \retval       iso_s16
                 - #E_NO_ERR        - 0K
                 - #E_NO_INSTANCE   - wrong instance
                 - #E_NOT_AVAILABLE - LC data are not available
                 - #E_RANGE         - au8LCdata is a NULL pointer
*/
ISO_CLIENT_API
iso_s16 IsoTC_ReadLCDataofConnection(const iso_u8 u8ClInst, iso_u8 au8LCdata[]);

/*****************************************************************************/
/*!
   \brief        Reads the handle of the connected TC server

   This function reads the handle of the connected TC server 

   \param[in]     \wp{s16CfHandleMaster, iso_s16}
                     CF handle of working set master which uses a TC Client
   \retval         iso_s16
                    - valid handle or #HANDLE_UNVALID   
*/
ISO_CLIENT_API
iso_s16 IsoTC_Read_TCHandle( iso_s16 s16CfHandleMaster );

/*****************************************************************************/
/*!
   \brief        Reads the handle of the connected DL server

   This function reads the handle of the connected DL server ( only for DL clients ) 

   \param[in]     \wp{s16CfHandleMaster, iso_s16}
                     CF handle of working set master which uses a DL Client
   \retval         iso_s16
                    - valid handle or #HANDLE_UNVALID
*/
ISO_CLIENT_API
iso_s16 IsoTC_Read_DLHandle( iso_s16 s16CfHandleMaster );

/*****************************************************************************/
/*!
   \brief     This function sends a Request Identify Task Controller message to the connected TC/DL

   \param[in]  \wpp{u8ClInst, const iso_u8}
               Number of TC Client instance
               - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \retval     iso_s16
               - #E_NO_ERR       - 0K
               - #E_NO_INSTANCE  - wrong instance
               - #E_USER_ERROR   - CF ( sender or receiver ) is not logged
               - #E_OVERFLOW     - CAN buffer full
               - #E_COM          - CAN bus-off
*/
ISO_CLIENT_API
iso_s16 IsoTC_Request_Identify_TC(const iso_u8 u8ClInst);

/************************************************************************************/
/*!
   \brief       Get informations of TCC status

   This function serves for the request of informations of the TC client

   \param[in]     \wp{s16CF, iso_s16}
                      - < TC_NUMB_TCCLIENTS: Client number
                      - > ISO_GLOBAL_ADDRESS: Handle of client CF
   \param[in]     \wp{eTCInfo, ISOTC_STATUS_e  }
                     Enum of wished information of TC
                      - TC_ALIVE - Controlling TC status message
                      - TCC_STATEOFANNOUNCING - see state ISOTC_ANNOUNCE_e
                      - TCC_STATE_ACT - Task active or inactive (after login)
   \retval          iso_u32
                      Value of requested info:
                      - #TC_ALIVE - ISO_TRUE means TC status msg is active
                      - #TCC_STATEOFANNOUNCING - for debug purposes see
                        value of ISOTC_ANNOUNCE_e in IsoTaskC.c
                      - #TCC_STATE_ACT - 1 means task active - 0 inactive
   \note  \par
      - For applications with DL and TC client on same CF s16CfCl must be the Client number !
*/
ISO_CLIENT_API
iso_u32 IsoTC_StatusInfoGet(iso_s16 s16CF, ISOTC_STATUS_e eTCInfo);

/* ************************************************************************* */
/*!
   \brief        Trigger connection event again

   Can only be called during the event callback call to stay in this state.
   If the call is supported in this state the the event callback will be triggered again in the next cycle. 

   Supported during the following events:
   - #IsoEvLoadObjects

   \param[in]   \wpp{u8ClInst, const iso_u8}
                 Number of TC Client instance
                 - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \retval       iso_s16
                 - #E_NO_ERR        - 0K
                 - #E_NO_INSTANCE   - wrong instance
                 - #E_NOACT         - Call not supported in current state
*/
ISO_CLIENT_API
iso_s16 IsoTC_TriggerEventAgain(const iso_u8 u8ClInst);

/** @} */
/** \name TC Client - Functions for creating a device description
  @{
*/

/*****************************************************************************/
/*!
   \brief         Setting Device Description Object "DeviceObject"

   This function initialises a Device DVC with an extended structure label \n
   This is necessary for connections with server of version 4 or higher.
   Attention: Device object ID is predefined with 0 (see ISO 11783 - 10). \n

   \param[in]  \wp{u8ClNum, iso_u8}
                     Number of TC Client instance
                     - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \param[in]  \wpp{rpcDeviceDesignator, const #iso_char[]}
                     Descriptive text of this device ( DeviceDesignator ) (B)
                     - Range: 0 .. 32(128 in version 4) characters
   \param[in]  \wpp{rpcDeviceSoftwareVersion, const #iso_char[]}
                     Software version indicating text (C)
                     - Range: 0 .. 32(128 in version 4) characters
   \param[in]  \wpp{rpbSerialNumber, const #iso_char[]}
                     Device and manufacturer-specific serial number (E)
                     - Range: 0 .. 32(128 in version 4) characters
   \param[in]  \wpp{rpcDeviceStructureLabel, const #iso_u8[]}
                     Label given by Device to identify the Device Description
                     Structure. This label allows the device to identify the
                     current version of the Device Description Object Pool
                     present in a Task Controller and to determine whether an
                     update is needed (7 characters)  (F)
   \param[in]  \wpp{rpcDeviceLocalisationLabel, const #iso_u8[]}
                     Label given by Device to identify the Device Description Localization. \n
                     Bytes 1 to 6 are defined by the Language Command PGN
                     (see ISO 11783-7). Byte 7 is reserved and set to 0xFF. (G)
   \param[in]  \wpp{rpcExtendedStructureLabel, const #iso_u8[]}
                     Extended structure label, introduced in version 4, max. 32 bytes
   \retval            iso_s16
                     - #E_NO_ERR        - 0K
                     - #E_RANGE         - rpcDeviceStructureLabel or rpcDeviceLocalisationLabel is a NULL pointer
                     - #E_OVERFLOW;     - Buffer is to small
                     - #E_NO_INSTANCE   - Clientnumber has wrong value
                     - #E_USER_ERROR    - Working set master not found
   \note  \par
         Every DeviceDescription has only one Device object.
*/
ISO_CLIENT_API
    iso_s16 IsoTC_DeviceExt_Set(iso_u8 u8ClNum,
                         const iso_char rpcDeviceDesignator[],
                         const iso_char rpcDeviceSoftwareVersion[],
                         const iso_char rpbSerialNumber[],
                         const iso_u8   rpcDeviceStructureLabel[],
                         const iso_u8   rpcDeviceLocalisationLabel[],
                         const iso_u8   rpcExtendedStructureLabel[]
						);

/*********************************************************************************/
/*!
   \brief         Setting Device Description Object "DeviceElement"

   This function initialises a Device Element DET.

   \param[in]  \wp{u8ClNum, iso_u8}
                        Number of TC Client instance
                        - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \param[in]  \wp{rwDeviceElementObjectID, iso_u16}
                        Unique object ID (B)
                        - Range: 0 - 65535
   \param[in]  \wp{reDeviceElementType, DevElemType_e}
                        Element type - see detailed description in Part 10 (C)
   \param[in]  \wpp{rpcDeviceElementDesignator, const iso_char[]}
                        Descriptive text to identify this device element (D)
                        - Range: 0 .. 32(128 in version 4) characters
   \param[in]  \wp{rwDeviceElementNumber, iso_u16}
                        Element number for process data variable addressing (E)
                        according to the definitions in Process Data Variable
                        definitions in ISO 11783-7.
   \param[in]  \wp{rwParentObjectID, iso_u16}
                        Object id of parent DeviceElementObject or DeviceObject (F)
                        in order to establish a hierarchical order of
                        DeviceElements ( 0 - 65535 )
   \retval            iso_s16
                        - #E_NO_ERR
                        - #E_OVERFLOW;     - Buffer is to small
                        - #E_NO_INSTANCE   - Clientnumber has wrong value
                        - #E_CONFIG        - Stack for nested device elements numbers too low (increase #TC_NUMNESTED_DE)
*/
ISO_CLIENT_API
    iso_s16 IsoTC_DeviceElement_Set(iso_u8  u8ClNum,
					                    iso_u16   rwDeviceElementObjectID,
							              DevElemType_e reDeviceElementType,
							              const iso_char   rpcDeviceElementDesignator[],
							              iso_u16    rwDeviceElementNumber,
							              iso_u16    rwParentObjectID
								          );

/***********************************************************************************************/
/*!
   \brief         Closing Device Element

   This function closes the last opended Device Element

   \param[in]  \wp{u8ClNum, iso_u8}
                      Number of TC Client instance
                        - Range: 0 - (#TC_NUMB_TCCLIENTS-1)
   \retval            iso_s16
                        - #E_NO_ERR        - 0K
                        - #E_NO_INSTANCE   - Clientnumber has wrong value
                        - #E_CONFIG        - No open Device Element
*/
ISO_CLIENT_API
    iso_s16 IsoTC_DeviceElement_End(iso_u8 u8ClNum);

/**********************************************************************/
/*!
   \brief        Add a DPD object to the last Device Element

   \param[in]  \wp{u8ClNum, iso_u8}
                        Number of TC Client instance
                        - Range: 0 - (#TC_NUMB_TCCLIENTS-1)
   \param[in]  \wp{wObjectAdd, iso_u16}
                       Unique object ID (A)
                        - Range: 0 - 65535
   \retval           iso_s16
                        - #E_NO_ERR        - 0K
                        - #E_OVERFLOW;     - Process data buffer is to small
                        - #E_NOT_AVAILABLE - DDOP buffer is to small
                        - #E_NO_INSTANCE   - Clientnumber has wrong value
                        - #E_CONFIG        - No open Device Element
*/
ISO_CLIENT_API
    iso_s16 IsoTC_AddDPDObject(iso_u8 u8ClNum, iso_u16 wObjectAdd);

/****************************************************************************/
/*!
   \brief        Add a DPT object to the last Device Element

   \param[in]  \wp{u8ClNum, iso_u8}
                        Number of TC Client instance
                        - Range: 0 - (#TC_NUMB_TCCLIENTS-1)
   \param[in]  \wp{wObjectAdd, iso_u16}
                       Unique object ID (A)
                        - Range: 0 - 65535
   \retval       iso_s16
                        - #E_NO_ERR        - 0K
                        - #E_OVERFLOW;     - Buffer is to small
                        - #E_NO_INSTANCE   - Clientnumber has wrong value
*/
ISO_CLIENT_API
    iso_s16 IsoTC_AddDPTObject(iso_u8 u8ClNum, iso_u16 wObjectAdd);

/*******************************************************************************/
/*!
   \brief         Setting Device Description Object "DeviceProcessData"

   This function initialises a Device Process Data DPD.

   \param[in]  \wp{u8ClNum, iso_u8}
                        Number of TC Client instance
                        - Range: 0 - (#TC_NUMB_TCCLIENTS - 1)
   \param[in]  \wp{rwProcessDataObjectID, iso_u16}
                        Unique object ID (A)
                        - Range: 0 - 65535
   \param[in]  \wp{rwProcessDataDDI, iso_u16}
                        Identifier of Process Data Variable(DDI) (B) \n
                        See Definitions in ISO 11783-7 and ISO 11783-11.
   \param[in]  \wp{rbProcessDataProperty, iso_u8}
                          Process data Property - a bitset combined of (C):
                          - Bit 0 = 1 = TC_PROP_DEFAULT_SET
                          - Bit 1 = 1 = TC_PROP_SETABLE
                          - Bit 2 = 1 = TC_PROP_CONTROL_SOURCE
   \param[in]  \wp{rbProcessDataTriggMethods, iso_u8}
                          Process data trigger methods - a bitset combined of  (D):
                          - Bit 0 = 1 = TC_TRIG_TIMEINTERVAL
                          - Bit 1 = 1 = TC_TRIG_DISTANCEINTERVAL
                          - Bit 2 = 1 = TC_TRIG_THRESHOLD_LIMITS
                          - Bit 3 = 1 = TC_TRIG_ON_CHANGE
                          - Bit 4 = 1 = TC_TRIG_TOTAL
   \param[in]  \wpp{rpcProcessDataDesignator, const iso_char[]}
                        Process data designator (E) \n
                        - Range: 0 .. 32(128 in version 4) characters
   \param[in]  \wp{rwDeviceValuePresentObjectID, iso_u16}
                        Object identifier of DeviceValuePresentationObject. Use
                        65535 when no DeviceValuePresentationObject is referenced.
   \retval            iso_s16
                        - #E_NO_ERR
                        - #E_OVERFLOW;     - Buffer is to small
                        - #E_NO_INSTANCE   - Clientnumber has wrong value
   \note  \par
   - IsoTC_AddDPDObject of this process data must be called before.
*/
ISO_CLIENT_API
    iso_s16 IsoTC_DeviceProcessData_Set(iso_u8  u8ClNum,
                                        iso_u16 rwProcessDataObjectID,
                                        iso_u16 rwProcessDataDDI,
                                        iso_u8  rbProcessDataProperty,
                                        iso_u8  rbProcessDataTriggMethods,
                                        const iso_char rpcProcessDataDesignator[],
                                        iso_u16 rwDeviceValuePresentObjectID
								  );

/**************************************************************************************/
/*!
   \brief         Setting the default trigger of a Device process data

   This function initialises the default trigger methods and values of a DDI. The default 
   trigger methods works independent of the trigger methods set for a DDI.

   \param[in]  \wp{u8ClNum, iso_u8}
                       Number of TC Client instance
                        - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
    \param[in]  \wp{rwProcessDataObjectID, iso_u16}
                        Unique object ID (A) - IsoTC_DeviceProcessData_Set was called before
                        - Range: 0 - 65534
    \param[in]  \wp{rbPdDeftTriggMethods, iso_u8}
                        Default trigger methods in case of DDI RequestDefaultProcessData
                        - Bit 0 = 1 = TC_TRIG_TIMEINTERVAL
                        - Bit 1 = 1 = TC_TRIG_DISTANCEINTERVAL
                        - Bit 2 = 1 = TC_TRIG_THRESHOLD_LIMITS
                        - Bit 3 = 1 = TC_TRIG_ON_CHANGE
   \param[in]  \wp{rlPdDeftValTimeInt, iso_s32}
                         Default trigger value for method time interval
                        - Unit: Milliseconds
                        - Range: 0 stops measurement, 10 minimum, 0 ... 60000
   \param[in]  \wp{rlPdDeftValDistanceInt, iso_s32}
                        Default trigger value for method distance interval
                        - Unit: Millimeter
                        - Range: 0 stops measurement, 0 ... 1000000
   \param[in]  \wp{rlPdDeftValThreshMini, iso_s32}
                        Default trigger value for method threshold minimum
                        - Unit: Depends on process data
                        - Range: -2^31+1 ... 2^31-2
   \param[in]  \wp{rlPdDeftValThreshMaxi, iso_s32}
                         Default trigger value for method threshold maximum
                        - Unit: Depends on process data
                        - Range: -2^31+2 ... 2^31-1
   \param[in]  \wp{rlPdDeftValThreshChan, iso_s32}
                        Default trigger value for method threshold change
                        - Unit: Depends on process data, signed long
                        - Range: 0 stops measurement, 1 logs each change, -2^31+1 ... 2^31-1
   \retval            iso_s16
                        - #E_NO_ERR
                        - #E_RANGE - Process data not found
                        - #E_NO_INSTANCE   - Clientnumber has wrong value

   \note  \par
   - IsoTC_AddDPDObject of this process data must be called before.
   - Attention: Function do not check if values are in range!
*/
ISO_CLIENT_API
iso_s16 IsoTC_ProcessDataDefTrigger_Set(iso_u8   u8ClNum,
                                       iso_u16   rwProcessDataObjectID,
                                       iso_u8    rbPdDeftTriggMethods,
                                       iso_s32   rlPdDeftValTimeInt,
                                       iso_s32   rlPdDeftValDistanceInt,
                                       iso_s32   rlPdDeftValThreshMini,
                                       iso_s32   rlPdDeftValThreshMaxi,
                                       iso_s32   rlPdDeftValThreshChan
                                      );

/********************************************************************************/
/*!
   \brief         Setting Device Description Object "DeviceProperty"

   This function initialises a Device Property DPT

   \param[in]  \wp{u8ClNum, iso_u8}
                        Number of TC Client instance
                        - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \param[in]  \wp{rwDevicePropertyObjectID, iso_u16}
                        Unique object ID (A)
                        - Range: 0 - 65535
   \param[in]  \wp{rwDevicePropertyDDI, iso_u16}
                        Property-DDI (B)
                        - Range: 0 -65535
   \param[in]  \wp{rlDevicePropertyValue, iso_s32}
                       Property Value (C)
                        - Full signed long range
   \param[in]  \wpp{rpcDevicePropertyDesignator, const iso_char[]}
                       Descriptive text for this device property
                        - Range: 0 .. 32(128 in version 4) characters
   \param[in]  \wp{rwDeviceValuePresentObjectID, iso_u16}
                        Object ID of DeviceValuePresentationObject. Use
                        65535 when no DeviceValuePresentationObject is referenced.
   \retval            iso_s16
                        - #E_NO_ERR
                        - #E_OVERFLOW;     - Buffer is to small
                        - #E_NO_INSTANCE   - Clientnumber has wrong value
*/
ISO_CLIENT_API
iso_s16 IsoTC_DeviceProperty_Set(iso_u8 u8ClNum,
								        iso_u16 rwDevicePropertyObjectID,
				                    iso_u16 rwDevicePropertyDDI,
						              iso_s32 rlDevicePropertyValue,
							           const iso_char  rpcDevicePropertyDesignator[],
								        iso_u16 rwDeviceValuePresentObjectID
								        );
/*********************************************************************************/
/*!
   \brief         Setting Device Description Object "DeviceValuePresentation"

   This function initialises a Device Value Presentation DVP.

   \param[in]  \wp{u8ClNum, iso_u8}
                        Number of TC Client instance
                        - Range: 0 - (TC_NUMB_TCCLIENTS - 1)
   \param[in]  \wp{rwDeviceValuePresentObjectID, iso_u16}
                        Unique object ID (A)
                        - Range: 0 - 65535
   \param[in]  \wp{rlOffset, iso_s32}
                        Offset to be applied to the value for presentation (B)
                        - Full signed long range
   \param[in]  \wp{rfScale, iso_char*}
                        Scale to be applied to the value for presentation (C)
                        - Range: 0.000000001 .. 100000000.0
   \param[in]  \wp{rbNumberOfDecimals, iso_u8}
                        Specify number of decimals to display after the decimal point (D)
                        - Range: 0 .. 7
   \param[in]  \wpp{rpcUnitDesignator, const iso_char[] }
                        Unit designator for this value presentation (E)
                        - Range: 0 .. 32(128 in version 4) characters
   \retval      iso_s16
                   - #E_NO_ERR
                   - #E_OVERFLOW;     - Buffer is to small
                   - #E_NO_INSTANCE   - Clientnumber has wrong value
*/
ISO_CLIENT_API
    iso_s16 IsoTC_DeviceValuePresent_Set(iso_u8 u8ClNum,
                                        iso_u16 rwDeviceValuePresentObjectID,
                                        iso_s32 rlOffset,
                                        iso_f32 rfScale,
                                        iso_u8  rbNumberOfDecimals,
                                        const iso_char rpcUnitDesignator[]
									   );

#ifdef ISO_EXTERNAL_DDOPBUFFER
    /*********************************************************************************/
/*!
   \brief  Pool RAM buffer set function
   \details Use the function to replace the internal with an extern buffer. \n
            The external buffer must have the size defined by DEVICEDESCRIPTION_SIZE and set before
            creating a device description object pool. \n
            Add the define #ISO_EXTERNAL_DDOPBUFFER to IsoConf.h to enable this function.
   \param[in]  \wp{abTcDDOPRAMBuffer,  iso_u8 HUGE_C[] }
               Pointer to the external pool RAM buffer array.
   \retval  iso_s16
             - E_NO_ERR
*/
ISO_CLIENT_API
iso_s16 IsoTcPoolSetBuffer(iso_u8 HUGE_C abTcDDOPRAMBuffer[]);

#endif

/** @} */
/** \name TC Client - Functions for working with a connected TC Client
  @{
*/
/*********************************************************************************/
/*!
   \brief        Sending of "change designator message"

   This message sends a change designator message. E. g. this can be necessary
   to update the language of the description strings.

   \param[in]     \wp{s16CfCl, iso_s16  }
                    - < TC_NUMB_TCCLIENTS: Client number
                    - > ISO_GLOBAL_ADDRESS: Handle of client CF 
   \param[in]     \wp{wObjectID, iso_u16  }
                    DD object ID 
                    - Range: 0 - 65535
   \param[in]     \wpp{rpcDesignatorNew, const #iso_char[] }
                    Designator string
                    - Range: 0 .. 32(128 in version 4) characters
   \retval        iso_s16
                   - #E_NO_ERR
                   - #E_OVERFLOW -  Transfer is busy - you must wait
                   - #E_NO_INSTANCE - Instance not found
                   - #E_USER_ERROR - Sender or receiver not available
   \note  \par
      - For applications with DL and TC client on same CF s16CfCl must be the Client number !
*/
ISO_CLIENT_API
	iso_s16 IsoTC_ChangeDesignator_Send( iso_s16 s16CfCl, iso_u16 wObjectID, const iso_char rpcDesignatorNew[] );

/*********************************************************************************/
/*!
   \brief        This function releases a DDOP upload ( only DVC and DVP objects )

   This function is used in case of reloading DDOP objects ( new language! ). After calling this 
   function the driver requests with callbackfunction IsoEvReloadDDOs for the changed objects.
   Calling only for TC/DL >= Version 4 allowed.

   \param[in]     \wp{s16CfCl, iso_s16  }
                   - < TC_NUMB_TCCLIENTS: Client number 
                   - > ISO_GLOBAL_ADDRESS: Handle of Client CF 
   \param[in]     \wp{e_SVType, ISO_CLTYPE_e  }
                    IsoClType_DontCare if s16CfCl is the Client number
   \retval        iso_s16
                   - #E_NO_ERR
                   - #E_BUSY - Pool service is not free at the moment
                   - #E_NO_INSTANCE - Instance not found
                   - #E_USER_ERROR - User unknown
   \note  \par
   - For applications with DL and TC client on same CF s16CfCl must be the Client number !
   */
ISO_CLIENT_API
   iso_s16 IsoTC_ReloadDDObjects(iso_s16 s16CfCl, ISO_CLTYPE_e e_SVType);

/******************************************************************************/
/*!
   \brief       This function sets the distance for triggermethod "distance interval"
   
   If a process data of a TC client uses the triggermethod "distance interval" then the application
   must set the distance ( ground or wheel or NMEA ) with this function.
   
   \param[in]     \wp{u32Distance,  iso_u32 }
                    Distance value of ground, wheel based speed or GPS
                    - Range:
                    - 0 - #ISO_VALID_SIGNAL_DW
                    - #ISO_NOT_AVAILABLE_DM ( default ) if distance is not available
                    - #ISO_ERROR_INDI_DWM if speed PGNs are missing or value is invalid
   \retval     iso_s16
                    - #E_NO_ERR - OK
   \note  \par
   This function should called every time a speed message ( 100ms ) is received
*/
ISO_CLIENT_API
    iso_s16 IsoTC_SetDistance(iso_u32 u32Distance);

/*******************************************************************************/
/*!
   \brief       This function sets and sends a DPD value manually to the TC

   A DPD value is sent manually to the TC only the thresholds are taken into consideration.
   The function also works if task is not active.

   \param[in]    \wp{s16CF, iso_s16}
                - < TC_NUMB_TCCLIENTS: Client number
                - > ISO_GLOBAL_ADDRESS: Handle of client CF
   \param[in]    \wp{wElementNumb,  iso_u16}
                  Element number of DPD ( process data )
                  - Range: 0 - 65534
   \param[in]    \wp{wDDI,  iso_u16}
                  DDI of DPD
   \param[in]    \wp{lPdValue,  iso_s32}
                  New Value of this DPD (full range)
   \retval     iso_s16
                - #E_NO_ERR - OK
                - #E_NO_INSTANCE - TC client not found 
                - #E_NOT_AVAILABLE - DPD not found
                - #E_RANGE - New value outside of thresholds
                - #E_OVERFLOW  - CAN buffer full
                - #E_COM       - CAN bus-off
   \note  \par
      - For applications with DL and TC client on same CF s16CfCl must be the Client number !
*/
ISO_CLIENT_API
    iso_s16 IsoTC_SetDPDValue(iso_s16 s16CF, iso_u16 wElementNumb, iso_u16 wDDI, iso_s32 lPdValue);
/** @} */
/* **************** End of functions and definitions which are only for LAYER 10 .. ******** */

/* ************************************************************************ */
/** @} */ /* END taskc                                                      */
/* ************************************************************************ */

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_IsoTccApi_H */
/* ************************************************************************ */
