/* ************************************************************************ */
/*!
   \file
   \brief       ISOBUS ECU Driver FS Client API Header File
   \details     File Server Client API
   \author      Wegscheider Peter
   \date        Created XX.07.13

   \copyright   Competence Center ISOBUS e.V.

   \par         History:
   \par
   04.07.2013 - author P. Wegscheider
   - API declarations moved to this file
   - Module version define added
   \par
   18.04.2016 - author P. Wegscheider
   - Module version number increased
   - Type names updated
   \par
   09.01.2017 - author P. Wegscheider
   - Non ASCII characters and typo fixes
   \par
   19.02.2018 -author P.Wegscheider
   - Feature ID 7528: add user parameter to callback functions
   - Moved deprecated pointer type definitions into ISO_FSC_DEPRECATED define section.
   \par
   06.05.2018 - author P.Wegscheider
   - Feature ID 3910: header files should include header files they depend on
   \par
   10.08.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files
   \par
   23.01.2020 - author P. Wegscheider
   - BugID 10423: Removed deprecated pointer type definitions (ISO_FSC_DEPRECATED)
*/
/* ************************************************************************ */
#ifndef DEF_IsoFscApi_H
    #define DEF_IsoFscApi_H

/* include configuration, driver standard types and common definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */
/* **** FILE SERVER CLIENT                                             **** */
/* ************************************************************************ */
/** \defgroup fsclient FS-Client
    \ingroup  clients
    \brief Part 13 - File Server Client

    The File Server Client Module has been developed for Part 13 Version 3
    ( Second published edition of the International Standard ).
    The Module is not backward compatible to previous versions. \n
    \n
    The FS-Client Module offers the following features:
    - Lowlevel implementation of the Part 13 protocol
    - Callback functions for returning the FS Response to the client application
    - Pre processed response header data
      ( response header data are pre processed and the extracted information are stored
        in the ISO_FSC_INFO_T usInfo union of the ISO_FSC_CBDATA_T callback structure )
    - Extended functions for reading and writing files
    - More than one client member (user) connection per server
    - More than one io channel per connection
    \internal
    - Simultaneous connections on different can nodes ( only Version 4.83 and 4.84 )
    \endinternal

    For the module version see \ref grp_versions #VERSION_FSC 
*/

/* ************************************************************************ */
/** \addtogroup fsclient
@{
*/
/* ************************************************************************ */

/* ************************************************************************ */
/** \name Part 13 - Enable FS-Client Module in IsoConf.h
@{
*/
#ifdef DOXYGEN
/** \def _LAY13_
    \brief Add the define _LAY13_ to IsoConf.h to enable the file server client functionality.
*/
#define _LAY13_

#endif
/** @} */

/* ************************************************************************ */
/** \brief FS-Client Definitions for IsoConf.h
*/
/** \addtogroup fscconfig FS-Client Configuration
@{
*/

/** \name Defines - Part 13 File Server Client Configuration
@{ */

/** \def FSC_MAX_CONNECTIONS
    \brief Maximum of simultaneous connections ( predefined is 2)
    \details This define is used to set the size of the CF / file server connection array.
*/
#ifndef FSC_MAX_CONNECTIONS
    #define FSC_MAX_CONNECTIONS     (2)
#endif
/** \def FSC_MAX_IO_HANDLES
    \brief Maximum of simultaneous io channels ( predefined is FSC_MAX_CONNECTIONS * 3)
    \details This define is used to set the size of the io channel array.
*/
#ifndef FSC_MAX_IO_HANDLES
    #define FSC_MAX_IO_HANDLES      (FSC_MAX_CONNECTIONS * 3)
#endif

/** @} */

/** \name Defines - Part 13 File Server Client Settings
@{
*/

/** \def FSC_CLIENT_VERSION
    \brief Version Number 0x03u = Second published edition of the International Standard - Part 13 B.5
*/
#ifndef FSC_CLIENT_VERSION
    #define FSC_CLIENT_VERSION         (3u)
#endif

/** \def FSC_MSG_PRIO
    \brief Default message priority - Part 13 C.1.1
*/
#ifndef FSC_MSG_PRIO
    #define FSC_MSG_PRIO               (0x07u)
#endif

/** \def FSC_MAX_CMD_REQUEST_TRIES
    \brief Maximum number of request tries - Part 13 5.3.1 / Part 3 5.12.3
*/
#ifndef FSC_MAX_CMD_REQUEST_TRIES
    #define FSC_MAX_CMD_REQUEST_TRIES    (3u)
#endif
/** @} */


/** @} */

/* ************************************************************************ */
/** \brief FS-Client Structure and Enum Type Definitions

    This part contains the structure, enum and type definitions for the FS-Client module.
*/
/** \addtogroup fscdefinitions FS-Client Type Definitions
@{
*/

#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoFscApi.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */


/** \name Defines - Part 13 B.14 File Handling Flags
    \brief See iso_FscOpenFile() parameter u8Flags for more information
    \details Sample: FSC_OPEN_READWRITE | FSC_OPEN_CREATE
@{
*/
#define FSC_OPEN_READONLY      0x00u	/**< \brief Open file for reading only. */
#define FSC_OPEN_WRITING       0x01u	/**< \brief Open file for writing only. */
#define FSC_OPEN_READWRITE     0x02u	/**< \brief Open file for reading and writing. */
#define FSC_OPEN_DIRECTORY     0x03u	/**< \brief Open directory. */

#define FSC_OPEN_CREATE        0x04u	/**< \brief Create a new file and/or directories if not yet existing. */
#define FSC_OPEN_APPEND        0x08u	/**< \brief Open file for appending data to the end of the file. */
#define FSC_OPEN_EXCLUSIVE     0x10u	/**< \brief Open file with exclusive access (fails if already open). */
/** @} */
/* *************************************************************************************** */

/** \name Defines - Part 13 B.15 Attributes
    \brief (ISO_FSC_FILE_INFO_T and ISO_FSC_FILE_ATTRIBUTES_T Property u8Attributes values)
@{
*/
#define FSC_ATTR_READONLY          0x01u	/**< \brief "Read-only" attribute is set. */
#define FSC_ATTR_HIDDEN            0x02u	/**< \brief "Hidden" attribute is set (not applicable unless volume supports hidden attribute). */
#define FSC_ATTR_HIDDEN_SUPPORT    0x04u	/**< \brief Volume supports hidden attribute. */
#define FSC_ATTR_VOLUME_HND        0x08u	/**< \brief Handle specifies a volume. */

#define FSC_ATTR_DIRECTORY_HND     0x10u	/**< \brief Handle specifies a directory. */
#define FSC_ATTR_LONG_NAMES        0x20u	/**< \brief Volume supports long filenames. */
#define FSC_ATTR_VOL_NOT_REMOVABLE 0x40u	/**< \brief Volume is not removable. */
#define FSC_ATTR_CASE_SENSITIVE    0x80u	/**< \brief Volume is case-sensitive. */
/** @} */
/* ************************************************************************ */

