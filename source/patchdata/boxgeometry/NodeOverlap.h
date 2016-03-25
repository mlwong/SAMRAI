//
// File:	NodeOverlap.h
// Package:	SAMRAI patch data geometry
// Copyright:	(c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 173 $
// Modified:	$Date: 2005-01-19 09:09:04 -0800 (Wed, 19 Jan 2005) $
// Description:	hier::Box intersection information for node centered objects
//

#ifndef included_pdat_NodeOverlap
#define included_pdat_NodeOverlap

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_BoxList
#include "BoxList.h"
#endif
#ifndef included_hier_BoxOverlap
#include "BoxOverlap.h"
#endif
#ifndef included_hier_IntVector
#include "IntVector.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif

namespace SAMRAI {
    namespace pdat {

/**
 * Class NodeOverlap<DIM> represents the intersection between two node 
 * centered geometry boxes.  It is a subclass of hier::BoxOverlap<DIM> and records
 * the portions of index space that needs to be copied between two objects
 * with node centered geometry.
 *
 * @see hier::BoxOverlap
 * @see pdat::NodeOverlap
 */

template<int DIM> class NodeOverlap : public hier::BoxOverlap<DIM>
{
public:
   /**
    * The constructor takes the list of boxes and the source offset between
    * the source and destination index spaces.  This information is used later
    * in the generation of communication schedules.
    */
   NodeOverlap(
      const hier::BoxList<DIM>& boxes, const hier::IntVector<DIM>& src_offset);

   /**
    * The virtual destructor does nothing interesting except deallocate
    * box data.
    */
   virtual ~NodeOverlap<DIM>();

   /**
    * Return whether there is an empty intersection between the two
    * node centered boxes.  This method over-rides the virtual function
    * in the hier::BoxOverlap<DIM> base class.
    */
   virtual bool isOverlapEmpty() const;

   /**
    * Return the list of boxes (in node centered index space) that constitute
    * the intersection.  The boxes are given in the destination coordinate
    * space and must be shifted by -(getSourceOffset()) to lie in the source
    * index space.
    */
   virtual const hier::BoxList<DIM>& getDestinationBoxList() const;

   /**
    * Return the offset between the destination and source index spaces.
    * The destination index space is the source index spaced shifted
    * by this amount.
    */
   virtual const hier::IntVector<DIM>& getSourceOffset() const;

private:
   bool d_is_overlap_empty;
   hier::IntVector<DIM> d_offset;
   hier::BoxList<DIM> d_dst_boxes;

};

}
}
#ifndef DEBUG_NO_INLINE
#include "NodeOverlap.I"
#endif
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "NodeOverlap.C"
#endif
