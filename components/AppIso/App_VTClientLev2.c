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
	{ AuxFunctionSectionOnOff,	SoftKeySectionOnOff	}
};


//make this Defines (Right side)
const int FIRST_AUX = SoftKeySectionOnOff;
const int  LAST_AUX = SoftKeySectionOnOff;
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
		case SoftKeySectionOnOff:
		case AuxFunctionSectionOnOff:
			changeWorkState();
			break;
		case SoftKey_down:
			onButtonDown();
			break;
		case SoftKey_up:
			onButtonUp();
			break;
		case SoftKey_upleft:
			onButtonUpLeft();
			break;
		case SoftKey_upright:
			onButtonUpRight();
			break;
		case SoftKey_down2:
			onButtonDownWork();
			break;
		case SoftKey_up2:
			onButtonUpWork();
			break;
		default:
			break;
	}

	vtc_instance = pButtonData->u8Instance;
	updateVTC();
}

enum State last_state = State_off;
void updateVTC(){
	if(vtc_instance == 0){
		return;
	}

	//hw_DebugPrint("updateVTC\n");
	double speed = getSpeedKmH();
	char data[30];
	sprintf(data,"%.1f km/h", speed);

	enum State state = getState();
	char data2[30];
	if(state == State_off){
		sprintf(data2,"off");
	} else if(state == State_time){
		sprintf(data2,"time");
	} else if(state == State_up){
		sprintf(data2,"up");
	} else if(state == State_work){
		sprintf(data2,"work");
	}
	last_state = state;
	//IsoVtcCmd_String(vtc_instance, StringVariable_State, (iso_u8 *)data2);

    //IsoVtcCmd_String(vtc_instance, StringVariable_Vitesse, (iso_u8 *)data);
	IsoVtcCmd_NumericValue(vtc_instance, aggress_hyd_21000, getAgressHyd());
	IsoVtcCmd_NumericValue(vtc_instance, sensor_left, getLastLeft());
	IsoVtcCmd_NumericValue(vtc_instance, sensor_right, getLastRight());
	IsoVtcCmd_NumericValue(vtc_instance, work_h, getWorkHeight());
	//ESP_LOGI("lemca", "updateVTC");
}

void VTC_handleNumericValues(const struct InputNumber_S * pInputNumberData) {
	// what number was entered
	hw_DebugPrint("VTC_handleNumericValues %d %d\n", pInputNumberData->objectIdOfInputNumber, pInputNumberData->newValue);
	switch (pInputNumberData->objectIdOfInputNumber) {
		case aggress_hyd_21000:
			setAgressHyd(pInputNumberData->newValue);
			break;
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
