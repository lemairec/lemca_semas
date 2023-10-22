/* ************************************************************************ */
/*!
   \file
   \brief       ECU Driver SC Client API Header File
   \author      Wegscheider Peter
   \date        Created XX.07.13

   \copyright   Competence Center ISOBUS e.V.

   \par         History:
   \par
   04.07.2013 - author P. Wegscheider
   - API declarations moved to this file
   - Module version define added
   \par
   05.09.2013 - author E. Hammerl
   - Event IsoSCMNotAlive added, SsInactiv corrected
   \par 
   08.05.2014 - author E. Hammerl
   - Added IsoSC_SetSCCVersion() and SCM font parameter
   28.09.2015 - author P. Wegscheider
   - Feature request ID 1711: Resolve typdef conflicts with ISO_TRUE;ISO_FALSE and types definitions
   \par
   14.12.2016 - author P. Wegscheider
   - Replaced source address parameter with CF handle in functions
     IsoSC_ExecutionIndication(), IsoSC_ExecutionStatus(), IsoSC_ClientAbort(),
     IsoSC_FunErrorStatusSet(), IsoSC_FunErrorStatusRead(), IsoSC_FunTriggerSet()
     and IsoSC_StatusInfoGet().
   \par
   21.02.2017 - author P. Wegscheider
   - Feature ID 6003: client interfaces should only use handles (rather then ISOBUS NAME) \n
     Replaced IsoSC_InstCmd() parameter rpbWorkSetMasterName with s16CfHandleMaster
   \par
   19.02.2018 -author P.Wegscheider
   - Feature ID 7528: add user parameter to callback functions
   \par
   06.05.2018 - author P.Wegscheider
   - Feature ID 3910: header files should include header files they depend on
   \par
   10.08.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files
*/
/* ************************************************************************ */
#ifndef DEF_IsoSccApi_H
    #define DEF_IsoSccApi_H

/* include configuration, driver standard types and common definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* ************************************************************************ */
/** \addtogroup sequencectrl SC-Client
    \ingroup  clients
    \brief Part 14 - Sequence Control Client
*/
/* ************************************************************************ */
/** \addtogroup sequencectrl
@{
*/
/* ************************************************************************ */
#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoSccApi.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */

/* ************** IsoScCtrl.c, IsoScLogin.c, IsoScWork.c ( Sequenz Control Iso 11783-14 )******* */

     /* Versions */
     #define SC_DIS          (0u)      /**< Draft international standard */
     #define SC_FDIS         (1u)      /**< Final draft international standard */
     #define SQC_IS_1        (2u)      /**< First edition as international standard - default */