/** \name Defines - Part 13 B.16 Set Attributes Command
    \brief See iso_FscSetFileAttributes() parameter u8AttrCmds for more information.
    \details Sample: FSC_ATTR_LEAVE_READONLY | FSC_ATTR_SET_HIDDEN | FSC_ATTR_SET_RESERVED
@{
*/
#define FSC_ATTR_CLEAR_READONLY         0x00u	/**< \brief Clear "read-only" attribute. */
#define FSC_ATTR_SET_READONLY           0x01u	/**< \brief Set "read-only" attribute. */
#define FSC_ATTR_LEAVE_READONLY         0x03u	/**< \brief Don't care, leave "read-only" attribute in current state. */

#define FSC_ATTR_CLEAR_HIDDEN           0x00u	/**< \brief Clear "hidden" attribute. */
#define FSC_ATTR_SET_HIDDEN             0x04u	/**< \brief Set "hidden" attribute (not applicable unless volume supports hidden attribute). */
#define FSC_ATTR_LEAVE_HIDDEN           0x0Cu	/**< \brief Don't care, leave "hidden" attribute in current state. */

#define FSC_ATTR_SET_RESERVED           0xF0u	/**< \brief Reserved bits 4..7, set to 1111 (Don't care) */
/** @} */
/* ************************************************************************ */


/** \name Defines - Part 13 B.17 Position Mode
    \brief See iso_FscSeekFile() parameter u8Mode for more information.
    \details Sample: FSC_ATTR_LEAVE_READONLY | FSC_ATTR_SET_HIDDEN | FSC_ATTR_SET_RESERVED
@{
*/
#define FSC_SEEK_BEGIN      0x00u	/**< \brief Seek from the beginning of the file. */
#define FSC_SEEK_CURRENT    0x01u	/**< \brief Seek from the beginning of the file. */
#define FSC_SEEK_END        0x02u	/**< \brief Seek from end of the file. */
/** @} */
/* ************************************************************************ */

/** \name Defines - Part 13 B.27 File Handling Mode
    \brief See iso_FscMoveFile() and iso_FscDeleteFile() parameter u8Mode for more information.
@{
*/
#define FSC_FILE_MODE_COPY      0x01u	/**< \brief "Copy" mode.  */
#define FSC_FILE_MODE_FORCE     0x02u	/**< \brief "Force" mode. */
#define FSC_FILE_MODE_RECURSIVE 0x04u	/**< \brief "Recursive" mode. */
/** @} */
/* ************************************************************************ */


/** \name Defines - Part 13 B.30 Volume Mode
    \brief See iso_FscGetVolumeStatus parameter u8Mode for more information.
@{
*/
#define FSC_VOL_MODE_NOT_IN_USE     0x00u	/**< \brief Report volume not in use by client.  */
#define FSC_VOL_MODE_IN_USE         0x01u	/**< \brief Report volume in use by client. */
#define FSC_VOL_MODE_REQ_REMOVAL    0x02u	/**< \brief Request volume to prepare for removal. */
/** @} */
/* ************************************************************************ */

/** \name Defines - Part 13 B.31 Volume Status
    \brief (ISO_FSC_VOLUME_STATUS_T Property u8VolumeStatus values)
@{
*/
#define FSC_VOLUME_STATUS_PRESENT   0x00u	/**< \brief Volume is present.  */
#define FSC_VOLUME_STATUS_IN_USE    0x01u	/**< \brief Volume is in use.  */
#define FSC_VOLUME_STATUS_REMOVAL   0x02u	/**< \brief Volume is prepared for removal. */
#define FSC_VOLUME_STATUS_REMOVED   0x03u	/**< \brief Volume is removed. */
/** @} */
/* ************************************************************************ */

#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

    /** \brief
    Typedef enum for file server response error codes - Part 13 B.9

    \par The enum contains also FS-Client specific error codes - start at 6400 (0x1900)
    */
    typedef enum
    {
        IsoFsSuccess                =  0,   /**< Success  */
        IsoFsAccessDenied           =  1,   /**< Access Denied */
        IsoFsInvalidAccess          =  2,   /**< Invalid Access */
        IsoFsTooManyFilesOpen       =  3,   /**< Too many files open */
        IsoFsItemNotFound           =  4,   /**< File, path or volume not found */
        IsoFsInvalidHandle          =  5,   /**< Invalid Handle */
        IsoFsInvalidSourceName      =  6,   /**< Invalid given source name */
        IsoFsInvalidDestinationName =  7,   /**< Invalid given destination name  */
        IsoFsVolumeOutOfFreeSpace   =  8,   /**< Volume out of free space */
        IsoFsWriteFailure           =  9,   /**< Failure during a write operation  */
        IsoFsMediaIsNotPresent      = 10,   /**< Media is not present [formerly the code for error 13, below, in Version 2 FSs (see B.5)] */
        IsoFsReadFailure            = 11,   /**< Failure during a read operation */
        IsoFsFunctionNotSupported   = 12,   /**< Function not supported */
        IsoFsVolumeNotInitialized   = 13,   /**< Volume is possibly not initialized */
                                            /**< 14 ... 41 Reserved */
        IsoFsInvalidRequestLength   = 42,   /**< Invalid request length (used when the file pointer hits the start/top of the file or on invalid space request of the volume)  */
        IsoFsOutOfMemory            = 43,   /**< Out of memory (used by FS to indicate out of resources at this time and can complete request)  */
        IsoFsError                  = 44,   /**< Any other error */
        IsoFsEndOfFileReached       = 45,   /**< End of file reached (reported only when file pointer is at end of file) */
                                            /**< ( 46 ... 255 Reserved ) */

        /* FSClient driver specific error codes - start at 0x1900 */
        IsoFscErrorTryAgain         = 6400,   /**< Request failed try again (0x1900) */
        IsoFscServerBusy            = 6401,   /**< file server busy */
        IsoFscServerTimeout         = 6402,   /**< Server status timeout - closing connections... */
        IsoFscRequestError          = 6403,   /**< Too many failed requests - no more retries */
        IsoFscResponseTimeout       = 6404,   /**< Response timeout - no more retries */
        IsoFscResponseError         = 6405,   /**< Response error - no more retries */
        IsoFscResponseDataError     = 6406,   /**< Response data error - response data length not valid */
        IsoFscInvalidHandle         = 6407,   /**< Invalid Handle */
        IsoFscInvalidFunction       = 6408,   /**< Function is not valid */
        IsoFscBufferIsFull          = 6409,   /**< The data buffer is full - copy the data and set the length to zero to continue...  */
        IsoFscError                 = 6410    /**< Any other client error */
    } ISO_FSC_ERRORCODE_e;

