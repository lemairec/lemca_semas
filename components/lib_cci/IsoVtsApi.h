/* ************************************************************************ */
/*!
   \file
   \brief       VT server service API for graphical auxiliary 
   \details     Contain the core VT service API functions

   \author      Wegscheider Peter
   \date        Created 07.02.2018

   \copyright   Competence Center ISOBUS e.V.

   \par  History:
   \par
   30.01.2018 - author P. Wegscheider
   - First implementation
   \par
   19.02.2018 -author P.Wegscheider
   - Feature ID 7528: add user parameter to callback functions
   \par
   12.07.2018 -author P.Wegscheider
   - Feature BugID 8426: integrate APA AUX - pool upload server
   - Moved API and renamed functions   
*/
/* ************************************************************************ */

#ifndef DEF_ISO_VTS_API_H
#define DEF_ISO_VTS_API_H

/* include configuration and common driver definitions */
#include "IsoCommonDef.h"
#include "IsoVtcApi.h"     /* include common VT definitions */

#if defined(DOXYGEN) 
   #define ISO_VT_SERVICE
#endif 

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* ************************************************************************ */
/*! \defgroup grp_vtservice VT-Service 
    \ingroup  clients
    \brief    Part 6 - Virtual Terminal service for graphical auxiliary input devices
    \details  This module offers a core service to implement a VT server. \n
              In the moment it contains only the functions needed to build 
              a VT server for a graphical auxiliary input device. 
*/

/* ************************************************************************ */
/*! \addtogroup grp_vtservice
@{
*/
/* ************************************************************************ */


/* **************************** defines *********************************** */

/* optional define to disable NACK for client maintenance message, if the fist message has not 01 in second byte */
/* #define VTSERVICE_NO_CLIENT_NACK */

/* **************************** constants ********************************* */


/* **************************** type definitions ************************** */

/*! \brief VT service state */
typedef enum
{
   IsoVtSv_Started,     /*!< VT service of a CF is active (running) */
   IsoVtSv_Stopped      /*!< VT service of a CF is not active */
} IsoVtSv_State_Te;

/*! \brief VT service busy flags */
typedef enum
{
   IsoVtSv_NotBusy = 0,
   /* IsoVtSv_BusyUpdatingMask = 1, */
   IsoVtSv_BusySavingData = 2,
   IsoVtSv_BusyExecutingCmd = 4,
   /* IsoVtSv_BusyExecutingMacro = 8,*/
   IsoVtSv_BusyParsingPool = 16,
   /* Reserved = 32 */
   /* IsoVtSv_AuxLearnMode = 64 */
   IsoVtSv_VtOutOfMemory = 128
} IsoVtSv_Busy_Te;

/*! \brief VT service callback events */
typedef enum
{
   IsoVtSv_EvOpen,         /*!< First WS maintenance message for a CF received */
   IsoVtSv_EvRemovePool,   /*!< Delete object pool from RAM (End of object pool error or delete_object_pool function) */
   IsoVtSv_EvActivated,    /*!< Object pool "loaded" and active (ready to use) */         
   IsoVtSv_EvAborted,      /*!< WS maintenance message timeout */
   IsoVtSv_EvClosed,       /*!< WS shutdown */
   IsoVtSv_EvRemoved       /*!< WS connection entry will be deleted*/
} IsoVtSv_EventId_Te;

/*! \brief VT service event callback function parameter */
typedef struct
{
   iso_s16           s16VtCfHnd;    /*!< \brief CF handle of the VT service */
   IsoVtSv_State_Te  eStateEvent;   /*!< \brief Event ID */
   ISO_USER_PARAM_T  userParam;     /*!< \brief User parameter set with VtService_AddVt() */
} IsoVtSv_StateEv_Ts;

/*! \brief VT service message callback function parameter */
typedef struct
{
   iso_s16              s16ConnHnd;   /*!< \brief Handle of the connection (can be #HANDLE_UNVALID if not connected) */
   iso_s16              s16WsCfHnd;   /*!< \brief CF handle of the external working set master */
   iso_s16              s16VtCfHnd;   /*!< \brief CF handle of the VT service */
   ISOVT_FUNC_e         eFunction;    /*!< \brief CF handle of the VT service */
   iso_u32              u32DataSize;  /*!< > 0 for message specific data else 0 */
   const iso_u8 HUGE_C  *pau8Data;    /*!< pointer to message data inclusive function byte (index 0) else NULL pointer \n
                                           Hint: for ISO_ETP_IN_PKG: objectpool_transfer_msg 
                                           has a data size greater zero but the pointer is a NULL pointer */
   ISO_USER_PARAM_T     userParam;    /*!< \brief User parameter set with VtService_AddVt() */
} IsoVtSv_Msg_Ts;