#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

     /** \brief
     Enum of command for login (setting the device description) or logout the SC client
     */
     typedef enum
     {
        IsoScOpenSCD,            /**< Open an new SC Client instance */
        IsoScCloseSCD,           /**< Finish the SCD initialisation */
        IsoScLogOut              /**< Resets (deletes) a SC Client */
     } ISO_SC_CMD_e;

     /** \brief

     */
     typedef enum
     {
        IsoTimeBased     = 0x1,
        IsoDistanceBased = 0x2,
        IsoDontCare      = 0xFF
     } PrefTrig_te;

    /** \brief

    */
    typedef enum
    {
        SsReserved            = 0x00,   /* */
        SsReady               = 0x01,   /* */
        SsRecording           = 0x02,
        SsRecordingCompletion = 0x03,
        SsPlayBack            = 0x04,
        SsAbort               = 0x05,
        SsInactiv             = 0xFF
    } StateSeq_te;

	 /** \brief
     Enum which indicates the kind of SC callback calling
     */
     typedef enum
     {
         IsoSCLoginFinished,       /**< Login of VT and SC finished -> SCOP objects manipulation possible*/
         IsoSCRecordingCompletion, /**< SCM is entried in sequence state "Recording Completion" */
         IsoSCMExeCmd,             /**< SCM execution command received */
         IsoRespToExeInd,          /**< Response to SC execution indication received */
         IsoRespToExeStatus,       /**< Response to SC execution status received */
         IsoClAbort,               /**< Abort of SCM received, SCC or own SCClientAbort */
         IsoSCMNotAlive,           /**< SCM status message not received */
         IsoSCtoAppLast
     } ISO_SCAPP_e;

	 /** \brief
     Enum of possible execution states
     */
     typedef enum
     {
         IsoFuncExeStartedCompleted,    /**<  */
         IsoFuncExeStarted,             /**<  */
         IsoFuncExeCompleted,
         IsoFuncExeError,
         IsoFuncExeLast
     } ISO_SCEXST_e;

     /** \brief

     */
     typedef enum
     {
          FuNoErr        = 0x0,     /**< No error */
          FuOneTimeErr   = 0x1,     /**< One time error */
          FuPermanentErr = 0x2,     /**< Permanent error */
          FuCFLocked     = 0x3,     /**< Client function is locked */
          FuCFDeactive   = 0x4,     /**< Client function deactivated at the SCC by the operator */
          FuAnyOtherErr  = 0xF      /**< Any other error */
     } FuncErrSta_te;

	 /** \brief
     Errorcodes for SCExecutionExecutionStatus(E7)
     */
     typedef enum
     {
         IsoNoErr                = 0,
         IsoErrInTheFunction     = 1,             /**<  */
         IsoExeOperatorInteract  = 2,
         IsoConditionSCCnoExecut = 3,
         IsoExeAnyOtherError     = 0xFF
     } ISO_SCEXEERR_e;

	 /** \brief
     Errorcodes for SCClientAbort(E3)
     */
     typedef enum
     {
         IsoReserved               = 0,
         IsoTimeoutOnStatusMsg     = 1,             /**<  */
         IsoOperatorInteraction    = 2,
         IsoErrorDuringFuncExecut  = 3,
         IsoAnyOtherError          = 0xFF
     } ISO_SCABORTERR_e;

     /** \brief
     Enum of status info
     */
     typedef enum
     {
         SCC_STATEOFANNOUNCING,        /**< See intern state machine of login */
         SCC_SEQUENCESTATE,            /**< SCC acutal Sequence state */
         SCC_VERSION,                  /**< SCC used standard version */
         SCM_ACTIVE_ALIVE,             /**< SCM status message ok? */
         SCM_ACTIVE_SOURCEADDRESS,     /**< SCM Source address */
         SCM_ACTIVE_CFHND,             /**< SCM CF handle */
         SCM_SEQUENCESTATE,            /**< SCM actual Sequence state */
         SCM_CAP_PIXELXAXIS,           /**< SCM Number of pixels X-axis for grafic objects */
         SCM_CAP_PIXELYAXIS,           /**< SCM Number of pixels Y-axis for grafic objects */
         SCM_CAP_MAXCHARSTR,           /**< SCM Number of characters for design. strings */
         SCM_FONTCOLOUR,               /**< SCM font colour */
         SCM_FONTSIZE,                 /**< SCM font size */
         SCM_FONTTYPE,                 /**< SCM font type */
         SCM_FONTSTYLE,                /**< SCM font style */
         SCM_VERSION,                  /**< SCM Version */
         SCD_NUMBERFUN,                /**< SCD Number of SCD function objects */
         SCD_NUMBERSTATE,              /**< SCD Number of SCD state objects */
         SCD_EXTOBJDEFID               /**< Object ID of external object definition object ID */
     } ISOSC_STATUS_e;

     /** \brief
     Struct which is used as interface to the application
     */
     typedef struct
     {
         ISO_SCAPP_e    eScCmd;            /**< Kind of SC callback calling */
         iso_u8         bFuncID;           /**< Function ID */
         iso_u8         bStateID;          /**< State ID */
         ISO_SCEXST_e   eScExeSta;         /**< Execution state */
         iso_u32        dwFunctVal;        /**< Function value */
         iso_u8         bErrorCode;        /**< ErrorCode */
         ISO_USER_PARAM_T  userParam;      /*!< \brief User parameter set with IsoSC_InstCmd() */
     } ISO_SCLINK_T, *ISO_SCLINK_t ;


     /* Functions for sequenz control initialisation */
