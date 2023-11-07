
#ifndef VIEngine_h__
#define VIEngine_h__



/*!
 * Various shorthand strucths to improve readability and maintainability
 * they are copies of ISOVT_MSG_STA_T
 * iso_s16          iVtFunction;       VT function of received message (#ISOVT_FUNC_e)
 * iso_u16          wObjectID;         Object ID (if available)
 * iso_u32          lValue;            Long value depending of command/activation message see table
 * iso_u16          wPara1;            Unsigned short value 1 depending of command/activation message see table
 * iso_u16          wPara2;            Unsigned short value 2 depending of command/activation message see table
 * iso_u8           bPara;             Unsigned char value depending of command/activation message see table
 * iso_u8           u8Instance;        Identifier of the client instance
 * iso_s16          iErrorCode;        Error code of response messages or error code e. g. #E_CANMSG_MISSED
 * iso_s32          lTimeSt;           Time stamp of received message
 * const iso_u8*    pabVtData;         Data of VT e. g. string characters see table
 * ISO_USER_PARAM_T userParam;         User parameter set with IsoVT_CreateInstance()
 */



/*!
   \brief       .
   \verbatim

    VT-Function:                Parameter of       Meaning:
                                ISOVT_MSG_STA_T:

    softkey_activation            wObjectID       key object ID
                                  wPara1          parent object ID
                                  bPara           key number (hard coded)
                                  lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
    button_activation             wObjectID       button object ID
                                  wPara1          parent object ID
                                  bPara           button key number
                                  lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
    pointing_event                wPara1          X position in pixel
                                  wPara2          Y position in pixel
    VT_select_input_object        wObjectID       input object ID
                                  wPara1          Selected/Deselected
                                  wPara2          Bitmask (Version 5 and later)
    VT_esc                        wObjectID       ID of input field where aborted
                                  iErrorCode      error code see ISO Doku.
    VT_change_numeric_value       wObjectID       ID of input object
                                  lValue          new value
    VT_change_active_mask         wObjectID       momentan active mask
                                  iErrorCode      error code see ISO Doku.
    VT_change_softkey_mask        wObjectID       data or alarm mask object ID
                                  wPara1          soft key mask object ID
                                  iErrorCode      error code see ISO Doku
    VT_change_string_value        wObjectID       ID of String object
                                  bPara           Length of string
                                  pabVtData       Pointer to characters
    ( Version 4 )
    VT_onUserLayout_hideShow      wObjectID       Object ID of WM, DM, SKM, KG
                                  wPara2          Hide/show
                                  wPara1          Object ID of second WM, DM, SKM, KG
                                  bPara           Hide/show of second
    get_attribute_value           wObjectID       Object ID
                                  bPara           AID
                                  wPara1          Current value of attribute
                                  iErrorCode      ErrorCode (see F.59)
    ( Version 3 )
    preferred_assignment          wObjectID       Auxiliary function object if faulty
                                  iErrorCode      Error code see ISO Doku.
    auxiliary_assign_type_1, .._2 wObjectID       Object ID auxiliary function
                                  wPara1          Object ID auxiliary input (or input number type 1)
                                                  0xFFFF for unassign
                                  wPara2          Type of auxiliary incl. Attribute bits see [2]
                                  bPara           ISO_TRUE: Store as pref. assign, else not (only type 2)
                                  lValue          Bit 16 - 27: Manufacturer code,
                                                  Bit  0 - 15 Model Identification code of auxiliary input
                                                  (only type 2)
                                  pabVtData       only for auxiliary_assign_type_2:
                                                  Pointer to the last/current aux unit ISONAME or 8*0xFF
    auxiliary_input_status_type_2
    aux_input_status_type_1       wObjectID       Object ID Auxiliary function type
                                  wPara1          Input object ID (type 1 = input number
                                  lValue          Value 1
                                  wPara2          Value 2
                                  iErrorCode      E_NO_ERR, E_CANMSG_MISSED (Alive of input)
    ( Version 5 )
    auxiliary_capabilities        bPara           Number of auxiliary Units
                                  pabVtData       Pointer to data ( Byte 3 ... )

               [1] Timeout control of softkeys and buttons have to be done of application !
               [2] Attribute bits are given to application as additional information
                   For getting the Auxiliary type application have to mask out it.
   \endverbatim

*/



