//
// File:	SAMRAIManager.h
// Package:     SAMRAI initialization and shutdown
// Copyright:	(c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 406 $
// Modified:	$Date: 2005-06-01 09:48:43 -0700 (Wed, 01 Jun 2005) $
// Description: SAMRAI class to manage package startup and shutdown
//

#ifndef included_tbox_SAMRAIManager
#define included_tbox_SAMRAIManager

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_tbox_Database
#include "tbox/Database.h"
#endif


namespace SAMRAI {
   namespace tbox {


/*!
 * @brief Class SAMRAIManager is a utility for managing startup and shutdown 
 * for SAMRAI applications and for changing the maximum number of patch data 
 * components supported by SAMRAI patches.  All applications should call 
 * SAMRAIManager::startup() (or SAMRAIManager::startup()) at the 
 * beginning of the program.  Startup should be called after initializing 
 * MPI but before any SAMRAI objects are used.  SAMRAIManager::shutdown()
 * (or SAMRAIManager:shutdown()) should be called near the end of the program, 
 * but before shutting down MPI and calling exit(0).  Note that the shutdown
 * function does not exit the program; it merely shuts down certain packages 
 * and deallocates memory (mostly objects with static members).
 */

struct SAMRAIManager
{
   /*!
    * Initialize the SAMRAI package.  Depending on the architecture and
    * compile flags, this routine sets up MPI, initializes IEEE exception
    * handlers, and other architecture-specific details.
    */
   static void startup();

   /*!
    * Shutdown the SAMRAI package.  Depending on the compile flags set at
    * compile-time, this routine shuts down MPI and calls registered shutdown
    * handlers.
    */
   static void shutdown();

   /*!
    * Return maximum number of patch data entries supported by SAMRAI patches.
    * The value is either the default value (256) or the value set by calling
    * the setMaxNumberPatchDataEntries() function.
    */
   static int getMaxNumberPatchDataEntries();

   /*!
    * Set maximum number of patch data entries supported by SAMRAI patches.
    * Note that this routine cannot be called more than once and it cannot be
    * called anytime after the max patch data entries value has been accessed
    * either by the user or internally within SAMRAI.  Typically, the first
    * access of this value occurs whenever any objects related to the patch 
    * hierarchy or variables are created.  If the argument value is < 0, the 
    * default value is used.
    */
   static void setMaxNumberPatchDataEntries(int maxnum);

private:
   static int s_max_patch_data_entries;
   static bool s_max_patch_data_entries_accessed;
   static bool s_max_patch_data_entries_set_by_user;
};

}
}

#endif
