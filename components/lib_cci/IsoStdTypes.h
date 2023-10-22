/* ************************************************************************ */
/*! \file
    \brief      ISOBUS ECU driver standard types 
                ( based on C99 types with fallback to the C90 types )

    \author     Peter Wegscheider
    \date       Created 28.09.2015
    \copyright  Competence Center ISOBUS e.V.

    \par History:
    \par
    28.09.2015 - author P. Wegscheider
    - Typedef of the common c types
    \par
    13.02.2018 - author P. Wegscheider
    - BugID 7418: iso_u32 may evaluate into an unsigned 64 bit value \n
      Fix: use stdint.h without C99 compatibility checks as base for the driver types.
    \par
    21.12.2020 - author P. Wegscheider
    - BugID 13030: add <stdint.h> detection into "IsoStdTypes.h"
*/
/* ************************************************************************ */

/* ************************************************************************ */
#ifndef DEF_ISOSTDTYPES_H
#define DEF_ISOSTDTYPES_H
/* ************************************************************************ */

/* Check wether <stdint.h> is available on your system. */
#if !defined(ISO_OMIT_STDINT_CHECK)
#if defined(ISO_STDTYPES_CONFIG) || defined(ISO_STDTYPES_FILE) || defined(ISO_STDTYPES_DEFINES)

#if (defined(__cplusplus) && (__cplusplus >= 199711L)) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || defined(_MSC_VER)
#if (!defined(_MSC_VER)) || (_MSC_VER >= 1900)  /* fix for VS 2008 c++ has no stdint.h per default  */
#error The above defines shall not be used if <stdint.h> is available on your system.
#endif /* (!defined(_MSC_VER)) || (_MSC_VER >= 1900) */
#endif /* ( defined(__cplusplus) && (__cplusplus >= 199711L)) || ( defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || defined(_MSC_VER) */

#endif /* defined(ISO_STDTYPES_CONFIG) || defined(ISO_STDTYPES_FILE) || defined(ISO_STDTYPES_DEFINES) */
#endif /* !defined(ISO_OMIT_STDINT_CHECK) */

/* ************************************************************************ */
/*! \addtogroup grp_lib_std_types
    \details
    This file contains the library type definitions for the used C types. \n
    As default the driver uses the stdint.h types (C99) as base. \n
    If the used compiler doesn't provide stdint.h you can add the 
    define ISO_STDTYPES_FILE with your type file to the application IsoConf.h.
    Alternative you can add the define ISO_STDTYPES_CONFIG to your configuration 
    and define the C types in the IsoConf.h file. 
    In both cases make sure that you define all types with the correct bit length. \n
    It is also possible to activate the old C90 default implementation with the 
    define ISO_STDTYPES_DEFINES. \n
    With version 12 we have added an availability check for stdint.h.
    To disable this check and use your current definitions, you can add the Define 
    ISO_OMIT_STDINT_CHECK to the IsoConf.h file (not recommended).
@{
*/

/*!
    \name Integer type with a width of exactly 8, 16, or 32 bits.
    \brief For signed types, negative values are represented using 2's complement.
    @{
    \typedef iso_u8
    \brief  Unsigned 8 bit integer
    \typedef iso_s8
    \brief  Signed 8 bit integer
    \typedef iso_u16
    \brief Unsigned 16 bit integer
    \typedef iso_s16
    \brief  Signed 16 bit integer
    \typedef iso_u32
    \brief  Unsigned 32 bit integer
    \typedef iso_s32
    \brief  Signed 32 bit integer
    @}

    \name Float type with a width of exactly 32 bits.
    @{
    \typedef iso_f32
    \brief  IEEE float 32bit
    @}

    \name       Boolean type with a width of exactly 8 bits.
    \brief      Special implementation using an unsigned 8 bit integer
    \details    Only the values #ISO_TRUE and #ISO_FALSE are allowed for the #iso_bool type 
    @{
    \typedef iso_bool
    \brief  Boolean type
    \def ISO_FALSE
    \brief  #iso_bool false value
    \def ISO_TRUE
    \brief #iso_bool true value
    @}

    \name       Bit field type 
    @{
    \typedef iso_bitfield
    \brief      Bit field type based on an unsigned integer
    \details    A single field must be less or equal 16 bits to avoid compiler errors. \n
                Bit fields should be grouped in the underlying structure to save memory. 
                For single bit fields the values #ISO_TRUE and #ISO_FALSE should be used.
    @}

    \name Character type with a width of exactly 8 bit.
    @{
    \typedef iso_char
    \brief  8 bit char type used for stings
    @}

*/
/*! @} */   /* END grp_lib_std_types */
/* ************************************************************************ */
#ifndef ISO_STDTYPES_CONFIG /* ISO_STDTYPES_CONFIG and types not defined in IsoConf.h */

#ifdef ISO_STDTYPES_FILE 
    #include ISO_STDTYPES_FILE
#else   /* !ISO_STDTYPES_FILE */

#ifdef ISO_STDTYPES_DEFINES
   /* use C90 types - if stdint.h is not available */
   typedef unsigned char     iso_u8;
   typedef signed char       iso_s8;
   typedef unsigned short    iso_u16;
   typedef signed short      iso_s16;
   typedef unsigned long     iso_u32;
   typedef signed long       iso_s32;

#else /* !ISO_STDTYPES_DEFINES */
    /* default: use stdint.h (C99 types) as base */
    #include <stdint.h>

    typedef uint8_t    iso_u8;     
    typedef int8_t     iso_s8;     
    typedef uint16_t   iso_u16;    
    typedef int16_t    iso_s16;    
    typedef uint32_t   iso_u32;    
    typedef int32_t    iso_s32;    

#endif /* !ISO_STDTYPES_DEFINES  */

    typedef float       iso_f32;  /* IEEE float 32bit */
    /* not used: typedef double            iso_f64;   IEEE float 64bit */

    typedef iso_u8      iso_bool;
    #define ISO_FALSE   (0u)
    #define ISO_TRUE    (1u) 

    typedef unsigned int iso_bitfield; /*   */

    typedef char  iso_char;     /* used for strings and debugging output */  

#endif  /* !ISO_STDTYPES_FILE */
#endif  /* ISO_STDTYPES_CONFIG and types not defined in IsoConf.h */
/* ************************************************************************ */
#endif  /* DEF_ISOSTDTYPES_H */
/* ************************************************************************ */