//SOFT KEY ACTIVATION CODE
enum SoftKeyActivationCode_S
{
	SK_RELEASED = 0,
	SK_PRESSED = 1,
	SK_STILL_HELD = 2,
	SK_ABORTED = 3 //VT Version 4< 
};


//BUTTON ACTIVATION CODE
enum ButtonActivationCode_S
{
	BT_RELEASED_UNLATCHED = 0,
	BT_PRESSED_LATCHED = 1,
	BT_STILL_HELD = 2, /*latchable buttons do not repeat*/
	BT_ABORTED = 3 /*VT Version 4*/
};









/*!
 *
 *     softkey_activation
 *     		wObjectID       key object ID
 *     		wPara1          parent object ID
 *     		bPara           key number (hard coded)
 *     		lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
 *
 */

// SOFT KEY ACTIVATION (Response == Request)
struct SoftKeyActivation_S
{
    iso_s16          iVtFunction;                           /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfKeyObject;                   /**< \brief key object ID */
    iso_u32          keyActivationCode;                     /**< \brief activation code (0, 1, 2, 3(Version 4)) see [1] */
    iso_u16          objectIdOfVisibleParentDataOrAlarmMask;/**< \brief parent object ID */
    iso_u16          wPara2;                                /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           softKeyCode;                           /**< \brief key number (hard coded) */
    iso_u8           u8Instance;                            /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;                            /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;                               /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;                             /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;                             /**< \brief User parameter set with IsoVT_CreateInstance() */
};

/*!
 *
 *     button_activation
 *     		wObjectID       button object ID
 *     		wPara1          parent object ID
 *     		bPara           button key number
 *     		lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
 *
 */

// BUTTON ACTIVATION (Response == Request)
struct ButtonActivation_S
{
    iso_s16          iVtFunction;                           /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfButtonObject;                /**< \brief button object ID */
    iso_u32          keyActivationCode;                     /**< \brief activation code (0, 1, 2, 3(Version 4)) see [1] */
    iso_u16          objectIdOfParentDataMask;              /**< \brief parent object ID */
    iso_u16          wPara2;                                /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           buttonKeyCode;                         /**< \brief button key number */
    iso_u8           u8Instance;                            /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;                            /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;                               /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;                             /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;                             /**< \brief User parameter set with IsoVT_CreateInstance() */
};


/*!
 *
 *  pointing_event                wPara1          X position in pixel
 *                                wPara2          Y position in pixel
 *
 *
 */


struct PointingEvent_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          Xposition;         /**< \brief X position in pixel */
    iso_u16          Yposition;         /**< \brief Y position in pixel */
    iso_u8           touchActivationCode;/**< \brief Touch Activation Code*/
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};






/*!
 *
 *
 * VT_select_input_object        wObjectID       input object ID
 *                               wPara1          Selected/Deselected
 *                               wPara2          Bitmask (Version 5 and later)
 *
 *
 *
 *
 */


struct SelectInput_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfInputObject;         /**< \brief input object ID */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          selected;          /**< \brief Selected/Deselected */
    iso_u16          bitmask;           /**< \brief Bitmask (Version 5 and later) */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};




/*!
 *
 *
 *     VT_esc                        wObjectID       ID of input field where aborted
 *                                   iErrorCode      error code see ISO Doku.
 *
 *
 *
 *
 */

struct VTEsc_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfInputObject; /**< \brief ID of input field where aborted */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief error code see ISO Doku. */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};