/* ************************************************************************ */
    /** \brief
    Typedef enum for file server command + functions - Part 13 C.1 - C.5
    */
    typedef enum
    {
        IsoFscCmdSignalIOChannelState       = -3,   /**< Client Cmd: signal currently changed IO channel state  */
        IsoFscCmdSignalConnectionState      = -2,   /**< Client Cmd: signal currently changed connection state  */
        IsoFsCmdUnknown                     = -1,   /**< Command function not set or unknown    */

        IsoFsCmdAliveStatus                 =  0,   /**< File server status or client connection Maintenance message */
        IsoFsCmdServerProperties            =  1,   /**< File Server properties */
        IsoFsCmdVolumeStatus                =  2,   /**< Volume Status          */
        IsoFsCmdGetCurrentDirectory         = 16,   /**< Get Current Directory      */
        IsoFsCmdChangeCurrentDirectory      = 17,   /**< Change Current Directory   */
        IsoFsCmdOpenFile                    = 32,   /**< Open File  */
        IsoFsCmdSeekFile                    = 33,   /**< Seek File  */
        IsoFsCmdReadFile                    = 34,   /**< Read File  */
        IsoFsCmdWriteFile                   = 35,   /**< Write File */
        IsoFsCmdCloseFile                   = 36,   /**< Close File */
        IsoFsCmdMoveFile                    = 48,   /**< Move File  */
        IsoFsCmdDeleteFile                  = 49,   /**< Delete File    */
        IsoFsCmdGetFileAttributes           = 50,   /**< Get File Attributes  */
        IsoFsCmdSetFileAttributes           = 51,   /**< Set File Attributes  */
        IsoFsCmdGetFileDateTime             = 52,   /**< Get File Date & Time */
        IsoFsCmdInitializeVolume            = 64    /**< Initialize Volume    */
    } ISO_FSC_CMDFUNCTION_e;

/* ************************************************************************ */
    /** \brief
        Typedef enum of file server client io channel or connection states
    */
    typedef enum
    {
        IsoFscFree              =  0,   /**< array member is free  */
        IsoFscInit              =  1,   /**< array member data are set to init values  */
        IsoFscClosed            =  2,   /**< array member data are valid - handle not active - can be (re)used  */
        IsoFscConnecting        =  3,   /**< wait for server status response ...     */
        IsoFscOpen              =  4,   /**< connection or IO can be used       */
        IsoFscDoRequest         =  5,   /**< (re)try to send the request        */
        IsoFscDoWaitReqested    =  6,   /**<  Wait for TP request finished      */
        IsoFscDoWaitResponse    =  7,   /**< wait for FS response start message */
        IsoFscDoResponse        =  8,   /**< wait for FS response data          */
        IsoFscDoCallBack        =  9,   /**< return data and current state - used from IsoFsCmdReadFile if the data buffer is full */
        IsoFscDoAbort           =  10,  /**< abort cmd function                 */
        IsoFscFinished          =  11   /**< cmd function processing is finished */
    } ISO_FSC_STATE_e;


/* ************************************************************************ */
    /** \brief FS client handle type definition

    - 0xFFFF    : Invalid handle ( use #ISO_FSC_HANDLE_INVALID )
    - Bits  0-7 : array index from 0 to 255
    - Bits  8-9 : random value between 0 and 3
    - Bits 10-11: sub type of the handle - 0 = IO handle, 1 = connection handle
    - Bits 12-15: main type of the handle - 4 = FSC handle 
    */
    typedef iso_u16 ISO_FSC_HANDLE_T; 

    /** \brief FS client invalid handle */
    #define ISO_FSC_HANDLE_INVALID  ((ISO_FSC_HANDLE_T) 0xFFFFu)

/* ************************************************************************ */
    /** \brief
    Typedef struct for file server client to server connection status
    */
    typedef struct 
    {
        ISO_FSC_HANDLE_T    hConn;              /**< \brief connection handle - set to ISO_FSC_HANDLE_INVALID to indicate a free/unused entry */
        ISO_FSC_STATE_e     eState;             /**< \brief client connection / command state                                */
        iso_s16              s16FSClientMember;  /**< \brief file server client member (user) handle							*/
        iso_s16              s16FServerMember;   /**< \brief current file server member (user) handle						*/
        iso_s32               lLastFServerAlive;  /**< \brief timestamp of last server status message                         */
        iso_s32               lLastFSClientAlive; /**< \brief timestamp of last client maintenance message                    */
        iso_u8               u8usedIOs;          /**< \brief number of IOs witch use this connections ...                    */
    } ISO_FSC_CONNECTION_STATUS_T;

/* ************************************************************************ */
    /** \brief Typedef struct for file server client data buffers */
    typedef struct 
    {
        iso_u8  HUGE_C   *au8Data;       /**< \brief Pointer on data buffer */
        iso_u32          u32DataSize;    /**< \brief Size of the data buffer */
        iso_u32          u32DataLength;  /**< \brief Number of used data bytes */
    } ISO_FSC_DATA_T; 
    
    typedef ISO_FSC_DATA_T  ISO_FSC_PATH_T; /**< Typedef of ISO_FSC_PATH_T   */

/* ************************************************************************ */
    /** \brief
    Typedef struct for file server status and properties response
    */
    typedef struct 
    {
        iso_u8           u8Status;             /**< \brief current file server status - Part 13 B.3							*/
        iso_u8           u8OpenFiles;          /**< \brief current open files on the file server - Part 13 B.4				*/
        iso_u8           u8MaxOpenFiles;       /**< \brief maximum open files on the file server - Part 13 B.6				*/
        iso_u8           u8Version;            /**< \brief version number of the file server - Part 13 B.5				    */
        iso_u8           u8Capabilities;       /**< \brief file server capabilities - Part 13 B.7				            */
    } ISO_FSC_FS_INFO_T; 

/* ************************************************************************ */
    /** \brief Typedef struct for file server volume status response */
    typedef struct 
    {
        iso_u8           u8VolumeStatus;         /**< \brief current file server status - Part 13 B.31						*/
        iso_u8           u8MaxTimeBeforeRemoval; /**< \brief current open files on the file server - Part 13 B.32 	        */
    } ISO_FSC_VOLUME_STATUS_T;

/* ************************************************************************ */
    /** \brief Typedef struct for file server get current directory response */
    typedef struct 
    {
        iso_u32          u32TotalSpace;          /**< \brief get current dir total space (in units of 512 bytes) - Part 13 B.11	*/
        iso_u32          u32FreeSpace;           /**< \brief get current dir free space (in units of 512 bytes) - Part 13 B.11 	*/
    } ISO_FSC_CURRENT_DIR_INFO_T;
    
/* ************************************************************************ */
    /** \brief Typedef struct for file server file response */
    typedef struct 
    {
        iso_u8           u8Attributes;       /**< \brief open file attributes - Part 13 B.15	                */
        iso_u16          u16Count;           /**< \brief number of bytes or directory entries - Part 13 B.20 	*/
        iso_u32          u32Position;        /**< \brief position after seek file  - Part 13 B.29 	            */
    } ISO_FSC_FILE_INFO_T;

