//
// File:	OutersideDataFactory.h
// Package:	SAMRAI patch data
// Copyright:	(c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 173 $
// Modified:	$Date: 2005-01-19 09:09:04 -0800 (Wed, 19 Jan 2005) $
// Description: Factory class for creating outerside data objects
//

#ifndef included_pdat_OutersideDataFactory
#define included_pdat_OutersideDataFactory

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_BoxGeometry
#include "BoxGeometry.h"
#endif
#ifndef included_hier_IntVector
#include "IntVector.h"
#endif
#ifndef included_hier_PatchDataFactory
#include "PatchDataFactory.h"
#endif
#ifndef included_tbox_Arena
#include "tbox/Arena.h"
#endif
#ifndef included_tbox_Complex
#include "tbox/Complex.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif

#ifndef NULL
#define NULL (0)
#endif

namespace SAMRAI {
    namespace pdat {

/**
 * Class OutersideDataFactory is a factory class used to allocate new
 * instances of OutersideData objects.  It is a subclass of the patch
 * data factory class and outerside data is a subclass of patch data.  Both
 * the factory and data classes are templated on the type of the contained
 * object (e.g., double or int).
 *
 * @see pdat::OutersideData
 * @see pdat::PatchDataFactory
 */

template<int DIM, class TYPE>
class OutersideDataFactory : public hier::PatchDataFactory<DIM>
{
public:
   /**
    * The default constructor for the outerside data factory class.
    * The depth (number of components) gives the default for all of
    * the outerside data objects created with this factory.
    */
   OutersideDataFactory(const int depth);

   /**
    * Virtual destructor for the outerside data factory class.
    */
   virtual ~OutersideDataFactory<DIM,TYPE>();

   /**
    * Virtual function to clone the patch data factory .  This will return
    * a new instantiation of the factory with the same properties (e.g., same
    * type and depth).  The properties of the cloned factory can then be
    * changed without modifying the original.
    */
   virtual tbox::Pointer< hier::PatchDataFactory<DIM> > cloneFactory();

   /**
    * Virtual factory function to allocate a concrete outerside data object.
    * The default information about the object (e.g., depth) is taken from
    * the factory.  If no memory pool is provided, then the allocation routine
    * assumes some default memory pool.
    */
   virtual tbox::Pointer< hier::PatchData<DIM> > allocate(
      const hier::Box<DIM>& box,
      tbox::Pointer<tbox::Arena> pool = tbox::Pointer<tbox::Arena>(NULL)) const;

   /**
    * Allocate the box geometry object associated with the patch data.
    * This information will be used in the computation of intersections
    * and data dependencies between objects.
    */
   virtual tbox::Pointer< hier::BoxGeometry<DIM> >
   getBoxGeometry(const hier::Box<DIM>& box) const;

   /**
    * Get the default ghost cell width.  This is the ghost cell width that
    * will be used in the instantiation of concrete outerside data objects.
    * This is set to zero currently for outerside data objects.
    */
   virtual const hier::IntVector<DIM>& getDefaultGhostCellWidth() const;

   /**
    * Set the default ghost cell width.  This is the ghost cell width that
    * will be used in the instantiation of concrete outerside data instances.
    * This routine should not be called with a non-zero ghost cell width and
    * will cause an abort if the code is compiled with assertions enabled.
    */
   virtual void setDefaultGhostCellWidth(const hier::IntVector<DIM>& ghosts);

   /**
    * Get the default depth (number of components).  This is the default
    * depth that will be used in the instantiation of outerside data objects.
    */
   int getDefaultDepth() const;

   /**
    * Set the default depth (number of components).  This is the default
    * depth that will be used in the instantiation of outerside data objects.
    */
   void setDefaultDepth(const int depth);

   /**
    * Calculate the amount of memory needed to store the outerside data
    * object, including object data and dynamically allocated data.
    */
   virtual size_t getSizeOfMemory(const hier::Box<DIM>& box) const;

   /**
    * Return a boolean true value indicating that fine data for the outerside quantity will
    * take precedence on coarse-fine interfaces.  See the OutersideVariable<DIM> class
    * header file for more information.
    */
   bool fineBoundaryRepresentsVariable() const {return true;}

   /**
    * Return true since the outerside data index space extends beyond the interior of
    * patches.  That is, outerside data lives on patch borders.
    */
   bool dataLivesOnPatchBorder() const {return true;}

   /**
    * Return whether it is valid to copy this OutersideDataFactory to the 
    * supplied destination patch data factory.  It will return true if 
    * dst_pdf is SideDataFactory or OutersideDataFactory, false otherwise.
    */
   bool validCopyTo(
      const tbox::Pointer< hier::PatchDataFactory<DIM> >& dst_pdf) const;
  
private:
   int d_depth;

   hier::IntVector<DIM> *d_no_ghosts;
};

}
}
#ifndef DEBUG_NO_INLINE
#include "OutersideDataFactory.I"
#endif
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "OutersideDataFactory.C"
#endif
