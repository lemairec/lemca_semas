/* ************************************************************************ */
/*!
   \file                       
   \brief       ECU driver helper functions
   \details     This file contains only driver internal declarations.
                Do not use any of this functions in the application.
   \author      Wegscheider Peter
   \date        Created 02.07.2013

   \copyright   Competence Center ISOBUS e.V.

   \par         History:
   \par
   02.07.2013 - author P. Wegscheider
   - HUGE_C and normal array helper functions added    
   \par
   05.12.2013 - author P. Wegscheider
   - iso_GetU16BitFromByteArrHuge() function added 
   \par
   16.04.2015 - author P. Wegscheider
   - iso_ByteCmp() function added
   \par
   20.12.2016 - author P. Wegscheider
   - iso_CharCpy() function added
   \par
   26.02.2018 - author P. Wegscheider
   - Added common used CF NAME functions:
   - iso_CfNameCompare()
   - iso_CfGetFunctionInstOfName()
   - iso_CfGetManuCodeOfName()
   - iso_CfSetCfName()
   \par
   08.03.2018 - author P. Wegscheider
   - Added function iso_TimeIsExpired()
   \par
   19.02.2020 - author P. Wegscheider
   - Added function iso_CfSetCfNameField()
*/
/* ************************************************************************ */

#ifndef DEF_ISOUTIL_H
    #define DEF_ISOUTIL_H

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* ************************************************************************ */
/*! \addtogroup common_drv_protected  
    @{ 
*/
/* ************************************************************************ */

/* Version 06.03.xx */
/* Byte array copy functions */
/** \name Byte array helper functions 
   @{ */
CCI_COMMON_API
void  iso_ByteCpyToHuge   ( iso_u8 HUGE_C pau8Dest[], const iso_u8 pau8Src[],        iso_u16 u16Num );
CCI_COMMON_API
void  iso_ByteCpyHuge     ( iso_u8 HUGE_C pau8Dest[], const iso_u8 HUGE_C pau8Src[], iso_u16 u16Num );
CCI_COMMON_API
void  iso_ByteCpyFromHuge ( iso_u8 pau8Dest[],        const iso_u8 HUGE_C pau8Src[], iso_u16 u16Num );
CCI_COMMON_API
void  iso_ByteCpy         ( iso_u8 pau8Dest[],        const iso_u8 pau8Src[],        iso_u16 u16Num );

CCI_COMMON_API
iso_u8 HUGE_C *       iso_BytePtrHuge( iso_u8 HUGE_C pau8Array[], iso_u32 u32Index );
CCI_COMMON_API
iso_u8 *              iso_BytePtr    ( iso_u8 pau8Array[],        iso_u16 u16Index );
CCI_COMMON_API
const iso_u8 HUGE_C * iso_BytePtrCstHuge( const iso_u8 HUGE_C pau8Array[], iso_u32 u32Index );

CCI_COMMON_API
iso_u32               iso_GetU24BitFromByteArrHuge( const iso_u8 HUGE_C pau8Array[], iso_u32 u32Index );
CCI_COMMON_API
iso_u16               iso_GetU16BitFromByteArrHuge( const iso_u8 HUGE_C pau8Array[], iso_u32 u32Index );
CCI_COMMON_API
iso_u8                iso_GetU8BitFromByteArrHuge ( const iso_u8 HUGE_C pau8Array[], iso_u32 u32Index );

CCI_COMMON_API
iso_s16               iso_ByteCmp(const iso_u8 pau8Array1[], const iso_u8 pau8Array2[], iso_u16 u16Num);
CCI_COMMON_API
iso_u16               iso_ByteArrayLen(const iso_u8 abStr[], const iso_u16 u16StrLenMax);
CCI_COMMON_API
iso_u16               iso_StrLen( const iso_char acStr[], const iso_u16 u16StrLenMax );
CCI_COMMON_API
void                  iso_CharCpy( iso_char paDest[], const iso_char paSrc[], iso_u16 u16Num );
/* @} */

/** \name CF helper functions
   @{ */
CCI_COMMON_API
void     iso_CfSetCfName( iso_bool bSelfConf, iso_u8 u8IndGroup, iso_u8 u8DevClass, iso_u8 u8DevClassInst,
                          iso_u8 u8Function, iso_u16 u16ManufCode, iso_u32 u32SeriNo,
                          iso_u8 u8FunctionInst, iso_u8 u8EcuInstance, iso_u8 au8IsoName[] );

CCI_COMMON_API
void     iso_CfSetCfNameField(const iso_u8 au8IsoName[], ISONAMEFIELD_T* psNameField);


CCI_COMMON_API
iso_bool iso_CfNameCompare( const iso_u8 pau8CfName1[], const iso_u8 pau8CfName2[] );
CCI_COMMON_API
iso_u8   iso_CfGetFunctionInstOfName( const iso_u8 au8Name[] );
CCI_COMMON_API
iso_u16  iso_CfGetManuCodeOfName( const iso_u8 au8CfName[] );
CCI_COMMON_API
iso_u8 iso_CfGetCanIdxFromCfHandle(iso_s16 s16CfHandle);

/* @} */

/** \name CF helper functions
   @{ */
CCI_COMMON_API
iso_bool iso_TimeIsExpired(iso_s32 s32ActTime, iso_s32 s32StartTime, iso_s32 s32TimeOut);
CCI_COMMON_API
iso_bool iso_TimeIsEqualOrExpired(iso_s32 s32ActTime, iso_s32 s32StartTime, iso_s32 s32TimeOut);
/* @} */

/* ************************************************************************ */
/*! @} */  /* end common_drv_protected */
/* ************************************************************************ */

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_ISOUTIL_H */
/* ************************************************************************ */
