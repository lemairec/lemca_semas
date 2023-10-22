/* ************************************************************************ */
/*!
   \file

   \brief          VT client demo application

   \author         Erwin Hammerl
   \date           Created 17.09.2007

   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft

   \par HISTORY:

*/
/* **************************  includes ********************************** */

#include "IsoDef.h"

#ifdef _LAY6_  /* compile only if VT client is enabled */


#include "VIEngine.h"
#include "App_VTClientLev2.h"   // -> Object defines
#include "MyProject1.iop.h"
#include "MyProject1.c.h"
#include "settings.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "AppCommon/AppHW.h"

#include "lemca/lemca.h"
#include "AppIso/config.h"

#define BEACON_PIN 6
#define WORKLIGHT_PIN 7
#define REVERSE_PIN 8


//********************************************************************************************
// Each command has several Unique Features. here they are encapsulated !
//********************************************************************************************
typedef struct {
	//
	//! The Commandnumber is here redundant, however a Testdriver can check for Validity !!!
	//
	iso_u16 objectIdOfAuxObject; // objectIdOfAuxObject
	iso_u16 objectIdOfButtonObject; // objectIdOfButtonObject

} CommandTranslateObject;

CommandTranslateObject CommandTranslate[] = {
	{ AuxFunction2_right,		SoftKey_right		},
	{ AuxFunction2_left,		SoftKey_left		},
	{ AuxFunction2_middle,		SoftKey_middle		},
	{ AuxFunction2_auto,		SoftKey_auto		},
	{ AuxFunctionSectionOnOff,	SoftKeySectionOnOff	},
	{ AuxFunctionSectionRight,	SoftKeySectionRight	},
	{ AuxFunctionSectionLeft,	SoftKeySectionLeft	}
};


//make this Defines (Right side)
const int FIRST_AUX = AuxFunction2_right;
const int  LAST_AUX = AuxFunctionSectionLeft;
//do not Change this.
const int  NUM_AUX_FUNCTIONS = ((LAST_AUX-FIRST_AUX)+1);
iso_s32 InputSignalData_old_value1[20] = {AUX_PRESS_OFF};



// called from AppPoolSettings()
void VTC_setPoolManipulation(const ISOVT_EVENT_DATA_T* psEvData)
{
   iso_u16  u16DM_Scal  = 10000u;          // Scaling factor * 10000
   iso_u16  u16SKM_Scal = 10000u;

   // ------------------------------------------------------------------------------

   // IsoVtcPoolSetIDRangeMode(u8Instance, 0, 60000, 10000, NoScaling);          // Switch off automatic scaling

   u16DM_Scal = (iso_u16)IsoVtcPoolReadInfo(psEvData->u8Instance, PoolDataMaskScalFaktor);       // Call only after PoolInit !!
   u16SKM_Scal = (iso_u16)IsoVtcPoolReadInfo(psEvData->u8Instance, PoolSoftKeyMaskScalFaktor);

   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 5100u, 5300u, u16SKM_Scal, Centering);       // Scale and center Keys
   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 20700u, 20799u, u16SKM_Scal, Scaling);         // Scale Pictures in keys


   // ------------------------------------------------------------------------------


   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 0u,     0u, u16SKM_Scal, Centering);  // Working set object
   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 20000u, 20000u, u16SKM_Scal, Scaling);    // Working set designator
   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 29000u, 29099u, u16SKM_Scal, Centering);  // Auxiliary function
   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 20900u, 20999u, u16SKM_Scal, Scaling);    // Auxiliary bitmaps
   (void)u16DM_Scal;


	if (IsoVtcGetStatusInfo(psEvData->u8Instance, VT_VERSIONNR) == VT_V2_FE)
	{
		// Transforming Auxiliary function Type 2 into Type 1
		IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 29000, 29999, 0, AuxToV2);
	}
}



iso_s8 vtc_instance = 0;

void VTC_handleSoftkeysAndButtons_RELEASED(const struct ButtonActivation_S *pButtonData) {
	// what button was released
	switch (pButtonData->objectIdOfButtonObject) {
		case SoftKey_left:
		case AuxFunction2_left:
			send_message_aux(0);
			break;
		case SoftKey_right:
		case AuxFunction2_right:
			send_message_aux(1);
			break;
		case SoftKey_auto:
		case AuxFunction2_auto:
			send_message_aux(2);
			break;
		case SoftKey_middle:
			send_message_aux(3);
			break;
		case SoftKeySectionOnOff:
		case AuxFunctionSectionOnOff:
			changeWorkState();
			break;
		case SoftKeySectionLeft:
		case AuxFunctionSectionLeft:
			startManualSectionLeft();
			break;
		case SoftKeySectionRight:
		case AuxFunctionSectionRight:
			startManualSectionRight();
			break;
		default:
			break;
	}

	vtc_instance = pButtonData->u8Instance;
	updateVTC();
}

char getCharSection(int i){
	if(i <= m_nbr_elements){
		if(getSection(i)){
			return '1';
		} else {
			return '0';
		}
	}
	return ' ';
}