/* ************************************************************************ */
    /** \brief Typedef struct for file server file attributes response */
    typedef struct 
    {
        iso_u8           u8Attributes;       /**< \brief file attributes - Part 13 B.15	        */
        iso_u32          u32Size;            /**< \brief file size  - Part 13 B.26 	            */
    } ISO_FSC_FILE_ATTRIBUTES_T;

/* ************************************************************************ */
    /** \brief Typedef struct for file server get file date time response */
    typedef struct 
    {
        iso_u16          u16Date;        /**< \brief file date - Part 13 B.24	        */
        iso_u16          u16Time;        /**< \brief file time - Part 13 B.25 	        */
    } ISO_FSC_DATE_TIME_T;

/* ************************************************************************ */
    /** \brief
    Typedef union for file server response

    The response content depend on ISO_FSC_CMDFUNCTION_e:
    - IsoFsCmdAliveStatus:              sServerInfo
    - IsoFsCmdServerProperties:         sServerInfo
    - IsoFsCmdVolumeStatus:             sVolumeStatus
    - IsoFsCmdGetCurrentDirectory:      sCurrentDirInfo
    - IsoFsCmdChangeCurrentDirectory:   not used
    - IsoFsCmdOpenFile:                 sFileInfo.u8Attributes
    - IsoFsCmdSeekFile:                 sFileInfo.u32Position
    - IsoFsCmdReadFile:                 sFileInfo.u16Count
    - IsoFsCmdWriteFile:                sFileInfo.u16Count
    - IsoFsCmdCloseFile:                not used
    - IsoFsCmdMoveFile:                 not used
    - IsoFsCmdDeleteFile:               not used
    - IsoFsCmdSetFileAttributes:        not used
    - IsoFsCmdGetFileDateTime:          sDateTime
    - IsoFsCmdInitializeVolume:         sInitVolumeAttributes.u8Attributes

    */
    typedef union 
    {
        ISO_FSC_FS_INFO_T           sServerInfo;        /**< \brief file server status and properties - IsoFsCmdServerProperties       */
        ISO_FSC_VOLUME_STATUS_T     sVolumeStatus;      /**< \brief file server volume status                                          */
        ISO_FSC_CURRENT_DIR_INFO_T  sCurrentDirInfo;    /**< \brief file server get current directory properties                       */
        ISO_FSC_FILE_INFO_T         sFileInfo;          /**< \brief file open read write or read directory entries info                */
        ISO_FSC_FILE_ATTRIBUTES_T   sFileAttributes;    /**< \brief file server get file attributes info                               */
        ISO_FSC_DATE_TIME_T         sDateTime;          /**< \brief file server get file date time info                                */
        ISO_FSC_FILE_ATTRIBUTES_T   sInitVolumeAttributes;    /**< \brief file server initialize volume attributes                     */
    } ISO_FSC_INFO_T;

/* ************************************************************************ */
    /** \brief Typedef struct for file server client callback data */
    typedef struct 
    {
        ISO_FSC_CMDFUNCTION_e   eFunction;      /**< \brief current / last cmd function                        */
        ISO_FSC_ERRORCODE_e     eError;         /**< \brief last file server response or client error          */
        ISO_FSC_HANDLE_T        hFscHandle;     /**< \brief IO channel (or connection) handle                  */
        ISO_FSC_STATE_e         eState;         /**< \brief client connection / IO command state               */
        ISO_FSC_INFO_T          usInfo;         /**< \brief union for the server response. \n
                                                     The content depend on eFunction and is only valid if eState is IsoFscFinished. */
        iso_u8  HUGE_C          *au8Data;       /**< \brief Pointer on data buffer. Contains the data without the usInfo values.            */
        iso_u32                 u32DataSize;    /**< \brief Size of the data buffer    */
        iso_u32                 u32DataLength;  /**< \brief Number of used data bytes  */
        ISO_USER_PARAM_T        userParam;      /*!< \brief User parameter */
    } ISO_FSC_CBDATA_T;
    
    typedef ISO_FSC_CBDATA_T* ISO_FSC_CBDATA_t;  /**< Pointer typedef of ISO_FSC_CBDATA_T   */

/* ************************************************************************ */
    /** \brief
    Typedef call back function ( for handling all unhandled responses and errors )

    The ISO_FSC_CBDATA_T data pointer and the referenced data are only valid during the call back.
    */
    typedef void (*ISO_FSC_CALLBACK_t)( ISO_FSC_CBDATA_T* psData );

/** @} */ /* end group fscdefinitions */
/* ************************************************************************ */
    /** \name Part 13 - Client Management Functions

    Use this functions to create and connect io channels to a file server

    @{
    */

    /*!
        \brief  Create a new io channel and connect it to the file server

        If the connection does not exist, a new connect between the client and the server is created and opened.
        The FSC module executes the callback function when the io channel ( or connection) is open and can be used.

        \param[out]    \wp{phIO,  ISO_FSC_HANDLE_T*}
                         Pointer to the new io channel handle
        \param[in]    \wp{s16FSClientMemberHandle,  iso_s16}
                         Valid client (internal) network member (user) handle
        \param[in]    \wp{s16FServerMemberHandle,  iso_s16}
                         Valid server (external) network member (user) handle
        \param[in]    \wpp{userParam, const #ISO_USER_PARAM_T}
                         User parameter value for the callback function calls. \n
                         Use #ISO_USER_PARAM_DEFAULT if not used/needed.
        \param[in]    \wp{pFunction,  ISO_FSC_CALLBACK_t}
                         Pointer to callback function or NULL pointer if you don't need a callback function for this io channel

        \retval           iso_s16
                            - E_NO_ERR
                            - E_RANGE (Input parameter not valid)
                            - E_CONFIG (no free connection or io channel)
    */
    ISO_CLIENT_API
    iso_s16  iso_FscConnect( /* out */ ISO_FSC_HANDLE_T* phIO,  iso_s16 s16FSClientMemberHandle, iso_s16 s16FServerMemberHandle, 
                             const ISO_USER_PARAM_T userParam, ISO_FSC_CALLBACK_t pFunction );