/*! \brief VT service connection message callback events */
typedef struct
{
   IsoVtSv_EventId_Te      eEventId;      /**< Event type identifier */
   iso_s16                 s16ConnHnd;    /**< Connection handle */
   iso_s16                 s16WsCfHnd;    /**< CF handle of the client */
   iso_s16                 s16VtCfHnd;    /**< CF handle of the server */
   ISO_USER_PARAM_T        userParam;     /*!< \brief User parameter set with VtService_AddVt() */
} IsoVtSv_ConnEv_Ts;

/*! \brief Technical data messages - characteristics of VT */
typedef struct
{
   iso_u8   u8VtVersion;         /**< Version of the VT >= 3 (VT_V3_SE_UT2) */
   iso_u8   u8SoftKeysNavi;      /**< Version 4: Number of physical SKs used for navigation in SKM */
   iso_u8   u8SoftKeysVirtual;   /**< number of virtual soft keys */
   iso_u8   u8SoftKeysPhysical;  /**< number of phys. soft keys */
   iso_u8   u8SoftKeyWidth;      /**< soft key x resolution (width)*/
   iso_u8   u8SoftKeyHeight;     /**< soft key y resolution (height)*/
   iso_u8   u8FontSmallSizes;    /**< supported small font sizes */
   iso_u8   u8FontLargeSizes;    /**< supported large font sizes */
   iso_u8   u8FontTypeAttributes;/**< supported font attributes */
   iso_u8   u8Boottime;          /**< boot time of VT in seconds */
   iso_u8   u8GraphicType;       /**< 0 = Monochrome; 1 = 16 Colour; 2 = 256 Colour */
   iso_u8   u8Hardware;          /**< supported hardware features */
   iso_u16  u16MaskSize;         /**< Data mask resolution in pixel (width and height) */
   iso_u8   u8BgColourOfULDM;    /**< background colour of VTs User-Layout Data Mask */
   iso_u8   u8BgColourOfKeyCell; /**< background colour of VTs Key Cells */
} IsoVtSv_Config_Ts;

/*! \brief type definition of the VT service state callback function */
typedef iso_s16 (*IsoVtSvStateCb_fpt)( const IsoVtSv_StateEv_Ts* psState );

/*! \brief type definition of the VT service message callback function

   - used return codes:
      - function get_memory:
         - E_NO_ERR: enough memory
         - E_OUT_OF_MEMORY : not enough memory

      - other function:
         - E_NO_ERR: processed (response sent)
         - E_NOACT:  message not handled
         - E_BUSY:   async. processing message  
         - else error

*/
typedef iso_s16 (*IsoVtSvMsgCb_fpt)(const IsoVtSv_Msg_Ts * pMsg);

/*! \brief type definition of the VT service connection event callback function */
typedef iso_s16 (*IsoVtSvEventCb_fpt)(const IsoVtSv_ConnEv_Ts * pEvent);

/* **************************** functions ********************************* */


/* ************************************************************************ */
/*! \brief Function to start a VT service 
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \param[in]  \wpp{psVtConfig, const #IsoVtSv_Config_Ts*}
                  Pointer to the application specific VT server configuration
   \param[in]  \wpp{userParam, const #ISO_USER_PARAM_T}
                  User parameter value for the callback function calls. \n
                  Use #ISO_USER_PARAM_DEFAULT if not used/needed.
   \param[in]  \wp{fpStateCb, IsoVtSvStateCb_fpt}
                  Pointer to the application specific VT service state callback function
   \param[in]  \wp{fpEventCb, IsoVtSvEventCb_fpt}
                  Pointer to the application specific VT service event callback function
   \param[in]  \wp{fpMsgCb, IsoVtSvMsgCb_fpt}
                  Pointer to the application specific VT service connection message callback function
   \retval     iso_s16
                - #E_NO_ERR - VT service added and started
                - #E_RANGE  - Parameter not valid
                - #E_OVERFLOW - No free entry to add a new service
                - #E_WARN - VT service for this CF handle already added
*/
ISO_CLIENT_API
iso_s16 IsoVtService_AddVt(iso_s16 s16CfHandleVt, const IsoVtSv_Config_Ts* psVtConfig,
   const ISO_USER_PARAM_T userParam,
   IsoVtSvStateCb_fpt  fpStateCb,
   IsoVtSvEventCb_fpt  fpEventCb,
   IsoVtSvMsgCb_fpt    fpMsgCb);

/* ************************************************************************ */
/*! \brief Function to stop a VT service 
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \retval     iso_s16
                - E_NO_ERR - VT service stopped
                - E_RANGE  - CF handle not found
*/
ISO_CLIENT_API
iso_s16 IsoVtService_RemoveVt(iso_s16 s16CfHandleVt);