/**************************************************************************************/
/*!
   \brief         Initialisation of a sequenz controller instance

   This function controls the initialisation of a device description and has the ability
   to find a SC Client instance.

     \param[in]    \wp{s16CfHandleMaster, iso_s16 }
                     CF handle of the client 
     \param[in]    \wpp{userParam, const #ISO_USER_PARAM_T}
                     User parameter value for the callback function calls. \n
     \param[in]    \wpp{rpfScCall, void*(#ISO_SCLINK_T * psScLink) }
                     Communication interface with SCM (Callbackfun.)
     \param[in]    \wp{eCommand, ISO_SC_CMD_e }
                     Command - what shall this function do?
                         - IsoScOpenSCD - Open an new SC Client instance and
                           starts the initialisation of a SCD
                         - IsoScCloseSCD - Finish the SCD
                         - IsoScGetPointOfInst - Returns the number of a SC Client instance
                         - IsoScLogOut - Shut down a SC client ( delete)
   \retval           iso_s16
                         - 0 ... ( WORKING_SETS - 1 )
                         - E_NO_INSTANCE - error - instance not found
*/
ISO_CLIENT_API
iso_s16   IsoSC_InstCmd ( iso_s16 s16CfHandleMaster,
                          const ISO_USER_PARAM_T userParam,
                          void (*rpfScCall)( ISO_SCLINK_T * psScLink ),
                          ISO_SC_CMD_e eCommand
						      );

/**************************************************************************/
/*!
   \brief       Setting the version supported of this SC client

   \param[in]   \wp{iScInst, iso_s16}      
                 (Valid) Return value of IsoSC_InstCmd( ... IsoScOpenSCD )
   \param[in]   \wp{bSCVersion, iso_u8}      
                  New Standard Version supported of this SC client
   \retval         iso_s16  
                   - #E_NO_ERR - OK  
                   - #E_NO_INSTANCE - SCC instance not found
*/
ISO_CLIENT_API
iso_s16 IsoSC_SetSCCVersion( iso_s16 iScInst, iso_u8 bSCVersion );

/**************************************************************************/
/*!
   \brief           Initialisation of the SCOP basic object

   This function initialises the basic object of a SCOP.

   \param[in]   \wp{iScInst, iso_s16}
                (Valid) Return value of IsoSC_InstCmd( ... IsoScOpenSCD )
   \param[in]   \wp{rwObjectId, iso_u16}
                 Object ID of basic object
   \param[in]   \wpp{rpabNameMask, const #iso_u8[]}
                 Mask for NAME used of SCM for filtering SCCs \n
                    NAME see ISO11783 - 5
   \param[in]   \wp{rwSCDDesign, iso_u8*}
                 Object ID of textual representation in the referenced SCOP
   \param[in]   \wp{rwSCDGrafic, iso_u16}
                 Object ID of graphical respresentation in the referenced SCOP
   \param[in]   \wpp{racVersion, const #iso_char[]}
                 Pointer to SCD version label \n
                  Range: 1 - 64 charakters
   \param[in]   \wpp{racConfig, const #iso_char[]}
                 Pointer to configuration label \n
                  Range: 1 - 64 charakters
   \param[in]   \wp{rbNumbFuncObj, iso_u8} 
                  Number of functions to follow
   \param[in]   \wpp{rpwListFuncObj, const #iso_u16[]}
                 Pointer to array of objects to follow ( list of function objects )
   \note  \par
         - There is only one basic object in a SCOP
         - Calling this function is only allowed between IsoSC_InstCmd( IsoScOpenSCD )
           and IsoSC_InstCmd( IsoScCloseSCD )
*/
ISO_CLIENT_API
void IsoSC_BasicObjSet( iso_s16 iScInst, iso_u16 rwObjectId, const iso_u8 rpabNameMask[],
                        iso_u16 rwSCDDesign, iso_u16 rwSCDGrafic,
                        const iso_char racVersion[], const iso_char racConfig[], 
                        iso_u8  rbNumbFuncObj, const iso_u16 rpwListFuncObj[]     );

