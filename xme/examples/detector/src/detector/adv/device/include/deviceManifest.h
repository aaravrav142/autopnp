/*
 * Copyright (c) 2011-2014, fortiss GmbH.
 * Licensed under the Apache License, Version 2.0.
 *
 * Use, modification and distribution are subject to the terms specified
 * in the accompanying license file LICENSE.txt located at the root directory
 * of this software distribution. A copy is available at
 * http://chromosome.fortiss.org/.
 *
 * This file is part of CHROMOSOME.
 *
 * $Id: deviceManifest.h 6378 2014-01-17 15:31:03Z kainz $
 */

/**
 * \file
 *         Defines function for creation of component type manifest
 *         for 'device'
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */
 
#ifndef DETECTOR_ADV_DEVICE_MANIFEST_H
#define DETECTOR_ADV_DEVICE_MANIFEST_H

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "xme/core/manifestTypes.h"

#include "xme/hal/include/mem.h"
#include "xme/hal/include/safeString.h"

/******************************************************************************/
/***   Type definitions                                                     ***/
/******************************************************************************/
/**
 * \enum   Enhancement of xme_core_componentType_t
 *
 * \brief  Defines an additonal component manifest type that is available
 *         for XME.
 */
enum
{
    XME_CORE_COMPONENT_TYPE_DEVICE = 4098U ///< Component type value for device.
};

/******************************************************************************/
/***   Prototypes                                                           ***/
/******************************************************************************/

XME_EXTERN_C_BEGIN

/**
 * \brief  Create manifest for for component type 'device'.
 *         Component type id: 4098.
 *
 * \param  componentManifest Pointer to component type manifest structure that
 *         will be populated. Must not be NULL.
 *
 * \retval XME_STATUS_INVALID_PARAMETER when componentManifest is NULL.
 * \retval XME_STATUS_SUCCESS when componentManifest has been created
 *         successfully.
 */
xme_status_t
detector_adv_device_manifest_createComponentTypeManifest
(
    xme_core_componentManifest_t* componentManifest
);

XME_EXTERN_C_END

#endif // #ifndef DETECTOR_ADV_DEVICE_MANIFEST_H