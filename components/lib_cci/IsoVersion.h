/* ************************************************************************* */
/*!
   \file
   \brief   CCI ISOBUS driver version

   \author     Wegscheider Peter
   \date       Created 22.12.2020
   \copyright  Competence Center ISOBUS e.V.

   \par  History :
   \par
   22.12.2020 - author P.Wegscheider
   - Feature BugID 12372: move version information from IsoCommonDef.h into new file IsoVersion.h
*/
/* ************************************************************************* */
#ifndef DEF_ISOVERSION_H
#define DEF_ISOVERSION_H

/* ************************************************************************* */
/*! \ingroup grp_versions
   \brief CCI ISOBUS Driver Version
   \details Version is returned from API function IsoDriverVersionRead()
*/
#define DRIVER_VERSION      120000uL

/*! \ingroup grp_versions
   \brief CCI ISOBUS Driver Maturity
   \details This define is used to mark in progress versions. \n
   - final, srl1 or empty string if finished
   - rc01, rc02, rc[x] for a release candidate
   - ( or pr01, pr02, pr[x] for a release candidate )
   - br01, br02, br[x] for a preview version
   - b001, b[svn ref], beta for a beta version
*/
#define DRIVER_MATURITY      ""

/*!
   \brief SVN revision information to be able to clearly identify the source code.
   Hint: This file needs to be touched with each commit. e.g. by changing the property revision of the file to a different value, preferable the next SVN revision number.
*/
#define DRIVER_SVN_REVISION  "$Rev: 834 $"

/* ************************************************************************* */
/*! \ingroup grp_versions
   \brief Global / Packet Version
*/
#define VERSION_GLOBAL 12.00

/* ************************************************************************* */
/*! \ingroup grp_versions
   \brief Core Driver Module Version
*/
#define VERSION_CORE 2.02     /* changed for v12.00 */

/* ************************************************************************* */
/*! \ingroup grp_versions
   \brief Base Driver Module Version
*/
#define VERSION_BASE 2.02     /* changed for v12.00 */

/* ************************************************************************* */
/*! \ingroup grp_versions
    \brief Client Shared Module Version
*/
#define VERSION_CSHARED 2.00   /* changed for v12.00 */

/*! \ingroup grp_versions
    \brief Virtual Terminal Client Module Version
*/
#define VERSION_VTC 6.00    /* changed for v12.00 */

/*! \ingroup grp_versions
    \brief Task Controller Client Client Module Version
*/
#define VERSION_TCC  4.10     /* changed for v12.00 */

/*! \ingroup grp_versions
    \brief File Server Client Module Version
*/
#define VERSION_FSC 3.6    /* changed for v11.00 */

/*! \ingroup grp_versions
    \brief Sequence Control Client Module Version
*/
#define VERSION_SCC 1.7    /* changed for v12.00 */

/*! \ingroup grp_versions
    \brief Virtual Terminal Service Module Version
*/
#define VERSION_VTSERVICE 1.02    /* changed for v12.00 */

/*! \ingroup grp_versions
    \brief Network Interconnection Unit Module Version
*/
#define VERSION_NIU 1.3       /* changed for v11.00 */

/* ************************************************************************* */
#endif /* DEF_ISOVERSION_H */
/* ************************************************************************* */
