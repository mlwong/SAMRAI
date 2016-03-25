/*
  File:        RelaunchableJob.h
  Package:     SAMRAI toolbox
  Copyright:   (c) 1997-2005 The Regents of the University of California
  Revision:    $Revision: 453 $
  Modified:    $Date: 2005-06-16 10:19:28 -0700 (Thu, 16 Jun 2005) $
  Description: Required user implementations for using JobRelauncher.
*/

#ifndef included_tbox_RelaunchableJob
#define included_tbox_RelaunchableJob

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif

namespace SAMRAI {
   namespace tbox {


class AsyncCommGroup;


/*!
  @brief Define interface for a relaunchable job managed by
  JobRelauncher.

  This is a strategy class for use with JobRelauncher.

  The implemented job should be written to be able to pause
  during a communication or non-communication wait.
*/
class RelaunchableJob
{

public:


   /*!
     @brief Default constructor.
   */
   RelaunchableJob(){};


   /*!
     @brief Destructor.

     Deallocate internal data.
   */
   virtual ~RelaunchableJob(void){};

   /*
     @brief Valid values for describing the state of a job.
   */
   enum JobState { COMMUNICATION_WAIT = 0,
                   NONCOMMUNICATION_WAIT = 1,
                   JOB_IS_COMPLETED = 2 };

   /*!
     Continue the user-defined job.
   */
   virtual void continueJob() = 0;


   /*!
     @brief Get the current state of the job, as a JobState enumeration.
   */
   virtual JobState getJobState() = 0;

   /*!
     @brief Get the communication group object that the job uses
     for communications.
   */
   virtual AsyncCommGroup *getCommunicationGroup() = 0;

};

}
}

#endif  // included_tbox_RelaunchableJob