/*!
 *
 *     VT_change_numeric_value
 *     		wObjectID       ID of input object
 *     		lValue          new value
 *
 */

// Input Number
struct InputNumber_S
{
    iso_s16          iVtFunction;                           /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfInputNumber;                 /**< \brief ID of input object */
    iso_u32          newValue;                              /**< \brief new value */
    iso_u16          wPara1;                                /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;                                /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;                                 /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;                            /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;                            /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;                               /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;                             /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;                             /**< \brief User parameter set with IsoVT_CreateInstance() */
};


/*
 *
 *     VT_change_string_value
 *     		wObjectID       ID of String object
 *     		bPara           Length of string
 *     		pabVtData       Pointer to characters
 *
 */

struct InputString_S
{
    iso_s16          iVtFunction;                           /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfInputString;                 /**< \brief ID of String object */
    iso_u32          lValue;                                /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;                                /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;                                /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           numberOfBytes;                         /**< \brief Length of string */
    iso_u8           u8Instance;                            /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;                            /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;                               /**< \brief Time stamp of received message */
    const iso_u8*    newStringValue;                        /**< \brief Pointer to characters */
    ISO_USER_PARAM_T userParam;                             /**< \brief User parameter set with IsoVT_CreateInstance() */
};





struct PreferredAssignment_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};

struct AuxAssignTypeOld_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};

struct AuxAssignTypeNew_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};

struct AuxiliaryOldInput_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};

struct AuxiliaryNewInput_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfAuxObject; /**< \brief Object ID (if available) */
    iso_u32          value1;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};


struct MaskHideShow_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};



struct AuxiliaryCapabilities_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};



struct AttributeValue_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};


struct EndOfPoolTransfer_S
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
};


enum AUX_PRESS_E {

	AUX_PRESS_OFF = 0, //0 = Off = backward, down, left, or not pressed
	AUX_PRESS_MOMENTARY = 1,//1 = Momentary = forward, up, right, or pressed
	AUX_PRESS_HELD = 2//2 = held
};



#define	AUX_DOWN_FLOAT  0xFAFF
#define	AUX_DOWN  		0xFAFE
#define	AUX_MIDDLE  	0x7D7F
#define	AUX_UP  		0x0



/* AUX input signal activation callback notification struct */
struct AUX_InputSignalData_T
{
	iso_s16    iVtFunction;       /**< Last function of VT response (#ISOVT_FUNC_e) */
	iso_u16    objectIdOfAuxObject;
	iso_s32    value1;            /**< Value of VT change numeric value */
	iso_u16    inputObjectID;     /**< Word storage 1 */
	iso_u16    value2;            /**< Word storage 2 */
	iso_u8     bPara;             /**< Byte storage i. e. soft key number */
    iso_u8     u8Instance;        /**< \brief Identifier of the client instance */
	iso_s16    iErrorCode;        /**< Error iso_u8 of response messages */

};

enum VT_line_width
{
	Line_Width_0,
	Line_Width_1,
	Line_Width_2,
	Line_Width_3,
};

enum
{
	Null_Language,
	German,
	English,
	Czech,	
	French,		
	Hungarian,	
	Italian,	
	Polish,	
	Portuguese,	
	Russian,	
	Spanish,
	Swedish,
	Bulgarian,
	Dutch

};

enum Button_States_E
{
	BUTTON_STATE_RELEASED,
	BUTTON_STATE_PRESSED,
	BUTTON_STATE_HELD,
	BUTTON_STATE_ABORTED
};

enum TouchActivationCode_S
{
	PT_RELEASED = 0,
	PT_PRESSED = 1,
	PT_HELD = 2
};

enum MaskHideShowCode_S
{
	M_HIDE = 0,
	M_SHOW = 1
};

enum SelectInputObjectCode_S
{
	DESELECTED = 0,
	SELECTED = 1
};

#endif // VIEngine_h__
