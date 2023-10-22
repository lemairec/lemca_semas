/* ************************************************************************ */
/*!
   \file
   \brief       ISOBUS ECU driver common API functions
   \details     This file is used instead of IsoDef.h to load the commonly used definitions 
                and defines.
                Do not use any of this file in the application.
   \author      Wegscheider Peter
   \date        Created 27.02.2018

   \copyright   Competence Center ISOBUS e.V.

   \par  History:
   \par
   27.02.2018 - author P. Wegscheider
   - Started to move API functions which can be used from all parts to this file. 
   \par
   14.06.2018 - author P.Wegscheider
   - Feature request ID 8424: use ISO_CF_NAME_T in API functions
   \par
   25.03.2019 - author P.Wegscheider
   - Feature request ID 10348: added function iso_NmCompareCfNames()
   \par
   08.04.2020 - author P.Wegscheider
   - Added more network management helper functions 
     ( iso_NmGetFunctionOfName(), iso_NmGetCanIdxFromCfHandle(), ...)

*/
/* ************************************************************************ */

#ifndef DEF_ISOCOMMONAPI_H
#define DEF_ISOCOMMONAPI_H

/* Standard C types are now included with IsoCommonDef.h */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/****************************************************************************/
/*! \defgroup common_general Common 
    \ingroup commonapi 
   @{ */

/* ************************************************************************ */
/*!
   \brief   Reading the actual ISO driver version
   \retval  iso_u32
            Version number of ISO driver ( e.g. 100101 means 10.01.01 )
*/
CCI_COMMON_API
iso_u32  IsoDriverVersionRead( void );

/*! @} */ 

/* ************************************************************************ */
/*! \defgroup grp_nm_common Network Management Helper Functions
    \ingroup nmma base_nmma commonapi
@{ */

/* ************************************************************************ */
/*!
    \brief      Setting the NAME of an ISO user ( see ISO 11783 - 5 - 5.1.2 )

     This function builds the NAME of an network member out of the single NAME fields.

    \param[in]     \wp{bSelfConf, iso_u8}  
                    Self-configurable address: ECU is self-configurable (ISO_TRUE) or not (ISO_FALSE)
    \param[in]     \wp{u8IndGroup, iso_u8} 
                    Industry group ( ISO PART1 - Annex B ) \n
                    Range: 0 - 7
    \param[in]     \wp{u8DevClass, iso_u8} 
                    Device class e. g. Tractor, Tillage .. ( ISO PART1 - Annex E ) \n
                    Range: 0 - 127
    \param[in]     \wp{u8DevClassInst, iso_u8}
                    Device class instance \n
                    ( e. g. identical implements of same device ) \n
                    Range: 0 - 15   
    \param[in]     \wp{u8Function, iso_u8}
                    Function of implement  \n
                    0 - 127 independent of other fields, > 127 and < 254 depends on device class,
                    when combined with industry group and device class, can be correlated to a common 
                    NAME for specific hardware ( ISO PART1 - Annex E )
    \param[in]     \wp{u16ManufCode, iso_u16}
                    Manufacturer code \n
                    Indicates manufacturer of ECU for which the NAME is being referenced ( ISO PART1 - Annex G ) \n
                    Range: 0 - 2047
    \param[in]     \wp{u32SeriNo, iso_u32}
                    Identity number (also serial number) \n 
                    Assigned by the ECU manufacturer, necessary where the NAME is not unique \n
                    Range: 0 - 2097152
    \param[in]     \wp{u8FunctionInst, iso_u8}
                    Function instance \n 
                    Indicates specific occurrence of a function on a particular device system of a network \n
                    Range: 0 - 31
    \param[in]     \wp{u8EcuInstance, iso_u8}
                    ECU instance \n
                    Indicates which of a group of ECUs associated with a given function is referenced \n
                    Range: 0 - 7
    \param[out]    \wp{au8IsoName, ISO_CF_NAME_T*}
                    Pointer to array ( Name[8] ) !!
   
    \note  \par  
                   - LSB begins with the identity number, MSB Bit 8 is the selfconfigurable bit  
                   - Array of bytes for the name is module global  
                   - Range is not controlled
 */
CCI_COMMON_API
void  iso_NmSetName( iso_bool bSelfConf, iso_u8 u8IndGroup, iso_u8 u8DevClass, iso_u8 u8DevClassInst, iso_u8 u8Function,
                     iso_u16 u16ManufCode, iso_u32 u32SeriNo, iso_u8 u8FunctionInst, iso_u8 u8EcuInstance, ISO_CF_NAME_T* au8IsoName );