/*************************************************************************/
/*!
   \brief           Initialisation of the SCD (client) function object

   This function initialises a function object of a SCOP and must be called for every function.

   \param[in]   \wp{iScInst, iso_s16}
                 (Valid) Return value of IsoSC_InstCmd( ... IsoScOpenSCD )
    \param[in]   \wp{rwObjectId, iso_u16}
                  Object ID of function object
    \param[in]   \wp{rbFuncID, iso_u8}
                  Unique Function ID (used as reference in CAN messages)
                    Range: 0 - 255
    \param[in]   \wp{rePrefTrigger, PrefTrig_te}
                   Preferred trigger of this SCD function \n
                   IsoTimeBased, IsoDistanceBased or IsoDontCare
     \param[in]   \wp{rbAttribute, iso_u8}
                    Additional attributes see SCD function object \n
                    see ISO 11783 - 14 - A.4
    \param[in]   \wp{rwObjIdDesig, iso_u16}
                  Object ID of textual representation in the referenced SCOP
    \param[in]   \wp{rwObjIdGraph, iso_u16}
                  Object ID of graphical respresentation in the referenced SCOP
    \param[in]   \wp{rbNumbStateObj, iso_u8}
                   Number of state objects of this client function \n
                   Range: 0 - 64
    \param[in]   \wpp{rpwListStateObj, const #iso_u16[] }
                   Pointer to array of objects to follow ( list of state objects )
    \retval          iso_s16
                    - #E_NO_ERR - OK
                    - #E_OVERFLOW - Array for functions is to small
                    - #E_NO_INSTANCE - SCC instance not found
   \note  \par
         - This function must called for a function before IsoSC_FunctValueSet()!
         - Calling this function is only allowed between IsoSC_InstCmd( IsoScOpenSCD )
           and IsoSC_InstCmd( IsoScCloseSCD )
*/
ISO_CLIENT_API
iso_s16 IsoSC_FunctionObjSet( iso_s16 iScInst, iso_u16 rwObjectId, iso_u8 rbFuncID, PrefTrig_te rePrefTrigger,
                              iso_u8 rbAttribute, iso_u16 rwObjIdDesig, iso_u16 rwObjIdGraph,
                              iso_u8 rbNumbStateObj, const iso_u16 rpwListStateObj[]
						       );

/************************************************************************/
/*!
   \brief           Initialisation of the function value of a function

   This function initialises the function value of a SCD function

   \param[in]   \wp{iScInst, iso_s16}
                 (Valid) Return value of IsoSC_InstCmd( ... IsoScOpenSCD )
   \param[in]   \wp{rbFuncId, iso_u8}
                  SCD Function ID
   \param[in]   \wp{rdwFuncValMin, iso_u32}
                    Minimum numeric function value \n
                    Range: 0 - 2^32 -1
   \param[in]   \wp{rdwFuncValMax, iso_u32}
                   Maximum numeric function value \n
                   Range: 0 - 2^32 -1
   \param[in]   \wp{rlFuncOffset, iso_s32}
                   Numeric function value offset \n
                    Range: -2^31  -  2^31-1 \n
                    Set to FFFFFFFF when the numeric function value representation in the attributes
                    is set to 00
   \param[in]   \wp{rfFuncScale, iso_f32}
                   Numeric function value scale factor \n
                    Set to FFFFFFFF when the numeric function value representation in the attributes
                    is set to 00
   \param[in]   \wp{rbNumbDec, iso_u8}
                  Number of decimals of numeric function value to display after the decimal point \n
                    Range: 0 - 7
   \param[in]   \wp{rwObjIdUnitStr, iso_u16}
                  Object ID of referenced VT string object containing the unit string for display
                    with the numeric function value. \n
                    Set to FFFF when the numeric function value representation in the attributes is
                    set to 00.
   \retval          iso_s16
                    - E_NO_ERR - OK
                    - E_RANGE - Function ID not found
                    - #E_NO_INSTANCE - SCC instance not found
   \note  \par
                    Corresponding SCD function have to be initialised before
*/
ISO_CLIENT_API
iso_s16 IsoSC_FunctValueSet( iso_s16 iScInst, iso_u8 rbFuncId, iso_u32 rdwFuncValMin, iso_u32 rdwFuncValMax,
                          iso_s32 rlFuncOffset, iso_f32 rfFuncScale, iso_u8 rbNumbDec, iso_u16 rwObjIdUnitStr
						 );