/* ************************************************************************ */
/*! \brief Function to check if a VT service active  
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \retval     iso_bool
                - ISO_TRUE  - VT service is in running mode and ready for connections
                - ISO_FALSE - VT service is stopped or in startup
*/
ISO_CLIENT_API
iso_bool IsoVtService_IsVtRunning(iso_s16 s16CfHandleVt);

/* ************************************************************************ */
/*! \brief Function to check if a VT service is connected with an implement  
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of internal VT server
   \param[in]  \wp{s16HandleWs, iso_s16}
                  CF handle of external working set

   \retval     iso_bool
                - ISO_TRUE  - VT service is connected with the working set CF
                - ISO_FALSE - VT service is not connected with the given CF
*/
ISO_CLIENT_API
iso_bool IsoVtService_IsConnected(iso_s16 s16CfHandleVt, iso_s16 s16HandleWs);

/* ************************************************************************ */
/*! \brief Function to set the language command parameters of a VT service 
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \param[in]  \wpp{au8LngCmd, const iso_u8[6]}
                  Language command data which should be used for the VT server.
   \retval     iso_s16
                - E_NO_ERR - on success
                - E_RANGE  - CF handle not found
*/
ISO_CLIENT_API
iso_s16 IsoVtService_SetLanguageCommand(iso_s16 s16CfHandleVt, const iso_u8 au8LngCmd[6]);

/* ************************************************************************ */
/*! \brief Function to get the language command data of a VT service 
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \retval     const #iso_u8*
                - Pointer to the language command data array (6 bytes).
*/
ISO_CLIENT_API
const iso_u8* IsoVtService_GetLanguageCommand(iso_s16 s16CfHandleVt);

/* ************************************************************************ */
/*! \brief Function to set a busy flag of a VT service 
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \param[in]  \wp{eFlag, IsoVtSv_Busy_Te}
                  Busy flag.
   \param[in]  \wp{qActive, iso_bool}
                  #ISO_TRUE to set, #ISO_FALSE to reset.
   \retval     iso_s16
                - E_NO_ERR - on success
                - E_RANGE  - CF handle not found
*/
ISO_CLIENT_API
iso_s16  IsoVtService_SetBusyFlag(iso_s16 s16CfHandleVt, IsoVtSv_Busy_Te eFlag, iso_bool qActive);

/* ************************************************************************ */
/*! \brief Function to get the state of busy flag of a VT service 
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \param[in]  \wp{eFlag, IsoVtSv_Busy_Te}
                  Busy flag
   \retval     iso_bool
               - #ISO_TRUE if active
               - #ISO_FALSE if not set
*/
ISO_CLIENT_API
iso_bool IsoVtService_GetBusyFlagState(iso_s16 s16CfHandleVt, IsoVtSv_Busy_Te eFlag);

/* ************************************************************************ */
/*! \brief Function to get the VT status busy codes of a VT service 
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \retval     iso_u8
                - VT status busy codes.
*/
ISO_CLIENT_API
iso_u8   IsoVtService_GetBusyCodes(iso_s16 s16CfHandleVt);

/* ************************************************************************ */
/*! \brief Function to set a special pool object as supported by the VT service.
   \param[in]  \wp{s16CfHandleVt, iso_s16}
                  CF handle of the VT server
   \param[in]  \wp{eObjectType, OBJTYP_e}
                  Supported object.
   \retval     iso_s16
                - #E_NO_ERR - on success
                - #E_RANGE  - CF handle not found
*/
ISO_CLIENT_API
iso_s16 IsoVtService_SetSupportedObject(iso_s16 s16CfHandleVt, OBJTYP_e eObjectType);

/* ************************************************************************ */
/*!   Function to respond to a message 
      forwarded with through the IsoVtSvMsgCb_fpt callback function.

      \param[in]  \wp{s16ConnHnd, iso_s16}
                     Handle of the connection
      \param[in]  \wp{u32DataSize, iso_u32}
                     >= 1 for message specific data
      \param[in]  \wpp{pau8Data, const #iso_u8 HUGE_C [] }
                     pointer to message specific data inclusive function (first byte) 

      \retval        iso_s16
                   - #E_NO_ERR   on success
                   - #E_RANGE    parameter not valid
                   - #E_NOACT    if the function could not be executed 

                   - #E_OVERFLOW - Transfers are busy (buffer full)
                   - #E_USER_ERROR - CF ( sender or receiver ) is not logged
                   - #E_OVERFLOW on send FIFO full
                   - #E_COM on bus-off
*/
ISO_CLIENT_API
iso_s16 IsoVtService_ConnMsgResponse(iso_s16 s16ConnHnd, iso_u32 u32DataSize, const iso_u8 HUGE_C pau8Data[]);


/* ************************************************************************ */
/*! @} */ /* End addtogroup grp_vtservice */
/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_ISO_VTS_API_H */
/* ************************************************************************ */
