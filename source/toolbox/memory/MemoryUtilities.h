//
// File:	MemoryUtilities.h
// Package:	SAMRAI toolbox
// Copyright:	(c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 690 $
// Modified:	$Date: 2005-10-28 13:19:16 -0700 (Fri, 28 Oct 2005) $
// Description:	Routine for tracking memory use in applications.
//

#ifndef included_tbox_MemoryUtilities
#define included_tbox_MemoryUtilities

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif

#ifndef included_iostream
#include <iostream>
using namespace std;
#endif

namespace SAMRAI {
   namespace tbox {

/*!
 * @brief Class MemoryUtilities provides utility methods to access 
 * information about the memory characteristics of an application.  
 * Currently, there are only methods, one called "printMemoryInfo()" which 
 * does a simple dump of the current memory usage on a processor, and 
 * "recordMemoryInfo()" which records the memory for post-process analysis.  
 *
 * Calls to these methods may be placed at various points in an application
 * to track memory usage characteristics.  For applications running on a 
 * single processor, the  call the print method is likely sufficient. The 
 * information can simply be printed to a log file or output stream.  For 
 * applications running on multiple processors, or which otherwise have 
 * complex memory patterns that cannot easily be deciphered from prints to 
 * a log file, the record method may be more useful.  Use of this method 
 * requires the TAU (Tuning and Analysis Utilities) package to keep a 
 * profile of the recorded memory information so that it can be analyzed 
 * via a post-processing tool.
 *
 * Note that all member functions of this class are static so it is not
 * necessary to instantiate the class.  Simply call the functions as 
 * static functions; e.g.,MemoryUtilities::function(...). 
 */
struct MemoryUtilities
{
   /*!
    * Print memory information to the supplied output stream.
    */
   static void printMemoryInfo(ostream& os);
 
   /*!
    * Record memory info to be analyzed by TAU (Tuning and Analysis 
    * Utilities).  If tracing is enabled, you can supply a time at
    * which the memory is recorded.  This method requires SAMRAI to 
    * be configured with TAU.  If it is not, the method will do nothing.
    */
   static void recordMemoryInfo(double time = 0.0);

   /*!
    * Print maximum memory used (i.e. high-water mark) to the 
    * supplied output stream.
    */
   static void printMaxMemory(ostream& os);
   
private:

   /*
    * Keep track of maximum memory used (updated each time print or 
    * record function called).
    */
   static double s_max_memory;
};


}
}

#endif