/* ************************************************************************ */
    /*!
        \brief  Get the status of a connection

        \param[in]    \wp{hFscHandle,  ISO_FSC_HANDLE_T}
                                        Valid connection or IO handle
        \param[out]   \wp{psConnStatus,  ISO_FSC_CONNECTION_STATUS_T*}
                                        Pointer to a ISO_FSC_CONNECTION_STATUS_T structure
        \retval                         iso_s16
                                        - E_NO_ERR
                                        - E_RANGE ( handle not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscGetConnectionStatus( ISO_FSC_HANDLE_T hFscHandle, ISO_FSC_CONNECTION_STATUS_T* psConnStatus );

/* ************************************************************************ */
    /*!
        \brief  Delete a connection or an io channel

        \param[in]    \wp{hFscHandle,  ISO_FSC_HANDLE_T}
                             Valid connection or IO handle

        \retval              iso_s16
                               - E_NO_ERR
                               - E_RANGE ( handle not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscDelete( ISO_FSC_HANDLE_T hFscHandle );

    /* ************************************************************************ */
    /*!
        \brief  Close an open connection or io channel

        \param[in]    \wp{hFscHandle,  ISO_FSC_HANDLE_T}
                         Valid connection or IO handle

        \retval              iso_s16
                             - E_NO_ERR
                             - E_RANGE ( handle not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscClose( ISO_FSC_HANDLE_T hFscHandle );

    /* ************************************************************************ */
    /*!
        \brief  Open or reopen a connection or an io channel

        \param[in]    \wp{hFscHandle,  ISO_FSC_HANDLE_T}
                             Valid connection or IO handle

        \retval              iso_s16
                             - E_NO_ERR
                             - E_RANGE ( handle not valid )
                             - E_CONFIG ( Connection not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscOpen( ISO_FSC_HANDLE_T hFscHandle );

    /** @} */
    /* ************************************************************************ */
    /** \name Part 13 C.1 Functions
        @{
    */
    /*!
        \brief  Request the file server properties

        \param[in]    \wp{hIO,  ISO_FSC_HANDLE_T}
                             Valid IO channel handle

        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( IO channel busy or connection not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscGetServerProperties( ISO_FSC_HANDLE_T hIO );

    /* ************************************************************************ */
    /*!
        \brief  Request the status of a file server volume

        \param[in]    \wp{hIO,  ISO_FSC_HANDLE_T}
                            Valid IO channel handle
        \param[in]    \wp{u8Mode,  iso_u8}
                            Volume Mode - Part 13 B.30
        \param[in]    \wpp{psPath, const #ISO_FSC_PATH_T*}
                            Pointer to volume name structure or NULL pointer to get the volume status of the current directory volume.

        \retval              iso_s16
                             - E_NO_ERR
                             - E_RANGE ( handle not valid )
                             - E_CONFIG ( IO channel busy or connection not valid )

        \note B.30 Volume Mode
        \par
         The data object used by a client to specify the mode of the volume access requested.
         A value of 00000000 requests the current status. \n
          - Bit 7..2: 000000 = Reserved, send as 000000.
          - Bit    1:      1 = Request volume to prepare for removal (#FSC_VOL_MODE_REQ_REMOVAL).
          - Bit    0:      1 = Report volume in use by client (#FSC_VOL_MODE_IN_USE).
                           0 = Report volume not in use by client (#FSC_VOL_MODE_NOT_IN_USE).
    */
    ISO_CLIENT_API
    iso_s16  iso_FscGetVolumeStatus( ISO_FSC_HANDLE_T hIO, iso_u8 u8Mode, const ISO_FSC_PATH_T* psPath );

    /** @} */


    /* ************************************************************************ */
    /** \name Part 13 C.2 Functions
        @{
    */

    /* ************************************************************************ */
    /*!
        \brief  Request the current directory path

         \param[in]    \wp{hIO,  ISO_FSC_HANDLE_T}
                             Valid IO channel handle
         \param[out]    \wp{psPath,  ISO_FSC_PATH_T*}
                             Pointer to path name structure to store the current directory or NULL pointer. \n
                             The pointer and the structure must be valid until the response is arrived \n

        \retval              iso_s16
                             - E_NO_ERR
                             - E_RANGE ( handle not valid )
                             - E_CONFIG ( IO channel busy or connection not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscGetCurrentDirectory( ISO_FSC_HANDLE_T hIO, ISO_FSC_PATH_T* psPath );

    /* ************************************************************************ */
    /*!
        \brief  Request for changing the current directory path

        \param[in]    \wp{hIO,  ISO_FSC_HANDLE_T}
                            Valid IO channel handle
        \param[out]    \wpp{psPath, const #ISO_FSC_PATH_T*}
                            Pointer to path name structure that contains the directory path. \n
                            The pointer and the structure must be valid until the response is arrived \n

        \retval          iso_s16
                             - E_NO_ERR
                             - E_RANGE ( handle not valid )
                             - E_CONFIG ( IO channel busy or connection not valid
    */
    ISO_CLIENT_API
    iso_s16  iso_FscChangeCurrentDirectory( ISO_FSC_HANDLE_T hIO, const ISO_FSC_PATH_T* psPath );

    /** @} */
    /* ************************************************************************ */
    /** \name Part 13 C.3 Functions
        @{
    */

    /* ************************************************************************ */
    /*!
        \brief  Request to open a file or directory

        \param[in]    \wp{hIO,  ISO_FSC_HANDLE_T}
                             Valid IO channel handle
        \param[in]    \wp{u8Flags,  iso_u8}
                             Flags (see Part 13 - B.14):
                             - Bit 7..5: 000 Reserved, send as 000.
                             - Bit   4:
                                - 0 = Open file for shared read access.
                                - 1 = #FSC_OPEN_EXCLUSIVE: Open file with exclusive access (fails if already open).
                             - Bit   3:
                                - 0 = Open file for random access (file pointer set to the start of the file).
                                - 1 = #FSC_OPEN_APPEND: Open file for appending data to the end of the file
                                      (file pointer set to the end of the file).
                             - Bit   2:
                                - 0 = Open an existing file (fails if non-existent file).
                                - 1 = #FSC_OPEN_CREATE: Create a new file and/or directories if not yet existing.
                             - Bit 1,0:
                                - 00 = #FSC_OPEN_READONLY: Open file for reading only.
                                - 01 = #FSC_OPEN_WRITING: Open file for writing only.
                                - 10 = #FSC_OPEN_READWRITE: Open file for reading and writing.
                                - 11 = #FSC_OPEN_DIRECTORY: Open directory.
        \param[in]    \wpp{psPath, const #ISO_FSC_PATH_T*}
                             Pointer to path name structure that contains the file or directory path. \n
                             The pointer and the structure must be valid until the response is arrived \n
        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( IO channel busy or connection not valid
    */
    ISO_CLIENT_API
    iso_s16  iso_FscOpenFile( ISO_FSC_HANDLE_T hIO, iso_u8 u8Flags , const ISO_FSC_PATH_T* psPath );

    /* ************************************************************************ */
    /*!
        \brief  Request to move the current position in an open file or directory

        \param[in]       \wp{hIO,  ISO_FSC_HANDLE_T}
                             Valid IO channel handle
        \param[in]       \wp{u8Mode,  iso_u8}
                             Position mode - Part 13 B.17 \n
                             The position mode specifies the location from which the  offset value is used to determine the file pointer position.
                             - #FSC_SEEK_BEGIN: 0x00u = From the beginning of the file.
                             - #FSC_SEEK_CURRENT: 0x01u = From the current pointer position.
                             - #FSC_SEEK_END: 0x02u = From the end of the file.
         \param[in]      \wp{s32Offset,  iso_s32}
                             Offset - Part 13 B.18 \n
                             The offset is used with the position mode to determine the file pointer position. \n

        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( IO is not assigned with a file handle or IO channel busy or connection not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscSeekFile( ISO_FSC_HANDLE_T hIO, iso_u8 u8Mode , iso_s32 s32Offset );

    /* ************************************************************************ */
    /*!
        \brief  Request to read data from an open file or directory

        \param[in]       \wp{hIO,  ISO_FSC_HANDLE_T}
                              Valid IO channel handle
        \param[out]      \wp{psDataBuffer,  ISO_FSC_DATA_T*}
                             Pointer to data structure to store the response data or NULL pointer. \n
                             The pointer and the structure must be valid until the response is arrived. \n
                             The function is reading (u32DataSize - u32DataLength) data bytes if u32DataLength is set to zero.
        \param[in]        \wp{u32DataLength,  iso_u32}
                              Optional: if greater than zero, the client tries to read this count of bytes or directory entries.
        \param[in]        \wp{u8ReportHidden,  iso_u8}
                             Report hidden files (only used, if the handle points to a directory - Part 13 B.28) \n
                             - 0x00u = Do not report hidden files in a directory listing.
                             - 0x01u = Report hidden files in a directory listing.
                             - 0xFFu = Parameter is not available, FS shall not report hidden files in a directory listing.
        \retval              iso_s16
                               - E_NO_ERR
                               - E_RANGE ( handle not valid )
                               - E_CONFIG ( IO is not assigned with a file handle or IO channel busy or connection not valid )
        \note
                             If the data buffer is full the FSC calls the callback function with the state IsoFscDoCallBack and the error code IsoFscBufferIsFull.
                             After this the FSC set the length of the buffer to zero, if the application has not done this...
    */
    ISO_CLIENT_API
    iso_s16  iso_FscReadFile( ISO_FSC_HANDLE_T hIO, ISO_FSC_DATA_T* psDataBuffer, iso_u32 u32DataLength, iso_u8 u8ReportHidden );

    /* ************************************************************************ */
    /*!
        \brief  Request to write data to an open file

        \param[in]       \wp{hIO,  ISO_FSC_HANDLE_T}
                             ISO_FSC_HANDLE_T     Valid IO channel handle
        \param[in]       \wpp{psDataBuffer, const #ISO_FSC_DATA_T*}
                             Pointer to data structure. \n
                             The pointer and the structure must be valid until the response is arrived \n
                             The function uses the TP protocol and is writing psDataBuffer->u32DataLength data bytes in one ore more FSC_RW_BLOCK_SIZE blocks ( FSC_RW_BLOCK_SIZE = BLOCK_SIZE_J1939 - 5uL). \n
        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( IO is not assigned with a file handle or IO channel busy or connection not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscWriteFile( ISO_FSC_HANDLE_T hIO, const ISO_FSC_DATA_T* psDataBuffer );

    /* ************************************************************************ */
    /*!
        \brief  Request to write data to an open file

        \param[in]      \wp{hIO,  ISO_FSC_HANDLE_T}
                             Valid IO channel handle
        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( IO is not assigned with a file handle or IO channel busy or connection not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscCloseFile( ISO_FSC_HANDLE_T hIO);

    /** @} */
    /* ************************************************************************ */
    /** \name Part 13 C.4 Functions
        @{
    */

    /* ************************************************************************ */
    /*!
        \brief  Request to move a file or directory

        \param[in]       \wp{hIO,  ISO_FSC_HANDLE_T}
                          Valid IO channel handle    \n
        \param[in]       \wp{u8Mode,  iso_u8}
                             File handling mode - Part 13 B.27 \n
                             - Bit 7-3: 00000 = Reserved, send as 00000.
                             - Bit 2  :
                                - 0 = "Recursive" mode is not set.
                                - 1 = "Recursive" mode is set (#FSC_FILE_MODE_RECURSIVE).
                             - Bit 1  :
                                - 0 = "Force" mode is not set.
                                - 1 = "Force" mode is set (#FSC_FILE_MODE_FORCE).
                             - Bit 0  :
                                - 0 = "Copy" mode is not set.
                                - 1 = "Copy" mode is set (#FSC_FILE_MODE_COPY).
        \param[in]       \wpp{psSourcePath, const #ISO_FSC_PATH_T*}
                             Pointer to path name structure that contains the file or directory source path.  \n
                             The pointer and the structure must be valid until the response is arrived \n
        \param[in]       \wp{psDestinationPath,  ISO_FSC_PATH_T*}
                              Pointer to path name structure that contains the file or directory destination path.  \n
                             The pointer and the structure must be valid until the response is arrived \n
        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( Source or destination path structure not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscMoveFile( ISO_FSC_HANDLE_T hIO, iso_u8 u8Mode , const ISO_FSC_PATH_T* psSourcePath, ISO_FSC_PATH_T* psDestinationPath );

    /* ************************************************************************ */
    /*!
        \brief  Request to delete a file or directory

        \param[in]       \wp{hIO,  ISO_FSC_HANDLE_T}
                            Valid IO channel handle    \n
        \param[in]       \wp{u8Mode,  iso_u8}
                            File handling mode - Part 13 B.27 \n
                             - Bit 7-3: 00000 = Reserved, send as 00000.
                             - Bit 2  :
                                - 0 = "Recursive" mode is not set.
                                - 1 = "Recursive" mode is set (#FSC_FILE_MODE_RECURSIVE).
                             - Bit 1  :
                                - 0 = "Force" mode is not set.
                                - 1 = "Force" mode is set (#FSC_FILE_MODE_FORCE).
                             - Bit 0  :
                                - 0 = "Copy" mode is not set.
                                - 1 = "Copy" mode is set (#FSC_FILE_MODE_COPY).
        \param[in]       \wpp{psPath, const #ISO_FSC_PATH_T*}
                              Pointer to path name structure that contains the file or directory path.  \n
                             The pointer and the structure must be valid until the response is arrived \n
        \retval              iso_s16
                             - E_NO_ERR
                             - E_RANGE ( handle not valid )
                             - E_CONFIG ( Path structure not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscDeleteFile( ISO_FSC_HANDLE_T hIO, iso_u8 u8Mode , const ISO_FSC_PATH_T* psPath );


    /* ************************************************************************ */
    /*!
        \brief  Request to get file attributes

        \param[in]       \wp{hIO,  ISO_FSC_HANDLE_T}
                             Valid IO channel handle
        \param[in]       \wpp{psPath, const #ISO_FSC_PATH_T*}
                             Pointer to path name structure that contains the file path.  \n
                             The pointer and the structure must be valid until the response is arrived

        \retval              iso_s16
                               - E_NO_ERR
                               - E_RANGE ( handle not valid )
                               - E_CONFIG ( path structure not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscGetFileAttributes( ISO_FSC_HANDLE_T hIO, const ISO_FSC_PATH_T* psPath );

    /* ************************************************************************ */
    /*!
        \brief  Request to set file attributes

        \param[in]       \wp{hIO,  ISO_FSC_HANDLE_T}
                             Valid IO channel handle
        \param[in]       \wp{u8AttrCmds,  iso_u8}
                             Set Attributes Command - Part 13 B.16 \n
                             The command from the client to the FS for setting or clearing file attributes.
                             - Bit 7,6 and Bit 5,4 : Reserved, set to #FSC_ATTR_SET_RESERVED ( 0xF0u ).
                             - Bit 3,2 :
                                - #FSC_ATTR_CLEAR_HIDDEN: 00 = Clear "hidden" attribute.
                                - #FSC_ATTR_SET_HIDDEN: 01 = Set "hidden" attribute.
                                - #FSC_ATTR_LEAVE_READONLY: 11 = Don't care, leave "hidden" attribute in current state.
                             - Bit 1,0 :
                                - #FSC_ATTR_CLEAR_READONLY: 00 = Clear "read-only" attribute.
                                - #FSC_ATTR_SET_READONLY: 01 = Set "read-only" attribute.
                                - #FSC_ATTR_LEAVE_READONLY: 11 = Don't care, leave "read-only" attribute in current state.
         \param[in]       \wpp{psPath, const #ISO_FSC_PATH_T*}
                             Pointer to path name structure that contains the file path.  \n
                             The pointer and the structure must be valid until the response is arrived \n
        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( path structure not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscSetFileAttributes( ISO_FSC_HANDLE_T hIO, iso_u8 u8AttrCmds , const ISO_FSC_PATH_T* psPath );

    /* ************************************************************************ */
    /*!
        \brief  Request to get file date and time

        \param[in]       \wp{hIO,  ISO_FSC_HANDLE_T}
                             Valid IO channel handle
        \param[in]       \wpp{psPath, const #ISO_FSC_PATH_T*}
                             Pointer to path name structure that contains the file path.  \n
                             The pointer and the structure must be valid until the response is arrived

        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( path stucture not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscGetFileDateTime( ISO_FSC_HANDLE_T hIO, const ISO_FSC_PATH_T* psPath );

    /** @} */
    /* ************************************************************************ */
    /** \name Part 13 C.5 Functions
        @{
    */

    /* ************************************************************************ */
    /*!
        \brief  Request for initializing a volume

        \param[in]        \wp{hIO,  ISO_FSC_HANDLE_T}
                            Valid IO channel handle
        \param[in]        \wp{u32Space,  iso_u32}
                            Space in 512 iso_u8 units - Part 13 B.11
        \param[in]        \wp{u8Flags,  iso_u8}
                            Flags see Part 13 B.29
        \param[in]        \wpp{psPath, const #ISO_FSC_PATH_T*}
                            Pointer to path name structure that contains the volume path. \n
                            The pointer and the structure must be valid until the response is arrived

        \retval              iso_s16
                              - E_NO_ERR
                              - E_RANGE ( handle not valid )
                              - E_CONFIG ( IO channel busy or connection not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscInitializeVolume( ISO_FSC_HANDLE_T hIO, iso_u32 u32Space, iso_u8 u8Flags , const ISO_FSC_PATH_T* psPath );

    /** @} */
    /* ************************************************************************ */
    /** \name  FSC - Extended Functions
        @{
    */

    /*!
        \brief         Set optional global call back function  for handling all unhandled responses

        \param[in]    \wpp{userParam, const #ISO_USER_PARAM_T}
                         User parameter value for the callback function calls. \n
                         Use #ISO_USER_PARAM_DEFAULT if not used/needed.
        \param[in]     \wp{pFunction,  ISO_FSC_CALLBACK_t}
                         pointer to callback function or NULL pointer to remove the module global callback function.

        \retval         iso_s16
                         E_NO_ERR
    */
    ISO_CLIENT_API
    iso_s16  iso_FscSetGlobalCallBack( const ISO_USER_PARAM_T userParam, ISO_FSC_CALLBACK_t pFunction );

    /* ************************************************************************ */
    /*!
        \brief         Set callback function for channel or connection ( for handling all unhandled responses or errors )

        \param[in]      \wp{hFscHandle,  ISO_FSC_HANDLE_T}
                         Valid connection or io channel handle
        \param[in]      \wpp{userParam, const #ISO_USER_PARAM_T}
                         User parameter value for the callback function calls. \n
                         Use #ISO_USER_PARAM_DEFAULT if not used/needed.
        \param[in]      \wp{pFunction,  ISO_FSC_CALLBACK_t}
                         Pointer to callback function or NULL pointer to remove the callback function.

        \retval        iso_s16
                        - E_NO_ERR
                        - E_RANGE ( handle not valid )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscSetCallbackFunction( ISO_FSC_HANDLE_T hFscHandle, const ISO_USER_PARAM_T userParam, ISO_FSC_CALLBACK_t pFunction );

    /* ************************************************************************ */
    /*!
        \brief  Extended function to read a complete file.

        The FS client is automatically creating and freeing the connection.

        \param[in]        \wp{s16FSClientMemberHandle,  iso_s16}
                              Valid client (internal) network member (user) handle.
        \param[in]        \wp{s16FServerMemberHandle,  iso_s16}
                             Valid server (external) network member (user) handle.
        \param[in]        \wpp{psPath, const #ISO_FSC_PATH_T*}
                             Pointer to file path structure. \n
                             The pointer and the structure must be valid until the response is arrived.
        \param[out]       \wp{psDataBuffer,  ISO_FSC_DATA_T*}
                             Pointer to data structure to store the response data or NULL pointer. \n
                             The pointer and the structure must be valid until the response is arrived.
        \param[in]        \wpp{userParam, const #ISO_USER_PARAM_T}
                             User parameter value for the callback function calls. \n
                             Use #ISO_USER_PARAM_DEFAULT if not used/needed.
        \param[in]        \wp{pFunction,  ISO_FSC_CALLBACK_t}
                             Pointer to callback function.

        \retval              iso_s16
                               - E_NO_ERR
                               - E_RANGE ( parameter not valid )
                               - E_CONFIG ( no free IO channel or connection entry )
        \note
                             If the data buffer is full the FSC calls the callback function with the state IsoFscDoCallBack and the error code IsoFscBufferIsFull.
                             After this the FSC set the length of the buffer to zero, if the application has not done this...
    */
    ISO_CLIENT_API
    iso_s16  iso_FscReadFileFromServer( iso_s16 s16FSClientMemberHandle, iso_s16 s16FServerMemberHandle,
                                       const ISO_FSC_PATH_T* psPath, ISO_FSC_DATA_T* psDataBuffer,
                                       const ISO_USER_PARAM_T userParam, ISO_FSC_CALLBACK_t pFunction );

    /* ************************************************************************ */
    /*!
        \brief  Extended function to write a complete file.

        The FS client is automatically creating and freeing the connection.
        The FS client deletes automatically an existing file, before writing the new file,
        to make sure that no invalid data are left at the end of the file...

        \param[in]        \wp{s16FSClientMemberHandle,  iso_s16}
                              Valid client (internal) network member (user) handle.
        \param[in]        \wp{s16FServerMemberHandle,  iso_s16}
                              Valid server (external) network member (user) handle.
        \param[in]        \wpp{psPath, const #ISO_FSC_PATH_T*}
                              Pointer to file path structure. \n
                              The pointer and the structure must be valid until the response is arrived.
        \param[in]        \wp{psDataBuffer,  ISO_FSC_DATA_T*}
                              Pointer to data structure. \n
                              The pointer and the structure must be valid until the response is arrived \n
                              The function uses the TP protocol and is writing psDataBuffer->u32DataLength data bytes in one ore more FSC_RW_BLOCK_SIZE blocks ( FSC_RW_BLOCK_SIZE = BLOCK_SIZE_J1939 - 5uL). \n
        \param[in]        \wpp{userParam, const #ISO_USER_PARAM_T}
                              User parameter value for the callback function calls. \n
                              Use #ISO_USER_PARAM_DEFAULT if not used/needed.
        \param[in]        \wp{pFunction,  ISO_FSC_CALLBACK_t}
                              Pointer to callback function.

        \retval              iso_s16
                               - E_NO_ERR
                               - E_RANGE ( parameter not valid )
                               - E_CONFIG ( no free IO channel or connection entry )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscWriteFileToServer( iso_s16 s16FSClientMemberHandle, iso_s16 s16FServerMemberHandle,
                                      const ISO_FSC_PATH_T* psPath, ISO_FSC_DATA_T* psDataBuffer,
                                      const ISO_USER_PARAM_T userParam, ISO_FSC_CALLBACK_t pFunction );

    /* ************************************************************************ */
    /*!
        \brief  Extended function to append data to a file.

        The FS client is automatically creating and freeing the connection.
        The FS client creates automatically the file, if it does not exist.

        \param[in]        \wp{s16FSClientMemberHandle,  iso_s16}
                             Valid client (internal) network member (user) handle.
        \param[in]        \wp{s16FServerMemberHandle,  iso_s16}
                             Valid server (external) network member (user) handle.
        \param[in]        \wpp{psPath, const #ISO_FSC_PATH_T*}
                             Pointer to file path structure. \n
                             The pointer and the structure must be valid until the response is arrived.
        \param[in]        \wp{psDataBuffer,  ISO_FSC_DATA_T* }
                             Pointer to data structure. \n
                             The pointer and the structure must be valid until the response is arrived \n
                             The function uses the TP protocol and is writing psDataBuffer->u32DataLength data bytes in one ore more FSC_RW_BLOCK_SIZE blocks ( FSC_RW_BLOCK_SIZE = BLOCK_SIZE_J1939 - 5uL). \n
        \param[in]        \wpp{userParam, const #ISO_USER_PARAM_T}
                             User parameter value for the callback function calls. \n
                             Use #ISO_USER_PARAM_DEFAULT if not used/needed.
        \param[in]         \wp{pFunction,  ISO_FSC_CALLBACK_t}
                             Pointer to callback function.
        \retval              iso_s16
                               - E_NO_ERR
                               - E_RANGE ( parameter not valid )
                               - E_CONFIG ( no free IO channel or connection entry )
    */
    ISO_CLIENT_API
    iso_s16  iso_FscAppendFileToServer( iso_s16 s16FSClientMemberHandle,
                                       iso_s16 s16FServerMemberHandle,
                                       const ISO_FSC_PATH_T* psPath,
                                       ISO_FSC_DATA_T* psDataBuffer,
                                       const ISO_USER_PARAM_T userParam,
                                       ISO_FSC_CALLBACK_t pFunction );

    /** @} */
    /* ************************************************************************ */
    /** \name  FSC - Helper Functions
        @{
    */

    /* ************************************************************************ */
    /*!
        \brief  Helper function to initialize a ISO_FSC_DATA_T buffer.

        \param[in]        \wp{psDataStruct,  ISO_FSC_DATA_T*}
                            Pointer to data buffer structure which shall be initialized.
        \param[in]        \wp{au8DataArray,  iso_u8*}
                            Pointer to the iso_u8 array which shall be used for the buffer.
        \param[in]        \wp{u32DataArraySize,  iso_u32}
                            Size of the iso_u8 array.
        \param[in]        \wp{u32DataLength,  iso_u32}
                            Currently used bytes of the array ( usually 0uL ).

        \retval             iso_s16
                             - E_NO_ERR
                             - E_RANGE ( parameter not valid )
    */
    ISO_CLIENT_API
    iso_s16 iso_FscInitDataStruct( ISO_FSC_DATA_T* psDataStruct, iso_u8 HUGE_C * au8DataArray, iso_u32 u32DataArraySize, iso_u32 u32DataLength );

    /* ************************************************************************ */
    /*!
        \brief  Helper function to copy a zero terminated char array into a ISO_FSC_DATA_T buffer.

        The function does not copy the zero byte into the buffer...
        The function is setting u32DataLength after the last copied byte.

        \param[in]        \wp{psDataStruct,  ISO_FSC_DATA_T*}
                              Pointer to data buffer structure. \n
        \param[in]        \wp{u32AtPos,  iso_u32}
                              Start position in the data buffer ( 0uL >= u32AtPos <= u32DataSize). \n
        \param[in]        \wpp{au8DataArray, const #iso_u8[]}
                              Pointer to the char array which shall be copied into the buffer. \n

        \retval             iso_s16
                             - E_NO_ERR
                             - E_RANGE ( parameter not valid )
    */
    ISO_CLIENT_API
    iso_s16 iso_FscCopyStringToDataStruct( ISO_FSC_DATA_T* psDataStruct, iso_u32 u32AtPos ,const iso_u8 HUGE_C au8DataArray[] );

    /* ************************************************************************ */
    /*!
        \brief  Helper function to copy data into a ISO_FSC_DATA_T buffer.

        The function is setting u32DataLength after the last copied byte.

        \param[in]        \wp{psDataStruct,  ISO_FSC_DATA_T*}
                              Pointer to data buffer structure.
        \param[in]        \wp{u32AtPos,  iso_u32}
                              Start position in the data buffer ( 0uL >= u32AtPos <= u32DataSize).
        \param[in]        \wpp{au8DataArray,  const #iso_u8[]}
                              Pointer to the iso_u8 array which shall be copied into the buffer.
        \param[in]        \wp{u32DataArrayLength,  iso_u32}
                              Number of bytes which shall be copied.

        \retval             iso_s16
                             - E_NO_ERR
                             - E_RANGE ( parameter not valid )
    */
    ISO_CLIENT_API
    iso_s16 iso_FscCopyArrayToDataStruct( ISO_FSC_DATA_T* psDataStruct, iso_u32 u32AtPos , const iso_u8 HUGE_C au8DataArray[], iso_u32 u32DataArrayLength );

    /** @} */

/* ************************************************************************ */
/** @} */  /* end defgroup fsclient                                         */
/* ************************************************************************ */

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_IsoFscApi_H */
/* ************************************************************************ */
