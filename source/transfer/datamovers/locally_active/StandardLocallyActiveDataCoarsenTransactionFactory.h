//
// File:	StandardLocallyActiveDataCoarsenTransactionFactory.h
// Package:	SAMRAI transfer
// Copyright:	(c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 684 $
// Modified:	$Date: 2005-10-21 14:59:38 -0700 (Fri, 21 Oct 2005) $
// Description:	Concrete factory for create standard copy transactions 
//              for locally-active data coarsen schedules. 
//

#ifndef included_xfer_StandardLocallyActiveDataCoarsenTransactionFactory
#define included_xfer_StandardLocallyActiveDataCoarsenTransactionFactory

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_BoxOverlap
#include "BoxOverlap.h"
#endif
#ifndef included_hier_PatchLevel
#include "PatchLevel.h"
#endif
#ifndef included_tbox_Arena
#include "tbox/Arena.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif
#ifndef included_tbox_Transaction
#include "tbox/Transaction.h"
#endif
#ifndef included_xfer_CoarsenClasses
#include "CoarsenClasses.h"
#endif
#ifndef included_xfer_LocallyActiveDataCoarsenTransactionFactory
#include "LocallyActiveDataCoarsenTransactionFactory.h"
#endif


namespace SAMRAI {
    namespace xfer {

/*!
 * @brief Concrete subclass of LocallyActiveDataCoarsenTransactionFactory<DIM> base 
 * class that allocates CoarsenCopyTransaction<DIM> objects for a 
 * LocallyActiveDataCoarsenSchedule<DIM> object.
 * 
 * @see xfer::CoarsenCopyTransaction
 * @see xfer::LocallyActiveDataCoarsenTransactionFactory
 */

template<int DIM> 
class StandardLocallyActiveDataCoarsenTransactionFactory : 
   public LocallyActiveDataCoarsenTransactionFactory<DIM>
{
public:
   /*!
    * @brief Default constructor.
    */
   StandardLocallyActiveDataCoarsenTransactionFactory();

   /*!
    * @brief Virtual destructor.
    */
   virtual ~StandardLocallyActiveDataCoarsenTransactionFactory<DIM>();

   /*!
    * @brief Set the array of CoarsenClass::Data items used by the transactions.
    */
   void setCoarsenItems(const typename CoarsenClasses<DIM>::Data** coarsen_items,
                        int num_coarsen_items);

   /*!
    * @brief Clear the array of CoarsenClass::Data items used by the transactions.
    */
   void unsetCoarsenItems();

   /*!
    * @brief Allocate a CoarsenCopyTransaction<DIM> object.
    *
    * @param dst_level      tbox::Pointer to destination patch level.
    * @param src_level      tbox::Pointer to source patch level.
    * @param overlap        tbox::Pointer to overlap region between patches.
    * @param dst_patch      Integer index of destination patch in destination
    *                       patch level.
    * @param src_patch      Integer index of source patch in source patch level.
    * @param citem_id       Integer index of CoarsenClass::Data item associated
    *                       with transaction.
    * @param pool           Optional pointer to memory pool from which the
    *                       coarsen transaction may be allocated. Default is null.
    */
   tbox::Pointer<tbox::Transaction>
   allocate(tbox::Pointer< hier::PatchLevel<DIM> > dst_level,
            tbox::Pointer< hier::PatchLevel<DIM> > src_level,
            tbox::Pointer< hier::BoxOverlap<DIM> > overlap,
            int dst_patch_id,
            int src_patch_id,
            int citem_id,
            tbox::Pointer<tbox::Arena> pool = (tbox::Arena *) NULL) const;

private:
   // The following two functions are not implemented
   StandardLocallyActiveDataCoarsenTransactionFactory(
      const StandardLocallyActiveDataCoarsenTransactionFactory<DIM>&);
   void operator=(const StandardLocallyActiveDataCoarsenTransactionFactory<DIM>&);

   const typename xfer::CoarsenClasses<DIM>::Data** d_coarsen_items;
   int d_num_coarsen_items;

};

}
}
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "StandardCoarsenTransactionFactory.C"
#endif
