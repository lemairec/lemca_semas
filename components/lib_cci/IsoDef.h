/* ************************************************************************ */
/*!
   \file        IsoDef.h
   \brief       API for basic driver (old style) and VT, TC, SC client

   Global defines like PGNs, function fields, application functions, user enumerations

   \author      Hammerl Erwin
   \date        Created 27.11.2003

   \copyright   Competence Center ISOBUS e.V.

   \par HISTORY:

   \par
   21.01.2013 - author E. Hammerl
   - Version 6.00.05
   \par
   24.01.2013 - author E. Hammerl
   - Version 6.00.06
   \par
   08.03.2013 - author P. Wegscheider
   - Client API declarations moved to IsoClientsApi.h
   - PGN definitions moved to IsoPgnDef.h
   - Single CAN node API declarations moved to IsoSnApi.h
   - Version 6.02.00
   \par
   25.04.2013 - author E. Hammerl
   - Version 6.02.01
   \par
   13.05.2013 - author P. Wegscheider
   - IsoSnApi.h is only included if _LAY78_ is not defined
   - Version 6.02.02
   \par
   04.06.2013 - author P. Wegscheider
   - Version 6.03.00
   - SRL1 Lint code review updates
   - iso_NodeConfigSet() u16CanNr parameter type set to iso_u16
   - iso_NodeConfigGet() u16CanNr parameter type set to iso_u16
   - define CFG_PARAM_EXTERNAL_ADDRESS_CLAIM replaced with CFG_PARAM_EXTERNAL_ADDR_CLAIM
   - define CFG_PARAM_CHECK_ADDRESS_VIOLATION replaced with CFG_PARAM_CHECK_ADDR_VIOLATION
   - define CFG_PARAM_REQ_FOR_ACL_ON_STARTUP replaced with CFG_PARAM_REQ_FOR_ACL_ON_START
   \par
   04.07.2013 - author P. Wegscheider
   - Module version defines VERSION_GLOBAL and VERSION_BASE added
   - Pointer cast defines for HUGE_C added ( should not defined in IsoConf.h if using SRL1 )
   - defines ISO_MODULE_* added for conditional compilation of the configurable driver modules 
   - define _DEBUG replaced with define ISO_DEBUG_ENABLED
   - Debug function TextToBuffer() replaced with iso_DebugPuts()
   - Debug function iso_DebugPrint() added
   - Debug function DebVtStatesTrace() replaced with iso_DebugVtStatesTrace() 
   - Debug functions PrintTRACE() and PrintTRACE3() replaced with iso_DebugTrace() 
   \par
   18.11.2013 - author P. Wegscheider
   - Version 6.04.00
   \par
   23.04.2014 - author E. Hammerl
   - Version 6.04.01
   \par
   15.05.2014 - author P. Wegscheider
   - Function IsoDriverVersionRead() return value changed from iso_u16 to iso_u32
   - Version 7.00.01
   - iso_DebugVtStatesTrace() moved to IsoVt.c
   - Debug fuction iso_DebugSetCallbackFunction() and define ISO_DEBUG_USE_CALLBACK_FUNCTION check added
   \par
   22.07.2014 - author P. Wegscheider
   - Version 7.00.02
   \par
   08.09.2014 - author P. Wegscheider
   - Bugfixes for ISO_DEBUG_CALLBACK_t handling
   \par
   02.03.2015 - author P. Wegscheider
   - Moved definitions to IsoBaseDef.h and include "IsoBaseDef.h"
   - Moved functions to IsoBaseApi.h and include "IsoBaseApi.h"
   \par
   04.11.2016 - author P. Wegscheider
   - Feature request ID 4625: removed single node API
   \par
   07.02.2018 - author P. Wegscheider
   - Feature request ID 7504: Split Base Driver into "Core" and "Base"
      - IsoBaseDef.h renamed to IsoCommonDef.h
      - Added IsoCoreApi.h
   \par
   27.02.2018 - author P. Wegscheider
   - Feature request ID 7504: Split Base Driver into "Core" and "Base"
      - Added IsoCommonApi.h
*/
/* ************************************************************************ */

/* ************************************************************************ */
#ifndef DEF_ISO_DEF_H
#define DEF_ISO_DEF_H

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

#include "IsoCommonApi.h"
#include "IsoCoreApi.h"
#include "IsoBaseApi.h"


/* ******************** Multi Node Base API ******************************* */
#include "IsoMnApi.h"

/* ******************** NIU - Network interconnection Unit API ************ */
#ifdef ISO_MODULE_NIU
    #include "IsoMnNiuApi.h"
#endif

/* ******************** CLIENTS ******************************************* */
#ifdef  ISO_MODULE_CLIENTS
    #include "IsoClientsApi.h"

   /* check and include client module API files */

   #ifdef ISO_MODULE_VTC
      #include "IsoVtcApi.h"
   #endif

   #if defined(ISO_VT_SERVICE)
      #include "IsoVtsApi.h"
   #endif

   #ifdef ISO_MODULE_TCC 
      #include "IsoTccApi.h"
   #endif


   #ifdef ISO_MODULE_SQCC
      #include "IsoSccApi.h"
   #endif

   #ifdef ISO_MODULE_FSC
      #include "IsoFscApi.h"
   #endif

#endif


/* ************************************************************************ */
/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* DEF_ISO_DEF_H */
/* ************************************************************************ */
/* ************************************************************************ */