/*****************************************************************************/
/*!
    \brief          Initialisation of a SCD state object

   This function initialises a SCD state object

   \param[in]   \wp{iScInst, iso_s16}
                 (Valid) Return value of IsoSC_InstCmd( ... IsoScOpenSCD )
   \param[in]   \wp{rwObjIDSta, iso_u16}
                 Object ID of state object
   \param[in]   \wp{rbStateID, iso_u8}
                 State ID, Range 0 - 63
   \param[in]   \wp{rwObjIdDesig, iso_u16}
                 Object ID of textual representation in the referenced SCOP
   \param[in]   \wp{rwObjIdGraph, iso_u16}
                 Object ID of graphical respresentation in the referenced SCOP
   \retval          iso_s16
                    - #E_NO_ERR - OK
                    - #E_OVERFLOW - Array for states is to small
                    - #E_NO_INSTANCE - SCC instance not found
   \par
         - Calling this function is only allowed between IsoSC_InstCmd( IsoScOpenSCD )
           and IsoSC_InstCmd( IsoScCloseSCD )
*/
ISO_CLIENT_API
iso_s16 IsoSC_StateObjSet( iso_s16 iScInst, iso_u16 rwObjIDSta, iso_u8 rbStateID, iso_u16 rwObjIdDesig, iso_u16 rwObjIdGraph );

/**************************************************************************/
/*!
    \brief          This function sets the external object definition object of this client

   \param[in]   \wp{iScInst, iso_s16}
                 (Valid) Return value of IsoSC_InstCmd( ... IsoScOpenSCD )
   \param[in]   \wp{wExternalObjDefObj, iso_u16}
                 Object ID of external object definition object

   \retval          iso_s16
                    - #E_NO_ERR - OK
                    - #E_NO_INSTANCE - SCC instance not found
   \par
            There is only one external object definition object for SC allowed
*/
ISO_CLIENT_API
iso_s16 IsoSC_ExternalObjDefSet( iso_s16 iScInst, iso_u16 wExternalObjDefObj );

/* Functions for sequenz control operations */
/*********************************************************************************/
/*!
   \brief        Command "SC Execution Indication"

   \param[in]   \wp{s16CfHandle, iso_s16}
                 CF handle of SC Client
   \param[in]   \wp{rbFuncID, iso_u8}
                 (Client)Function ID \n
                  Range: 0 - 255
   \param[in]   \wp{rbStateID, iso_u8}
                  State ID \n
                  Range: 0 - 63
   \param[in]   \wp{reExeSta, ISO_SCEXST_e}
                 (Function)-Execution state \n
                 IsoFuncExeStartedCompleted, IsoFuncExeStarted, IsoFuncExeCompleted, IsoFuncExeError
   \param[in]   \wp{rdwFuncVal, iso_u32}
                 Function value \n
                 Range: 0 - 2^32 -1
   \retval       iso_s16
                 - #E_NO_ERR - OK
                 - #E_VALUE_WRONG - Function ID or State ID not valid
                 - #E_USER_ERROR - there is no SC instance for this SA
                 - #E_NOACT - SC Client is in the wrong (sequence)-state
*/
ISO_CLIENT_API
iso_s16 IsoSC_ExecutionIndication( iso_s16 s16CfHandle, iso_u8 rbFuncID, iso_u8 rbStateID, ISO_SCEXST_e reExeSta, iso_u32 rdwFuncVal );