/* ************************************************************************ */
/*!
   \brief      Fills the NAME field structure out of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \param[out] \wp{psNameField, ISONAMEFIELD_T*}
               Pointer to the NAME field structure which should be filled
*/
CCI_COMMON_API
void iso_NmSetNameField(const ISO_CF_NAME_T* au8IsoName, ISONAMEFIELD_T* psNameField);

/* ************************************************************************** */
/*!
   \brief  Compares two names ignoring the self-configurable address bit, 
           if identical the function returns ISO_TRUE

   \param[in]  \wpp{pau8Name1, const #ISO_CF_NAME_T*}
               Pointer to CF NAME 1 byte array

   \param[in]  \wpp{pau8Name2, const #ISO_CF_NAME_T*}
               Pointer to CF NAME 2 byte array
   \param[out] \wp{pqScDiff, iso_bool*}
               Pointer to return #ISO_TRUE if the names differ in the self-configurable address bit.

   \retval     iso_bool
               Result, if NAMES identical then ISO_TRUE

*/
CCI_COMMON_API
iso_bool iso_NmCompareCfNames(const ISO_CF_NAME_T* pau8Name1, const ISO_CF_NAME_T* pau8Name2, iso_bool* pqScDiff);


/* ************************************************************************ */
/*!
   \brief      returns the self-configurable bit of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_bool
               ISO_TURE if self-configurable
*/
CCI_COMMON_API
iso_bool iso_NmGetSelfConfigurableOfName(const ISO_CF_NAME_T* au8IsoName);

/* ************************************************************************ */
/*!
   \brief      returns the industry group of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_u8
               Industry group of the name
*/
CCI_COMMON_API
iso_u8 iso_NmGetIndustryGroupOfName(const ISO_CF_NAME_T* au8IsoName);

/* ************************************************************************ */
/*!
   \brief      returns the device class of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_u8
               Device class of the name
*/
CCI_COMMON_API
iso_u8 iso_NmGetDeviceClassOfName(const ISO_CF_NAME_T* au8IsoName);

/* ************************************************************************ */
/*!
   \brief      returns the device class instance of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_u8
               Device class instance of the name
*/
CCI_COMMON_API
iso_u8 iso_NmGetDeviceClassInstanceOfName(const ISO_CF_NAME_T* au8IsoName);

/* ************************************************************************ */
/*!
   \brief      returns the function of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_u8
               Function of the name
*/
CCI_COMMON_API
iso_u8 iso_NmGetFunctionOfName(const ISO_CF_NAME_T* au8IsoName);


/* ************************************************************************ */
/*!
   \brief      returns the function instance of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_u8
               Function instance of the name
*/
CCI_COMMON_API
iso_u8 iso_NmGetFunctionInstanceOfName(const ISO_CF_NAME_T* au8IsoName);

/* ************************************************************************ */
/*!
   \brief      returns the manufacturer code of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_u16
               Manufacturer code of the name
*/
CCI_COMMON_API
iso_u16 iso_NmGetManufacturerOfName(const ISO_CF_NAME_T* au8IsoName);

/* ************************************************************************ */
/*!
   \brief      returns the ECU instance of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_u8
               ECU instance of the name
*/
CCI_COMMON_API
iso_u8 iso_NmGetEcuInstanceOfName(const ISO_CF_NAME_T* au8IsoName);

/* ************************************************************************ */
/*!
   \brief      returns the identity number of an ISO NAME ( see ISO 11783 - 5 - 5.1.2 )
   \param[in]  \wpp{au8IsoName, const #ISO_CF_NAME_T*}
               Pointer to the ISO NAME byte array ( 8 bytes ) 
   \retval     iso_u8
               Identity number of the name
*/
CCI_COMMON_API
iso_u32 iso_NmGetIdentityNumberOfName(const ISO_CF_NAME_T* au8IsoName);

/* ************************************************************************** */
/*!
    \brief      Extracts the CAN bus node index from the CF member handle

    \param[in]  \wp{s16CfHandle, iso_s16}
                 CF / user handle

    \retval     iso_u8
                CAN node index (only valid if the handle was valid)
*/
CCI_COMMON_API
iso_u8 iso_NmGetCanIdxFromCfHandle(iso_s16 s16CfHandle);

/*! @} */

/* ************************************************************************ */
/*! \addtogroup commonapi
@{
*/
/* ************************************************************************ */

/* ************************************************************************ */
/*! @} */  /* end commonapi */
/* ************************************************************************ */

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_ISOCOMMONAPI_H */
/* ************************************************************************ */