void updateVTC(){
	if(vtc_instance == 0){
		return;
	}

	//hw_DebugPrint("updateVTC\n");
	char data[40];
	char c1 = getCharSection(1);
	char c2 = getCharSection(2);
	char c3 = getCharSection(3);
	char c4 = getCharSection(4);
	char c5 = getCharSection(5);
	char c6 = getCharSection(6);
	char c7 = getCharSection(7);
	char c8 = getCharSection(8);
	char c9 = getCharSection(9);
	char c10 = getCharSection(10);
	char c11 = getCharSection(11);
	char c12 = getCharSection(12);
	char c13 = getCharSection(13);
	char c14 = getCharSection(14);
	char c15 = getCharSection(15);
	char c16 = getCharSection(16);

	double speed = getSpeedKmH();
	
	sprintf(data,"%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c", c1, c2, c3, c4, c5 , c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16);

	IsoVtcCmd_String(vtc_instance, StringVariable_Debug, (iso_u8 *)data);

	if(getWorkState()){
		char data2[40];
		sprintf(data2, "TC Play");

		IsoVtcCmd_String(vtc_instance, StringVariable_Debug2, (iso_u8 *)data2);
	
	} else {
		char data2[45];
		sprintf(data2,"TC Pause - %i elts ( %i cm), lg %i cm", (char)m_nbr_elements, (char)(m_inter_rang_mm/10), (short)(m_machine_lg/10));

		IsoVtcCmd_String(vtc_instance, StringVariable_Debug2, (iso_u8 *)data2);
	}
	
	if(getRearWork()){
		char data2[30];
		sprintf(data2, "Bas (play) - %.1f km/h", speed);

		IsoVtcCmd_String(vtc_instance, StringVariable_Vitesse, (iso_u8 *)data2);
	
	} else {
		char data2[30];
		sprintf(data2, "Haut (pause) - %.1f km/h", speed);

		IsoVtcCmd_String(vtc_instance, StringVariable_Vitesse, (iso_u8 *)data2);
	}
}

void VTC_handleNumericValues(const struct InputNumber_S * pInputNumberData) {
	// what number was entered
	switch (pInputNumberData->objectIdOfInputNumber) {



	default:
		break;
	}
}


void VTC_setNewVT(const ISOVT_EVENT_DATA_T* psEvData)
{
   // ------------------------------------------------------------------------------

   PARAM_UNUSED(psEvData->u8Instance);


   // ------------------------------------------------------------------------------
}

void VTC_setPoolReady(const ISOVT_EVENT_DATA_T* psEvData)
{
	vtc_instance = psEvData->u8Instance;
	updateVTC();
}







void VTC_handleSoftkeysAndButtons(const struct ButtonActivation_S *pButtonData)
{
	switch (pButtonData->keyActivationCode)
	{
	case BUTTON_STATE_RELEASED:
		VTC_handleSoftkeysAndButtons_RELEASED(pButtonData);
		break;
	case BUTTON_STATE_PRESSED:
		//BUTTON_InputSignalCallback_PRESSED(pButtonData);
		break;
	case BUTTON_STATE_HELD:
		//BUTTON_InputSignalCallback_HELD(pButtonData);
		break;
	case BUTTON_STATE_ABORTED:
		//BUTTON_InputSignalCallback_ABORTED(pButtonData);
		break;
	}
}

void VTC_handleAux(const struct AUX_InputSignalData_T *InputSignalData) {
	struct ButtonActivation_S pButtonData;


	// Application may decide to lookup the object ID of the function assigned to this input
	// and then check the status data reported...
	//functionObjID = <maybe you have a lookup to get function object Id from (InputSignalData.inputObjectID)>;

	// Store the sprintf format string in HUGE ROM.
	//static SprinthfFormatChar_T format[] = "Pressed = %s, Status= %i\n";


	if (InputSignalData->objectIdOfAuxObject < FIRST_AUX)
	{
		return;
	}



	pButtonData.objectIdOfButtonObject = CommandTranslate[InputSignalData->objectIdOfAuxObject - FIRST_AUX].objectIdOfButtonObject;
	pButtonData.wPara2 = (iso_u16)InputSignalData->value1;
	pButtonData.u8Instance = InputSignalData->u8Instance;

	switch (InputSignalData->value1) {
	case AUX_PRESS_OFF:
		switch (InputSignalData_old_value1[InputSignalData->objectIdOfAuxObject - FIRST_AUX]) {
		case AUX_PRESS_OFF:
			//NOOP!
			break;
		default:
			pButtonData.keyActivationCode = BUTTON_STATE_RELEASED;
			VTC_handleSoftkeysAndButtons(&pButtonData);
			break;
		}
		break;
	case AUX_PRESS_MOMENTARY:
		pButtonData.keyActivationCode = BUTTON_STATE_PRESSED;
		VTC_handleSoftkeysAndButtons(&pButtonData);
		break;
	case AUX_PRESS_HELD:
		switch (InputSignalData_old_value1[InputSignalData->objectIdOfAuxObject - FIRST_AUX]) {
		case AUX_PRESS_OFF:
			pButtonData.keyActivationCode = BUTTON_STATE_PRESSED;
			VTC_handleSoftkeysAndButtons(&pButtonData);
			break;
		default:
			pButtonData.keyActivationCode = BUTTON_STATE_HELD;
			VTC_handleSoftkeysAndButtons(&pButtonData);
			break;
		}
		break;
	default:
		break;

	}

	InputSignalData_old_value1[InputSignalData->objectIdOfAuxObject - FIRST_AUX] = InputSignalData->value1;
}



/* ************************************************************************ */
#endif /* _LAY6_ */
/* ************************************************************************ */