/*************************************************************************/
/*!
   \brief      Sending Client command response to SC Master Execution Command

   \param[in]   \wp{s16CfHandle, iso_s16}
                 CF handle of SC Client
   \param[in]   \wp{rbFuncID, iso_u8}
                (Client)Function ID \n
                   Range: 0 - 255
   \param[in]   \wp{rbStateID, iso_u8}
                 State ID \n
                  Range: 0 - 63
   \param[in]   \wp{reExeSta, ISO_SCEXST_e}
                 (Function)-Execution state \n
                  IsoFuncExeStartedCompleted, IsoFuncExeStarted, IsoFuncExeCompleted, IsoFuncExeError
    \param[in]   \wp{eErrorCode, ISO_SCEXEERR_e}
                  Error codes of SCClientExecutionStatus \n
                   IsoNoErr, IsoErrInTheFunction, IsoExeOperatorInteract, IsoConditionSCCnoExecut,
                   IsoExeAnyOtherError
   \retval         iso_s16
                   - #E_NO_ERR - OK
                   - #E_VALUE_WRONG - Function ID or State ID not valid
                   - #E_NOACT - SC Client is in the wrong (sequence)-state
                   - #E_USER_ERROR - there is no SC instance for this SA
*/
ISO_CLIENT_API
iso_s16 IsoSC_ExecutionStatus( iso_s16 s16CfHandle, iso_u8 rbFuncID, iso_u8 rbStateID, ISO_SCEXST_e reExeSta, ISO_SCEXEERR_e eErrorCode );

/******************************************************************************************/
/*!
   \brief       Sending SC Client Abort as broadcast message

   \param[in]   \wp{s16CfHandle, iso_s16}
                  CF handle of sending SCC
   \param[in]   \wp{eErrorCode, ISO_SCABORTERR_e}
                  Specific error code of SC Client Abort \n
                      IsoTimeoutOnStatusMsg, IsoOperatorInteraction, IsoErrorDuringFuncExecut,
                      IsoAnyOtherError
   \retval            iso_s16
                      - #E_NO_ERR - OK
                      - #E_NOACT - SC Client is in the wrong (sequence)-state
                      - #E_USER_ERROR - there is no SC instance for this CF handle
                      - #E_OVERFLOW - CAN buffer full
                      - #E_COM on bus-off
*/
ISO_CLIENT_API
iso_s16 IsoSC_ClientAbort( iso_s16 s16CfHandle, ISO_SCABORTERR_e eErrorCode );


/*********************************************************************************************/
/*!
   \brief          Setting a error state for a client function

   \param[in]   \wp{s16CfHandle, iso_s16}
                  CF handle of SC Client
   \param[in]   \wp{rbFuncID, iso_u8}
                  SCD Function ID
   \param[in]   \wp{eFunErrCode, FuncErrSta_te}
                  Specific errorcode of client functions \n
                   FuNoErr, FuOneTimeErr, FuPermanentErr, FuCFLocked, FuCFDeactive, FuAnyOtherErr

   \retval         iso_s16
                   - E_NO_ERR - OK
                   - E_VALUE_WRONG - Function ID is not available
                   - E_USER_ERROR - there is no SC instance for this SA
*/
ISO_CLIENT_API
iso_s16 IsoSC_FunErrorStatusSet( iso_s16 s16CfHandle, iso_u8 rbFuncID, FuncErrSta_te eFunErrCode );

/***************************************************************************/
/*!
   \brief           Reading the error state for a client function

   This function reads the actual error state of a SCD (client) function

   \param[in]   \wp{s16CfHandle, iso_s16}
                  CF handle of SC Client
   \param[in]   \wp{rbFuncID, iso_u8}
                  SCD Function ID of client function \n
                    Range: 0 - 255
   \retval      FuncErrSta_te
                - Actual function error state
                    FuNoErr, FuOneTimeErr, FuPermanentErr, FuCFLocked, FuCFDeactive, FuAnyOtherErr
*/
ISO_CLIENT_API
FuncErrSta_te IsoSC_FunErrorStatusRead( iso_s16 s16CfHandle, iso_u8 rbFuncID );

/**********************************************************************/
/*!
   \brief         Setting trigger mode for a function ID

   This function sets the trigger mode for a SCD function

   \param[in]   \wp{s16CfHandle, iso_s16}
                  CF handle of SC Client
   \param[in]   \wp{rbFuncID, iso_u8}
                  Function ID of client function getting a new trigger mode
   \param[in]   \wp{eTrigger, PrefTrig_te}
                  New trigger for a function \n
                     IsoTimeBased, IsoDistanceBased or IsoDontCare

   \retval           iso_s16
                     - E_NO_ERR - OK
                     - E_RANGE - Function or SA not valid
*/
ISO_CLIENT_API
iso_s16 IsoSC_FunTriggerSet( iso_s16 s16CfHandle, iso_u8 rbFuncID, PrefTrig_te eTrigger );

/****************************************************************************/
/*!
   \brief       Get some information of sequence control

         This function serves for the request of information of the SC

   \param[in]       \wp{s16CfHandle, iso_s16}
                     - CF handle of sequence controller client 
   \param[in]       \wp{eSCInfo, ISOVT_STATUS_e}
                     Enum of wished information of VT
                      - SCC_STATEOFANNOUNCING - See intern state machine (SubLogin_te)
                      - SCC_SEQUENCESTATE - Sequence state of SCC
                      - SCC_VERSION - Client Standard Version 
                      - SCM_ACTIVE_ALIVE - SCM status message ok?
                      - SCM_ACTIVE_SOURCEADDRESS - Source address of active SCM
                      - SCM_SEQUENCESTATE - Sequence state of SCM
                      - SCM_CAP_PIXELXAXIS - Number of Pixels X-axis
                      - SCM_CAP_PIXELYAXIS - Number of Pixels X-axis
                      - SCM_CAP_MAXCHARSTR - Max. number of char of strings
                      - SCM_FONTCOLOUR - SCM font colour 
                      - SCM_FONTSIZE -SCM font size 
                      - SCM_FONTTYPE - SCM font type 
                      - SCM_FONTSTYLE - SCM font style 
                      - SCM_VERSION - Version of supported SC Standard
                      - SCD_NUMBERFUN - SCD function objects
                      - SCD_NUMBERSTATE - SCD state objectsn
                      - SCD_EXTOBJDEFID - External object definition object ID
   \retval            iso_s32
                      Value of requested info:
                      - SCC_STATEOFANNOUNCING - Number of SubLogin_te
                      - SCC_SEQUENCESTATE - See StateSeq_te
                      - SCC_VERSION - Standard Version used of this client 
                      - SCM_ACTIVE_ALIVE - ISO_TRUE means TC status msg is active, ISO_FALSE not
                      - SCM_ACTIVE_SOURCEADDRESS - Source address of SCM or ISO_NULL_ADDRESS
                      - SCM_SEQUENCESTATE - See StateSeq_te
                      - SCM_CAP_PIXELXAXIS - Number pixel X-axis or ISO_NOT_AVAILABLE_DM
                      - SCM_CAP_PIXELYAXIS - Number pixel Y-axis or ISO_NOT_AVAILABLE_DM
                      - SCM_CAP_MAXCHARSTR - Number char or ISO_NOT_AVAILABLE_DM
                      - SCM_FONTCOLOUR - SCM font colour (0xFF default likely not received)
                      - SCM_FONTSIZE -SCM font size (0xFF default likely not received)
                      - SCM_FONTTYPE - SCM font type (0xFF default likely not received)
                      - SCM_FONTSTYLE - SCM font style (0xFF default likely not received)
                      - SCM_VERSION - Number of Version see Part 14 - C3
                      - SCD_NUMBERFUN - Number of SCD function objects
                      - SCD_NUMBERSTATE - Number of SCD state objects
                      - SCD_EXTOBJDEFID - Object ID of external object definition object
    \note  \par
    All SCM_FONT_.. set to 0xFF means that its very unlikely that data receiced of SCM.
*/
ISO_CLIENT_API
iso_s32 IsoSC_StatusInfoGet( iso_s16 s16CfHandle, ISOSC_STATUS_e eSCInfo );

/* ************************************************************************ */
/** @} */ /* END sequencectrl                                               */
/* ************************************************************************ */


/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_IsoSccApi_H */
/* ************************************************************************ */
